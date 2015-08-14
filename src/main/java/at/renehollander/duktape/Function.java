package at.renehollander.duktape;

import at.renehollander.duktape.values.DukValue;

public interface Function {

    interface NoArg {
        @FunctionalInterface
        interface WithoutReturn extends Function {
            void invoke();
        }

        @FunctionalInterface
        interface WithReturnDukValue extends Function {
            DukValue invoke();
        }
    }

    interface OneArg {
        @FunctionalInterface
        interface WithoutReturn extends Function {
            void invoke(DukValue arg1);
        }

        @FunctionalInterface
        interface WithReturn extends Function {
            DukValue invoke(DukValue arg1);
        }
    }

    interface TwoArg {
        @FunctionalInterface
        interface WithoutReturn extends Function {
            void invoke(DukValue arg1, DukValue arg2);
        }

        @FunctionalInterface
        interface WithReturn extends Function {
            DukValue invoke(DukValue arg1, DukValue arg2);
        }
    }

    interface ThreeArg {
        @FunctionalInterface
        interface WithoutReturn extends Function {
            void invoke(DukValue arg1, DukValue arg2, DukValue arg3);
        }

        @FunctionalInterface
        interface WithReturn extends Function {
            DukValue invoke(DukValue arg1, DukValue arg2, DukValue arg3);
        }
    }

}
