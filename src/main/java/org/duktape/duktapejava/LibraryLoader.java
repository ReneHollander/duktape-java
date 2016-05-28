package org.duktape.duktapejava;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.nio.file.Files;
import java.util.Properties;
import java.util.UUID;

public class LibraryLoader {

    private static final String platform;
    private static final Properties properties;
    private static final File tempDir;
    private static boolean loaded = false;

    static {
        String jvmName = System.getProperty("java.vm.name", "").toLowerCase();
        String osName = System.getProperty("os.name", "").toLowerCase();
        String osArch = System.getProperty("os.arch", "").toLowerCase();
        if (jvmName.startsWith("dalvik") && osName.startsWith("linux")) {
            osName = "android";
        } else if (jvmName.startsWith("robovm") && osName.startsWith("darwin")) {
            osName = "ios";
            osArch = "arm";
        } else if (osName.startsWith("mac os x")) {
            osName = "macosx";
        } else {
            int spaceIndex = osName.indexOf(' ');
            if (spaceIndex > 0) {
                osName = osName.substring(0, spaceIndex);
            }
        }
        if (osArch.equals("i386") || osArch.equals("i486") || osArch.equals("i586") || osArch.equals("i686")) {
            osArch = "x86";
        } else if (osArch.equals("amd64") || osArch.equals("x86-64") || osArch.equals("x64")) {
            osArch = "x86_64";
        } else if (osArch.startsWith("aarch64") || osArch.startsWith("armv8") || osArch.startsWith("arm64")) {
            osArch = "arm64";
        } else if (osArch.startsWith("arm")) {
            osArch = "arm";
        }

        platform = osName + "-" + osArch;
        properties = loadProperties(platform);
        tempDir = new File(new File(System.getProperty("java.io.tmpdir")), "duktape-java-" + UUID.randomUUID());
        tempDir.deleteOnExit();

    }

    public static void load() {
        if (!loaded) {
            loaded = true;
            String name = properties.getProperty("platform.library.prefix") + "duktape-java-" + platform + properties.getProperty("platform.library.suffix");
            InputStream is = LibraryLoader.class.getResourceAsStream(name);
            File lib = null;
            if (is == null) {
                lib = new File("build/native/" + name);
            } else {
                try {
                    lib = new File(tempDir, name);
                    Files.copy(is, lib.getAbsoluteFile().toPath());
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
            System.load(lib.getAbsolutePath());
        }
    }

    public static Properties loadProperties(String name) {
        Properties p = new Properties();
        p.put("platform", name);
        p.put("platform.path.separator", File.pathSeparator);
        String s = System.mapLibraryName("/");
        int i = s.indexOf('/');
        p.put("platform.library.prefix", s.substring(0, i));
        p.put("platform.library.suffix", s.substring(i + 1));
        name = "properties/" + name + ".properties";
        InputStream is = LibraryLoader.class.getResourceAsStream(name);
        try {
            try {
                p.load(new InputStreamReader(is));
            } catch (NoSuchMethodError e) {
                p.load(is);
            }
        } catch (Exception e) {
            name = "properties/generic.properties";
            is = LibraryLoader.class.getResourceAsStream(name);
            try {
                try {
                    p.load(new InputStreamReader(is));
                } catch (NoSuchMethodError e2) {
                    p.load(is);
                }
            } catch (Exception e2) {
                // give up and return defaults
            }
        }
        return p;
    }

}
