#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>

using namespace std;

/**
 * Populates a vector with all the lines in a file
 * @param ref to vector of strings vec
 * @return none
 */
void getVectorFromFile(vector<string> &vec);

/**
 * Calculates file statistics from a vector of lines
 * @param reference to vector of lines, reference to a vector for file stats
 * @return none
 */
void calculateFileStats(vector<string> &vec, vector<int> &stats);

/**
 * Adds sentence to the file
 * @param sentence
 */
void addToFile(string sentence);

int main(int argc, char* argv[]) {
    //get input from command line
    int choice = stoi(argv[1]);
    //declare vectors to alter
    vector<string> text;
    vector<int> textStats;

    //create text area
    cout << "<textarea name=\"text-body\" rows=\"15\" cols=\"100\">";
    //0 is new, 2 is update, 4 is add random sentence, 5 is download
    if (choice == 0 || choice == 2 || choice == 4 || choice == 5) {
        getVectorFromFile(text);
        for (int i = 0; i < text.size(); ++i) {
            cout << text.at(i);
        }
    }
    //add the sentence
    if (choice == 4) {
        //seed random
        srand(time(0));
        //declare vectors of word types
        vector<string> verbs;
        vector<string> nouns;
        vector<string> adjectives;
        vector<string> misc;
        //other variables
        int option;
        string sentence;

        //populate them
        verbs.push_back("runs");
        verbs.push_back("jumps");
        verbs.push_back("walks");
        verbs.push_back("speaks");
        verbs.push_back("drinks");
        verbs.push_back("games");
        verbs.push_back("eats");
        verbs.push_back("fights");
        verbs.push_back("wins");
        verbs.push_back("loses");

        nouns.push_back("dog");
        nouns.push_back("man");
        nouns.push_back("woman");
        nouns.push_back("cat");
        nouns.push_back("she");
        nouns.push_back("house");
        nouns.push_back("car");
        nouns.push_back("food");
        nouns.push_back("computer");
        nouns.push_back("he");

        adjectives.push_back("BIGLY");
        adjectives.push_back("slowly");
        adjectives.push_back("quickly");
        adjectives.push_back("white");
        adjectives.push_back("black");
        adjectives.push_back("yellow");
        adjectives.push_back("cold");
        adjectives.push_back("hot");
        adjectives.push_back("small");
        adjectives.push_back("big");

        misc.push_back("a");
        misc.push_back("it");
        misc.push_back("to");
        misc.push_back("has");
        misc.push_back("for");
        misc.push_back("with");
        misc.push_back("of");
        misc.push_back("at");
        misc.push_back("an");
        misc.push_back("and");

        //generate random number
        option = rand() % 4;

        //create different sentence structures
        if (option == 0) {
            //create the sentence
            sentence = nouns[rand() % 10] + " " + verbs[rand() % 10] + " " +
                    misc[rand() % 10] + " " + nouns[rand() % 10] + ".";

            //add to file
            addToFile(sentence);
            //add to vector
            text.push_back(sentence);
            //add to the textarea
            cout << sentence;
        }
        else if (option == 1) {
            //create the sentence
            sentence = misc[rand() % 10] + " " + adjectives[rand() % 10] + " " + nouns[rand() % 10] + " " +
                    verbs[rand() % 10] + ", " + misc[rand() % 10] + " " + nouns[rand() % 10] + " " +
                    verbs[rand() % 10] + ".";

            //add to file
            addToFile(sentence);
            //add to vector
            text.push_back(sentence);
            //add to the textarea
            cout << sentence;
        }
        else if (option == 2) {
            //create the sentence
            sentence = adjectives[rand() % 10] + " " + nouns[rand() % 10] + " " + misc[rand() % 10] + " " +
                    nouns[rand() % 10] + ".";

            //add to file
            addToFile(sentence);
            //add to vector
            text.push_back(sentence);
            //add to the textarea
            cout << sentence;
        }
        else {
            //create the sentence
            sentence = nouns[rand() % 10] + " " + misc[rand() % 10] + " " + adjectives[rand() % 10] + " " +
                    nouns[rand() % 10] + " " + verbs[rand() % 10] + " " +
                    misc[rand() % 10]  + " " + nouns[rand() % 10] + ".";

            //add to file
            addToFile(sentence);
            //add to vector
            text.push_back(sentence);
            //add to the textarea
            cout << sentence;
        }
    }
    cout << "</textarea>";
    //generate stats from vector
    calculateFileStats(text, textStats);
    cout << "☐ " << textStats.at(0);
    cout << "☐" << textStats.at(1);
    cout << "☐" << textStats.at(2);
    cout << "☐";
    return 0;
}

void getVectorFromFile(vector<string> &vec) {
    //open file
    ifstream infile;
    infile.open("edit.txt");

    //make a temp string to store lines
    string temp;

    //get all the lines from the file, and add a newline since getline removes it
    while (infile.peek() != EOF) {
        getline(infile, temp);
        temp += "\n";
        vec.push_back(temp);
    }
    //close the file
    infile.close();
}

void calculateFileStats(vector<string> &vec, vector<int> &stats) {
    // statistics calculated from a file
    // 0. letters
    // 1. words
    // 2. lines

    string word;
    int letterCount = 0, wordCount = 0;
    for (string &line : vec) {
        // search for letters
        for (char &c : line) {
            if (isalpha(c)) {
                ++letterCount;
            }
        }
        // search for words
        stringstream isString(line);
        while (isString >> word) {
             ++wordCount;
        }
    }

    //populate vector
    stats.push_back(letterCount);
    stats.push_back(wordCount);
    stats.push_back(vec.size());
}

void addToFile(string sentence) {
    //open file
    ofstream outfile;
    outfile.open("edit.txt", ios_base::app);

    //add the sentence
    outfile << endl << sentence;

    //close the file
    outfile.close();
}
