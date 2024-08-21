#include "header.h"
#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>

#pragma pack(push, 1)
struct BMPFileHeader {
    uint16_t fileType;
    uint32_t fileSize;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offsetData;

    BMPFileHeader()
        : fileType(0x4D42), fileSize(0), reserved1(0), reserved2(0), offsetData(0) {}
};

struct BMPInfoHeader {
    uint32_t size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitCount;
    uint32_t compression;
    uint32_t sizeImage;
    int32_t xPixelsPerMeter;
    int32_t yPixelsPerMeter;
    uint32_t colorsUsed;
    uint32_t colorsImportant;

    BMPInfoHeader()
        : size(40), width(0), height(0), planes(1), bitCount(4),
          compression(0), sizeImage(0), xPixelsPerMeter(0), yPixelsPerMeter(0),
          colorsUsed(5), colorsImportant(5) {}
};

struct BMPColorTableEntry {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
    uint8_t reserved;

    BMPColorTableEntry(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0)
        : blue(b), green(g), red(r), reserved(0) {}
};
#pragma pack(pop)

void fillBMP(const twoAxesGrid & grid, int numberIncrease) {
    const int32_t width = grid.width;
    const int32_t height = grid.height;

    BMPColorTableEntry colorTable[5] = {
        BMPColorTableEntry(255, 255, 255),
        BMPColorTableEntry(0, 255, 0),
        BMPColorTableEntry(255, 255, 0),
        BMPColorTableEntry(128, 0, 128),
        BMPColorTableEntry(0, 0, 0)
    };

    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;

    infoHeader.width = width;
    infoHeader.height = -height;

    // Выравнивание строки на 4 байта
    int rowSize = ((width + 1) / 2 + 3) & ~3;
    infoHeader.sizeImage = rowSize * height;
    fileHeader.offsetData = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + sizeof(colorTable);
    fileHeader.fileSize = fileHeader.offsetData + infoHeader.sizeImage;

    std::vector<uint8_t> pixelData(rowSize * height, 0);

    // Заполнение данных изображения (строки идут снизу вверх)
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < (width + 1) / 2; ++j) {
            if (grid.twoAxesArray[i][j * 2] <= 4 && grid.twoAxesArray[i][j * 2 + 1] <= 4) {
                pixelData[i * rowSize + j] = (grid.twoAxesArray[i][j * 2] << 4) | grid.twoAxesArray[i][j * 2 + 1];
            }
            else if(grid.twoAxesArray[i][j * 2] > 4 && grid.twoAxesArray[i][j * 2 + 1] > 4) {
                pixelData[i * rowSize + j] = (4 << 4) | 4;
            }
            else{
                if(grid.twoAxesArray[i][j * 2] > 4)
                    pixelData[i * rowSize + j] = (4 << 4) | grid.twoAxesArray[i][j * 2 + 1];
                else
                    pixelData[i * rowSize + j] = (grid.twoAxesArray[i][j * 2] << 4) | 4;
            }
        }
    }

    std::string direct = grid.bmpDirect;
    std::string filename = direct + "output" + std::to_string(numberIncrease) + ".bmp";

    std::ofstream outFile(filename, std::ios::binary);

    if (!outFile) {
        std::cerr << "Ошибка: не удалось создать файл!" << std::endl;
        return;
    }

    outFile.write(reinterpret_cast<const char*>(&fileHeader), sizeof(fileHeader));
    outFile.write(reinterpret_cast<const char*>(&infoHeader), sizeof(infoHeader));
    outFile.write(reinterpret_cast<const char*>(colorTable), sizeof(colorTable));
    outFile.write(reinterpret_cast<const char*>(pixelData.data()), pixelData.size());

    outFile.close();
    std::cout << "Файл BMP успешно создан!" << std::endl;

    return;
}
