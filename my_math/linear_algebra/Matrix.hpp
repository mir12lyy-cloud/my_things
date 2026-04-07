#pragma once

#include<vector>
#include<cmath>
#include<type_traits>
#include<iostream>
#include<numeric>
#include<algorithm> //Necessary headers.
#include "extra_func.hpp"


namespace my_math{
    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>, T>>
    class matrix final {
    public:
        matrix() = default;
        matrix(size_t row, size_t col) : rows(row), cols(col), defaultInit(false), mat(row * col), row_map(row), col_map(col) {
            std::iota(row_map.begin(), row_map.end(), 0U);
            std::iota(col_map.begin(), col_map.end(), 0U);
        }
        matrix(size_t row, size_t col, const T init) : rows(row), cols(col), defaultInit(false), mat(row * col, init), row_map(row), col_map(col) {
            std::iota(row_map.begin(), row_map.end(), 0U);
            std::iota(col_map.begin(), col_map.end(), 0U);
        }
        matrix(size_t row, size_t col, const std::vector<T>& init) : rows(row), cols(col), defaultInit(false), mat(row * col, 0), row_map(row), col_map(col) {
            for (size_t i = 0; i < init.size(); i++) mat[i] = init[i];
            std::iota(row_map.begin(), row_map.end(), 0U);
            std::iota(col_map.begin(), col_map.end(), 0U);
        }
        matrix(size_t row, bool diag, const T init) : rows(row), cols(row), defaultInit(false), mat(row * row, diag ? 0 : init), row_map(row), col_map(row) {
            if (diag) for (size_t i = 0; i < row; i++) mat[i * row + i] = init;
            std::iota(row_map.begin(), row_map.end(), 0U);
            std::iota(col_map.begin(), col_map.end(), 0U);
        }
        matrix(size_t row, const std::vector<T>& init) : rows(row), cols(row), defaultInit(false), mat(row * row, 0), row_map(row), col_map(row) {
            for (size_t i = 0; i < row; i++) {
                if (i >= init.size()) mat[i * row + i] = 1;
                else mat[i * row + i] = init[i];
            }
            std::iota(row_map.begin(), row_map.end(), 0U);
            std::iota(col_map.begin(), col_map.end(), 0U);
        }
        T& operator() (size_t i, size_t j) { return transposed ? mat[row_map[j] * cols + col_map[i]] : mat[row_map[i] * cols + col_map[j]]; }
        const T& operator() (size_t i, size_t j) const { return transposed ? mat[row_map[j] * cols + col_map[i]] : mat[row_map[i] * cols + col_map[j]]; }
        T& at(size_t i, size_t j) {return transposed ? mat[row_map[j] * cols + col_map[i]] : mat[row_map[i] * cols + col_map[j]];}
        const T& at(size_t i, size_t j) const {return transposed ? mat[row_map[j] * cols + col_map[i]] : mat[row_map[i] * cols + col_map[j]];}
        constexpr size_t get_row() const{return transposed ? cols : rows;}
        constexpr size_t get_col() const{return transposed ? rows : cols;}
        constexpr size_t get_size() const{return rows * cols;}

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
        void swap_row(size_t r1, size_t r2){std::swap(row_map[r1], row_map[r2]);}
        void swap_col(size_t c1, size_t c2){std::swap(col_map[c1], col_map[c2]);}

        bool is_same_type(const matrix& B) const{return get_row() == B.get_row() && get_col() == B.get_col();}
        bool is_square() const{return get_row() == get_col();}

        bool operator== (const matrix& B) const {
            if (!is_same_type(B)) return false;
            for (size_t i = 0; i < get_size(); i++) {
                if (at(i / get_col(), i % get_col()) != B.at(i / B.get_col(), i % B.get_col())) return false;
            }
            return true;
        }
        bool operator!= (const matrix& B) const {
            if (!is_same_type(B)) return true;
            for (size_t i = 0; i < get_size(); i++) {
                if (at(i / get_col(), i % get_col()) != B.at(i / get_col(), i % get_col())) return true;
            }
            return false;
        }
        matrix& operator+=(const matrix& B) {
            if (!is_same_type(B)) throw std::runtime_error("Cannot add matrices between matrices");
            for (size_t i = 0; i < get_size(); i++) {
                at(i / get_col(), i % get_col()) += B.at(i / B.get_col(), i % B.get_col());
            }
            return *this;
        }
        matrix& operator-=(const matrix& B) {
            if (!is_same_type(B)) throw std::runtime_error("Cannot add matrices between matrices");
            for (size_t i = 0; i < get_size(); i++) {
                at(i / get_col(), i % get_col()) -= B.at(i / B.get_col(), i % B.get_col());
            }
            return *this;
        }
        matrix& operator*=(const T B) {
            for (auto &i : mat) i *= B;
            return *this;
        }
        matrix& operator/=(const T B) {
            if (B == T{0}) throw std::runtime_error("Cannot divide by zero");
            for (auto &i : mat) i /= B;
            return *this;
        }

        matrix& operator%=(const T B) {
            static_assert(std::is_integral_v<T>);
            for (auto &i : mat) i %= B;
            return *this;
        }

        long double get_col_vector_norm(size_t col, size_t L = 2) const{
            if(col >= get_col()) throw std::out_of_range("Out of the matrix");
            long double result = 0;
            if(L == 1){
                for(size_t i = 0; i < get_row(); i++) result += std::abs(at(i, col));
                return static_cast<long double>(result);
            }
            for(size_t i = 0; i < get_col(); i++) result += extraFunc::pow(static_cast<long double>(std::abs(at(i, col))), L);
            return std::pow(result, (1.0 / static_cast<long double>(L)));
        }
        long double get_row_vector_norm(size_t row, size_t L = 2) const{
            if(row >= get_row()) throw std::out_of_range("Out of the matrix");
            long double result = 0;
            if(L == 1){
                for(size_t i = 0; i < get_col(); i++) result += std::abs(at(row, i));
                return static_cast<long double>(result);
            }
            for(size_t i = 0; i < get_col(); i++) result += extraFunc::pow(static_cast<long double>(std::abs(at(row, i))), L);
            return std::pow(result, (1.0 / static_cast<long double>(L)));
        }
        T get_col_inf_norm(size_t col) const{
            if(col >= get_col()) throw std::out_of_range("Out of the matrix");
            T result = at(0, col);
            for(size_t i = 0; i < get_row(); i++) result = std::max(result, at(i, col));
            return result;
        }
        T get_row_inf_Norm(size_t row) const{
            if(row >= get_row()) throw std::out_of_range("Out of the matrix");
            T result = at(row, 0);
            for(size_t i = 0; i < get_col(); i++) result = std::max(result, at(row, i));
            return result;
        }
        matrix children_matrix(const std::vector<size_t>& Row, const std::vector<size_t>& Col) const{
            if(Row.empty() || Col.empty()) return Matrix();
            if(Row.size() > get_row() || Col.size() > get_col()) throw std::out_of_range("Invalid");
            matrix<T> B(Row.size(), Col.size());
            for(size_t i = 0; i < Row.size(); i++){
                if(Row[i] >= get_col()) throw std::out_of_range("Invalid");
                for(size_t j = 0; j < Col.size(); j++){
                    if(Col[i] >= get_col()) throw std::out_of_range("Invalid");
                    B.at(i, j) = at(Row[i], Col[j]);
                }
            }
            return B;
        }
        matrix<long double> get_block(size_t rowStart, size_t rowEnd, size_t colStart, size_t colEnd){
            matrix<long double> result(rowEnd - rowStart, colEnd - colStart, 0.0);
            for(size_t i = rowStart; i < rowEnd; i++){
                for(size_t j = colStart; j < colEnd; j++) result.at(i - rowStart, j - colStart) = static_cast<long double>(at(i, j));
            }
            return result;
        }
        matrix get_block(size_t start, bool byRow) const{
            if(byRow){
                if(start >= get_row()) throw std::out_of_range("Invalid");
                matrix<T> B(get_row() - start, get_col());
                for(size_t i = 0; i < B.get_size(); i++)
                    B.at(i / get_col(), i % get_col()) = at(i / get_col() + start, i % get_col());
                return B;
            }
            if(start >= get_col()) throw std::out_of_range("Invalid");
            matrix<T> B(get_row(), get_col() - start);
            for(size_t i = 0; i < B.get_size(); i++)
                B.at(i / (get_col() - start) , i % (get_col() - start)) = at(i / (get_col() - start), i % (get_col() - start) + start);
            return B;
        }
        matrix get_block(size_t Start, size_t End, bool byRow) const{
            if(byRow){
                if(Start >= get_row() || Start >= End || End >= get_row()) throw std::out_of_range("Invalid");
                matrix<T> B(End - Start, get_col());
                for(size_t i = 0; i < B.get_size(); i++)
                    B.at(i / get_col(), i % get_col()) = at((i / get_col() + Start), i % get_col());
                return B;
            }
            if(Start >= get_col() || Start >= End || End >= get_col()) throw std::out_of_range("Invalid");
            matrix<T> B(get_row(), End - Start);
            for(size_t i = 0; i < B.get_size(); i++)
                B.at(i / (End - Start), i % (End - Start)) = at(i / (End - Start), i % (End - Start) + Start);
            return B;
        }
        matrix cut_matrix(const std::vector<size_t>& ind, bool byRow) const{
            if(ind.empty()) return Matrix();
            if(byRow) {
                matrix<T> B(ind.size(), get_col());
                for(size_t i = 0; i < ind.size(); i++){
                    if(ind[i] >= get_row()) throw std::out_of_range("Invalid");
                    for(size_t j = 0; j < get_col(); j++){
                        B.at(i, j) = at(ind[i], j);
                    }
                }
                return B;
            }
            matrix<T> B(get_row(), ind.size());
            for(size_t i = 0; i < ind.size(); i++){
                if(ind[i] >= get_col()) throw std::out_of_range("Invalid");
                for(size_t j = 0; j < get_row(); j++){
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

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const matrix<T>& A) {
        for(size_t i = 0; i < A.get_size(); i++){
            os << A.at(i / A.get_col(), i % A.get_col()) << " ";
            if(!((i + 1) % A.get_col())) os << "\n";
        }
        return os;
    }

    template<typename T>
    matrix<T> get_E(size_t n){return matrix<T>(n, true, 1);};

    template<typename T>
    constexpr bool could_multiplying(const matrix<T>& A, const matrix<T>& B){return A.get_col() == B.get_row();}

    template<typename T>
    constexpr bool is_same_type(const matrix<T>& A, const matrix<T>& B){return A.get_col() == B.get_col() && A.get_row() == B.get_row();}

    template<typename T>
    matrix<T> operator+(const matrix<T>& A, const matrix<T>& B){
        if(!is_same_type(A, B)) throw std::out_of_range("Invalid");
        matrix<T> C = matrix<T>(A.get_row(), A.get_col());
        for(size_t i = 0; i < A.get_size(); i++){
            C.at(i / A.get_col(), i % A.get_col()) = A.at(i / A.get_col(), i % A.get_col()) + B.at(i / A.get_col(), i % A.get_col());
        }
        return C;
    }
    template<typename T>
    matrix<T> operator-(const matrix<T>& A, const matrix<T>& B){
        if(!is_same_type(A, B)) throw std::out_of_range("Invalid");
        matrix<T> C = matrix<T>(A.get_row(), A.get_col());
        for(size_t i = 0; i < A.get_size(); i++){
            C.at(i / A.get_col(), i % A.get_col()) = A.at(i / A.get_col(), i % A.get_col()) - B.at(i / A.get_col(), i % A.get_col());
        }
        return C;
    }

    template<typename T>
    matrix<T> operator*(const matrix<T>& A, const matrix<T>& B){
        if(!could_multiplying(A, B)) throw std::out_of_range("Invalid");
        matrix<T> C = matrix<T>(A.get_row(), B.get_col());
        for(size_t i = 0; i < A.get_row(); i++){
            for(size_t k = 0; k < A.get_col(); k++){
                T mid = A.at(i, k);
                for(size_t j = 0; j < B.get_col(); j++){
                    C.at(i, j) += mid * B.at(k, j);
                }
            }
        }
        return C;
    }

    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>, T>>
    matrix<T> operator*(T B, matrix<T> A){
        for(size_t i = 0; i < A.get_size(); i++){
            A.at(i / A.get_col(), i % A.get_col()) *= B;
        }
        return A;
    }

    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>, T>>
    matrix<T> operator/(T B, matrix<T> A){
        if(!B) throw std::invalid_argument("Division by zero.");
        for(size_t i = 0; i < A.get_size(); i++){
            A.at(i / A.get_col(), i % A.get_col()) /= B;
        }
        return A;
    }

    template<typename T, typename = std::enable_if_t<std::is_integral_v<T>, T>> 
    matrix<T> operator% (T B, matrix<T> A){
        for(size_t i = 0; i < A.get_size(); i++){
            A.at(i / A.get_col(), i % A.get_col()) %= B;
        }
        return A;
    }

    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>, T>>
    matrix<T> operator*(matrix<T> A, T B){
        for(size_t i = 0; i < A.get_size(); i++){
            A.at(i / A.get_col(), i % A.get_col()) *= B;
        }
        return A;
    }

    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>, T>>   
    matrix<T> operator/(matrix<T> A, T B){
        if(!B) throw std::invalid_argument("Division by zero.");
        for(size_t i = 0; i < A.get_size(); i++){
            A.at(i / A.get_col(), i % A.get_col()) /= B;
        }
        return A;
    }

    template<typename T, typename = std::enable_if_t<std::is_integral_v<T>, T>> 
    matrix<T> operator% (matrix<T> A, T B){
        for(size_t i = 0; i < A.get_size(); i++){
            A.at(i / A.get_col(), i % A.get_col()) %= B;
        }
        return A;
    }

    template<typename T>
    matrix<T> pow(matrix<T> A, size_t n){
        if(!A.is_square()) throw std::invalid_argument("Invalid.");
        matrix<T> ans(A.get_row(), true, 1);
        while(n > 0){
            if(n & 1) ans = ans * A;
            A = A * A;
            n >>= 1;
        }
        return ans;
    }

    template<typename T>
    matrix<T> transpose(matrix<T> A){
        A.transpose();
        return A;
    }
}