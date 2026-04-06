#pragma once

#include<vector>
#include<cmath>
#include<type_traits>
#include<iostream>
#include<numeric>
#include<algorithm> //Necessary headers.
#include "extraFunc.hpp"


namespace mymath{
    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>, T>>
    class Matrix final {
    public:
        Matrix() = default;
        Matrix(size_t row, size_t col) : rows(row), cols(col), defaultInit(false), mat(row * col), row_map(row), col_map(col) {
            std::iota(row_map.begin(), row_map.end(), 0U);
            std::iota(col_map.begin(), col_map.end(), 0U);
        }
        Matrix(size_t row, size_t col, const T init) : rows(row), cols(col), defaultInit(false), mat(row * col, init), row_map(row), col_map(col) {
            std::iota(row_map.begin(), row_map.end(), 0U);
            std::iota(col_map.begin(), col_map.end(), 0U);
        }
        Matrix(size_t row, size_t col, const std::vector<T>& init) : rows(row), cols(col), defaultInit(false), mat(row * col, 0), row_map(row), col_map(col) {
            for (size_t i = 0; i < init.size(); i++) mat[i] = init[i];
            std::iota(row_map.begin(), row_map.end(), 0U);
            std::iota(col_map.begin(), col_map.end(), 0U);
        }
        Matrix(size_t row, bool diag, const T init) : rows(row), cols(row), defaultInit(false), mat(row * row, diag ? 0 : init), row_map(row), col_map(row) {
            if (diag) for (size_t i = 0; i < row; i++) mat[i * row + i] = init;
            std::iota(row_map.begin(), row_map.end(), 0U);
            std::iota(col_map.begin(), col_map.end(), 0U);
        }
        Matrix(size_t row, const std::vector<T>& init) : rows(row), cols(row), defaultInit(false), mat(row * row, 0), row_map(row), col_map(row) {
            for (size_t i = 0; i < row; i++) {
                if (i >= init.size()) mat[i * row + i] = 1;
                else mat[i * row + i] = init[i];
            }
            std::iota(row_map.begin(), row_map.end(), 0U);
            std::iota(col_map.begin(), col_map.end(), 0U);
        }

        T& at(size_t i, size_t j) {return transposed ? mat[row_map[j] * cols + col_map[i]] : mat[row_map[i] * cols + col_map[j]];}
        const T& at(size_t i, size_t j) const {return transposed ? mat[row_map[j] * cols + col_map[i]] : mat[row_map[i] * cols + col_map[j]];}
        constexpr size_t getRow() const{return transposed ? cols : rows;}
        constexpr size_t getCol() const{return transposed ? rows : cols;}
        constexpr size_t getSize() const{return rows * cols;}

        void assign(size_t row, size_t col, const T init = T{0}) {
            if (!defaultInit) throw::std::logic_error("Cannot assign to a initialized matrix.");
            rows = row, cols = col, defaultInit = false;
            mat.resize(row * col);
            row_map.resize(row);
            col_map.resize(col);
            std::fill(mat.begin(), mat.end(), init);
            std::iota(row_map.begin(), row_map.end(), 0U);
            std::iota(col_map.begin(), col_map.end(), 0U);
        }
        void fill(T init = T{0}){std::fill(mat.begin(), mat.end(), init);}
        void transpose() {transposed = !transposed;}
        void swapRow(size_t r1, size_t r2){std::swap(row_map[r1], row_map[r2]);}
        void swapCol(size_t c1, size_t c2){std::swap(col_map[c1], col_map[c2]);}

        bool isSameType(const Matrix& B){return getRow() == B.getRow() && getCol() == B.getCol();}
        bool isSquare() const{return getRow() == getCol();}

        bool operator== (const Matrix& B) {
            if (!isSameType(B)) return false;
            for (size_t i = 0; i < getSize(); i++) {
                if (at(i / getCol(), i % getCol()) != B.at(i / B.getCol(), i % B.getCol())) return false;
            }
            return true;
        }
        bool operator!= (const Matrix& B) {
            if (!isSameType(B)) return true;
            for (size_t i = 0; i < getSize(); i++) {
                if (at(i / getCol(), i % getCol()) != B.at(i / getCol(), i % getCol())) return true;
            }
            return false;
        }
        Matrix& operator+=(const Matrix& B) {
            if (!isSameType(B)) throw std::runtime_error("Cannot add matrices between matrices");
            for (size_t i = 0; i < getSize(); i++) {
                at(i / getCol(), i % getCol()) += B.at(i / B.getCol(), i % B.getCol());
            }
            return *this;
        }
        Matrix& operator-=(const Matrix& B) {
            if (!isSameType(B)) throw std::runtime_error("Cannot add matrices between matrices");
            for (size_t i = 0; i < getSize(); i++) {
                at(i / getCol(), i % getCol()) -= B.at(i / B.getCol(), i % B.getCol());
            }
            return *this;
        }
        Matrix& operator*=(const T B) {
            for (auto &i : mat) i *= B;
            return *this;
        }
        Matrix& operator/=(const T B) {
            if (B == T{0}) throw std::runtime_error("Cannot divide by zero");
            for (auto &i : mat) i /= B;
            return *this;
        }

        Matrix& operator%=(const T B) {
            static_assert(std::is_integral_v<T>);
            for (auto &i : mat) i %= B;
            return *this;
        }

        long double getColVectorNorm(size_t col, size_t L = 2) const{
            if(col >= getCol()) throw std::out_of_range("Out of the matrix");
            long double result = 0;
            if(L == 1){
                for(size_t i = 0; i < getRow(); i++) result += std::abs(at(i, col));
                return static_cast<long double>(result);
            }
            for(size_t i = 0; i < getCol(); i++) result += extraFunc::pow(static_cast<long double>(std::abs(at(i, col))), L);
            return std::pow(result, (1.0 / static_cast<long double>(L)));
        }
        long double getRowVectorNorm(size_t row, size_t L = 2) const{
            if(row >= getRow()) throw std::out_of_range("Out of the matrix");
            long double result = 0;
            if(L == 1){
                for(size_t i = 0; i < getCol(); i++) result += std::abs(at(row, i));
                return static_cast<long double>(result);
            }
            for(size_t i = 0; i < getCol(); i++) result += extraFunc::pow(static_cast<long double>(std::abs(at(row, i))), L);
            return std::pow(result, (1.0 / static_cast<long double>(L)));
        }
        T getColInfNorm(size_t col) const{
            if(col >= getCol()) throw std::out_of_range("Out of the matrix");
            T result = at(0, col);
            for(size_t i = 0; i < getRow(); i++) result = std::max(result, at(i, col));
            return result;
        }
        T getRowInfNorm(size_t row) const{
            if(row >= getRow()) throw std::out_of_range("Out of the matrix");
            T result = at(row, 0);
            for(size_t i = 0; i < getCol(); i++) result = std::max(result, at(row, i));
            return result;
        }
        Matrix childrenMatrix(const std::vector<size_t>& Row, const std::vector<size_t>& Col) const{
            if(Row.empty() || Col.empty()) return Matrix();
            if(Row.size() > getRow() || Col.size() > getCol()) throw std::out_of_range("Invalid");
            Matrix<T> B(Row.size(), Col.size());
            for(size_t i = 0; i < Row.size(); i++){
                if(Row[i] >= getCol()) throw std::out_of_range("Invalid");
                for(size_t j = 0; j < Col.size(); j++){
                    if(Col[i] >= getCol()) throw std::out_of_range("Invalid");
                    B.at(i, j) = at(Row[i], Col[j]);
                }
            }
            return B;
        }
        Matrix<long double> getBlock(size_t rowStart, size_t rowEnd, size_t colStart, size_t colEnd){
            Matrix<long double> result(rowEnd - rowStart, colEnd - colStart, 0.0);
            for(size_t i = rowStart; i < rowEnd; i++){
                for(size_t j = colStart; j < colEnd; j++) result.at(i - rowStart, j - colStart) = static_cast<long double>(at(i, j));
            }
            return result;
        }
        /*
        subMatrix<T> getBlock(size_t rowStart, size_t rowEnd, size_t colStart, size_t colEnd){
            reutrn subMatrix<T>(mat.data(), cols, transposed, row_map, col_map, rowStart, rowEnd, colStart, colEnd);
        }
        */
        Matrix getBlock(size_t start, bool byRow) const{
            if(byRow){
                if(start >= getRow()) throw std::out_of_range("Invalid");
                Matrix<T> B(getRow() - start, getCol());
                for(size_t i = 0; i < B.getSize(); i++)
                    B.at(i / getCol(), i % getCol()) = at(i / getCol() + start, i % getCol());
                return B;
            }
            if(start >= getCol()) throw std::out_of_range("Invalid");
            Matrix<T> B(getRow(), getCol() - start);
            for(size_t i = 0; i < B.getSize(); i++)
                B.at(i / (getCol() - start) , i % (getCol() - start)) = at(i / (getCol() - start), i % (getCol() - start) + start);
            return B;
        }
        Matrix getBlock(size_t Start, size_t End, bool byRow) const{
            if(byRow){
                if(Start >= getRow() || Start >= End || End >= getRow()) throw std::out_of_range("Invalid");
                Matrix<T> B(End - Start, getCol());
                for(size_t i = 0; i < B.getSize(); i++)
                    B.at(i / getCol(), i % getCol()) = at((i / getCol() + Start), i % getCol());
                return B;
            }
            if(Start >= getCol() || Start >= End || End >= getCol()) throw std::out_of_range("Invalid");
            Matrix<T> B(getRow(), End - Start);
            for(size_t i = 0; i < B.getSize(); i++)
                B.at(i / (End - Start), i % (End - Start)) = at(i / (End - Start), i % (End - Start) + Start);
            return B;
        }
        Matrix cutMatrix(const std::vector<size_t>& ind, bool byRow) const{
            if(ind.empty()) return Matrix();
            if(byRow) {
                Matrix<T> B(ind.size(), getCol());
                for(size_t i = 0; i < ind.size(); i++){
                    if(ind[i] >= getRow()) throw std::out_of_range("Invalid");
                    for(size_t j = 0; j < getCol(); j++){
                        B.at(i, j) = at(ind[i], j);
                    }
                }
                return B;
            }
            Matrix<T> B(getRow(), ind.size());
            for(size_t i = 0; i < ind.size(); i++){
                if(ind[i] >= getCol()) throw std::out_of_range("Invalid");
                for(size_t j = 0; j < getRow(); j++){
                    B.at(j, i) = at(j, ind[i]);
                }
            }
         return B;
        }
    private:
        size_t rows = 0, cols = 0;
        bool defaultInit = true;
        std::vector<T> mat;
        bool transposed = false;
        std::vector<size_t> row_map;
        std::vector<size_t> col_map;
    };

    /*template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>, T>>
    class subMatrix final{
    public:
        subMatrix(T* from, size_t org_c, bool transposed, 
                  const std::vector<size_t>& row_map, const std::vector<size_t> col_map,
                  size_t rowBegin, size_t rowEnd, size_t colBegin, size_t colEnd) 
                  : value_(from), org_col(org_c), transposed(org_trans), row(rowEnd - rowBegin), col(colEnd - colBegin) {
                    sub_row_map.assign(row_map.begin() + rowBegin, row_map.begin() + rowEnd);
                    sub_col_map.assign(col_map.begin() + colBegin, col_map.begin() + colEnd);
                }
        T& at(size_t i, size_t j) {return transposed ? value_[sub_row_map[j] * org_col + sub_col_map[i]] : value_[sub_row_map[i] * org_col + sub_col_map[j]];}
        const T& at(size_t i, size_t j) const {return transposed ? value_[sub_row_map[j] * org_col + sub_col_map[i]] : value_[sub_row_map[i] * org_col + sub_col_map[j]];}
        constexpr size_t getRow() const{return transposed ? col : row;}
        constexpr size_t getCol() const{return transposed ? row : col;}
        constexpr size_t getSize() const{return row * col;}
        void swapRow(size_t r1, size_t r2){std::swap(sub_row_map[r1], sub_row_map[r2]);}
        void swapCol(size_t c1, size_t c2){std::swap(sub_col_map[c1], sub_col_map[c2]);}

        bool isSameType(const subMatrix& B){return getRow() == B.getRow() && getCol() == B.getCol();}
        bool isSquare() const{return getRow() == getCol();}

        bool operator== (const subMatrix& B) {
            if (!isSameType(B)) return false;
            for (size_t i = 0; i < getSize(); i++) {
                if (at(i / getCol(), i % getCol()) != B.at(i / B.getCol(), i % B.getCol())) return false;
            }
            return true;
        }
        bool operator!= (const subMatrix& B) {
            if (!isSameType(B)) return true;
            for (size_t i = 0; i < getSize(); i++) {
                if (at(i / getCol(), i % getCol()) != B.at(i / getCol(), i % getCol())) return true;
            }
            return false;
        }
        subMatrix& operator+=(const subMatrix& B) {
            if (!isSameType(B)) throw std::runtime_error("Cannot add matrices between matrices");
            for (size_t i = 0; i < getSize(); i++) {
                at(i / getCol(), i % getCol()) += B.at(i / B.getCol(), i % B.getCol());
            }
            return *this;
        }
        subMatrix& operator-=(const subMatrix& B) {
            if (!isSameType(B)) throw std::runtime_error("Cannot add matrices between matrices");
            for (size_t i = 0; i < getSize(); i++) {
                at(i / getCol(), i % getCol()) -= B.at(i / B.getCol(), i % B.getCol());
            }
            return *this;
        }
        subMatrix& operator+=(const Matrix<T>& B) {
            if (!isSameType(B)) throw std::runtime_error("Cannot add matrices between matrices");
            for (size_t i = 0; i < getSize(); i++) {
                at(i / getCol(), i % getCol()) += B.at(i / B.getCol(), i % B.getCol());
            }
            return *this;
        }
        subMatrix& operator-=(const Matrix<T>& B) {
            if (!isSameType(B)) throw std::runtime_error("Cannot add matrices between matrices");
            for (size_t i = 0; i < getSize(); i++) {
                at(i / getCol(), i % getCol()) -= B.at(i / B.getCol(), i % B.getCol());
            }
            return *this;
        }
        subMatrix& operator*=(const T B) {
            for (size_t i = 0; i < getSize(); i++) {
                at(i / getCol(), i % getCol()) *= B;
            }
            return *this;
        }
        subMatrix& operator/=(const T B) {
            if (B == T{0}) throw std::runtime_error("Cannot divide by zero");
           for (size_t i = 0; i < getSize(); i++) {
                at(i / getCol(), i % getCol()) /= B;
            }
            return *this;
        }

        subMatrix& operator%=(const T B) {
            static_assert(std::is_integral_v<T>);
            for (size_t i = 0; i < getSize(); i++) {
                at(i / getCol(), i % getCol()) %= B;
            }
            return *this;
        }

        long double getColVectorNorm(size_t c, size_t L = 2) const{
            if(c >= getCol()) throw std::out_of_range("Out of the matrix");
            long double result = 0;
            if(L == 1){
                for(size_t i = 0; i < getRow(); i++) result += std::abs(at(i, c));
                return static_cast<long double>(result);
            }
            for(size_t i = 0; i < getCol(); i++) result += extraFunc::pow(static_cast<long double>(std::abs(at(i, c))), L);
            return std::pow(result, (1.0 / static_cast<long double>(L)));
        }
        long double getRowVectorNorm(size_t r, size_t L = 2) const{
            if(r >= getRow()) throw std::out_of_range("Out of the matrix");
            long double result = 0;
            if(L == 1){
                for(size_t i = 0; i < getCol(); i++) result += std::abs(at(r, i));
                return static_cast<long double>(result);
            }
            for(size_t i = 0; i < getCol(); i++) result += extraFunc::pow(static_cast<long double>(std::abs(at(r, i))), L);
            return std::pow(result, (1.0 / static_cast<long double>(L)));
        }
        T getColInfNorm(size_t c) const{
            if(c >= getCol()) throw std::out_of_range("Out of the matrix");
            T result = at(0, c);
            for(size_t i = 0; i < getRow(); i++) result = std::max(result, at(i, c));
            return result;
        }
        T getRowInfNorm(size_t r) const{
            if(r >= getRow()) throw std::out_of_range("Out of the matrix");
            T result = at(r, 0);
            for(size_t i = 0; i < getCol(); i++) result = std::max(result, at(r, i));
            return result;
        }
    private:
        T* value_;
        size_t org_col;
        bool transposed;
        std::vector<size_t> sub_row_map;
        std::vector<size_t> sub_col_map;
        size_t row, col;
    };*/

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const Matrix<T>& A) {
        for(size_t i = 0; i < A.getSize(); i++){
            os << A.at(i / A.getCol(), i % A.getCol()) << " ";
            if(!((i + 1) % A.getCol())) os << "\n";
        }
        return os;
    }
    /*template<typename T>
    std::ostream& operator<<(std::ostream& os, const subMatrix<T>& A) {
        for(size_t i = 0; i < A.getSize(); i++){
            os << A.at(i / A.getCol(), i % A.getCol()) << " ";
            if(!((i + 1) % A.getCol())) os << "\n";
        }
        return os;
    }*/

    template<typename T>
    Matrix<T> getE(size_t n){return Matrix<T>(n, true, 1);};

    template<typename T>
    constexpr bool couldMultiplying(const Matrix<T>& A, const Matrix<T>& B){return A.getCol() == B.getRow();}

    template<typename T>
    constexpr bool isSameType(const Matrix<T>& A, const Matrix<T>& B){return A.getCol() == B.getCol() && A.getRow() == B.getRow();}

    template<typename T>
    Matrix<T> operator+(const Matrix<T>& A, const Matrix<T>& B){
        if(!isSameType(A, B)) throw std::out_of_range("Invalid");
        Matrix<T> C = Matrix<T>(A.getRow(), A.getCol());
        for(size_t i = 0; i < A.getSize(); i++){
            C.at(i / A.getCol(), i % A.getCol()) = A.at(i / A.getCol(), i % A.getCol()) + B.at(i / A.getCol(), i % A.getCol());
        }
        return C;
    }
    template<typename T>
    Matrix<T> operator-(const Matrix<T>& A, const Matrix<T>& B){
        if(!isSameType(A, B)) throw std::out_of_range("Invalid");
        Matrix<T> C = Matrix<T>(A.getRow(), A.getCol());
        for(size_t i = 0; i < A.getSize(); i++){
            C.at(i / A.getCol(), i % A.getCol()) = A.at(i / A.getCol(), i % A.getCol()) - B.at(i / A.getCol(), i % A.getCol());
        }
        return C;
    }

    template<typename T>
    Matrix<T> operator*(const Matrix<T>& A, const Matrix<T>& B){
        if(!couldMultiplying(A, B)) throw std::out_of_range("Invalid");
        Matrix<T> C = Matrix<T>(A.getRow(), B.getCol());
        for(size_t i = 0; i < A.getRow(); i++){
            for(size_t k = 0; k < A.getCol(); k++){
                T mid = A.at(i, k);
                for(size_t j = 0; j < B.getCol(); j++){
                    C.at(i, j) += mid * B.at(k, j);
                }
            }
        }
        return C;
    }

    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>, T>>
    Matrix<T> operator*(T B, Matrix<T> A){
        for(size_t i = 0; i < A.getSize(); i++){
            A.at(i / A.getCol(), i % A.getCol()) *= B;
        }
        return A;
    }

    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>, T>>
    Matrix<T> operator/(T B, Matrix<T> A){
        if(!B) throw std::invalid_argument("Division by zero.");
        for(size_t i = 0; i < A.getSize(); i++){
            A.at(i / A.getCol(), i % A.getCol()) /= B;
        }
        return A;
    }

    template<typename T, typename = std::enable_if_t<std::is_integral_v<T>, T>> 
    Matrix<T> operator% (T B, Matrix<T> A){
        for(size_t i = 0; i < A.getSize(); i++){
            A.at(i / A.getCol(), i % A.getCol()) %= B;
        }
        return A;
    }

    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>, T>>
    Matrix<T> operator*(Matrix<T> A, T B){
        for(size_t i = 0; i < A.getSize(); i++){
            A.at(i / A.getCol(), i % A.getCol()) *= B;
        }
        return A;
    }

    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>, T>>   
    Matrix<T> operator/(Matrix<T> A, T B){
        if(!B) throw std::invalid_argument("Division by zero.");
        for(size_t i = 0; i < A.getSize(); i++){
            A.at(i / A.getCol(), i % A.getCol()) /= B;
        }
        return A;
    }

    template<typename T, typename = std::enable_if_t<std::is_integral_v<T>, T>> 
    Matrix<T> operator% (Matrix<T> A, T B){
        for(size_t i = 0; i < A.getSize(); i++){
            A.at(i / A.getCol(), i % A.getCol()) %= B;
        }
        return A;
    }

    template<typename T>
    Matrix<T> pow(Matrix<T> A, size_t n){
        if(!A.isSquare()) throw std::invalid_argument("Invalid.");
        Matrix<T> ans(A.getRow(), true, 1);
        while(n > 0){
            if(n & 1) ans = ans * A;
            A = A * A;
            n >>= 1;
        }
        return ans;
    }

    template<typename T>
    Matrix<T> transpose(Matrix<T> A){
        A.transpose();
        return A;
    }
}