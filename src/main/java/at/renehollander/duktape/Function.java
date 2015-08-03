package at.renehollander.duktape;

public interface Function {

    interface NoArg {
        @FunctionalInterface
        interface WithoutReturn extends Function {
            void invoke();
        }

        @FunctionalInterface
        interface WithReturn<R> extends Function {
            R invoke();
        }
    }

    interface OneArg {
        @FunctionalInterface
        interface WithoutReturn<A1> extends Function {
            void invoke(A1 arg1);
        }

        @FunctionalInterface
        interface WithReturn<R, A1> extends Function {
            R invoke(A1 arg1);
        }
    }

    interface TwoArg {
        @FunctionalInterface
        interface WithoutReturn<A1, A2> extends Function {
            void invoke(A1 arg1, A2 arg2);
        }

        @FunctionalInterface
        interface WithReturn<R, A1, A2> extends Function {
            R invoke(A1 arg1, A2 arg2);
        }
    }

    interface ThreeArg {
        @FunctionalInterface
        interface WithoutReturn<A1, A2, A3> extends Function {
            void invoke(A1 arg1, A2 arg2, A3 arg3);
        }

        @FunctionalInterface
        interface WithReturn<R, A1, A2, A3> extends Function {
            R invoke(A1 arg1, A2 arg2, A3 arg3);
        }
    }

}
