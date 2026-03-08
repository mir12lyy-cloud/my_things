#pragma once

#include "Matrix.hpp"
#include "publicFunc.hpp"

namespace linearAlgebra{
    template<typename T1, typename T2>
    void fillMatrix(const Matrix<T1>& A, Matrix<T2>& B){
        if(A.getCol() != B.getCol() || A.getRow() != B.getRow()) throw std::invalid_argument("Invalid");
        for(size_t i = 0; i < A.getSize(); i++) 
            B.at(i / A.getCol(), i % A.getCol()) = static_cast<T1>(A.at(i / A.getCol(), i % A.getCol()));  
    }
    template<typename T1, typename T2>
    Matrix<long double> linkMatrix(const Matrix<T1> &A, const Matrix<T2> &B, bool colType){
        if(colType && A.getRow() == B.getRow()){
            Matrix<long double> C(A.getRow(), A.getCol() + B.getCol(), 0.0L);
            for(size_t i = 0; i < A.getSize(); i++){
                C.at(i / A.getCol(), i % A.getCol()) = static_cast<long double>(A.at(i / A.getCol(), i % A.getCol()));
            }
            for(size_t i = 0; i < B.getSize(); i++){
                C.at(i / B.getCol(), i % B.getCol() + A.getCol()) = static_cast<long double>(B.at(i / B.getCol(), i % B.getCol()));
            }
            return C;
        }
        if(!colType && A.getCol() == B.getCol()){
        Matrix<long double> C(A.getRow() + B.getRow(), A.getCol());
            for(size_t i = 0; i < A.getSize(); i++){
                C.at(i / A.getCol(), i % A.getCol()) = static_cast<long double>(A.at(i / A.getCol(), i % A.getCol()));
            }
            for(size_t i = 0; i < B.getSize(); i++){
                C.at(i / B.getCol() + A.getRow(), i % B.getCol()) = static_cast<long double>(B.at(i / B.getCol(), i % B.getCol()));
            }
            return C;
        }
        return Matrix<long double>();
    }
    template<typename T1, typename T2>
    void fillMatrix(const Matrix<T1>& A, Matrix<T2>& B, size_t rowBegin, size_t rowEnd, size_t colBegin, size_t colEnd){
        for(size_t i = rowBegin; i < rowEnd; i++){
            for(size_t j = colBegin; j < colEnd; j++) B.at(i, j) = A.at(i - rowBegin, j - colBegin);
        }
    }
    template<typename T>
    Matrix<T> linkMatrix(const Matrix<T> &A, const Matrix<T> &B, bool colType){
        if(colType && A.getRow() == B.getRow()){
            Matrix<T> C(A.getRow(), A.getCol() + B.getCol());
            for(size_t i = 0; i < A.getSize(); i++){
                C.at(i / A.getCol(), i % A.getCol()) = A.at(i / A.getCol(), i % A.getCol());
            }
            for(size_t i = 0; i < B.getSize(); i++){
                C.at(i / B.getCol(), i % B.getCol() + A.getCol()) = B.at(i / B.getCol(), i % B.getCol());
            }
            return C;
        }
        if(!colType && A.getCol() == B.getCol()){
            Matrix<T> C(A.getRow() + B.getRow(), A.getCol());
            for(size_t i = 0; i < A.getSize(); i++){
                C.at(i / A.getCol(), i % A.getCol()) = A.at(i / A.getCol(), i % A.getCol());
            }
            for(size_t i = 0; i < B.getSize(); i++){
                C.at(i / B.getCol() + A.getRow(), i % B.getCol()) = B.at(i / B.getCol(), i % B.getCol());
            }
            return C;
        }
        return Matrix<T>();
    }
    template<typename T>
    T tr(const Matrix<T>& A){
        if (!A.isSquare()) throw std::invalid_argument("Not a square matrix");
        T result = T{0};
        for (size_t i = 0; i < A.getRow(); i++) result += A.at(i, i);
        return result;
    }
    template<typename T>
    T det(Matrix<T> temp){
        static_assert(std::is_signed_v<T>);
        if (!temp.isSquare()) throw std::invalid_argument("Not a square matrix");
        if (temp.getRow() == 1) return temp.at(0, 0);
        if (temp.getRow() == 2) return temp.at(0, 0) * temp.at(1, 1) - temp.at(0, 1) * temp.at(1, 0);
        T sign = 1;
        T M = 1;
        for(size_t k = 0; k < temp.getRow(); k++){
            if(temp.at(k, k) == 0){
                for(size_t i = k + 1; i < temp.getRow(); i++){
                    if(temp.at(k, i)){
                        temp.swapRow(i, k);
                        sign *= -1;
                        break;
                    }
                }
                if(temp.at(k, k) == 0) return 0;
            }
            for(size_t i = k + 1; i < temp.getRow(); i++){
                for(size_t j = k + 1; j < temp.getRow(); j++){
                    temp.at(i, j) = temp.at(k, k) * temp.at(i, j) - temp.at(i, k) * temp.at(k, j);
                    temp.at(i, j) /= M;
                }
            }
            M = temp.at(k, k);
        }
        return sign * temp.at(temp.getRow() - 1, temp.getRow() - 1);
    }
    template<typename T>
    Matrix<long double> basicGaussianElimination(const Matrix<T>& A, long double epsilon = 1e-9){
        size_t n = A.getRow();
        size_t m = A.getCol();
        auto B = Matrix<long double>(n, m, 0);
        fillMatrix(A, B);
        for(size_t k = 0; k < n; k++){
            size_t i_max = k;
            for(size_t i = k + 1; i < n; i++){
                if(std::abs(B.at(i, k)) > std::abs(B.at(i_max, k))) i_max = i;
            }
            if(std::abs(B.at(i_max, k)) < epsilon) continue;
            if(i_max != k) B.swapRow(i_max, k);
            for(size_t i = k + 1; i < n; i++){
                long double f = B.at(i, k) / B.at(k, k);
                B.at(i, k) = 0;
                for(size_t j = k + 1; j < m; j++) B.at(i, j) -= B.at(k, j) * f;
            }
        }
        return B;
    }

    template<typename T>
    std::pair<Matrix<long double>, Matrix<long double>> getQR(const Matrix<T>& A, long double eps = 1e-9){
        std::pair<Matrix<long double>, Matrix<long double>> result;
        size_t m = A.getRow(), n = A.getCol();
        result.second = Matrix<long double>(m, n, 0.0);
        result.first = getE<long double>(m);
        fillMatrix(A, result.second);
        for(size_t i = 0; i < n; i++){
            colVector<long double> x = getColVector(result.second.getBlock(i, m, i, i + 1), 0);
            colVector<long double> e(m - i, 0.0);
            e.at(0) = 1.0;
            colVector<long double> v = x - (x.getNorm() * e);
            if(v.getNorm() < eps) continue;
            v /= v.getNorm();
            Matrix<long double> H = getE<long double>(m);
            Matrix<long double> Hm = H.getBlock(i, m, i, m);
            Hm -= static_cast<long double>(2.0) * v * transpose(v);
            fillMatrix(Hm, H, i, m, i, m);
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

    /*template<typename T>
    std::vector<Matrix<long double>> getPQR(const Matrix<T>& A){
        std::vector<Matrix<long double>> result(3);
        return result;
    }*/

    template<typename T>
    std::vector<Matrix<long double>> getPLU(const Matrix<T>& A, long double eps = 1e-9){
        if(std::abs(det(A)) < eps) throw std::invalid_argument("Invalid");
        std::vector<Matrix<long double>> result(3);
        result[0] = Matrix<long double>(A.getRow(), true, 1.0F);
        result[1] = Matrix<long double>(A.getRow(), true, 1.0F);
        result[2] = Matrix<long double>(A.getRow(), false, 0.0F);
        fillMatrix(A, result[2]);
        for(size_t k = 0; k < A.getRow(); k++){
            size_t i_max = k;
            for(size_t i = k + 1; i < A.getRow(); i++){
                if(std::abs(result[2].at(i, k)) > std::abs(result[2].at(i_max, k))) i_max = i;
            }
            if(i_max != k) {
                result[2].swapRow(i_max, k);
                result[0].swapRow(i_max, k);
                result[1].swapRow(i_max, k);
                result[1].swapCol(i_max, k);
            }
            for(size_t j = k + 1; j < A.getRow(); j++){
                result[1].at(j, k) = result[2].at(j, k) / result[2].at(k, k);
                long double f = result[2].at(j, k) / result[2].at(k, k);
                for(size_t i = 0; i < A.getRow(); i++) result[2].at(j, i) -= f * result[2].at(k, i);
            }
        }
        return result;
    }

    template<typename T>
    Matrix<long double> getInverse(const Matrix<T>& A, long double epsilon = 1e-9){
        if(std::abs(det(A)) < 1e-9 || A.getCol() != A.getRow()) throw std::invalid_argument("Invalid.");
        size_t n = A.getRow();
        Matrix<long double> B = linkMatrix(A, Matrix<long double>(n, true, 1.0L), true);
        B = basicGaussianElimination(B);
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
        return B.getBlock(n, false);
    }
    template<typename T>
    Matrix<long double> getAdjoint(const Matrix<T>& A, long double epsilon = 1e-9){
        if(std::abs(det(A)) < epsilon){
            std::cout << "It is my guilt that I didn't add method to compute the adjoint of a matrix which can not be inversed\n";
            std::cout << "The normal way, computing algebraic cofactor, is O(n^5) in time, which is unacceptable in my thought.\n";
            std::cout << "After I could use SVD, and could compute a rank of a Matrix, I will complete the function.\n";
            std::cout << "I feel sorry for the inconvenience that I made.\n";
            throw std::invalid_argument("Now It can't work.");
        }
        return static_cast<long double>(det(A)) * getInverse(A);
    }
}