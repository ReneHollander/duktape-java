package at.renehollander.duktape.exception;

public class WrongValueTypeException extends RuntimeException {

    public WrongValueTypeException(String type) {
        super("Value is not a " + type);
    }

}
