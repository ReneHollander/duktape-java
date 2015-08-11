package at.renehollander.duktape;

import at.renehollander.duktape.values.DukObject;

import java.util.HashMap;
import java.util.Map;

public class Benchmark {

    public static void main(String[] args) {
        Duktape duktape = new Duktape();

        {
            DukObject object = new DukObject(duktape);
            object.put("key", 1D);
            System.out.println("DukObject:");
            {
                long start = System.nanoTime();
                for (int i = 0; i < 1000000; i++) {
                    object.get("key");
                }
                long diff = System.nanoTime() - start;
                System.out.println("Warmup: " + (diff / 1000000D) + "ns, " + (diff / 1000000D / 1000000) + "ms per call");
            }
            {
                long start = System.nanoTime();
                for (int i = 0; i < 1000000; i++) {
                    object.get("key");
                }
                long diff = System.nanoTime() - start;
                System.out.println("Run: " + (diff / 1000000D) + "ns, " + (diff / 1000000D / 1000000) + "ms per call");
            }
            object.destroy();
        }

        {
            Map<String, Double> object = new HashMap<>();
            object.put("key", 1D);
            System.out.println("HashMap:");
            {
                long start = System.nanoTime();
                for (int i = 0; i < 1000000; i++) {
                    object.get("key");
                }
                long diff = System.nanoTime() - start;
                System.out.println("Warmup: " + (diff / 1000000D) + "ns, " + (diff / 1000000D / 1000000) + "ms per call");
            }
            {
                long start = System.nanoTime();
                for (int i = 0; i < 1000000; i++) {
                    object.get("key");
                }
                long diff = System.nanoTime() - start;
                System.out.println("Run: " + (diff / 1000000D) + "ns, " + (diff / 1000000D / 1000000) + "ms per call");
            }
        }

        duktape.destroy();
    }

}
