package at.renehollander.duktape;

import java.io.File;

public class Duktape {

    static {
        File libraryFile = new File("build/libduktape-java.so");
        System.load(libraryFile.getAbsolutePath());
    }

    public static native void execute(String script);

}
