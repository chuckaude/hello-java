public class ReverseNullExample {
    public static Object callA(Object o) {
        return "hi";
    }
    public static Object callB(Object o) {
        return o.toString();
    }

    public static String testA(Object o) {
        // callB dereferences o, making the later check a bug
        // if this were callA, no bug would be reported here.
        System.out.println(callB(o));
        if( o == null ) {
            System.out.println("It's null");
        }
        return "done";
    }
}
