#include <iostream>
#include "SpreadSheet.h"

void test_cell_constructors() {
    cell c1;
    cell c2(42);
    cell c3("Hello");
    cell c4(3.14);

    std::cout << c1 << std::endl;
    std::cout << c2 << std::endl;
    std::cout << c3 << std::endl;
    std::cout << c4 << std::endl;
}

void test_cell_operators() {
    cell c1;
    c1 = 42;
    cell c2;
    c2 = "World";
    cell c3;
    c3 = 3.14;

    cell c4(42);
    cell c5(42);
    std::cout << (c4 == c5) << std::endl;

    cell c6(42);
    int val = c6;
    std::cout << val << std::endl;
    std::string str = c6;
    std::cout << str << std::endl;
    double dval = c6;
    std::cout << dval << std::endl;
}

void test_SpreadSheet_constructors() {
    SpreadSheet sheet1;
    SpreadSheet sheet2(3);
    SpreadSheet sheet3(2, 4);

    std::cout << "Rows in sheet1: " << sheet1.row() << ", Cols in sheet1: " << sheet1.col() << std::endl;
    std::cout << "Rows in sheet2: " << sheet2.row() << ", Cols in sheet2: " << sheet2.col() << std::endl;
    std::cout << "Rows in sheet3: " << sheet3.row() << ", Cols in sheet3: " << sheet3.col() << std::endl;
}

void test_SpreadSheet_operations() {
    SpreadSheet sheet(3, 3);

    sheet[0][0] = 10;
    sheet[0][1] = 20;
    sheet[0][2] = 30;
    sheet[1][0] = 40;
    sheet[1][1] = 50;
    sheet[1][2] = 60;
    sheet[2][0] = 70;
    sheet[2][1] = 80;
    sheet[2][2] = 90;


    std::cout << "SpreadSheet content:" << std::endl;
    std::cout << sheet << std::endl;

    sheet.resizeRow(4);
    sheet.resizeCol(7);
    std::cout << "SpreadSheet after resizing:" << std::endl;
    std::cout << sheet << std::endl;
}

void test_SpreadSheet_operations2(){
    SpreadSheet sheet(3, 3);
  
    int num = 0;
    for (std::size_t i = 0; i < sheet.row(); ++i) {
        for (std::size_t j = 0; j < sheet.col(); ++j) {
            sheet[i][j] = num++;
        }
    }

    std::cout << "Original SpreadSheet content:" << std::endl;
    std::cout << sheet << std::endl;

    std::cout << "SpreadSheet after resizing rows:" << std::endl;
    sheet.resizeRow(5);
    std::cout << sheet << std::endl;

    std::cout << "SpreadSheet after resizing cols:" << std::endl;
    sheet.resizeCol(4);
    std::cout << sheet << std::endl;

    std::cout << "SpreadSheet after resizing both rows and cols:" << std::endl;
    sheet.resize(2, 2);
    std::cout << sheet << std::endl;

    std::cout << "Number of rows: " << sheet.row() << std::endl;
    std::cout << "Number of cols: " << sheet.col() << std::endl;

    //SpreadSheet copy(sheet);

    // std::cout << "Is the original SpreadSheet equal to the copy? " << (sheet == copy) << std::endl;
    // std::cout << "Is the original SpreadSheet not equal to the copy? " << (sheet != copy) << std::endl;

    // std::cout << "SpreadSheet after rotating:" << std::endl;
    // sheet.rotate(1);
    // std::cout << sheet << std::endl;

    // std::cout << "SpreadSheet after horizontal mirror:" << std::endl;
    // sheet.mirrorh();
    // std::cout << sheet << std::endl;

    // std::cout << "SpreadSheet after vertical mirror:" << std::endl;
    // sheet.mirrorv();
    // std::cout << sheet << std::endl;

    // std::cout << "SpreadSheet after main diagonal mirror:" << std::endl;
    // sheet.mirrorD();
    // std::cout << sheet << std::endl;

    // std::cout << "SpreadSheet after anti-diagonal mirror:" << std::endl;
    // sheet.mirrord();
    // std::cout << sheet << std::endl;

    // std::cout << "SpreadSheet after removing row 1 and col 1:" << std::endl;
    // sheet.removeRow(1);
    // sheet.removeCol(1);
    // std::cout << sheet << std::endl;

    // std::cout << "Slice of SpreadSheet:" << std::endl;
    // SpreadSheet& slicedSheet = sheet.slice({0}, {0, 2});
    // std::cout << slicedSheet << std::endl;
}



int main() {

    test_cell_constructors();
    test_cell_operators();
    test_SpreadSheet_constructors();
    test_SpreadSheet_operations();
    test_SpreadSheet_operations2();
    

    return 0;
}
