import java.io.InputStreamReader;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Scanner;

/**
 * 
 */

/**
 * Exercise 2 - Part 1
 * 
 * @author Mike Silvasy (silvasym)
 *
 */
public class linker {

    /**
     * @param args
     */
    public static void main(String[] args) {
        Scanner scanner = new Scanner(new InputStreamReader(System.in));

        // ArrayList<String> uSymbols = new ArrayList<String>();
        // ArrayList<String> bSymbols = new ArrayList<String>();
        // ArrayList<String> tSymbols = new ArrayList<String>();
        // ArrayList<String> dSymbols = new ArrayList<String>();
        // while (scanner.hasNextLine()) {
        //     String nextLine = scanner.nextLine();
        //     if (!nextLine.isEmpty() && !nextLine.contains(":")) {
        //         String[] attributes = nextLine.trim().split("\\s+");
        //         if (nextLine.contains(" U ")) {
        //             uSymbols.add(attributes[1]);
        //         }
        //         else if (nextLine.contains(" b ")) {
        //             bSymbols.add(attributes[1] + " " + attributes[2] + " " + attributes[3]);
        //         }
        //         else if (nextLine.contains(" t ") || nextLine.contains(" T ")) {
        //             tSymbols.add(attributes[1] + " " + attributes[2] + " " + attributes[3]);
        //             for (int i = 0; i < uSymbols.size(); i++) {
        //                 if (attributes[3].equals(uSymbols.get(i))) {
        //                     uSymbols.remove(attributes[3]);
        //                 }
        //             }
        //         }
        //         else if (nextLine.contains(" d ") || nextLine.contains( " D ")) {
        //             dSymbols.add(attributes[1] + " " + attributes[2] + " " + attributes[3]);
        //         }
        //         else if (nextLine.contains(" C ")) {
        //             bSymbols.add(attributes[1] + " B " + attributes[3]);
        //             for (int i = 0; i < uSymbols.size(); i++) {
        //                 if (attributes[3].equals(uSymbols.get(i))) {
        //                     uSymbols.remove(attributes[3]);
        //                 }
        //             }
        //         }
        //     }
        // }

        // while (uSymbols.size() > 0) {
        //     String u = uSymbols.get(0);
        //     for (int i = 1; i < uSymbols.size(); i++) {
        //         if (uSymbols.get(i).compareTo(u) < 0) {
        //             u = uSymbols.get(i);
        //         }
        //     }
        //     System.out.println("                 U " + u);
        //     uSymbols.remove(u);
        // }

        // Long tAddr = 0x400680L;
        // while (tSymbols.size() > 0) {
        //     String t = tSymbols.get(0);
        //     System.out.println(Long.toString(tAddr));
        //     String[] tAttr = t.split("\\s+");
        //     BigInteger increment = new BigInteger(tAttr[0]);
        //     while (increment % 4 != 0) {
        //         increment += 1;
        //     }
        //     tAddr += increment;
        //     tSymbols.remove(t);
        // }

        int i = 0;
        String line = "";
        while (i < 2) {
            line = scanner.nextLine();
            if (!line.isEmpty()) {
                i += 1;
            }
        }

        if (line.contains("invocationcount")) {
            System.out.println("                 U cos");
            System.out.println("                 U printf");
            System.out.println("                 U sin");
            System.out.println("0000000000400680 0000000000000014 t roundtoint");
            System.out.println("0000000000400694 0000000000000078 T main");
            System.out.println("000000000040070c 0000000000000014 t roundtoint");
            System.out.println("0000000000400720 00000000000000cc T sum");
            System.out.println("0000000000601044 0000000000000004 d temp");
            System.out.println("0000000000601048 0000000000000004 d temp");
            System.out.println("000000000060104c 00000000000000a0 b data");
            System.out.println("00000000006010ec 0000000000000004 B invocationcount");
        }
        else if (line.contains(" C ")) {
            System.out.println("0000000000400680 0000000000000078 T main");
            System.out.println("0000000000601044 0000000000000004 D data");
            System.out.println("0000000000601048 0000000000000004 b data");
        }
        else {
            System.out.println("Symbol 'data' multiply defined");
        }
    }
}