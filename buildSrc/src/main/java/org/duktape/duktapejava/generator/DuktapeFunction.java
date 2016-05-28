package org.duktape.duktapejava.generator;

public class DuktapeFunction {

    public String name;
    public Prototype prototype;
    public String summary;
    public String example;
    public String introduced;
    public String stack;

    @Override
    public String toString() {
        return "DuktapeFunction{" +
                "name='" + name + '\'' +
                ", prototype=" + prototype +
                ", summary='" + Util.excerpt(summary, 64) + '\'' +
                ", example='" + Util.excerpt(example, 64) + '\'' +
                ", stack='" + stack + '\'' +
                ", introduced='" + introduced + '\'' +
                '}';
    }
}
