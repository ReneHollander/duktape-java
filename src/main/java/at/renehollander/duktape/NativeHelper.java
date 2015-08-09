package at.renehollander.duktape;

public class NativeHelper {

    public static native void unref(long contextPtr, int ref);

}
