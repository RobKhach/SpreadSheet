#include <iostream>
#include <iomanip>
#include "SpreadSheet.h"

cell::cell(){}

cell::cell(int val){
    this->val =std::to_string(val);
}

cell::cell(std::string val){
    this->val = val;
}

cell::cell(double val){
    this->val = std::to_string(val);
}

cell::cell(const cell& rhv) : val(rhv.val){}

cell::cell(cell&& rhv) : val(std::move(rhv.val)){}

cell& cell::operator=(int val){
    this->val = std::to_string(val);
    return *this;
}

cell& cell::operator=(double val){
    this->val = std::to_string(val);
        return *this;

}

cell& cell::operator=(std::string val){
    this->val = val;
        return *this;

}

cell& cell::operator=(cell&& rhv){
    this->val = rhv.val;
    return *this;
}

cell& cell::operator=(char rhv){
    val = rhv;
    return *this;
}

cell& cell::operator=(bool rhv){
    val = (rhv) ? 1  : 0 ;
    return * this;
}
cell& cell::operator=(const std::vector<int>& rhv){
    
    val.clear();
    for(auto it : rhv){
        val += std::to_string(it);
    }
    return *this;
}

cell& cell::operator=(const cell& rhv){
    this->val = rhv.val;
    return *this;
}

bool cell::operator==(const cell& rhv){
    return this->val == rhv.val;
}

bool cell::operator!=(const cell& rhv){
    return this->val != rhv.val;
}

std::ostream& operator<<(std::ostream& os, const cell& data){
    os << data.val;
    return os;
}

cell::operator int() const{
    return std::stoi(val);
}

cell::operator double() const{
    return std::stod(val);
}

cell::operator std::string() const{
    return val;
}
cell::operator std::vector<int>() {

        std::vector<int> result;
        result.push_back(std::stoi(val));
        return result;
}

SpreadSheet::SpreadSheet(){

    cols = rows = 2;

    Sheet = new cell*[rows];
    for(std::size_t i = 0; i < rows; ++i){
            Sheet[i] = new cell[cols];
    }

}


SpreadSheet::SpreadSheet(std::size_t size){
    cols = rows = size;

    Sheet = new cell*[rows];

    for(std::size_t i = 0; i < rows; ++i){
        Sheet[i] = new cell[cols];
    }

}

SpreadSheet::SpreadSheet(std::size_t row, std::size_t col): rows(row), cols(col){
    Sheet = new cell*[rows];

    for(std::size_t i = 0; i < rows; ++i){
        Sheet[i] = new cell[cols];
    }
}

SpreadSheet::SpreadSheet(const SpreadSheet& rhv): rows(rhv.rows), cols(rhv.cols){
    Sheet = new cell*[rows];

    for(std::size_t i = 0; i < rows; ++i){
        Sheet[i] = new cell[cols];
    }

    for(std::size_t i = 0; i < rows; ++i){
        for(std::size_t j = 0; j < cols; ++j){
            Sheet[i][j] = rhv.Sheet[i][j];
        }
    }
}

SpreadSheet::SpreadSheet(SpreadSheet&& rhv): Sheet(std::move(rhv.Sheet)), rows(std::move(rhv.rows)), cols(std::move(rhv.cols)){
  
    rhv.Sheet = nullptr;
    rhv.rows = 0;
    rhv.cols = 0;
}

SpreadSheet::~SpreadSheet(){

    for(std::size_t i = 0; i < rows; ++i){
        delete[] Sheet[i];
    }
    delete[] Sheet;
}



SpreadSheet::ProxyRow::ProxyRow(cell* row): row(row){}

 cell& SpreadSheet::ProxyRow::operator[](std::size_t colindex){
    return row[colindex];
 }

 SpreadSheet::ProxyRow SpreadSheet::operator[](std::size_t rowindex){
    if(rowindex >= rows){
        std::cout << "out off range" <<std::endl;
        throw std::out_of_range("Row index out of range");

    }else{
        return ProxyRow(Sheet[rowindex]);
    }
 }

 void SpreadSheet::resizeRow(std::size_t size){
     
    cell** newSheet = new cell*[size];

    for(std::size_t i = 0; i < size; ++i){
        newSheet[i] = new cell[cols];
    }

    for(std::size_t i = 0; i < size; ++i){
        for(std::size_t j = 0; j < cols; ++j){
            if(i >= rows){
                rows = size;
                delete[] Sheet;
                Sheet = newSheet;
                return;
            }

            newSheet[i][j] = Sheet[i][j];
        }
    }

    for(std::size_t i = 0; i < rows; ++i){
         delete[] Sheet[i];
    }
    rows = size;
    delete[] Sheet;
    Sheet = newSheet;
     

}

void SpreadSheet::resizeCol(std::size_t size) {
    cell** newSheet = new cell*[rows];
    for (std::size_t i = 0; i < rows; ++i) {
        newSheet[i] = new cell[size];
    }

    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < size; ++j) {
            if (j < cols) {
                newSheet[i][j] = Sheet[i][j];
            } else {
                newSheet[i][j] = cell();
            }
        }
    }

    for (std::size_t i = 0; i < rows; ++i) {
        delete[] Sheet[i];
    }
    delete[] Sheet;

    Sheet = newSheet;
    cols = size;
}

void SpreadSheet::resize(std::size_t rows_size, std::size_t cols_size){
    cell** newSheet = new cell*[rows_size];

    for(std::size_t i = 0; i < rows; ++i){
        newSheet[i] = new cell[cols_size];
    }

    for(std::size_t i = 0; i < std::min(rows, rows_size); ++i){
        for(std::size_t j = 0; j < std::min(cols, cols_size); ++j){
            newSheet[i][j] = Sheet[i][j];
        }
    }

    for(std::size_t i = 0; i < rows; ++i){
         delete[] Sheet[i];
    }
    rows = rows_size;
    cols = cols_size;
    delete[] Sheet;
    Sheet = newSheet;     

}


 std::size_t SpreadSheet::row() const{
    return rows;
 }

 std::size_t SpreadSheet::col() const{
    return cols;
 }

 bool SpreadSheet::operator==(const SpreadSheet& rhv){
    if(rows != rhv.rows || cols != rhv.cols ){
        return false;
    }

    for(std::size_t i = 0; i < rows; ++i){
        for(std::size_t j = 0; j < cols; ++j){
            if(Sheet[i][j] != rhv.Sheet[i][j]){
                return false;
            }
        }
    }

    return true;
 }

 bool SpreadSheet::operator!=(const SpreadSheet& rhv){
        return !(*this == rhv);
 }

 void SpreadSheet::rotate(int reps){
    reps = reps % 4;

    for(int k = 0; k < reps; ++k){

        cell** tmpSheet = new cell*[cols];
        for(std::size_t i = 0; i < cols; ++i){
           tmpSheet[i] = new cell[rows]; 
        }

        for(std::size_t i  = 0; i < rows; ++i){
            for(std::size_t j = 0; j < cols; ++j){
                tmpSheet[j][rows - i - 1] = Sheet[i][j];
            }
        }

        for(std::size_t i = 0; i < rows; ++i){
            delete[] Sheet[i];
        }
        delete[] Sheet;

        std::swap(rows, cols);
        Sheet = tmpSheet; 

    }
 }

 void SpreadSheet::mirrorh(){

    cell** tmpsheet = new cell*[rows];
    for(std::size_t i = 0; i < rows; ++i){
        tmpsheet[i] = new cell[cols];
    }

    for(std::size_t i = 0; i < rows; ++i){
        for(std::size_t j = 0; j < cols; ++j){
            tmpsheet[i][j] = Sheet[rows - i - 1][j];
        }
    }

    for(std::size_t i = 0; i < rows; ++i){
        delete[] Sheet[i];
    }
    delete[] Sheet;

    Sheet = tmpsheet;

 }

void SpreadSheet::mirrorv(){

    cell** tmpsheet = new cell*[rows];
    for(std::size_t i = 0; i < rows; ++i){
        tmpsheet[i] = new cell[cols];
    }

    for(std::size_t i = 0; i < rows; ++i){
        for(std::size_t j = 0; j < cols; ++j){
            tmpsheet[i][j] = Sheet[i][cols - j - 1];
        }
    }

    for(std::size_t i = 0; i < rows; ++i){
        delete[] Sheet[i];
    }
    delete[] Sheet;

    Sheet = tmpsheet;

 }

 void SpreadSheet::mirrorD(){

    cell** tmpSheet = new cell*[rows];
    for(std::size_t i = 0; i < rows; ++i){
        tmpSheet[i] = new cell[cols];
    }

    std::size_t tmprows = rows;
    std::size_t tmpcols = cols;

    if(tmprows > tmpcols){
        tmprows = tmpcols;
    }else if(tmprows < tmpcols){
        tmpcols = tmprows;
    }

    for(std::size_t i = 0; i < tmprows; ++i){
        for(std::size_t j = 0; j < tmpcols; ++j){
            if(i != j){
                tmpSheet[i][j] = Sheet[tmprows - i - 1][tmpcols - j - 1];
            }else{
                tmpSheet[i][j] = Sheet[i][j];
            }

        }
    }

    for(std::size_t i = 0; i < tmprows; ++i){
        for(std::size_t j = 0; j < tmpcols; ++j){
            Sheet[i][j] = tmpSheet[i][j];
        }
    }


    for(std::size_t i = 0; i < tmprows; ++i){
        delete[] tmpSheet[i];
    }
    delete[] tmpSheet;


 }


void SpreadSheet::mirrord(){

    cell** tmpSheet = new cell*[rows];
    for(std::size_t i = 0; i < rows; ++i){
        tmpSheet[i] = new cell[cols];
    }

    std::size_t tmprows = rows;
    std::size_t tmpcols = cols;

    if(tmprows > tmpcols){
        tmprows = tmpcols;
    }else if(tmprows < tmpcols){
        tmpcols = tmprows;
    }

    for(std::size_t i = 0; i < tmprows; ++i){
        for(std::size_t j = 0; j < tmpcols; ++j){
            if(i != cols - j - 1){
                tmpSheet[i][j] = Sheet[tmprows - i - 1][tmpcols - j - 1];
            }else{
                tmpSheet[i][j] = Sheet[i][j];
            }

        }
    }

    for(std::size_t i = 0; i < tmprows; ++i){
        for(std::size_t j = 0; j < tmpcols; ++j){
            Sheet[i][j] = tmpSheet[i][j];
        }
    }


    for(std::size_t i = 0; i < tmprows; ++i){
        delete[] tmpSheet[i];
    }
    delete[] tmpSheet;


 }

 void SpreadSheet::removeRow(int index){
    
    if(index >= rows){
        return;
    }

    if (rows == 0) {
        return;
    }

    cell** tmpSheet = new cell*[rows - 1];
    for(std::size_t i = 0; i < rows - 1; ++i){
        tmpSheet[i] = new cell[cols];
    }

    for(std::size_t i = 0; i < rows - 1; ++i){
        for(std::size_t j = 0; j < cols; ++j){
            if(i >= index){
                tmpSheet[i][j] = Sheet[i + 1][j];
            }else{
            tmpSheet[i][j] = Sheet[i][j];
            }
        }
    }

    --rows;
    for(std::size_t i = 0; i < rows; ++i){
        delete[] Sheet[i];
    }
    delete[] Sheet;

    Sheet = tmpSheet;


 }

  void SpreadSheet::removeCol(int index){
    
    if(index >= cols){
        return;
    }

    if (cols == 0) {
        return;
    }

    cell** tmpSheet = new cell*[rows];
    for(std::size_t i = 0; i < rows; ++i){
        tmpSheet[i] = new cell[cols - 1];
    }

    for(std::size_t i = 0; i < rows; ++i){
        for(std::size_t j = 0; j < cols - 1; ++j){
            if(j >= index){
                tmpSheet[i][j] = Sheet[i][j + 1];
            }else{
            tmpSheet[i][j] = Sheet[i][j];
            }
        }
    }

    --cols;
    for(std::size_t i = 0; i < rows; ++i){
        delete[] Sheet[i];
    }
    delete[] Sheet;

    Sheet = tmpSheet;


 }

 SpreadSheet& SpreadSheet::slice(std::initializer_list<std::size_t> row_indices, std::initializer_list<std::size_t> col_indices) {
    std::vector<std::size_t> rows_to_include(row_indices);
    std::vector<std::size_t> cols_to_include(col_indices);

    for (auto& index : rows_to_include) {
        if (index >= rows) {
            throw std::out_of_range("Row index out of range");
        }
    }

    for (auto& index : cols_to_include) {
        if (index >= cols) {
            throw std::out_of_range("Column index out of range");
        }
    }

    SpreadSheet* slicedSheet = new SpreadSheet(rows_to_include.size(), cols_to_include.size());

    for (std::size_t i = 0; i < rows_to_include.size(); ++i) {
        for (std::size_t j = 0; j < cols_to_include.size(); ++j) {
            slicedSheet->Sheet[i][j] = Sheet[rows_to_include[i]][cols_to_include[j]];
        }
    }


    return *slicedSheet;
}


std::ostream& operator<<(std::ostream& os, const SpreadSheet& sheet) {
    for (std::size_t i = 0; i < sheet.row(); ++i) {
        for (std::size_t j = 0; j < sheet.col(); ++j) {
            os << std::setw(3) << sheet.Sheet[i][j];
        }
        os << '\n'; 
    }
    return os;
}
std::istream& operator>>(std::istream& in, cell& ob){

    in >> ob.val;
    return in;
}

