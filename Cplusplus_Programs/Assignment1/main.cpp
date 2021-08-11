#include <iostream>
#include <fstream>
#include <sstream>

//using namespace std;

// On my honor:
//
// - I have not discussed the C++ language code in my program with
//   anyone other than my instructor or the teaching assistants
//   assigned to this course.
//
// - I have not used C++ language code obtained from another student,
//   or any other unauthorized source, either modified or unmodified.
//
// - If any C++ language code or documentation used in my program
//   was obtained from an allowed source, such as a text book or course
//   notes, that has been clearly noted with a proper citation in
//   the comments of my program.
//
//    <Mike Silvasy>

int main()
{
    //The following code block prompts the user to enter an input file.
    std::string inputFileName;
    std::cout << "Please enter the name of the input file:  ";
    std::cin >> inputFileName;
    std::cout << std::endl;

    //This code block opens the file inputted by the user.
    std::ifstream inputFile(inputFileName.c_str());

    //This code block prime reads the file.
    std::string num;
    std::getline(inputFile, num);

    //This code block sets the boolean fileExists to false if the inputted file
    //could not be found and outputs "Could not find file or file is empty."
    bool fileExists = true;
    if (!inputFile) {
        std::cout << "Could not find file or file is empty." << std::endl;
        fileExists = false;
    }

    //The following will be done while there is more to read in the input file.
    while (inputFile) {
        //Outputs "Decoded message:"
        std::cout << "Decoded message:" << std::endl;

        //Creates an integer object that saves the number of words to decode.
        int numWords;
        std::istringstream iss(num);
        iss >> numWords;

        //For how ever many words there are to be decoded, a line will be read
        //from the input file.  Afterwards, the line is parsed by each white
        //space and every two adjacent ints are added together to get the ASCII
        //value of a char.  All of these chars are combined to create a word.
        std::string charNums;
        for (int i = 0; i < numWords; i += 1) {
            std::getline(inputFile, charNums);
            int c1, c2;
            std::stringstream ss(charNums);
            ss >> c1 >> c2;
            while (ss) {
                std::cout << char(c1 + c2);
                ss >> c1 >> c2;
            }

            //If this line is not the last word to read, a space is added to
            //separate the words in the decoded message.
            if (i < numWords - 1) {
                std::cout << " ";
            }
        }

        //getline() is called twice to get to the next message.
        std::getline(inputFile, num);
        std::getline(inputFile, num);
        std::cout << "\n" << std::endl;
    }

    //If the file inputted exists and contains text, "You've reached the end
    //of the file!" is outputted.
    if (fileExists) {
        std::cout << "You've reached the end of the file!" << std::endl;
    }

    return 0;
}
