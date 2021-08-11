/**
 * The reachability class contains a static class node and a main function.
 */
public class reachability {
    /**
     * The static class node contains val and next values, as well as a constructor.
     */
    static class node {
        Object val;
        node next;

        /**
         * Creates a new node object with val val and next pointer next.
         * @param val
         * @param next
         */
        public node (Object val, node next) {
            this.val = val;
            this.next = next;
        }
    }

    /**
     * Runs the program to produce the reachability graph in question 4.2.
     * @param args Arguments passed to the program
     */
    public static void main(String[] args) {
        node obj0 = new node("obj0", null);
        node root = new node("root", obj0);

        node obj1 = null;
        node obj2 = null;
        node obj3 = null;
        node obj4 = null;
        node obj5 = null;
        node obj6 = null;
        node obj7 = null;
        node obj8 = null;
        node obj9 = null;
    }
}