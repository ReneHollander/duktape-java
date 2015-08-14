package at.renehollander.duktape.values;

import at.renehollander.duktape.Duktape;

import java.util.HashMap;
import java.util.Map;

public class DukError extends AbstractDukReferencedValue {

    protected DukError(Duktape parent, int ref) {
        super(parent, ref);
    }

    public DukError(Duktape parent, ErrorType errorType, String message) {
        this(parent, _createDukError(parent.getContextPointer(), errorType.getCode(), message));
    }

    public ErrorType getErrorType() {
        return ErrorType.fromCode(_getErrorCode(this.getParent().getContextPointer(), this.getRef()));
    }

    public String getErrorMessage() {
        return _getErrorMessage(this.getParent().getContextPointer(), this.getRef());
    }

    @Override
    public boolean isError() {
        return true;
    }

    @Override
    public DukError asError() {
        return this;
    }

    @Override
    public String toString() {
        return this.getErrorMessage();
    }

    public enum ErrorType {
        DUK_ERR_NONE(0, "no error"),
        DUK_ERR_UNIMPLEMENTED_ERROR(50, "UnimplementedError"),
        DUK_ERR_UNSUPPORTED_ERROR(51, "UnsupportedError"),
        DUK_ERR_INTERNAL_ERROR(52, "InternalError"),
        DUK_ERR_ALLOC_ERROR(53, "AllocError"),
        DUK_ERR_ASSERTION_ERROR(54, "AssertionError"),
        DUK_ERR_API_ERROR(55, "APIError"),
        DUK_ERR_UNCAUGHT_ERROR(56, "UncaughtError"),
        DUK_ERR_ERROR(100, "Error"),
        DUK_ERR_EVAL_ERROR(101, "EvalError"),
        DUK_ERR_RANGE_ERROR(102, "RangeError"),
        DUK_ERR_REFERENCE_ERROR(103, "ReferenceError"),
        DUK_ERR_SYNTAX_ERROR(104, "SyntaxError"),
        DUK_ERR_TYPE_ERROR(105, "TypeError"),
        DUK_ERR_URI_ERROR(106, "URIError");

        private int code;
        private String readableName;

        ErrorType(int code, String readableName) {
            this.code = code;
            this.readableName = readableName;
        }

        public int getCode() {
            return this.code;
        }

        public String getReadableName() {
            return readableName;
        }

        @Override
        public String toString() {
            return this.getReadableName();
        }

        private static Map<Integer, ErrorType> codeErrorTypeMapping;

        static {
            codeErrorTypeMapping = new HashMap<>();
            for (ErrorType errorType : values()) {
                codeErrorTypeMapping.put(errorType.getCode(), errorType);
            }
        }

        public static ErrorType fromCode(int code) {
            return codeErrorTypeMapping.get(code);
        }
    }

    private static native int _createDukError(long contextPointer, int code, String message);

    private static native int _getErrorCode(long contextPointer, int ref);

    private static native String _getErrorMessage(long contextPointer, int ref);
}
