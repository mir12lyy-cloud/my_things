#pragma once

#include "CRVectors.hpp"
#include "Matrix.hpp"

namespace linearAlgebra{
    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>, T>>
    colVector<T> getColVector(const Matrix<T>& A, size_t col) {
        colVector<T> result(A.getRow());
        for (size_t i = 0; i < A.getRow(); i++) result.at(i) = A.at(i, col);
            return result;
    }
    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>, T>>
    rowVector<T> getRowVector(const Matrix<T>& A, size_t row){
        rowVector<T> result(A.getCol());
        for (size_t i = 0; i < A.getCol(); i++) result.at(i) = A.at(row, i);
        return result;
    }
    template<typename T>
    colVector<T> operator*(const Matrix<T>& A, const colVector<T>& B){
        if(A.getCol() != B.getSize()) throw std::out_of_range("Invalid");
        colVector<T> C = colVector<T>(A.getRow());
        for (size_t i = 0; i < A.getRow(); i++) {
            for (size_t j = 0; j < B.getSize(); j++) C.at(i) += A.at(i, j) * B.at(j);
        }
        return C;
    }
    template<typename T>
    rowVector<T> operator*(const rowVector<T>& A, const Matrix<T>& B){
        if(A.getSize() != B.getRow()) throw std::out_of_range("Invalid");
        rowVector<T> C = rowVector<T>(B.getCol());
        for (size_t i = 0; i < B.getRow(); i++) {
            for (size_t j = 0; j < A.getSize(); j++) C.at(i) += A.at(j) * B.at(i, j);
        }
        return C;
    }
    /*template<typename T>
    colVector<T> operator*(const subMatrix<T>& A, const colVector<T>& B){
        if(A.getCol() != B.getSize()) throw std::out_of_range("Invalid");
        colVector<T> C = colVector<T>(A.getRow());
        for (size_t i = 0; i < A.getRow(); i++) {
            for (size_t j = 0; j < B.getSize(); j++) C.at(i) += A.at(i, j) * B.at(j);
        }
        return C;
    }
    template<typename T>
    rowVector<T> operator*(const rowVector<T>& A, const subMatrix<T>& B){
        if(A.getSize() != B.getRow()) throw std::out_of_range("Invalid");
        rowVector<T> C = rowVector<T>(B.getCol());
        for (size_t i = 0; i < B.getRow(); i++) {
            for (size_t j = 0; j < A.getSize(); j++) C.at(i) += A.at(j) * B.at(i, j);
        }
        return C;
    }*/
    template<typename T>
    Matrix<T> operator*(const colVector<T>& A, const rowVector<T>& B){
        if(A.getSize() != B.getSize()) throw std::invalid_argument("Not matched.");
        Matrix<T> result(A.getSize(), B.getSize(), 0);
        for (size_t i = 0; i < A.getSize(); i++) {
            for (size_t j = 0; j < B.getSize(); j++) result.at(i, j) = A.at(i) * B.at(j);
        }
        return result;
    }
}