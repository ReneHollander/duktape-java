package org.duktape.duktapejava.generator;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class DefineParser {

    public static Define process(String str, List<String> comments) {
        Define define = new Define();
        str = str.substring(str.indexOf(' '), str.length()).trim();
        define.name = str.substring(0, str.indexOf(' '));
        str = str.substring(str.indexOf(' '), str.length()).trim();
        int end = str.indexOf("/*");
        if (end == -1) end = str.length();
        define.value = str.substring(0, end).trim();
        define.value = define.value.replace("(duk_int_t)", "");
        define.value = define.value.replace("(", "");
        define.value = define.value.replace(")", "");
        define.comment = comments.stream().collect(Collectors.joining("\n\n"));
        if (str.contains("/*") && str.contains("*/")) {
            if (define.comment == null) {
                define.comment = "";
            } else {
                define.comment += "\n\n";
            }
            define.comment += str.substring(str.indexOf("/*") + 3, str.indexOf("*/") - 1);
        }
        return define;
    }

    public static List<Define> parse(File headerFile) throws IOException {
        List<Define> defines = new ArrayList<>();

        Stream<String> html = Files.lines(headerFile.toPath());
        final List<String>[] comments = new List[]{new ArrayList<>()};
        final StringBuilder[] currentComment = {new StringBuilder()};
        html.forEach(str -> {
            if (str.startsWith("/* ")) {
                currentComment[0].append(str.substring(3, str.contains("*/") ? str.indexOf("*/") - 1 : str.length()));
                if (str.contains("*/")) {
                    comments[0].add(currentComment[0].toString());
                    currentComment[0] = new StringBuilder();
                } else {
                    currentComment[0].append("\n");
                }
            } else if (str.startsWith(" * ")) {
                currentComment[0].append(str.substring(3, str.contains("*/") ? str.indexOf("*/") - 1 : str.length()));
                if (str.contains("*/")) {
                    comments[0].add(currentComment[0].toString());
                    currentComment[0] = new StringBuilder();
                } else {
                    currentComment[0].append("\n");
                }
            } else if (str.equals(" */")) {
                comments[0].add(currentComment[0].toString());
                currentComment[0] = new StringBuilder();
            } else if (str.startsWith("#define ")) {
                defines.add(process(str, comments[0]));
            } else if (str.isEmpty()) {
                currentComment[0] = new StringBuilder();
                comments[0] = new ArrayList<>();
            }
        });
        return defines;
    }

}
