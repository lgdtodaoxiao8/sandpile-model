#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class twoAxesGrid {
    int ** twoAxesArray;
    int height;
    int width;

    char* bmpDirect;

    void deleteDynamicMemory(twoAxesGrid & obj);

    void update();
    bool canChange();

    void increaseLineToTheTop(twoAxesGrid & temp);
    void increaseLineToTheDown(twoAxesGrid & temp);
    void increaseColumnToTheRight(twoAxesGrid & temp);
    void increaseColumnToTheLeft(twoAxesGrid & temp);
public:
    twoAxesGrid(int x, int y, int count, char* outputDirectory);
    twoAxesGrid(const twoAxesGrid & other);
    twoAxesGrid(char* outputDirectory);
    ~twoAxesGrid();

    twoAxesGrid & operator = (twoAxesGrid && other);
    twoAxesGrid & operator = (const twoAxesGrid & other);

    void printArray();
    void makeChanges(int numberOfIterations, int outputRate);
    void addPoint(int x, int y, int count);

    friend void fillBMP(const twoAxesGrid & grid, int numberIncrease);
};

void fillBMP(const twoAxesGrid & grid, int numberIncrease);
bool stringIsEqual(char* firstString, char* secondSrting, int length);
void fillTheVariabels(char** value);