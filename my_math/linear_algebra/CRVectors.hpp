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
    class rowVector final{
    public:
        rowVector() : rowVectorSize(0) , vec(0){};
        rowVector(size_t s, const T init = T{0}) : rowVectorSize(s), vec(s, init){}
        rowVector(const std::vector<T> &init) : rowVectorSize(init.size()), vec(init.size(), 0){
            for(size_t i = 0; i < init.size(); i++) vec[i] = init[i];
        }
        void fill(T init = T{0}){std::fill(vec.begin(), vec.end(), init);}
        T& operator[](size_t idx) {return vec[idx];}
        const T& operator[](size_t idx) const {return vec[idx];}
        T& at(size_t idx){
            if(idx >= rowVectorSize) throw std::out_of_range("Out of the Vector!");
            return vec[idx];
        }
        const T& at(size_t idx) const{
            if(idx >= rowVectorSize) throw std::out_of_range("Out of the Vector!");
            return vec[idx];
        }
        size_t getSize() const{return rowVectorSize;}
        bool operator==(const rowVector& B){
            if(B.getSize() != rowVectorSize) return false;
            for(size_t i = 0; i < rowVectorSize; i++){
                if(B.at(i) != vec[i]) return false;
            }
            return true;
        }
        bool operator!=(const rowVector& B){
            if(B.getSize() != rowVectorSize) return true;
            for(size_t i = 0; i < rowVectorSize; i++){
                if(B.at(i) != vec[i]) return true;
            }
            return false;
        }
        rowVector& operator+=(const rowVector& B){
            if(B.getSize() != rowVectorSize) throw std::invalid_argument("Not matched.");
            for(size_t i = 0; i < rowVectorSize; i++) vec[i] += B.at(i);
            return *this;
        }
        rowVector& operator-=(const rowVector& B){
            if(B.getSize() != rowVectorSize) throw std::invalid_argument("Not matched.");
            for(size_t i = 0; i < rowVectorSize; i++) vec[i] -= B.at(i);
            return *this;
        }
        rowVector& operator*=(const T B){
            for(auto &i : vec) i *= B;
            return *this;
        }
        rowVector& operator/=(const T B){
            if(B == T{0}) throw std::invalid_argument("Divsion by zero.");
            for(auto &i : vec) i /= B;
            return *this;
        }
        rowVector& operator%=(const T B){
            static_assert(std::is_integral_v<T>);
            for(auto &i : vec) i %= B;
            return *this;
        }
        long double getNorm(size_t L = 2){
            long double result = 0.0;
            if(L == 1){
                for(const auto &i : vec) result += std::abs(i);
                return result;
            }
            for(const auto &i : vec) result += extraFunc::pow(static_cast<long double>(std::abs(i)), L);
            return std::pow(result, (1.0 / static_cast<long double>(L)));
        }
        T getInfNorm() const{
            T result = vec[0];
            for(const auto& i : vec) result = std::max(result, i);
            return result;
        }
    private:
        size_t rowVectorSize;
        std::vector<T> vec;
    };

    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>, T>>
    class colVector final{
    public:
        colVector() : colVectorSize(0) , vec(0){};
        colVector(size_t s, const T init = T{0}) : colVectorSize(s), vec(s, init){}
        colVector(const std::vector<T> &init) : colVectorSize(init.size()), vec(init.size()){
            for(size_t i = 0; i < init.size(); i++) vec[i] = init[i];
        }
        void fill(T init = T{0}){std::fill(vec.begin(), vec.end(), init);}
        T& operator[](size_t idx) {return vec[idx];}
        const T& operator[](size_t idx) const {return vec[idx];}
        T& at(size_t idx){
            if(idx >= colVectorSize) throw std::out_of_range("Out of the Vector!");
            return vec[idx];
        }
        const T& at(size_t idx) const{
            if(idx >= colVectorSize) throw std::out_of_range("Out of the Vector!");
            return vec[idx];
        }
        size_t getSize() const{return colVectorSize;}
        bool operator==(const colVector& B){
            if(B.getSize() != colVectorSize) return false;
            for(size_t i = 0; i < colVectorSize; i++){
                if(B.at(i) != vec[i]) return false;
            }
            return true;
        }
        bool operator!=(const colVector& B){
            if(B.getSize() != colVectorSize) return true;
            for(size_t i = 0; i < colVectorSize; i++){
                if(B.at(i) != vec[i]) return true;
            }
            return false;
        }
        colVector& operator+=(const colVector& B){
            if(B.getSize() != colVectorSize) throw std::invalid_argument("Not matched.");
            for(size_t i = 0; i < colVectorSize; i++) vec[i] += B.at(i);
            return *this;
        }
        colVector& operator-=(const colVector& B){
            if(B.getSize() != colVectorSize) throw std::invalid_argument("Not matched.");
            for(size_t i = 0; i < colVectorSize; i++) vec[i] -= B.at(i);
            return *this;
        }
        colVector& operator*=(const T B){
            for(auto &i : vec) i *= B;
            return *this;
        }
        colVector& operator/=(const T B){
            if(B == T{0}) throw std::invalid_argument("Divsion by zero.");
            for(auto &i : vec) i /= B;
            return *this;
        }
        colVector& operator%=(const T B){
            static_assert(std::is_integral_v<T>);
            for(auto &i : vec) i %= B;
            return *this;
        }
        long double getNorm(size_t L = 2){
            long double result = 0;
            if(L == 1){
                for(const auto &i : vec) result += std::abs(i);
                return static_cast<long double>(result);
            }
            for(const auto &i : vec) result += extraFunc::pow(static_cast<long double>(std::abs(i)), L);
            return std::pow(result, (1.0 / static_cast<long double>(L)));
        }
        T getInfNorm() const{
            T result = vec[0];
            for(const auto& i : vec) result = std::max(result, i);
            return result;
        }
    private:
        size_t colVectorSize;
        std::vector<T> vec;
    };

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const colVector<T>& A) {
        for (size_t i = 0; i < A.getSize(); i++) os << A.at(i) << "\n";
        return os;
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const rowVector<T>& A) {
        for (size_t i = 0; i < A.getSize(); i++) os << A.at(i) << " ";
        return os;
    }

    template<typename T>
    colVector<T> operator+(const colVector<T>& A, const colVector<T>& B){
        if(A.getSize() != B.getSize()) throw std::invalid_argument("No matched.");
        colVector<T> result(A.getSize(), 0.0);
        for(size_t i = 0; i < A.getSize(); i++) result.at(i) = A.at(i) + B.at(i);
        return result;
    }

    template<typename T>
    colVector<T> operator-(const colVector<T>& A, const colVector<T>& B){
        if(A.getSize() != B.getSize()) throw std::invalid_argument("No matched.");
        colVector<T> result(A.getSize(), 0.0);
        for(size_t i = 0; i < A.getSize(); i++) result.at(i) = A.at(i) - B.at(i);
        return result;
    }

    template<typename T>
    rowVector<T> operator+(const rowVector<T>& A, const rowVector<T>& B){
        if(A.getSize() != B.getSize()) throw std::invalid_argument("No matched.");
        rowVector<T> result(A.getSize(), 0.0);
        for(size_t i = 0; i < A.getSize(); i++) result.at(i) = A.at(i) + B.at(i);
        return result;
    }

    template<typename T>
    rowVector<T> operator-(const rowVector<T>& A, const rowVector<T>& B){
        if(A.getSize() != B.getSize()) throw std::invalid_argument("No matched.");
        rowVector<T> result(A.getSize(), 0.0);
        for(size_t i = 0; i < A.getSize(); i++) result.at(i) = A.at(i) - B.at(i);
        return result;
    }

    template<typename T>
    colVector<T> operator*(colVector<T> A, T B){
        for(size_t i = 0; i < A.getSize(); i++) A.at(i) *= B;
        return A;
    }

    template<typename T>
    colVector<T> operator/(colVector<T> A, T B){
        for(size_t i = 0; i < A.getSize(); i++) A.at(i) /= B;
        return A;
    }

    template<typename T, typename = std::enable_if_t<std::is_integral_v<T>, T>>
    colVector<T> operator%(colVector<T> A, T B){
        for(size_t i = 0; i < A.getSize(); i++) A.at(i) %= B;
        return A;
    }

    template<typename T>
    colVector<T> operator*(T B, colVector<T> A){
        for(size_t i = 0; i < A.getSize(); i++) A.at(i) *= B;
        return A;
    }

    template<typename T>
    colVector<T> operator/(T B, colVector<T> A){
        for(size_t i = 0; i < A.getSize(); i++) A.at(i) /= B;
        return A;
    }

    template<typename T>
    colVector<T> operator%(T B, colVector<T> A){
        for(size_t i = 0; i < A.getSize(); i++) A.at(i) %= B;
        return A;
    }

    template<typename T>
    rowVector<T> operator*(rowVector<T> A, T B){
        for(size_t i = 0; i < A.getSize(); i++) A.at(i) *= B;
        return A;
    }

    template<typename T>
    rowVector<T> operator/(rowVector<T> A, T B){
        for(size_t i = 0; i < A.getSize(); i++) A.at(i) /= B;
        return A;
    }

    template<typename T, typename = std::enable_if_t<std::is_integral_v<T>, T>>
    rowVector<T> operator%(rowVector<T> A, T B){
        for(size_t i = 0; i < A.getSize(); i++) A.at(i) %= B;
        return A;
    }

    template<typename T>
    rowVector<T> operator*(T B, rowVector<T> A){
        for(size_t i = 0; i < A.getSize(); i++) A.at(i) *= B;
        return A;
    }

    template<typename T>
    rowVector<T> operator/(T B, rowVector<T> A){
        for(size_t i = 0; i < A.getSize(); i++) A.at(i) /= B;
        return A;
    }

    template<typename T>
    rowVector<T> operator%(T B, rowVector<T> A){
        for(size_t i = 0; i < A.getSize(); i++) A.at(i) %= B;
        return A;
    }

    template<typename T>
    T operator*(const colVector<T>& A, const colVector<T>& B){
        T result = T{0};
        if(A.getSize() != B.getSize()) throw std::invalid_argument("Not matched.");
        for(size_t i = 0; i < A.getSize(); i++) result += A.at(i) * B.at(i);
        return result;
    }

    template<typename T>
    T operator*(const rowVector<T>& A, const rowVector<T>& B) {
        T result = T{0};
        if(A.getSize() != B.getSize()) throw std::invalid_argument("Not matched.");
        for(size_t i = 0; i < A.getSize(); i++) result += A.at(i) * B.at(i);
        return result;
    }

    template<typename T>
    T operator*(const rowVector<T>& A, const colVector<T>& B){
        T result = T{0};
        if(A.getSize() != B.getSize()) throw std::invalid_argument("Not matched.");
        for(size_t i = 0; i < A.getSize(); i++) result += A.at(i) * B.at(i);
        return result;
    }
    template<typename T>
    colVector<T> transpose(const rowVector<T>& A){
        colVector<T> result(A.getSize());
        for (size_t i = 0; i < A.getSize(); i++) result.at(i) = A.at(i);
        return result;
    }

    template<typename T>
    rowVector<T> transpose(const colVector<T>& A){
        rowVector<T> result(A.getSize());
        for (size_t i = 0; i < A.getSize(); i++) result.at(i) = A.at(i);
        return result;
    }
}