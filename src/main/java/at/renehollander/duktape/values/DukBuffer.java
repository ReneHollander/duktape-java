package at.renehollander.duktape.values;

import at.renehollander.duktape.Duktape;

import java.nio.ByteBuffer;

public class DukBuffer extends AbstractDukReferencedValue {

    private ByteBuffer byteBuffer;

    private DukBuffer(Duktape parent, int ref) {
        super(parent, ref);
    }

    public ByteBuffer getByteBuffer() {
        if (this.byteBuffer == null) {
            this.byteBuffer = _getByteBuffer(this.getParent().getContextPointer(), this.getRef());
        }
        return byteBuffer;
    }

    @Override
    public boolean isBuffer() {
        return true;
    }

    @Override
    public DukBuffer asBuffer() {
        return this;
    }

    public static DukBuffer allocate(Duktape parent, int size) {
        return new DukBuffer(parent, _createDukBuffer(parent.getContextPointer(), size));
    }

    private static native int _createDukBuffer(long contextPointer, int size);

    private static native ByteBuffer _getByteBuffer(long contextPointer, int ref);
}
