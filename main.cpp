#include "header.h"

using namespace std;

char* tsvFileDirectory;
char* bmpFileDirectory;
int maxIterations = 0;
int freqIterations = 0;

void collectValuesFromTSV(twoAxesGrid & grid, const char* filename) {
    ifstream fileTSV(filename);
    if (!fileTSV.is_open()) {
        std::cerr << "Incorrect filename" << std::endl;
        return;
    }

    int variables[3]{}, counter = 0;
    string line;
    while (getline(fileTSV, line)) {
        istringstream linestream(line);
        string field;
        while (getline(linestream, field, '\t') && counter < 3) {
            variables[counter] = stoi(field);
            counter++;
        }
        grid.addPoint(variables[0], variables[1], variables[2]);
        counter = 0;
    }
}

void fillTheVariabels(char** value) {
    if (stringIsEqual(*value, "-i", 2) || stringIsEqual(*value, "--input", 7)) {
        tsvFileDirectory = *(value + 1);
    }
    else if (stringIsEqual(*value, "-o", 2) || stringIsEqual(*value, "--output", 8)) {
        bmpFileDirectory = *(value + 1);
    }
    else if (stringIsEqual(*value, "-m", 2) || stringIsEqual(*value, "--max-iter", 10)) {
        maxIterations = stoi((*(value + 1)));
    }
    else if (stringIsEqual(*value, "-f", 2) || stringIsEqual(*value, "--freq", 6)) {
        freqIterations = stoi((*(value + 1)));
    }
}

bool stringIsEqual(char* firstString, char* secondSrting, int length) {
    if (std::strlen(firstString) == length) {
        for (int i = 0; i < length; i++) {
            if (firstString[i] != secondSrting[i]) {
                return false;
            }
        }
        return true;
    }
    return false;

}


int main(int argc, char** argv)
{

    for (int i = 1; i < argc; i++) {
        fillTheVariabels(argv + i);
    }

    twoAxesGrid grid(bmpFileDirectory);

    collectValuesFromTSV(grid, tsvFileDirectory);

    grid.makeChanges(maxIterations, freqIterations);

    return 0;
}



