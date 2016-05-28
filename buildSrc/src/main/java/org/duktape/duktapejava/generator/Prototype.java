package org.duktape.duktapejava.generator;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Prototype {

    public static class Argument {
        public String name;
        public String type;

        @Override
        public String toString() {
            return "Argument{" +
                    "name='" + name + '\'' +
                    ", type=" + type +
                    '}';
        }
    }

    public String name;
    public String type;
    public List<Argument> arguments = new ArrayList<>();

    @Override
    public String toString() {
        return "Prototype{" +
                "name='" + name + '\'' +
                ", type=" + type +
                ", arguments=" + arguments +
                '}';
    }
}
