// Cedric Nagata
// nagatac@uw.edu

#include <fstream>
#include <iostream>

#include <string>
#include <map>
#include <algorithm>

using namespace std;

// function to print out values in map
void PrintOut(const pair<string, int> &word) {
    cout << word.first << " " << word.second << endl;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        cout << "Argument Input is Invalid" << endl;
        exit(EXIT_FAILURE);
    }

    string file_name = argv[1]; // get file name

    ifstream file(file_name.c_str()); // try to open file
    if (!file.is_open()) {
        cout << "Couldn't open file" << endl;
        exit(EXIT_FAILURE);
    }

    map<string, int> word_inv; //initialize map
    string word;

    while (file >> word) {
        if (word_inv.count(word)) { // if map contains word increment
            word_inv[word]++;
        } else { // if not then create new key
            word_inv.insert(pair<string, int>(word, 1));
        }
    }

    // apply print function to each word in map
    for_each(word_inv.begin(), word_inv.end(), &PrintOut);
    
    file.close();
    
    return EXIT_SUCCESS;
}