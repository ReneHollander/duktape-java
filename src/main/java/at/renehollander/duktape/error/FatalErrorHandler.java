package at.renehollander.duktape.error;

@FunctionalInterface
public interface FatalErrorHandler {

    public void fatalError(int code, String msg);

}
