#pragma once

#include "matrix.hpp"
#include "public_func.hpp"

namespace my_math{
    template<typename T1, typename T2>
    void fill_matrix(const matrix<T1>& A, matrix<T2>& B){
        if(A.get_col() != B.get_col() || A.get_row() != B.get_row()) throw std::invalid_argument("Invalid");
        for(size_t i = 0; i < A.get_size(); i++) 
            B.at(i / A.get_col(), i % A.get_col()) = static_cast<T1>(A.at(i / A.get_col(), i % A.get_col()));  
    }
    template<typename T1, typename T2>
    matrix<long double> link_matrix(const matrix<T1> &A, const matrix<T2> &B, bool colType){
        if(colType && A.get_row() == B.get_row()){
            matrix<long double> C(A.get_row(), A.get_col() + B.get_col(), 0.0L);
            for(size_t i = 0; i < A.get_size(); i++){
                C.at(i / A.get_col(), i % A.get_col()) = static_cast<long double>(A.at(i / A.get_col(), i % A.get_col()));
            }
            for(size_t i = 0; i < B.get_size(); i++){
                C.at(i / B.get_col(), i % B.get_col() + A.get_col()) = static_cast<long double>(B.at(i / B.get_col(), i % B.get_col()));
            }
            return C;
        }
        if(!colType && A.get_col() == B.get_col()){
        matrix<long double> C(A.get_row() + B.get_row(), A.get_col());
            for(size_t i = 0; i < A.get_size(); i++){
                C.at(i / A.get_col(), i % A.get_col()) = static_cast<long double>(A.at(i / A.get_col(), i % A.get_col()));
            }
            for(size_t i = 0; i < B.get_size(); i++){
                C.at(i / B.get_col() + A.get_row(), i % B.get_col()) = static_cast<long double>(B.at(i / B.get_col(), i % B.get_col()));
            }
            return C;
        }
        return matrix<long double>();
    }
    template<typename T1, typename T2>
    void fill_matrix(const matrix<T1>& A, matrix<T2>& B, size_t rowBegin, size_t rowEnd, size_t colBegin, size_t colEnd){
        for(size_t i = rowBegin; i < rowEnd; i++){
            for(size_t j = colBegin; j < colEnd; j++) B.at(i, j) = A.at(i - rowBegin, j - colBegin);
        }
    }
    template<typename T>
    matrix<T> link_matrix(const matrix<T> &A, const matrix<T> &B, bool colType){
        if(colType && A.get_row() == B.get_row()){
            matrix<T> C(A.get_row(), A.get_col() + B.get_col());
            for(size_t i = 0; i < A.get_size(); i++){
                C.at(i / A.get_col(), i % A.get_col()) = A.at(i / A.get_col(), i % A.get_col());
            }
            for(size_t i = 0; i < B.get_size(); i++){
                C.at(i / B.get_col(), i % B.get_col() + A.get_col()) = B.at(i / B.get_col(), i % B.get_col());
            }
            return C;
        }
        if(!colType && A.get_col() == B.get_col()){
            matrix<T> C(A.get_row() + B.get_row(), A.get_col());
            for(size_t i = 0; i < A.get_size(); i++){
                C.at(i / A.get_col(), i % A.get_col()) = A.at(i / A.get_col(), i % A.get_col());
            }
            for(size_t i = 0; i < B.get_size(); i++){
                C.at(i / B.get_col() + A.get_row(), i % B.get_col()) = B.at(i / B.get_col(), i % B.get_col());
            }
            return C;
        }
        return matrix<T>();
    }
    template<typename T>
    T tr(const matrix<T>& A){
        if (!A.is_square()) throw std::invalid_argument("Not a square matrix");
        T result = T{0};
        for (size_t i = 0; i < A.get_row(); i++) result += A.at(i, i);
        return result;
    }
    template<typename T>
    T det(matrix<T> temp){
        static_assert(std::is_signed_v<T>);
        if (!temp.is_square()) throw std::invalid_argument("Not a square matrix");
        if (temp.get_row() == 1) return temp.at(0, 0);
        if (temp.get_row() == 2) return temp.at(0, 0) * temp.at(1, 1) - temp.at(0, 1) * temp.at(1, 0);
        T sign = 1;
        T M = 1;
        for(size_t k = 0; k < temp.get_row(); k++){
            if(temp.at(k, k) == 0){
                for(size_t i = k + 1; i < temp.get_row(); i++){
                    if(temp.at(k, i)){
                        temp.swap_row(i, k);
                        sign *= -1;
                        break;
                    }
                }
                if(temp.at(k, k) == 0) return 0;
            }
            for(size_t i = k + 1; i < temp.get_row(); i++){
                for(size_t j = k + 1; j < temp.get_row(); j++){
                    temp.at(i, j) = temp.at(k, k) * temp.at(i, j) - temp.at(i, k) * temp.at(k, j);
                    temp.at(i, j) /= M;
                }
            }
            M = temp.at(k, k);
        }
        return sign * temp.at(temp.get_row() - 1, temp.get_row() - 1);
    }
    template<typename T>
    matrix<long double> basic_gaussian_elimination(const matrix<T>& A, long double epsilon = 1e-9){
        size_t n = A.get_row();
        size_t m = A.get_col();
        auto B = matrix<long double>(n, m, 0);
        fill_matrix(A, B);
        for(size_t k = 0; k < n; k++){
            size_t i_max = k;
            for(size_t i = k + 1; i < n; i++){
                if(std::abs(B.at(i, k)) > std::abs(B.at(i_max, k))) i_max = i;
            }
            if(std::abs(B.at(i_max, k)) < epsilon) continue;
            if(i_max != k) B.swap_row(i_max, k);
            for(size_t i = k + 1; i < n; i++){
                long double f = B.at(i, k) / B.at(k, k);
                B.at(i, k) = 0;
                for(size_t j = k + 1; j < m; j++) B.at(i, j) -= B.at(k, j) * f;
            }
        }
        return B;
    }

    template<typename T>
    std::pair<matrix<long double>, matrix<long double>> get_QR(const matrix<T>& A, long double eps = 1e-9){
        std::pair<matrix<long double>, matrix<long double>> result;
        size_t m = A.get_row(), n = A.get_col();
        result.second = matrix<long double>(m, n, 0.0);
        result.first = get_E<long double>(m);
        fill_matrix(A, result.second);
        for(size_t i = 0; i < n; i++){
            col_vector<long double> x = get_col_vector(result.second.get_block(i, m, i, i + 1), 0);
            col_vector<long double> e(m - i, 0.0);
            e.at(0) = 1.0;
            col_vector<long double> v = x - (x.getNorm() * e);
            if(v.getNorm() < eps) continue;
            v /= v.getNorm();
            matrix<long double> H = get_E<long double>(m);
            matrix<long double> Hm = H.get_block(i, m, i, m);
            Hm -= static_cast<long double>(2.0) * v * transpose(v);
            fill_matrix(Hm, H, i, m, i, m);
            result.second = H * result.second;
            result.first = result.first * transpose(H);
        }
        for(size_t i = 0; i < m; i++){
            for(size_t j = 0; j < n; j++) {
                if(std::abs(result.second.at(i, j)) < eps) result.second.at(i, j) = 0.0;
            }
        }
        return result;
    }

    template<typename T>
    std::vector<matrix<long double>> get_PLU(const matrix<T>& A, long double eps = 1e-9){
        if(std::abs(det(A)) < eps) throw std::invalid_argument("Invalid");
        std::vector<matrix<long double>> result(3);
        result[0] = matrix<long double>(A.get_row(), true, 1.0F);
        result[1] = matrix<long double>(A.get_row(), true, 1.0F);
        result[2] = matrix<long double>(A.get_row(), false, 0.0F);
        fill_matrix(A, result[2]);
        for(size_t k = 0; k < A.get_row(); k++){
            size_t i_max = k;
            for(size_t i = k + 1; i < A.get_row(); i++){
                if(std::abs(result[2].at(i, k)) > std::abs(result[2].at(i_max, k))) i_max = i;
            }
            if(i_max != k) {
                result[2].swap_row(i_max, k);
                result[0].swap_row(i_max, k);
                result[1].swap_row(i_max, k);
                result[1].swap_col(i_max, k);
            }
            for(size_t j = k + 1; j < A.get_row(); j++){
                result[1].at(j, k) = result[2].at(j, k) / result[2].at(k, k);
                long double f = result[2].at(j, k) / result[2].at(k, k);
                for(size_t i = 0; i < A.get_row(); i++) result[2].at(j, i) -= f * result[2].at(k, i);
            }
        }
        return result;
    }

    template<typename T>
    matrix<long double> get_inverse(const matrix<T>& A, long double epsilon = 1e-9){
        if(std::abs(det(A)) < 1e-9 || A.get_col() != A.get_row()) throw std::invalid_argument("Invalid.");
        size_t n = A.get_row();
        matrix<long double> B = link_matrix(A, matrix<long double>(n, true, 1.0L), true);
        B = basic_gaussian_elimination(B);
        for(int i = n - 1; i >= 0; i--){
            for(int j = 2 * n - 1; j > i; j--){
                if(std::abs(B.at(i, i)) < epsilon) throw std::invalid_argument("Invalid.");
                B.at(i, j) /= B.at(i, i);
            }
            B.at(i, i) = 1.0L;
            for(int j = i - 1; j >= 0; j--){
                long double f = B.at(j, i);
                B.at(j, i) = 0;
                for(size_t k = i + 1; k < 2 * n; k++) B.at(j, k) -= B.at(i, k) * f;
            }
        }
        return B.get_block(n, false);
    }
    template<typename T>
    matrix<long double> get_adjoint(const matrix<T>& A, long double epsilon = 1e-9){
        if(std::abs(det(A)) < epsilon){
            std::cout << "It is my guilt that I didn't add method to compute the adjoint of a matrix which can not be inversed\n";
            std::cout << "The normal way, computing algebraic cofactor, is O(n^5) in time, which is unacceptable in my thought.\n";
            std::cout << "After I could use SVD, and could compute a rank of a matrix, I will complete the function.\n";
            std::cout << "I feel sorry for the inconvenience that I made.\n";
            throw std::invalid_argument("Now It can't work.");
        }
        return static_cast<long double>(det(A)) * get_inverse(A);
    }
}