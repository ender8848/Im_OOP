//
// Created by 85378 on 5/7/2022.
//

#ifndef OOP2020_ANSWER2_H
#define OOP2020_ANSWER2_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

class Cell {
protected:
    std::string content;
public:
    Cell() = default;
    virtual void constructContent() = 0;
    void print(int cellWidth, char errorChar) {
        constructContent();
        if (content.length() > cellWidth){
            for (int i = 0; i < cellWidth; i++) { std::cout << errorChar; }
        } else {
            std::cout.width(cellWidth);
            std::cout << std::left << content;
        }
    };
};

class TextCell : public Cell {
protected:
    std::string text;
public:
    TextCell(std::string const &text):text(text) {}
    void constructContent() override {content = text;} // no need to do anything
};

class CurrencyCell : public Cell {
private:
    std::string postfix;
    double const value;
    int const precision;
    int const spaceNum;
public:
    CurrencyCell(const std::string &postfix, double value, int precision = 2, int spaceNum = 0):
            postfix(postfix), value(value), precision(precision), spaceNum(spaceNum) {}

    void constructContent() override {
        std::stringstream stream;
        stream << std::fixed << std::setprecision(precision) << value;
        for (int i = 0; i < spaceNum; i++) { content += " "; }
        content += stream.str() + " " + postfix;
    }
};

class DurationCell: public Cell {
private:
    int minutes;
public:
    DurationCell(int minutes) : minutes(minutes) {}

    void constructContent() override {
        content = std::to_string(minutes/60) + ":" + std::to_string(minutes%60) ;
    }
};


template <char errorChar, int cellWidth>
class Table {
private:
    int maxRow;
    int maxCol;
    int row = 0, col = 0;
    std::vector<std::vector<Cell*>> cells;

public:
    Table(int rows, int cols): maxRow(rows), maxCol(cols){
        cells = std::vector<std::vector<Cell*>>(rows, std::vector<Cell*>(cols));
    }

    void addCell(Cell* pCell) {
        cells[row][col] = pCell;
        row += ++col/maxCol;
        col %= maxCol;
    }

    void print() {
        for (int i = 0; i < maxRow; i++) {
            for (int j = 0; j < maxCol; j++) {
                std::cout << '|';
                cells[i][j]->print(cellWidth, errorChar);
            }
            std::cout << '|' << std::endl;
        }
    }

    virtual ~Table() {
        for (int i = 0; i < maxRow; i++) {
            for (int j = 0; j < maxCol; j++) {
                if (cells[i][j] != nullptr) {
                    delete cells[i][j];
                }
            }
        }
    }
};


#endif //OOP2020_ANSWER2_H
