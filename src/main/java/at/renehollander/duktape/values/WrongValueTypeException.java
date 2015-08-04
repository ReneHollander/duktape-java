package at.renehollander.duktape.values;

public class WrongValueTypeException extends RuntimeException {

    public WrongValueTypeException(String type) {
        super("Value is not a " + type);
    }

}
