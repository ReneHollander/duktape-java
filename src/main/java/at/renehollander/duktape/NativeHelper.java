package at.renehollander.duktape;

import at.renehollander.duktape.values.DukReferencedValue;

public class NativeHelper {

    public static void unref(DukReferencedValue value) {
        _unref(value.getParent().getContextPointer(), value.getRef());
    }

    public static void mark_for_unref(DukReferencedValue value) {
        synchronized (value.getParent()) {
            _mark_for_unref(value.getParent().getContextPointer(), value.getRef());
        }
    }

    private static native void _unref(long contextPtr, int ref);

    private static native void _mark_for_unref(long contextPtr, int ref);

}
