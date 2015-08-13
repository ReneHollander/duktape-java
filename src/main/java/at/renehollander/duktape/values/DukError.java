package at.renehollander.duktape.values;

import at.renehollander.duktape.Duktape;

import java.util.HashMap;
import java.util.Map;

public class DukError extends AbstractDukValue {

    private ErrorType errorType;
    private String errorMessage;
    private String[] stackTrace;

    public DukError(Duktape parent, ErrorType errorType, String errorMessage) {
        this(parent, errorType, errorMessage, null);
    }

    public DukError(Duktape parent, ErrorType errorType, String errorMessage, String[] stackTrace) {
        super(parent);
        this.errorType = errorType;
        this.errorMessage = errorMessage;
        this.stackTrace = stackTrace;
    }

    public ErrorType getErrorType() {
        return errorType;
    }

    public String getErrorMessage() {
        return errorMessage;
    }

    public String[] getStackTrace() {
        return stackTrace;
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
        StringBuilder stringBuilder = new StringBuilder();
        stringBuilder.append(getErrorType().getReadableName()).append(": ").append(this.getErrorMessage()).append("\n");
        for (int i = 0; i < stackTrace.length; i++) {
            String stackElement = stackTrace[i];
            stringBuilder.append("\t").append(stackElement);
            if (i < stackTrace.length - 1)
                stringBuilder.append("\n");
        }
        return stringBuilder.toString();
    }

    private static DukError createError(Duktape duktape, int code, String msg) {
        String[] lines = msg.split(System.lineSeparator());
        String line0 = lines[0].trim();
        String errorMessage = line0.substring(line0.indexOf(':') + 2, line0.length());
        String[] stackTrace = new String[lines.length - 1];
        for (int i = 1; i < lines.length; i++) {
            stackTrace[i - 1] = lines[i].trim();
        }
        return new DukError(duktape, ErrorType.fromCode(code), errorMessage, stackTrace);
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
}
