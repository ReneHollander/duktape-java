package org.duktape.duktapejava.generator;

import com.sun.codemodel.*;
import org.apache.commons.io.IOUtils;
import org.bytedeco.javacpp.IntPointer;
import org.bytedeco.javacpp.Pointer;
import org.bytedeco.javacpp.annotation.Cast;
import org.bytedeco.javacpp.annotation.Name;
import org.bytedeco.javacpp.annotation.Namespace;
import org.bytedeco.javacpp.annotation.Platform;
import org.gradle.api.DefaultTask;
import org.gradle.api.tasks.TaskAction;

import java.io.File;
import java.io.IOException;
import java.util.List;

public class Generator extends DefaultTask {

    public File apiDirectory = new File(".");
    public File headerFile = new File("constants.h");
    public File outputDirectory = new File(".");

    private static final int PUBLIC_STATIC_ABSTRACT_CLASS_MODS = JMod.PUBLIC | JMod.STATIC | JMod.ABSTRACT;
    private static final int PRIVATE_NATIVE_METHOD = JMod.PRIVATE | JMod.NATIVE;
    private static final int PUBLIC_ABSTRACT_METHOD = JMod.PUBLIC | JMod.ABSTRACT;
    private static final int PUBLIC_STATIC_NATIVE_METHOD = JMod.PUBLIC | JMod.STATIC | JMod.NATIVE;
    private static final int PUBLIC_STATIC_FINAL_FIELD = JMod.PUBLIC | JMod.STATIC | JMod.FINAL;

    private JCodeModel cm;

    private JDefinedClass duk_context;
    private JDefinedClass duktape;
    private JClass function;
    private JClass fatalfunction;
    private JClass functionListEntryArray;

    private final JType POINTER;
    private final JType STRING;

    public Generator() {
        cm = new JCodeModel();
        POINTER = cm._ref(Pointer.class);
        STRING = cm._ref(String.class);

        function = cm.directClass("org.duktape.duktapejava.Duktape.Function");
        fatalfunction = cm.directClass("org.duktape.duktapejava.Duktape.FatalHandler");
        functionListEntryArray = cm.directClass("org.duktape.duktapejava.Duktape.FunctionListEntryArray");
    }

    public boolean shouldCast(String type) {
        return !(type.equals("const char *") || type.equals("duk_context *"));
    }

    public JType getType(String type) {
        switch (type) {
            case "duk_context *":
                return duk_context;
            case "void":
                return cm.VOID;
            case "duk_bool_t":
                return cm.BOOLEAN;
            case "duk_int_t":
            case "duk_idx_t":
            case "duk_int32_t":
            case "duk_ret_t":
            case "duk_codepoint_t":
            case "duk_size_t":
            case "duk_errcode_t":
            case "duk_uint16_t":
                return cm.INT;
            case "duk_uint32_t":
            case "duk_uint_t":
            case "duk_uarridx_t":
            case "duk_int64_t":
                return cm.LONG;
            case "duk_double_t":
                return cm.DOUBLE;
            case "void *":
                return POINTER;
            case "const char *":
                return STRING;
            case "duk_c_function":
            case "duk_safe_call_function":
                return function;
            case "const duk_function_list_entry *":
                return functionListEntryArray;
            case "duk_size_t *":
                return cm._ref(IntPointer.class);
            case "duk_fatal_function":
                return fatalfunction;
            default:
                throw new IllegalArgumentException("Unknown type: " + type);
        }
    }

    private void addLibraryLoader(JDefinedClass cls) {
        cls.direct("static { org.duktape.duktapejava.LibraryLoader.load(); }");
    }

    public JMethod methodFromPrototype(JDefinedClass cls, Prototype prototype) {
        JMethod m = null;
        try {
            m = cls.method(PUBLIC_STATIC_NATIVE_METHOD, getType(prototype.type), prototype.name);
            for (Prototype.Argument arg : prototype.arguments) {
                JVar param = m.param(getType(arg.type), arg.name);
                if (shouldCast(arg.type)) {
                    JAnnotationUse annotationUse = param.annotate(Cast.class);
                    annotationUse.param("value", arg.type);
                }
            }
            return m;
        } catch (Exception e) {
            cls.methods().remove(m);
            throw new RuntimeException(e);
        }

    }

    @TaskAction
    public void generate() throws JClassAlreadyExistsException, IOException {
        List<DuktapeFunction> functions = APIParser.parseDirectory(apiDirectory);
        List<Define> defines = DefineParser.parse(headerFile);

        duk_context = cm._class("org.duktape.duktapejava.duk_context");
        duk_context._extends(Pointer.class);
        duk_context.annotate(Namespace.class).param("value", "");
        duk_context.annotate(Name.class).param("value", "duk_context");
        addLibraryLoader(duk_context);

        duktape = cm._class("org.duktape.duktapejava.Duktape");
        addLibraryLoader(duktape);
        duktape.direct(getResourceAsString("/default_code.txt"));

        for (Define define : defines) {
            Class<?> type = int.class;
            if (define.value.endsWith("L")) type = long.class;
            if (define.value.startsWith("\"") && define.value.endsWith("\"")) type = String.class;
            define.value = define.value.replace("DUK_IDX_MIN", "Integer.MIN_VALUE");
            JFieldVar field = duktape.field(PUBLIC_STATIC_FINAL_FIELD, type, define.name, JExpr.direct(define.value));
            if (define.comment != null && !define.comment.isEmpty()) {
                field.javadoc().add(define.comment);
            }
        }

        duktape.annotate(Platform.class).paramArray("cinclude").param("duktape.c").param("duktape-java.c");
        {
            methodFromPrototype(duktape, APIParser.parsePrototype("duk_context *duk_create_context();"));
            methodFromPrototype(duktape, APIParser.parsePrototype("duk_context *duk_create_context_with_fatal_handler(duk_fatal_function fatal_handler);"));
            methodFromPrototype(duktape, APIParser.parsePrototype("duk_int64_t duk_get_memory_usage(duk_context *ctx);"));
        }
        int allcount = functions.size();
        int count = 0;
        for (DuktapeFunction fn : functions) {
            switch (fn.name) {
                case "duk_push_c_function":
                    allcount--;
                    JMethod m1 = duktape.method(PUBLIC_STATIC_NATIVE_METHOD, getType(fn.prototype.type), "duk_push_java_function");
                    m1.annotate(Name.class).param("value", "duk_push_c_function");
                    m1.param(duk_context, "ctx");
                    m1.param(function, "func");
                    m1.param(getType("duk_idx_t"), "nargs").annotate(Cast.class).param("value", "duk_idx_t");

                    JMethod m2 = duktape.method(JMod.PUBLIC | JMod.STATIC, getType(fn.prototype.type), "duk_push_java_function");
                    JVar ctx = m2.param(duk_context, "ctx");
                    JVar func = m2.param(cm.directClass("org.duktape.duktapejava.FunctionInterface"), "func");
                    JVar nargs = m2.param(getType("duk_idx_t"), "nargs");
                    nargs.annotate(Cast.class).param("value", "duk_idx_t");
                    m2.body()._return(JExpr.invoke(m1).arg(ctx).arg(func.invoke("asFunction")).arg(nargs));
                    break;
                case "duk_create_heap":
                case "duk_create_heap_default":
                    allcount--;
                    break;
                default:
                    try {
                        JMethod m = methodFromPrototype(duktape, fn.prototype);
                        m.javadoc().append(fn.summary);
                        if (fn.stack != null && !fn.stack.isEmpty()) {
                            m.javadoc().append(System.lineSeparator() + System.lineSeparator() + "<p>Stack:" + System.lineSeparator() + "<code>" + javadocEscapeAngleBrackets(fn.stack) + "</code></p>");
                        }
                        if (fn.example != null && !fn.example.isEmpty())
                            m.javadoc().append(System.lineSeparator() + System.lineSeparator() + "Example:<pre><code>" + System.lineSeparator() + javadocEscapeAnd(javadocEscapeAngleBrackets(fn.example)) + "</code></pre>");
                        for (JVar param : m.params()) {
                            JCommentPart part = m.javadoc().addParam(param);
                            part.add(param.name());
                        }
                        if (m.type() != cm.VOID) m.javadoc().addReturn().add(m.type().name());
                        m.javadoc().append(System.lineSeparator() + System.lineSeparator() + "@since " + fn.introduced);
                        count++;
                    } catch (Exception e) {
                        System.err.println("Error creating method stub for " + fn.name + ": " + e.getMessage());
//                        System.err.println(" - `" + fn.name + "`");
                    }
                    break;
            }
        }
        System.out.println("Successfully generated bindings for " + count + " out of " + allcount + " functions. Thats " +
                (count / (double) allcount) * 100 + "% coverage");
        outputDirectory.mkdirs();
        cm.build(outputDirectory);
    }

    private String javadocEscapeAngleBrackets(String stack) {
        stack = stack.replace("<", "&lt;");
        stack = stack.replace(">", "&gt;");
        return stack;
    }

    private String javadocEscapeAnd(String stack) {
        stack = stack.replace("&", "{@literal &}");
        return stack;
    }

    private String getResourceAsString(String name) throws IOException {
        return IOUtils.toString(this.getClass().getResourceAsStream(name), "UTF-8");
    }

}
