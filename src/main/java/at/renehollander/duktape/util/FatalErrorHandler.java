package at.renehollander.duktape.util;

@FunctionalInterface
public interface FatalErrorHandler {

    void fatalError(int code, String msg);

}
