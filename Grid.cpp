#include "header.h"

twoAxesGrid::twoAxesGrid(int x, int y, int count, char* outputDirectory) {
    height = y + 1;
    width = x + 1;
    bmpDirect = outputDirectory;

    twoAxesArray = new int*[height];
    for (int i = 0; i < height; ++i) {
        twoAxesArray[i] = new int[width];
    }

    twoAxesArray[y][x] = count;
}
twoAxesGrid::twoAxesGrid(const twoAxesGrid & other) {
    this->height = other.height;
    this->width = other.width;
    this->bmpDirect = other.bmpDirect;

    twoAxesArray = new int*[height];

    for (int i = 0; i < height; ++i) {
        twoAxesArray[i] = new int[width];
        for (int j = 0; j < width; ++j) {
            this->twoAxesArray[i][j] = other.twoAxesArray[i][j];
        }
    }
}
twoAxesGrid::twoAxesGrid(char* outputDirectory) {
    height = 1;
    width = 1;
    bmpDirect = outputDirectory;

    twoAxesArray = new int*[height];
    for (int i = 0; i < height; ++i) {
        twoAxesArray[i] = new int[width];
    }
}
twoAxesGrid::~twoAxesGrid() {
    deleteDynamicMemory(*this);
}

void twoAxesGrid::deleteDynamicMemory(twoAxesGrid & obj) {
    if(obj.twoAxesArray != nullptr) {
        for (int i = obj.height - 1; i >= 0; i--) {
            delete [] obj.twoAxesArray[i];
        }
    }
    delete [] obj.twoAxesArray;
}

twoAxesGrid & twoAxesGrid::operator = (twoAxesGrid && other){
    this->twoAxesArray = other.twoAxesArray;
    other.twoAxesArray = nullptr;
    this->height = other.height;
    this->width = other.width;
    this->bmpDirect = other.bmpDirect;
    return *this;
}

twoAxesGrid & twoAxesGrid::operator = (const twoAxesGrid & other) {
    if(twoAxesArray != nullptr) {
        for (int i = height - 1; i >= 0; i--) {
            delete [] twoAxesArray[i];
        }
    }
    delete [] twoAxesArray;

    this->height = other.height;
    this->width = other.width;
    this->bmpDirect = other.bmpDirect;

    twoAxesArray = new int*[height];

    for (int i = 0; i < height; ++i) {
        twoAxesArray[i] = new int[width];
        for (int j = 0; j < width; ++j) {
            this->twoAxesArray[i][j] = other.twoAxesArray[i][j];
        }
    }
    return *this;
}

void twoAxesGrid::printArray() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (twoAxesArray[i][j]) {
                std::cout<<twoAxesArray[i][j]<<'\t';
            }
            else
                std::cout<<'-'<<'\t';
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}

void twoAxesGrid::update() {
    twoAxesGrid temp(*this);
    bool increaseUp = false, increaseDown = false,
    increaseLeft = false, increaseRight = false;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (twoAxesArray[i][j] > 3) {
                if (i == 0 && !increaseUp) {
                    increaseLineToTheTop(temp);
                    increaseUp = true;
                }
                if (i == height - 1 && !increaseDown) {
                    increaseLineToTheDown(temp);
                    increaseDown = true;
                }
                if (j == 0 && !increaseLeft) {
                    increaseColumnToTheLeft(temp);
                    increaseLeft = true;
                }
                if (j == width - 1 && !increaseRight) {
                    increaseColumnToTheRight(temp);
                    increaseRight = true;
                }
                temp.twoAxesArray[i + increaseUp][j + increaseLeft] -= 4;

                temp.twoAxesArray[i + increaseUp - 1][j + increaseLeft] += 1;
                temp.twoAxesArray[i + increaseUp + 1][j + increaseLeft] += 1;
                temp.twoAxesArray[i + increaseUp][j + increaseLeft - 1] += 1;
                temp.twoAxesArray[i + increaseUp][j + increaseLeft + 1] += 1;
            }
        }
    }

    *this = temp;
}

void twoAxesGrid::makeChanges(const int numberOfIterations, const int outputRate) {
    int counter = 0;
    const bool onceOut = !outputRate;
    const bool noLimitIterations = !numberOfIterations;

    while (canChange() && (counter < numberOfIterations || noLimitIterations)) {
        counter++;
        if (!onceOut) {
            if(!(counter % outputRate)) {
                //printArray();
                fillBMP(*this, counter);
            }
        }
        update();
    }
    printArray();
    fillBMP(*this, counter);
}

void twoAxesGrid::addPoint(const int x, const int y, const int count) {
    if (x + 1 > width || y + 1 > height) {
        const twoAxesGrid copy(*this);
        deleteDynamicMemory(*this);
        height = y + 1;
        width = x + 1;

        twoAxesArray = new int*[height];
        for (int i = 0; i < height; ++i) {
            twoAxesArray[i] = new int[width];
            for (int j = 0; j < width; ++j) {
                if(i < copy.height && j < copy.width) {
                    twoAxesArray[i][j] = copy.twoAxesArray[i][j];
                }
                else {
                    twoAxesArray[i][j] = 0;
                }
            }
        }
    }
    twoAxesArray[y][x] += count;
}

bool twoAxesGrid::canChange() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if(twoAxesArray[i][j] > 3) {
                return true;
            }
        }
    }
    return false;
}

void twoAxesGrid::increaseLineToTheTop(twoAxesGrid & temp) {
    const twoAxesGrid result(temp);
    deleteDynamicMemory(temp);
    temp.height = result.height + 1;

    temp.twoAxesArray = new int*[temp.height];
    for (int i = 0; i < temp.height; ++i) {
        temp.twoAxesArray[i] = new int[temp.width];
        for (int j = 0; j < temp.width; ++j) {
            if(i == 0) {
                temp.twoAxesArray[i][j] = 0;
            }
            else {
                temp.twoAxesArray[i][j] = result.twoAxesArray[i - 1][j];
            }
        }
    }
}
void twoAxesGrid::increaseLineToTheDown(twoAxesGrid &temp) {
    const twoAxesGrid result(temp);
    deleteDynamicMemory(temp);
    temp.height = result.height + 1;

    temp.twoAxesArray = new int*[temp.height];
    for (int i = 0; i < temp.height; ++i) {
        temp.twoAxesArray[i] = new int[temp.width];
        for (int j = 0; j < temp.width; ++j) {
            if(i == temp.height - 1) {
                temp.twoAxesArray[i][j] = 0;
            }
            else {
                temp.twoAxesArray[i][j] = result.twoAxesArray[i][j];
            }
        }
    }
}
void twoAxesGrid::increaseColumnToTheLeft(twoAxesGrid &temp) {
    const twoAxesGrid result(temp);
    deleteDynamicMemory(temp);
    temp.width = result.width + 1;

    temp.twoAxesArray = new int*[temp.height];
    for (int i = 0; i < temp.height; ++i) {
        temp.twoAxesArray[i] = new int[temp.width];
        for (int j = 0; j < temp.width; ++j) {
            if(j == 0) {
                temp.twoAxesArray[i][j] = 0;
            }
            else {
                temp.twoAxesArray[i][j] = result.twoAxesArray[i][j - 1];
            }
        }
    }
}
void twoAxesGrid::increaseColumnToTheRight(twoAxesGrid &temp) {
    const twoAxesGrid result(temp);
    deleteDynamicMemory(temp);
    temp.width = result.width + 1;

    temp.twoAxesArray = new int*[temp.height];
    for (int i = 0; i < temp.height; ++i) {
        temp.twoAxesArray[i] = new int[temp.width];
        for (int j = 0; j < temp.width; ++j) {
            if(j == temp.width - 1) {
                temp.twoAxesArray[i][j] = 0;
            }
            else {
                temp.twoAxesArray[i][j] = result.twoAxesArray[i][j];
            }
        }
    }
}
