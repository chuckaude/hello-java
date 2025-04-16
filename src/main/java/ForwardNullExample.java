// https://documentation.blackduck.com/bundle/coverity-docs/page/checker-ref/checkers/FGH/forward_null.html

public class ForwardNullExample {
    public static Object callA() {
        // This causes a FORWARD_NULL defect report
        return testA(null);
    }

    public static Object callB() {
        // No defect report
        return testA(new Object());
    }

    public static String testA(Object o) {
        return o.toString();
    }
}
