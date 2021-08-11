/**
 * The A class contains a static B class, a main method and a function fun.
 */
public class A {
    /**
     * The static B class contains long, String and B values, as well as a constructor to define these values.
     */
    static class B {
        long value;
        String msg;
        B next;

        /**
         * Creates a new B object with value value, msg msg and next next.
         * @param value The value of the B object
         * @param msg The msg of the B object
         * @param next The next pointer of the B object
         */
        public B(long value, String msg, B next) {
            this.value = value;
            this.msg = msg;
            this.next = next;
        }
    }

    /**
     * Runs the program.
     * @param args Arguments passed to the program
     */
    public static void main(String[] args) {
        B a = new B(0L, "", null);
        B b = fun(a);

        // System.out.println(a.value + " " + a.msg);
        // System.out.println(b.value + " " + b.msg);
    }

    /**
     * This method produces the reachability graph in question 4.1.
     * @param arg The B object called arg
     * @return arg's next pointer
     */
    public static B fun(B arg) {
        arg.value = 42L;
        arg.msg = "CS3214";
        arg.next = new B(43L, "rocks", null);

        B local = arg;
        return arg.next;
    }
}