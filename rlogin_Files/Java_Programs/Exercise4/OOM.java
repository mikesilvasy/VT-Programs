public class OOM {
    static class ListCell {
        byte payload[];
        Long num;
        ListCell next;
        public ListCell() {
            payload = new byte[1024];
            num = 1999L;
            next = null;
        }
    }
    public static void main(String args[]) {
        ListCell listcell_1 = new ListCell();
        while (true) {
            ListCell listcell_2 = new ListCell();
            listcell_2.num = listcell_1.num + 1;
            listcell_2.next = listcell_1;
            listcell_1 = listcell_2;
        }
    }
}