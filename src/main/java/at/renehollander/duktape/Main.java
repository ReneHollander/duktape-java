package at.renehollander.duktape;

import at.renehollander.duktape.values.DukArray;

public class Main {

    public static void main(String[] args) {

        System.out.println("Duktape Version " + Duktape.getVersion());

        Duktape duktape = new Duktape();

        DukArray array = new DukArray(duktape);

        array.add(7);
        array.add(9);

        //array.add(1, 8);

        System.out.println(array.toJSON());

        duktape.destroy();
    }

}
