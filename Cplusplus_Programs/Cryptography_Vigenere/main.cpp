#include <iostream>
#include <iomanip>

using namespace std;

void createSubstrings();
void calculateIndices();
//void printTable();
void findKeyword();
void decipherText();
void printDivider();
void printPartDivider();

int m[5] = {4, 5, 6, 7, 8};
int currM;
string substrings[8];
int key[7];
string cipher = "LAVHEBSJMDINFGXCLWTUUWARWBQWFTEHWUDDTCAAKKTXTSMYALMVHTAHJHKICFAFZKLEXA"
                "TXIXYMFVLVGUDALRFJTTGKXNLOYOWLVVVQAFKVGEZLEHEXHEZGPVZEDOWARZEAFSGVASOS"
                "DXJIEZESBEWTDWSFGVOPMUMJENPKWKMMCQKVXJMGZWVBEEWMQLARXGUNWLLWEDKKHCICAF"
                "LKFPOHWJTTGEEKLHKLEUJVTKEAESJXJYLFDSPVRFAJUXDINFAKLFQEFAEXJYNMTDXKSRQU"
                "GOVVTTWUHEXEZLGYVPEOLJHEMCOGEFLRIOSLBFRSRJGFKLEFWUAESLAYQIISVUVWKVZEZA"
                "FKVWPAFKXKSAOGMKKSRPWJHIHUXQSNKLODARXUAADJSGKMSEMWWSCARWVXIELVMVZVJODW"
                "PTDTLQESGPGOYEMGZGAFAGGJWEDNAVVWNAOWGTVYBLUXIXAUFUHDQUZAUTKMOZKTRUIFMM"
                "DMNMTTLZXBIYZWUXJWADQLHUICDQHMKLEOGEFLRIOSLBFRSEGDXCCIZLZXYENPKGYKLEQF"
                "VNJIRFZALRTPXAWLSSTTOZXEXHQVSMRMSUFEHKMOZGNXIILQULKFRIOFWMNSRWKGKRXRQK"
                "LHEENQDWVKVOZAUWVZIOWAYKLEOGEFLRIOSLBFRSBJGOZHEDAKLVVVQVOBKLAISJKRRTEW"
                "WDZRGFZGLVGOYEMGZGAFAGGJXHQHJHMMDQJUTEROFHJHMMDQLZXUETMTWVRYSQALARWDQK"
                "AZEIDFZWMVGHZGDHXCSGUZMYETULUTEROFTWTTGEEKWWSCAZQLAZVDBSJMPAEPGFHKLAHW"
                "SGPWIXNWKSYLXWLLRRDFZWWZWCGKKBFRSIALAZRTTWWQVGUFANXSVAZUZTIISFADEFRGAA"
                "FZNLIXWLAVVETSKGFXYQLTXVRAPWUBJMOZOZXKLEDLGLVIKXWYBJPAFAGGNIMGKLPFVKIA"
                "LATSNSJWLJMNPMKMICAOSVXDMCEHJBMECKYJHLTSMFVHKLEDKLHTVARLSGRTPDGSVYXHML"
                "SWUVEEKWLRPLAXLAVQUXLAICICAEHXKMNSUGGTIRZKLARXHMNWUVINFZWYFGUEGXLFQUOZ"
                "VXSETQTMMNICMFSECEGDWWMYETIWOBCPNQWVHEKOUFYAFREELSGUMNRGJFVHPGTDBTHENS"
                "LXRFOGLZHNFEELLHGVOFWUMCMBQJLRRRDEWUNIMTKAFUFXHAMJERASMFVHLVTQUZGFPOSQ";

/*
 * Runs the program.
 */
int main()
{
    // Part 1
    cout << "PART 1\n" << endl;
    cout << "m = 4\n" << endl;
    for (int i = 0; i < 5; i++) {
        currM = m[i];
        createSubstrings();
        calculateIndices();
        if (i < 4) {
            printDivider();
        }
    }
    cout << "==> We know m = 7 because the indices of coincidence are closest to 0.065 (Limiting Case) when m = 7.\n" << endl;
    printPartDivider();

    // Part 2
    cout << "PART 2\n" << endl;
    //printTable();
    currM = 7;
    createSubstrings();
    findKeyword();
    printPartDivider();

    // Part 3
    cout << "PART 3\n" << endl;
    decipherText();

    return 0;
}

/*
 * Creates m number of substrings from the cipher text.
 */
void createSubstrings() {
    for (int i = 0; i < 8; i++) {
        substrings[i] = "";
    }

    for (int i = 0; i < currM; i++) {
        for (int j = i; j < cipher.length(); j += currM) {
            substrings[i] += cipher[j];
        }
    }
}

/*
 * Calculates the index of coincidence for each substring.
 */
void calculateIndices() {
    for (int i = 0; i < currM; i++) {
        string currSubstr = substrings[i];
        int letterFreq[26];
        for (int j = 0; j < 26; j++) {
            letterFreq[j] = 0;
        }

        for (int j = 0; j < currSubstr.length(); j++) {
            if (currSubstr[j] == 'A') {
                letterFreq[0] += 1;
            }
            else if (currSubstr[j] == 'B') {
                letterFreq[1] += 1;
            }
            else if (currSubstr[j] == 'C') {
                letterFreq[2] += 1;
            }
            else if (currSubstr[j] == 'D') {
                letterFreq[3] += 1;
            }
            else if (currSubstr[j] == 'E') {
                letterFreq[4] += 1;
            }
            else if (currSubstr[j] == 'F') {
                letterFreq[5] += 1;
            }
            else if (currSubstr[j] == 'G') {
                letterFreq[6] += 1;
            }
            else if (currSubstr[j] == 'H') {
                letterFreq[7] += 1;
            }
            else if (currSubstr[j] == 'I') {
                letterFreq[8] += 1;
            }
            else if (currSubstr[j] == 'J') {
                letterFreq[9] += 1;
            }
            else if (currSubstr[j] == 'K') {
                letterFreq[10] += 1;
            }
            else if (currSubstr[j] == 'L') {
                letterFreq[11] += 1;
            }
            else if (currSubstr[j] == 'M') {
                letterFreq[12] += 1;
            }
            else if (currSubstr[j] == 'N') {
                letterFreq[13] += 1;
            }
            else if (currSubstr[j] == 'O') {
                letterFreq[14] += 1;
            }
            else if (currSubstr[j] == 'P') {
                letterFreq[15] += 1;
            }
            else if (currSubstr[j] == 'Q') {
                letterFreq[16] += 1;
            }
            else if (currSubstr[j] == 'R') {
                letterFreq[17] += 1;
            }
            else if (currSubstr[j] == 'S') {
                letterFreq[18] += 1;
            }
            else if (currSubstr[j] == 'T') {
                letterFreq[19] += 1;
            }
            else if (currSubstr[j] == 'U') {
                letterFreq[20] += 1;
            }
            else if (currSubstr[j] == 'V') {
                letterFreq[21] += 1;
            }
            else if (currSubstr[j] == 'W') {
                letterFreq[22] += 1;
            }
            else if (currSubstr[j] == 'X') {
                letterFreq[23] += 1;
            }
            else if (currSubstr[j] == 'Y') {
                letterFreq[24] += 1;
            }
            else {
                letterFreq[25] += 1;
            }
        }

        double numerator = 0;
        for (int j = 0; j < 26; j++) {
            if (letterFreq[j] > 1) {
                numerator += letterFreq[j] * (letterFreq[j] - 1);
            }
        }

        cout << "y" << (i + 1) << ":  " << currSubstr << "\n";
        cout << "Index of Coincidence for y" << (i + 1) << ":  " << (numerator/(currSubstr.length() * (currSubstr.length() - 1))) << "\n" << endl;
    }
}

///*
// * Prints the table for Part 2 (# of Displacements and # of Coincidences).
// */
//void printTable() {
//    cout << "-----------------------------------------------------------\n";
//    cout << "Displacements\t\t4\t5\t6\t7\t8\n";
//
//    int coincidences[5] = {0, 0, 0, 0, 0};
//    for (int i = 4; i <= 8; i++) {
//        for (int j = 0; j < cipher.length(); j++) {
//            if (j + i < cipher.length() && cipher[j] == cipher[j + i]) {
//                coincidences[i - 4] += 1;
//            }
//        }
//    }
//
//    cout << "-----------------------------------------------------------\n";
//    cout << "Coincidences\t\t" << coincidences[0] << "\t" << coincidences[1] << "\t" << coincidences[2];
//    cout << "\t" << coincidences[3] << "\t" << coincidences[4] << "\n";
//    cout << "-----------------------------------------------------------\n" << endl;
//}

/*
 * Finds the keyword used in this Vigenere Cipher and prints the table for part 2.
 */
void findKeyword() {
    cout << "-------------------------------------------------------------------------------------";
    cout << "----------------------------------\n";
    cout << "g\t\t1 - Mg\t\t2 - Mg\t\t3 - Mg\t\t4 - Mg\t\t5 - Mg\t\t6 - Mg\t\t7 - Mg";
    double M[currM][26];
    for (int i = 0; i < currM; i++) {
        string currSubstr = substrings[i];
        double letterFreq[26];
        for (int j = 0; j < 26; j++) {
            letterFreq[j] = 0;
        }

        for (int j = 0; j < currSubstr.length(); j++) {
            if (currSubstr[j] == 'A') {
                letterFreq[0] += 1;
            }
            else if (currSubstr[j] == 'B') {
                letterFreq[1] += 1;
            }
            else if (currSubstr[j] == 'C') {
                letterFreq[2] += 1;
            }
            else if (currSubstr[j] == 'D') {
                letterFreq[3] += 1;
            }
            else if (currSubstr[j] == 'E') {
                letterFreq[4] += 1;
            }
            else if (currSubstr[j] == 'F') {
                letterFreq[5] += 1;
            }
            else if (currSubstr[j] == 'G') {
                letterFreq[6] += 1;
            }
            else if (currSubstr[j] == 'H') {
                letterFreq[7] += 1;
            }
            else if (currSubstr[j] == 'I') {
                letterFreq[8] += 1;
            }
            else if (currSubstr[j] == 'J') {
                letterFreq[9] += 1;
            }
            else if (currSubstr[j] == 'K') {
                letterFreq[10] += 1;
            }
            else if (currSubstr[j] == 'L') {
                letterFreq[11] += 1;
            }
            else if (currSubstr[j] == 'M') {
                letterFreq[12] += 1;
            }
            else if (currSubstr[j] == 'N') {
                letterFreq[13] += 1;
            }
            else if (currSubstr[j] == 'O') {
                letterFreq[14] += 1;
            }
            else if (currSubstr[j] == 'P') {
                letterFreq[15] += 1;
            }
            else if (currSubstr[j] == 'Q') {
                letterFreq[16] += 1;
            }
            else if (currSubstr[j] == 'R') {
                letterFreq[17] += 1;
            }
            else if (currSubstr[j] == 'S') {
                letterFreq[18] += 1;
            }
            else if (currSubstr[j] == 'T') {
                letterFreq[19] += 1;
            }
            else if (currSubstr[j] == 'U') {
                letterFreq[20] += 1;
            }
            else if (currSubstr[j] == 'V') {
                letterFreq[21] += 1;
            }
            else if (currSubstr[j] == 'W') {
                letterFreq[22] += 1;
            }
            else if (currSubstr[j] == 'X') {
                letterFreq[23] += 1;
            }
            else if (currSubstr[j] == 'Y') {
                letterFreq[24] += 1;
            }
            else {
                letterFreq[25] += 1;
            }
        }

        // Used to calculate the Msubg values.
        double p[26] = {0.082, 0.015, 0.028, 0.043, 0.127, 0.022, 0.020, 0.061, 0.070, 0.002, 0.008, 0.040, 0.024, 0.067, 0.075, 0.019,
            0.001, 0.060, 0.063, 0.091, 0.028, 0.010, 0.023, 0.001, 0.020, 0.001};
        double q[26];
        for (int j = 0; j < 26; j++) {
            q[j] = letterFreq[j] / currSubstr.length();
        }

        double largestM = 0;
        int letter = -1;
        for (int j = 0; j < 26; j++) {
            double currM = 0;
            for (int k = 0; k < 26; k++) {
                currM += p[k] * q[k];
            }

            M[i][j] = currM;

            if (currM > largestM) {
                largestM = currM;
                letter = j;
            }

            for (int k = 0; k < 26; k++) {
                if (k < 25) {
                    q[k] = q[k + 1];
                }
                else {
                    q[k] = q[0];
                }
            }
        }

        key[i] = letter;
    }

    // Creates the table from slide 26.
    for (int i = 0; i < 26; i++) {
        cout << "\n-------------------------------------------------------------------------------------";
        cout << "----------------------------------\n";
        cout << i << "\t\t";
        for (int j = 0; j < currM; j++) {
            cout << setprecision(2);
            cout << M[j][i] << "\t\t";
        }
    }
    cout << "\n-------------------------------------------------------------------------------------";
    cout << "----------------------------------\n" << endl;

    cout << "==> K = (" << key[0] << ", " << key[1] << ", " << key[2] << ", " << key[3] << ", " << key[4] << ", " << key[5] << ", ";
    cout << key[6] << ") = (s, t, r, e, a, m, s)\n";
    cout << "==> Keyword:  streams" << endl;
}

/*
 * Uses the keyword to decipher the cipher text and display it in plain text.
 */
void decipherText() {
    string decipher = "";
    int currChar;
    int currKeyIndex = 0;
    for (int i = 0; i < cipher.length(); i++) {
        if (cipher[i] == 'A') {
            currChar = 0;
        }
        else if (cipher[i] == 'B') {
            currChar = 1;
        }
        else if (cipher[i] == 'C') {
            currChar = 2;
        }
        else if (cipher[i] == 'D') {
            currChar = 3;
        }
        else if (cipher[i] == 'E') {
            currChar = 4;
        }
        else if (cipher[i] == 'F') {
            currChar = 5;
        }
        else if (cipher[i] == 'G') {
            currChar = 6;
        }
        else if (cipher[i] == 'H') {
            currChar = 7;
        }
        else if (cipher[i] == 'I') {
            currChar = 8;
        }
        else if (cipher[i] == 'J') {
            currChar = 9;
        }
        else if (cipher[i] == 'K') {
            currChar = 10;
        }
        else if (cipher[i] == 'L') {
            currChar = 11;
        }
        else if (cipher[i] == 'M') {
            currChar = 12;
        }
        else if (cipher[i] == 'N') {
            currChar = 13;
        }
        else if (cipher[i] == 'O') {
            currChar = 14;
        }
        else if (cipher[i] == 'P') {
            currChar = 15;
        }
        else if (cipher[i] == 'Q') {
            currChar = 16;
        }
        else if (cipher[i] == 'R') {
            currChar = 17;
        }
        else if (cipher[i] == 'S') {
            currChar = 18;
        }
        else if (cipher[i] == 'T') {
            currChar = 19;
        }
        else if (cipher[i] == 'U') {
            currChar = 20;
        }
        else if (cipher[i] == 'V') {
            currChar = 21;
        }
        else if (cipher[i] == 'W') {
            currChar = 22;
        }
        else if (cipher[i] == 'X') {
            currChar = 23;
        }
        else if (cipher[i] == 'Y') {
            currChar = 24;
        }
        else {
            currChar = 25;
        }

        // Finding the number representing the deciphered character.
        currChar -= key[currKeyIndex];
        currChar = currChar % 26;
        while (currChar < 0) {
            currChar += 26;
        }
        currKeyIndex = (currKeyIndex + 1) % currM;

        if (currChar == 0) {
            decipher += 'a';
        }
        else if (currChar == 1) {
            decipher += 'b';
        }
        else if (currChar == 2) {
            decipher += 'c';
        }
        else if (currChar == 3) {
            decipher += 'd';
        }
        else if (currChar == 4) {
            decipher += 'e';
        }
        else if (currChar == 5) {
            decipher += 'f';
        }
        else if (currChar == 6) {
            decipher += 'g';
        }
        else if (currChar == 7) {
            decipher += 'h';
        }
        else if (currChar == 8) {
            decipher += 'i';
        }
        else if (currChar == 9) {
            decipher += 'j';
        }
        else if (currChar == 10) {
            decipher += 'k';
        }
        else if (currChar == 11) {
            decipher += 'l';
        }
        else if (currChar == 12) {
            decipher += 'm';
        }
        else if (currChar == 13) {
            decipher += 'n';
        }
        else if (currChar == 14) {
            decipher += 'o';
        }
        else if (currChar == 15) {
            decipher += 'p';
        }
        else if (currChar == 16) {
            decipher += 'q';
        }
        else if (currChar == 17) {
            decipher += 'r';
        }
        else if (currChar == 18) {
            decipher += 's';
        }
        else if (currChar == 19) {
            decipher += 't';
        }
        else if (currChar == 20) {
            decipher += 'u';
        }
        else if (currChar == 21) {
            decipher += 'v';
        }
        else if (currChar == 22) {
            decipher += 'w';
        }
        else if (currChar == 23) {
            decipher += 'x';
        }
        else if (currChar == 24) {
            decipher += 'y';
        }
        else {
            decipher += 'z';
        }
    }

    // Prints out the deciphered message.
    cout << "==> DECIPHERED MESSAGE:  " << decipher << endl;;
    cout << "==> IN READABLE FORMAT:  The department of justice has been and will always be committed to protecting the liberty and security of those whom we serve.  ";
    cout << "In recent months however we have on a new scale seen mainstream products and services designed in a way that gives users sole control over access to their data.  ";
    cout << "As a result law enforcement is sometimes unable to recover the content of electronic communications from the technology provider even in response to a court order or duly authorized warrant issued by a federal judge.  ";
    cout << "For example many communications services now encrypt certain communications by default with the key necessary to decrypt the communications solely in the hands of the end user.  ";
    cout << "This applies both when the data is in motion over electronic networks or at rest on an electronic device.  ";
    cout << "If the communications provider is served with a warrant seeking those communications the provider cannot provide the data because it has designed the technology such that it cannot be accessed by any third party.  ";
    cout << "We dont have any silver bullet and the discussions within the executive branch are still ongoing.  ";
    cout << "While there has not yet been a decision whether to seek legislation we must work with congress industry academics privacy groups and others to craft an approach that addresses all of the multiple competing legitimate concerns that have been the focus of so much debate in recent months.  ";
    cout << "But we can all agree that we will need ongoing honest and informed public debate about how best to protect liberty and security in both our laws and our technology." << endl;
}

/*
 * Prints dividers for Part 1.
 */
void printDivider() {
    cout << "-------------------------------------------------------------------------------------------------------------------------------";
    cout << "--------------------------------------------------------------------" << endl;
    cout << "m = " << (currM + 1) << "\n" << endl;
}

/*
 * Prints dividers between each part.
 */
void printPartDivider() {
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;
}
