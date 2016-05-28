package org.duktape.duktapejava.generator;

public class Util {

    public static String excerpt(String str, int maxLen) {
        str = str.trim();
        int end = str.indexOf('\n');
        if (end == -1) end = str.length();
        if (end > maxLen) end = maxLen;
        return str.substring(0, end);
    }

}
