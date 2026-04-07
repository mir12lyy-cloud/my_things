#pragma once

#include "col_row_vectors.hpp"
#include "matrix.hpp"

namespace my_math{
    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>, T>>
    col_vector<T> get_col_vector(const matrix<T>& A, size_t col) {
        col_vector<T> result(A.get_row());
        for (size_t i = 0; i < A.get_row(); i++) result.at(i) = A.at(i, col);
            return result;
    }
    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>, T>>
    row_vector<T> get_row_vector(const matrix<T>& A, size_t row){
        row_vector<T> result(A.get_col());
        for (size_t i = 0; i < A.get_col(); i++) result.at(i) = A.at(row, i);
        return result;
    }
    template<typename T>
    col_vector<T> operator*(const matrix<T>& A, const col_vector<T>& B){
        if(A.get_col() != B.get_size()) throw std::out_of_range("Invalid");
        col_vector<T> C = col_vector<T>(A.get_row());
        for (size_t i = 0; i < A.get_row(); i++) {
            for (size_t j = 0; j < B.get_size(); j++) C.at(i) += A.at(i, j) * B.at(j);
        }
        return C;
    }
    template<typename T>
    row_vector<T> operator*(const row_vector<T>& A, const matrix<T>& B){
        if(A.get_size() != B.get_row()) throw std::out_of_range("Invalid");
        row_vector<T> C = row_vector<T>(B.get_col());
        for (size_t i = 0; i < B.get_row(); i++) {
            for (size_t j = 0; j < A.get_size(); j++) C.at(i) += A.at(j) * B.at(i, j);
        }
        return C;
    }
    template<typename T>
    matrix<T> operator*(const col_vector<T>& A, const row_vector<T>& B){
        if(A.get_size() != B.get_size()) throw std::invalid_argument("Not matched.");
        matrix<T> result(A.get_size(), B.get_size(), 0);
        for (size_t i = 0; i < A.get_size(); i++) {
            for (size_t j = 0; j < B.get_size(); j++) result.at(i, j) = A.at(i) * B.at(j);
        }
        return result;
    }
}