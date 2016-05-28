package org.duktape.duktapejava.generator;

import org.apache.commons.io.filefilter.WildcardFileFilter;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.nodes.TextNode;
import org.jsoup.select.Elements;
import org.yaml.snakeyaml.Yaml;

import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Objects;

public class APIParser {

    private static final Yaml yaml = new Yaml();

    private static Prototype.Argument extractTypeAndName(String string) {
        Prototype.Argument ret = new Prototype.Argument();

        String[] arr = string.split(" ");
        if (arr.length == 1) {
            String str = arr[0];
            if (str.equals("...")) {
                ret.type = "...";
                return ret;
            }
            return null;
        }
        String type = arr[0];
        String name = arr[1];
        if (Objects.equals(type, "const")) {
            type += " " + arr[1];
            name = arr[2];
        }
        if (name == null || name.isEmpty()) return null;
        if (name.charAt(0) == '*') {
            name = name.substring(1, name.length());
            type += " *";
        }
        ret.name = name.trim();
        ret.type = type.trim();

        return ret;
    }

    public static Prototype parsePrototype(String prototype) {

        prototype = prototype.replaceAll("\\r|\\n", "");

        Prototype ret = new Prototype();
        String v1 = prototype.substring(0, prototype.indexOf('('));
        String v2 = prototype.substring(prototype.indexOf('(') + 1, prototype.lastIndexOf(')'));

        Prototype.Argument v3 = extractTypeAndName(v1);
        ret.name = v3.name;
        ret.type = v3.type;

        String[] i2 = v2.split(",");
        for (String i : i2) {
            i = i.trim();
            Prototype.Argument v4 = extractTypeAndName(i);
            if (v4 != null) ret.arguments.add(v4);
        }

        return ret;
    }

    private static String processHTML(File apiDirectory, String in) throws IOException {
        Document document = Jsoup.parse(in);
        Elements includes = document.getElementsByAttribute("include");
        for (Element include : includes) {
            String includeContent = new String(Files.readAllBytes(new File(apiDirectory, include.attr("include")).toPath()), StandardCharsets.UTF_8);
            if (include.tagName().equals("p")) {
                includeContent = Jsoup.parse(includeContent).getElementsByTag("body").first().text();
            }
            include.removeAttr("include");
            include.html(includeContent);
        }
        Elements tables = document.getElementsByTag("table");
        for (Element table : tables) {
            table.attr("summary", "");
        }
        Elements as = document.getElementsByTag("a");
        for (Element a : as) {
            String href = a.attr("href");
            href = href.replace("()", "");
            if (!href.equals("#duk_push_c_function") && href.startsWith("#")) {
                a.parent().replaceWith(new TextNode("{@link " + href + " " + href.replace("#", "") + "()}", ""));
            }
        }
        return document.getElementsByTag("body").first().html();
    }

    private static DuktapeFunction parse(File apiDirectory, File file) throws FileNotFoundException {
        try {
            Map<String, Object> data = (Map<String, Object>) yaml.load(new FileReader(file));
            DuktapeFunction df = new DuktapeFunction();
            df.name = (String) data.get("name");
            df.summary = processHTML(apiDirectory, (String) data.get("summary"));
            df.example = (String) data.get("example");
            df.prototype = parsePrototype((String) data.get("proto"));
            df.introduced = (String) data.get("introduced");
            df.stack = (String) data.get("stack");
            return df;
        } catch (Exception e) {
            throw new RuntimeException("Error parsing " + file.getName(), e);
        }
    }

    public static List<DuktapeFunction> parseDirectory(File apiDirectory) throws FileNotFoundException {
        FileFilter fileFilter = new WildcardFileFilter("*.yaml");
        File[] files = apiDirectory.listFiles(fileFilter);
        List<DuktapeFunction> ret = new ArrayList<>();
        for (File file : files) {
            ret.add(parse(apiDirectory, file));
        }
        return ret;
    }

}
