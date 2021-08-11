import java.io.*;
import java.util.*;

public class question1 {
    static class graph {
        private HashMap<Integer, LinkedList<Integer>> map;

        public graph() {
            map = new HashMap<Integer, LinkedList<Integer>>();
        }

        public void insertEdge(int a, int b) {
            if (!map.containsKey(a)) {
                map.put(a, null);
            }
            if (!map.containsKey(b)) {
                map.put(b, null);
            }

            LinkedList<Integer> aNeighbors = map.get(a);
            if (aNeighbors == null) {
                aNeighbors = new LinkedList<Integer>();
            }
            else {
                if (!aNeighbors.isEmpty() && aNeighbors.contains(b)) {
                    aNeighbors.remove(b);
                }
            }
            aNeighbors.add(b);
            map.put(a, aNeighbors);
        }

        public boolean hasEdge(int a, int b) {
            return (map.containsKey(a) && map.get(a).contains(b));
        }

        public void dfs(int n, boolean visited[], ArrayList<Integer> nodes, ArrayList<Integer> output) {                // Depth-first Search
            visited[nodes.indexOf(n)] = true;
            output.add(n);

            LinkedList<Integer> nNeighbors = map.get(n);
            if (nNeighbors == null) {
                return;
            }
            for (Integer i : nNeighbors) {
                if (!visited[nodes.indexOf(i)]) {
                    dfs(i, visited, nodes, output);
                }
            }
        }
    }

    public static void main(String args[]) throws FileNotFoundException {
        // READING
        Scanner scanner = new Scanner(System.in);

        int nVal = scanner.nextInt();
        int mVal = scanner.nextInt();
        int rVal = scanner.nextInt();

        int[] nodeSizes = new int[nVal];                       // Keeps track of all the sizes (will be of size n)                  Second Line
        boolean visited[] = new boolean[nVal];
        int heapSize = 0;                              // Keeps track of the size total (used for calculation of s later)
        for (int i = 0; i < nVal; i++) {
            nodeSizes[i] = scanner.nextInt();
            visited[i] = false;
            heapSize += nodeSizes[i];
        }

        graph g = new graph();
        ArrayList<Integer> nodes = new ArrayList<Integer>();
        for (int i = 0; i < mVal; i++) {
            int iVal = scanner.nextInt();
            int jVal = scanner.nextInt();
            g.insertEdge(iVal, jVal);

            if (i == 0) {
                nodes.add(iVal);
            }
            if (!nodes.contains(iVal)) {
                nodes.add(iVal);
            }
            if (!nodes.contains(jVal)) {
                nodes.add(jVal);
            }
        }
        Collections.sort(nodes);

        // WRITING
        String rootsMemStr = "";
        for (int i = 0; i < rVal; i++) {
            ArrayList<Integer> output = new ArrayList<Integer>();
            g.dfs(scanner.nextInt(), visited, nodes, output);
            int rootMem = 0;
            for (int j : output) {
                rootMem += nodeSizes[nodes.indexOf(j)];
            }
            rootsMemStr += rootMem + "\n";
        }

        int sVal = 0;
        for (int i = 0; i < nVal; i++) {
            if (!visited[i]) {
                sVal += nodeSizes[i];
            }
        }
        System.out.println((heapSize - sVal) + " " + sVal);
        System.out.print(rootsMemStr);
    }
}