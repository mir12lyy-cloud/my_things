#pragma once

#include<vector>
#include<cmath>
#include<type_traits>
#include<iostream>
#include<numeric>
#include<initializer_list>
#include<algorithm> //Necessary headers.
#include "extra_func.hpp"

namespace my_math{
    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>, T>>
    class row_vector final{
    public:
        row_vector() : row_vector_size(0) , vec(0), default_init(true){};
        row_vector(std::initializer_list<T> list) : row_vector_size(list.size()), vec(list) {}
        row_vector(size_t s, const T init = T{0}) : row_vector_size(s), vec(s, init){}
        row_vector(const std::vector<T> &init) : row_vector_size(init.size()), vec(init.size(), 0){
            for(size_t i = 0; i < init.size(); i++) vec[i] = init[i];
        }
        void fill(T init = T{0}){std::fill(vec.begin(), vec.end(), init);}
        void assign(size_t s, const T init = T{0}) {
            if(!default_init) throw std::invalid_argument("A initialized vector can't be assign again!")
            vec.assign(s, init); default_init = false;
        }
        void assign(std::initializer_list<T> list) {
            if(!default_init) throw std::invalid_argument("A initialized vector can't be assign again!")
            vec.assign(list); default_init = false;
        }

        T& operator()(size_t idx) {return vec[idx];}
        const T& operator()(size_t idx) const {return vec[idx];}
        T& operator[](size_t idx) {return vec[idx];}
        const T& operator[](size_t idx) const {return vec[idx];}
        T& at(size_t idx){
            if(idx >= row_vector_size) throw std::out_of_range("Out of the Vector!");
            return vec[idx];
        }
        const T& at(size_t idx) const{
            if(idx >= row_vector_size) throw std::out_of_range("Out of the Vector!");
            return vec[idx];
        }
        size_t get_size() const{return row_vector_size;}
        bool operator==(const row_vector& B){
            if(B.get_size() != row_vector_size) return false;
            for(size_t i = 0; i < row_vector_size; i++){
                if(B.at(i) != vec[i]) return false;
            }
            return true;
        }
        bool operator!=(const row_vector& B){
            if(B.get_size() != row_vector_size) return true;
            for(size_t i = 0; i < row_vector_size; i++){
                if(B.at(i) != vec[i]) return true;
            }
            return false;
        }
        row_vector& operator+=(const row_vector& B){
            if(B.get_size() != row_vector_size) throw std::invalid_argument("Not matched.");
            for(size_t i = 0; i < row_vector_size; i++) vec[i] += B.at(i);
            return *this;
        }
        row_vector& operator-=(const row_vector& B){
            if(B.get_size() != row_vector_size) throw std::invalid_argument("Not matched.");
            for(size_t i = 0; i < row_vector_size; i++) vec[i] -= B.at(i);
            return *this;
        }
        row_vector& operator*=(const T B){
            for(auto &i : vec) i *= B;
            return *this;
        }
        row_vector& operator/=(const T B){
            if(B == T{0}) throw std::invalid_argument("Divsion by zero.");
            for(auto &i : vec) i /= B;
            return *this;
        }
        row_vector& operator%=(const T B){
            static_assert(std::is_integral_v<T>);
            for(auto &i : vec) i %= B;
            return *this;
        }
        long double get_norm(size_t L = 2){
            long double result = 0.0;
            if(L == 1){
                for(const auto &i : vec) result += std::abs(i);
                return result;
            }
            for(const auto &i : vec) result += extraFunc::pow(static_cast<long double>(std::abs(i)), L);
            return std::pow(result, (1.0 / static_cast<long double>(L)));
        }
        T get_inf_norm() const{
            T result = vec[0];
            for(const auto& i : vec) result = std::max(result, i);
            return result;
        }
    private:
        bool default_init = false;
        size_t row_vector_size;
        std::vector<T> vec;
    };

    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>, T>>
    class col_vector final{
    public:
        col_vector() : col_vector_size(0) , vec(0), default_init(true){};
        col_vector(std::initializer_list<T> list) : col_vector_size(list.size()), vec(list) {}
        col_vector(size_t s, const T init = T{0}) : col_vector_size(s), vec(s, init){}
        col_vector(const std::vector<T> &init) : col_vector_size(init.size()), vec(init.size()){
            for(size_t i = 0; i < init.size(); i++) vec[i] = init[i];
        }
        void fill(T init = T{0}){std::fill(vec.begin(), vec.end(), init);}
        void assign(size_t s, const T init = T{0}) {
            if(!default_init) throw std::invalid_argument("A initialized vector can't be assign again!")
            vec.assign(s, init); default_init = false;
        }
        void assign(std::initializer_list<T> list) {
            if(!default_init) throw std::invalid_argument("A initialized vector can't be assign again!")
            vec.assign(list); default_init = false;
        }
        
        T& operator()(size_t idx) {return vec[idx];}
        const T& operator()(size_t idx) const {return vec[idx];}
        T& operator[](size_t idx) {return vec[idx];}
        const T& operator[](size_t idx) const {return vec[idx];}
        T& at(size_t idx){
            if(idx >= col_vector_size) throw std::out_of_range("Out of the Vector!");
            return vec[idx];
        }
        const T& at(size_t idx) const{
            if(idx >= col_vector_size) throw std::out_of_range("Out of the Vector!");
            return vec[idx];
        }
        size_t get_size() const{return col_vector_size;}
        bool operator==(const col_vector& B){
            if(B.get_size() != col_vector_size) return false;
            for(size_t i = 0; i < col_vector_size; i++){
                if(B.at(i) != vec[i]) return false;
            }
            return true;
        }
        bool operator!=(const col_vector& B){
            if(B.get_size() != col_vector_size) return true;
            for(size_t i = 0; i < col_vector_size; i++){
                if(B.at(i) != vec[i]) return true;
            }
            return false;
        }
        col_vector& operator+=(const col_vector& B){
            if(B.get_size() != col_vector_size) throw std::invalid_argument("Not matched.");
            for(size_t i = 0; i < col_vector_size; i++) vec[i] += B.at(i);
            return *this;
        }
        col_vector& operator-=(const col_vector& B){
            if(B.get_size() != col_vector_size) throw std::invalid_argument("Not matched.");
            for(size_t i = 0; i < col_vector_size; i++) vec[i] -= B.at(i);
            return *this;
        }
        col_vector& operator*=(const T B){
            for(auto &i : vec) i *= B;
            return *this;
        }
        col_vector& operator/=(const T B){
            if(B == T{0}) throw std::invalid_argument("Divsion by zero.");
            for(auto &i : vec) i /= B;
            return *this;
        }
        col_vector& operator%=(const T B){
            static_assert(std::is_integral_v<T>);
            for(auto &i : vec) i %= B;
            return *this;
        }
        long double get_norm(size_t L = 2){
            long double result = 0;
            if(L == 1){
                for(const auto &i : vec) result += std::abs(i);
                return static_cast<long double>(result);
            }
            for(const auto &i : vec) result += extraFunc::pow(static_cast<long double>(std::abs(i)), L);
            return std::pow(result, (1.0 / static_cast<long double>(L)));
        }
        T get_inf_norm() const{
            T result = vec[0];
            for(const auto& i : vec) result = std::max(result, i);
            return result;
        }
    private:
        bool default_init = false;
        size_t col_vector_size;
        std::vector<T> vec;
    };

    template<typename T>
    std::istream& operator>>(std::istream& os, col_vector<T>& A) {
        for (size_t i = 0; i < A.get_size(); i++) is >> A.at(i);
        return is;
    }

    template<typename T>
    std::istream& operator>>(std::istream& os, row_vector<T>& A) {
        for (size_t i = 0; i < A.get_size(); i++) is >> A.at(i);
        return is;
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const col_vector<T>& A) {
        for (size_t i = 0; i < A.get_size(); i++) os << A.at(i) << "\n";
        return os;
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const row_vector<T>& A) {
        for (size_t i = 0; i < A.get_size(); i++) os << A.at(i) << " ";
        return os;
    }

    template<typename T>
    col_vector<T> operator+(const col_vector<T>& A, const col_vector<T>& B){
        if(A.get_size() != B.get_size()) throw std::invalid_argument("No matched.");
        col_vector<T> result(A.get_size(), 0.0);
        for(size_t i = 0; i < A.get_size(); i++) result.at(i) = A.at(i) + B.at(i);
        return result;
    }

    template<typename T>
    col_vector<T> operator-(const col_vector<T>& A, const col_vector<T>& B){
        if(A.get_size() != B.get_size()) throw std::invalid_argument("No matched.");
        col_vector<T> result(A.get_size(), 0.0);
        for(size_t i = 0; i < A.get_size(); i++) result.at(i) = A.at(i) - B.at(i);
        return result;
    }

    template<typename T>
    row_vector<T> operator+(const row_vector<T>& A, const row_vector<T>& B){
        if(A.get_size() != B.get_size()) throw std::invalid_argument("No matched.");
        row_vector<T> result(A.get_size(), 0.0);
        for(size_t i = 0; i < A.get_size(); i++) result.at(i) = A.at(i) + B.at(i);
        return result;
    }

    template<typename T>
    row_vector<T> operator-(const row_vector<T>& A, const row_vector<T>& B){
        if(A.get_size() != B.get_size()) throw std::invalid_argument("No matched.");
        row_vector<T> result(A.get_size(), 0.0);
        for(size_t i = 0; i < A.get_size(); i++) result.at(i) = A.at(i) - B.at(i);
        return result;
    }

    template<typename T>
    col_vector<T> operator*(col_vector<T> A, T B){
        for(size_t i = 0; i < A.get_size(); i++) A.at(i) *= B;
        return A;
    }

    template<typename T>
    col_vector<T> operator/(col_vector<T> A, T B){
        for(size_t i = 0; i < A.get_size(); i++) A.at(i) /= B;
        return A;
    }

    template<typename T, typename = std::enable_if_t<std::is_integral_v<T>, T>>
    col_vector<T> operator%(col_vector<T> A, T B){
        for(size_t i = 0; i < A.get_size(); i++) A.at(i) %= B;
        return A;
    }

    template<typename T>
    col_vector<T> operator*(T B, col_vector<T> A){
        for(size_t i = 0; i < A.get_size(); i++) A.at(i) *= B;
        return A;
    }

    template<typename T>
    col_vector<T> operator/(T B, col_vector<T> A){
        for(size_t i = 0; i < A.get_size(); i++) A.at(i) /= B;
        return A;
    }

    template<typename T>
    col_vector<T> operator%(T B, col_vector<T> A){
        for(size_t i = 0; i < A.get_size(); i++) A.at(i) %= B;
        return A;
    }

    template<typename T>
    row_vector<T> operator*(row_vector<T> A, T B){
        for(size_t i = 0; i < A.get_size(); i++) A.at(i) *= B;
        return A;
    }

    template<typename T>
    row_vector<T> operator/(row_vector<T> A, T B){
        for(size_t i = 0; i < A.get_size(); i++) A.at(i) /= B;
        return A;
    }

    template<typename T, typename = std::enable_if_t<std::is_integral_v<T>, T>>
    row_vector<T> operator%(row_vector<T> A, T B){
        for(size_t i = 0; i < A.get_size(); i++) A.at(i) %= B;
        return A;
    }

    template<typename T>
    row_vector<T> operator*(T B, row_vector<T> A){
        for(size_t i = 0; i < A.get_size(); i++) A.at(i) *= B;
        return A;
    }

    template<typename T>
    row_vector<T> operator/(T B, row_vector<T> A){
        for(size_t i = 0; i < A.get_size(); i++) A.at(i) /= B;
        return A;
    }

    template<typename T>
    row_vector<T> operator%(T B, row_vector<T> A){
        for(size_t i = 0; i < A.get_size(); i++) A.at(i) %= B;
        return A;
    }

    template<typename T>
    T operator*(const col_vector<T>& A, const col_vector<T>& B){
        T result = T{0};
        if(A.get_size() != B.get_size()) throw std::invalid_argument("Not matched.");
        for(size_t i = 0; i < A.get_size(); i++) result += A.at(i) * B.at(i);
        return result;
    }

    template<typename T>
    T operator*(const row_vector<T>& A, const row_vector<T>& B) {
        T result = T{0};
        if(A.get_size() != B.get_size()) throw std::invalid_argument("Not matched.");
        for(size_t i = 0; i < A.get_size(); i++) result += A.at(i) * B.at(i);
        return result;
    }

    template<typename T>
    T operator*(const row_vector<T>& A, const col_vector<T>& B){
        T result = T{0};
        if(A.get_size() != B.get_size()) throw std::invalid_argument("Not matched.");
        for(size_t i = 0; i < A.get_size(); i++) result += A.at(i) * B.at(i);
        return result;
    }
    template<typename T>
    col_vector<T> transpose(const row_vector<T>& A){
        col_vector<T> result(A.get_size());
        for (size_t i = 0; i < A.get_size(); i++) result.at(i) = A.at(i);
        return result;
    }

    template<typename T>
    row_vector<T> transpose(const col_vector<T>& A){
        row_vector<T> result(A.get_size());
        for (size_t i = 0; i < A.get_size(); i++) result.at(i) = A.at(i);
        return result;
    }
}