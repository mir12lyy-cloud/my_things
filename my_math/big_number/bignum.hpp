#pragma once

#include<string>
#include<cstring>
#include<iostream>
#include<cmath>
#include<optional>
#include<bit>

namespace mynum {
static inline constexpr unsigned long long normal_size = 10000;
namespace extra_num{
static inline constexpr unsigned long long g = 3;
static inline constexpr unsigned long long P = 119ULL * (1ULL << 23ULL) + 1;
static inline constexpr unsigned long long gi = P / g + 1;
}

using namespace extra_num;

template<typename T>
T power(T a, size_t b, size_t mod) noexcept{
    if (!a) return 0;
    T res = 1;
    while (b > 0) {
        if (b & 1) res = ((res % mod) * (a % mod)) % mod;
        a = ((a % mod) * (a % mod)) % mod;
        b >>= 1;
    }
    return res;
}
template<typename T>
T power(T a, size_t b) noexcept{
    if (!a) return 0;
    T res = 1;
    while (b > 0) {
        if (b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}
template<typename T>
T fast_multiply(T a, T b, size_t mod){
    a = (a % mod + mod) % mod;
    b = (b % mod + mod) % mod;
    T res = 0;
    while(b > 0){
        if(b & 1) res = (res + a) % mod;
        a = (a << 1) % mod;
        b >>= 1;
    }
    return res;
}
template<typename T>
void NTT(T* A, size_t n, int op){
    if(n == 1) return;
    T *A1 = new T[n / 2], *A2 = new T[n / 2];
    for(size_t i = 0; i < n / 2; i++) A1[i] = A[i * 2], A2[i] = A[i * 2 + 1];
    NTT(A1, n / 2, op); NTT(A2, n / 2, op);
    T g1 = power<size_t>(op == 1 ? g : gi, (P - 1) / n, P);
    T gk = 1;
    for(size_t i = 0; i < n / 2; i++){
        A[i] = (A1[i] + A2[i] * gk) % P;
        A[i + n / 2] = (A1[i] - A2[i] * gk % P + P) % P;
        gk = gk * g1 % P;
    }
    delete[] A1; delete[] A2;
}

template<typename T = long long>
class bigNum{
public:
    bigNum(){
        data_ = new T[normal_size];
        num_end_ = data_;
        end_ = data_ + normal_size;
        std::memset(data_, 0, normal_size * sizeof(T));
        positive = true;
    }
    explicit bigNum(T x) : positive(x >= 0){
        data_ = new T[normal_size];
        num_end_ = data_;
        end_ = data_ + normal_size;
        std::memset(data_, 0, normal_size * sizeof(T));
        x = std::abs(x);
        if(!x) {
            ++num_end_;
            return;
        }
        size_t digit = 0;
        while(x > 0){
            data_[digit] = x % 10;
            x /= 10;
            digit++;
        }
        num_end_ = data_ + digit;
    }
    bigNum(const bigNum &x){
        data_ = new T[x.end_ - x.data_];
        end_ = data_ + (x.end_ - x.data_);
        num_end_ = data_ + (x.num_end_ - x.data_);
        positive = x.positive;
        std::memmove(data_, x.data_, (x.end_ - x.data_) * sizeof(T));
    }
    bigNum(bigNum &&x) noexcept
        : data_(std::move(x.data_)), num_end_(std::move(x.num_end_)), end_(std::move(x.end_)), positive(x.positive){
            x.data_ = nullptr;
            x.end_ = nullptr;
            x.num_end_ = nullptr;
            x.positive = true;
    }
    bigNum(const std::string& x){
        if(x.empty()) throw std::invalid_argument("Fail.");
        size_t new_digits = (x.length() - (x[0] == '-' ? 1 : 0));
        size_t new_size = (((x.length() - (x[0] == '-' ? 1 : 0)) + normal_size - 1) / normal_size) * normal_size;
        data_ = new T[new_size];
        end_ = data_ + new_size;
        num_end_ = data_ + new_digits;
        std::memset(data_, 0, new_size * sizeof(T));
        positive = (x[0] != '-');
        for(size_t i = 0; i < new_digits; i++) data_[i] = x[x.length() - 1 - i] - '0';
    }
    ~bigNum(){
        num_end_ = nullptr;
        end_ = nullptr;
        delete[] data_;
        data_ = nullptr;
    }

    bigNum& operator=(const bigNum& x){
        if(this == &x) return *this;
        delete[] data_;
        data_ = new T[x.end_ - x.data_];
        end_ = data_ + (x.end_ - x.data_);
        num_end_ = data_ + (x.num_end_ - x.data_);
        positive = x.positive;
        std::memmove(data_, x.data_, (x.end_ - x.data_) * sizeof(T));
        return *this;
    }
    bigNum& operator=(bigNum &&x) noexcept{
        delete[] data_;
        data_ = std::move(x.data_);
        end_ = std::move(x.end_);
        num_end_ = std::move(x.num_end_);
        x.data_ = nullptr;
        x.end_ = nullptr;
        x.num_end_ = nullptr;
        positive = x.positive;
        x.positive = true;
        return *this;
    }
    bigNum& operator=(T x){
        if(!x){
            resize(1);
            data_[0] = 0;
            return *this;
        }
        if(x < 0) positive = false;
        x = std::abs(x);
        size_t digit = 0;
        while(x > 0){
            data_[digit] = x % 10;
            x /= 10;
            digit++;
        }
        resize(digit);
        return *this;
    }

    void swap(bigNum& B) noexcept {
        std::swap(data_, B.data_);
        std::swap(num_end_, B.num_end_);
        std::swap(end_, B.end_);
        std::swap(positive, B.positive);
    }

    friend void swap(bigNum& A, bigNum& B) noexcept{
        std::swap(A.data_, B.data_);
        std::swap(A.num_end_, B.num_end_);
        std::swap(A.end_, B.end_);
        std::swap(A.positive, B.positive);
    }

    constexpr unsigned long long capacity() const noexcept {return end_ - data_;}
    constexpr unsigned long long digits() const noexcept {return num_end_ - data_;}
    bool operator==(const bigNum& B) const noexcept{
        if(positive != B.positive) return false;
        if(digits() != B.digits()) return false;
        for(size_t i = 0; i < digits(); i++){
            if(data_[i] != B.data_[i]) return false;
        }
        return true;
    }
    bool operator!=(const bigNum& B) const noexcept{
        if(positive != B.positive) return true;
        if(digits() != B.digits()) return true;
        for(size_t i = 0; i < digits(); i++){
            if(data_[i] != B.data_[i]) return true;
        }
        return false;
    }
    bool operator>=(const bigNum& B) const noexcept{
        if(positive != B.positive) return positive == true;
        if(digits() < B.digits()) return positive == false;
        if(digits() > B.digits()) return positive == true;
        for(size_t i = 0; i < digits(); i++){
            if(positive && (data_[digits() - 1 - i] > B.data_[digits() - 1 - i])) return true;
            else if(positive && (data_[digits() - 1 - i] < B.data_[digits() - 1 - i])) return false;
            else if(!positive && (data_[digits() - 1 - i] < B.data_[digits() - 1 - i])) return true;
            else if(!positive && (data_[digits() - 1 - i] > B.data_[digits() - 1 - i])) return false;
        }
        return true;
    }
    bool operator<=(const bigNum& B) const noexcept{
        if(positive != B.positive) return positive == false;
        if(digits() < B.digits()) return positive == true;
        if(digits() > B.digits()) return positive == false;
        for(size_t i = 0; i < digits(); i++){
            if(positive && (data_[digits() - 1 - i] > B.data_[digits() - 1 - i])) return false;
            else if(positive && (data_[digits() - 1 - i] < B.data_[digits() - 1 - i])) return true;
            else if(!positive && (data_[digits() - 1 - i] < B.data_[digits() - 1 - i])) return false;
            else if(!positive && (data_[digits() - 1 - i] > B.data_[digits() - 1 - i])) return true;
        }
        return true;
    }
    bool operator>(const bigNum& B) const noexcept{
        if(positive != B.positive) return positive == true;
        if(digits() < B.digits()) return positive == false;
        if(digits() > B.digits()) return positive == true;
        for(size_t i = 0; i < digits(); i++){
            if(positive && (data_[digits() - 1 - i] > B.data_[digits() - 1 - i])) return true;
            else if(positive && (data_[digits() - 1 - i] < B.data_[digits() - 1 - i])) return false;
            else if(!positive && (data_[digits() - 1 - i] < B.data_[digits() - 1 - i])) return true;
            else if(!positive && (data_[digits() - 1 - i] > B.data_[digits() - 1 - i])) return false;
        }
        return false;
    }
    bool operator<(const bigNum& B) const noexcept{
        if(positive != B.positive) return positive == false;
        if(digits() < B.digits()) return positive == true;
        if(digits() > B.digits()) return positive == false;
       for(size_t i = 0; i < digits(); i++){
            if(positive && (data_[digits() - 1 - i] > B.data_[digits() - 1 - i])) return false;
            else if(positive && (data_[digits() - 1 - i] < B.data_[digits() - 1 - i])) return true;
            else if(!positive && (data_[digits() - 1 - i] < B.data_[digits() - 1 - i])) return false;
            else if(!positive && (data_[digits() - 1 - i] > B.data_[digits() - 1 - i])) return true;
        }
        return false;
    }
    bool operator==(T B) const noexcept{
        if(!B) return digits() == 1 && data_[0] == 0;
        if((B > 0 && !positive) || (B < 0 && positive)) return false;
        B = std::abs(B);
        size_t digit = 0;
        while(B > 0){
            if(B % 10 != data_[digit]) return false;
            B /= 10;
            digit++;
        }
        return digit == digits();
    }
    bool operator!=(const T& B) const noexcept{
        if(!B) return digits() != 1 || data_[0] != 0;
        if((B > 0 && !positive) || (B < 0 && positive)) return true;
        B = std::abs(B);
        size_t digit = 0;
        while(B > 0){
            if(B % 10 != data_[digit]) return true;
            B /= 10;
            digit++;
        }
        return digit != digits();
    }
    bool operator>=(T B) const noexcept{
        if(!B) return positive;
        if(B > 0 && !positive) return false;
        if(B < 0 && positive) return true;
        B = std::abs(B);
        T C = B;
        size_t digit = 0;
        while(C > 0){
            C /= 10;
            digit++;
        }
        if(digit != digits()) return (digit > digits() && !positive) || (digit < digits() && positive);
        for(int i = digit - 1; i >= 0; i--){
            T this_digit = (B / power<T>(10, i)) % 10;
            if(this_digit > data_[i]) return !positive;
            if(this_digit < data_[i]) return positive; 
        }
        return true;
    }
    bool operator<=(T B) const noexcept{
        if(!B) return !positive || *this == 0;
        if(B > 0 && !positive) return true;
        if(B < 0 && positive) return false;
        B = std::abs(B);
        T C = B;
        size_t digit = 0;
        while(C > 0){
            C /= 10;
            digit++;
        }
        if(digit != digits()) return (digit < digits() && !positive) || (digit > digits() && positive);
        for(int i = digit - 1; i >= 0; i--){
            T this_digit = (B / power<T>(10, i)) % 10;
            if(this_digit > data_[i]) return positive;
            if(this_digit < data_[i]) return !positive;
        }
        return true;
    }
    bool operator>(T B) const noexcept{
        if(!B) return positive && data_[0] != 0;
        if(B > 0 && !positive) return false;
        if(B < 0 && positive) return true;
        B = std::abs(B);
        T C = B;
        size_t digit = 0;
        while(C > 0){
            C /= 10;
            digit++;
        }
        if(digit != digits()) return (digit > digits() && !positive) || (digit < digits() && positive);
        for(int i = digit - 1; i >= 0; i--){
            T this_digit = (B / power<T>(10, i)) % 10;
            if(this_digit > data_[i]) return !positive;
            if(this_digit < data_[i]) return positive; 
        }
        return false;
    }
    bool operator<(T B) const noexcept{
        if(!B) return !positive;
        if(B > 0 && !positive) return true;
        if(B < 0 && positive) return false;
        B = std::abs(B);
        T C = B;
        size_t digit = 0;
        while(C > 0){
            C /= 10;
            digit++;
        }
        if(digit != digits()) return (digit < digits() && !positive) || (digit > digits() && positive);
        for(int i = digit - 1; i >= 0; i--){
            T this_digit = (B / power<T>(10, i)) % 10;
            if(this_digit > data_[i]) return positive;
            if(this_digit < data_[i]) return !positive;
        }
        return false;
    }

    bigNum operator-() const{
        bigNum temp = *this;
        temp.positive = !positive;
        return temp;
    }
    friend void NTT<T>(T* A, size_t n, int op);

    explicit operator bool() const noexcept{return *this == 0;}
    [[nodiscard]] explicit operator int() const noexcept{
        if(*this > INT32_MAX || *this < INT32_MIN){
            int res = 0;
            for(size_t i = 0; i < digits(); i++){
                res = ((res % (INT32_MAX + 1ULL)) + (data_[i] * power<size_t>(10, i, INT32_MAX + 1ULL)) % (INT32_MAX + 1ULL)) % (INT32_MAX + 1ULL);
            }
            return positive ? res : -res;
        }
        int res = 0;
        for(size_t i = 0; i < digits(); i++) res += data_[i] * power(10U, i);
        return positive ? res : -res;
    }
    [[nodiscard]] explicit operator unsigned int() const noexcept{
        unsigned int res = 0;
        for(size_t i = 0; i < digits(); i++) res += data_[i] * power(10U, i);
        return res;
    }
    [[nodiscard]] explicit operator long long() const noexcept{
        if(*this > INT64_MAX || *this < INT64_MIN){
            long long res = 0;
            for(size_t i = 0; i < digits(); i++){
                res = ((res % (INT64_MAX + 1ULL)) + (data_[i] * power<size_t>(10, i, INT64_MAX + 1ULL)) % (INT64_MAX + 1ULL)) % (INT64_MAX + 1ULL);
            }
            return positive ? res : -res;
        }
        long long res = 0;
        for(size_t i = 0; i < digits(); i++) res += data_[i] * power(10ULL, i);
        return positive ? res : -res;
    }
    [[nodiscard]] explicit operator unsigned long long() const noexcept{
        unsigned long long res = 0;
        for(size_t i = 0; i < digits(); i++) res += data_[i] * power(10ULL, i);
        return res;
    }

    [[nodiscard]] std::optional<int> turn_to_int() const noexcept{
        if(*this > INT32_MAX || *this < INT32_MIN) return std::nullopt;
        return static_cast<int>(*this);
    }
    [[nodiscard]] std::optional<unsigned int> turn_to_unsigned_int() const noexcept{
        if(*this > UINT32_MAX) return std::nullopt;
        return static_cast<unsigned int>(*this);
    }
    [[nodiscard]] std::optional<long long> turn_to_long_long() const noexcept{
        if(*this > INT64_MAX || *this < INT64_MIN) return std::nullopt;
        return static_cast<long long>(*this);
    }
    [[nodiscard]] std::optional<unsigned long long> turn_to_unsigned_long_long() const noexcept{
        if(*this > UINT64_MAX) return std::nullopt;
        return static_cast<unsigned long long>(*this);
    }
    std::string turn_to_string() {
        std::string returnString;
        returnString.reserve(digits() + 1);
        if(!positive) returnString.push_back('-');
        for(size_t i = 0; i < digits(); i++){
            returnString.push_back(data_[digits() - 1 - i] + '0');
        }
        return returnString;
    }
 
    bigNum abs() const{
        bigNum temp = *this;
        temp.positive = true;
        return temp;
    }

    bigNum& operator+=(const bigNum& B){
        if(positive != B.positive) return *this -= -B;
        size_t from = std::min(digits(), B.digits());
        size_t newsize = std::max(digits(), B.digits());
        resize(newsize);
        for(size_t i = 0; i < from; i++) data_[i] += B.data_[i];
        for(size_t i = from; i < B.digits(); i++) data_[i] = B.data_[i];
        T carry = 0;
        for(size_t i = 0; i < newsize; i++){
            data_[i] += carry;
            carry = data_[i] / 10;
            data_[i] %= 10;
        }
        if(carry > 0) push_back(carry);
        return *this;
    }
    bigNum& operator-=(const bigNum& B){
        if(positive != B.positive) return *this += -B;
        size_t from = std::min(digits(), B.digits());
        size_t newsize = std::max(digits(), B.digits());
        T borrow = 0;
        if((*this > B && !positive) || (*this < B && positive)){
            resize(newsize);
            positive = !positive;
            for(size_t i = 0; i < from; i++){
                if(B.data_[i] >= data_[i] + borrow){
                    data_[i] = B.data_[i] - data_[i] - borrow;
                    borrow = 0;
                }
                else{
                    data_[i] = B.data_[i] + (10 - data_[i]) - borrow;
                    borrow = 1;
                }
            }
            for(size_t i = from; i < newsize; i++){
                if(!B.data_[i] && borrow){
                    data_[i] = 9;
                    borrow = 1;
                }
                else{
                    data_[i] = B.data_[i] - borrow;
                    borrow = 0;
                }
            }
        }
        else{
            for(size_t i = 0; i < from; i++){
                if(data_[i] >= B.data_[i] + borrow){
                    data_[i] = data_[i] - B.data_[i] - borrow;
                    borrow = 0;
                }
                else{
                    data_[i] = data_[i] + (10 - B.data_[i]) - borrow;
                    borrow = 1;
                }
            }
            for(size_t i = from; i < newsize && borrow; i++){
                if(data_[i]){
                    data_[i]--;
                    borrow = 0;
                }
                else{
                    data_[i] = 9;
                    borrow = 1;
                }
            }
        }
        for(size_t i = newsize - 1; i != 0 && data_[i] == 0; i--) pop_back();
        return *this;   
    }
    bigNum& operator*=(bigNum B){
        size_t m = 0, n = 0;
        for(size_t m = digits() + B.digits(), n = 1; n <= m; n <<= 1);
        resize(n), B.resize(n);
        NTT(data_, n, 1); NTT(B.data_, n, 1);
        for(size_t i = 0; i < n; i++) data_[i] *= B.data_[i];
        NTT(data_, n, -1);
        T inv_n = power<size_t>(n, P - 2, P);
        T carry = 0;
        for(size_t i = 0; i < n; i++){
            data_[i] = ((1LL * data_[i] * inv_n) % P) + carry;
            carry = data_[i] / 10;
            data_[i] %= 10;
        }
        if(carry > 0) push_back(carry);
        else for(size_t i = n - 1; i != 0 && data_[i] == 0; i--) pop_back();
        positive = positive == B.positive;
        return *this;
    }
    bigNum& operator/=(const bigNum& B) {
        if(B == 0) throw std::invalid_argument("Input number is a zero.");
        if(*this == 0) return *this;
        if(B.digits() > digits()){
            resize(1);
            data_[0] = 0;
            return *this;
        }
        
    }
    bigNum& operator%=(const bigNum& B){
        if(B == 0) throw std::invalid_argument("Input number is a zero.");
        if(*this == 0) return *this;
        return *this;
    }
    bigNum& operator+=(T B){
        if(!B) return *this;
        if((positive && B < 0) || (!positive && B > 0)) return *this -= -B;
        B = std::abs(B);
        size_t digit = 0;
        T carry = 0;
        while(B > 0){
            if(digit >= digits()) push_back((B % 10) + carry);
            else data_[digit] += (B % 10) + carry;
            B /= 10;
            carry = data_[digit] / 10;
            data_[digit] %= 10;
            digit++;
        }
        if(carry > 0) push_back(carry);
        return *this;
    }
    bigNum& operator-=(T B){
        if(!B) return *this;
        if((positive && B < 0) || (!positive && B > 0)) return *this += -B;
        
        T C = std::abs(B);
        size_t digit = 0;
        while(C > 0){
            C /= 10;
            digit++;
        }
        size_t from = std::min(digits(), digit);
        size_t newsize = std::max(digits(), digit);
        B = std::abs(B);
        if((*this > B && !positive) || (*this < B && positive)){
            resize(newsize);
            positive = !positive;
            T borrow = 0;
            for(size_t i = 0; i < from; i++){
                T now = B % 10;
                if(now >= data_[i] + borrow){
                    data_[i] = now - data_[i] - borrow;
                    borrow = 0;
                }
                else{
                    data_[i] = 10 + now - data_[i] - borrow;
                    borrow = 1;
                }
                B /= 10;
            }
            for(size_t i = from; i < newsize; i++){
                T now = B % 10;
                if(now || !borrow){
                    data_[i] = now - borrow;
                    borrow = 0;
                }
                else{
                    data_[i] = 9;
                    borrow = 1;
                }
                B /= 10;
            }
        }
        else{
            T borrow = 0;
            for(size_t i = 0; i < from; i++){
                T now = B % 10;
                if(data_[i] >= now + borrow){
                    data_[i] = data_[i] - now - borrow;
                    borrow = 0;
                }
                else{
                    data_[i] = 10 + data_[i] - now - borrow;
                    borrow = 1;
                }
                B /= 10;
            }
            for(size_t i = from; i < newsize && borrow; i++){
                if(data_[i]){
                    data_[i]--;
                    borrow = 0;
                }
                else{
                    data_[i] = 9;
                    borrow = 1;
                }
            }
        }
        for(size_t i = newsize - 1; i != 0 && data_[i] == 0; i--) pop_back();
        return *this;
    }
    bigNum& operator*=(T B){
        if(B < 0) positive = !positive;
        if(B == 0){
            resize(1);
            data_[0] = 0;
            return *this;
        }
        B = std::abs(B);
        T carry = 0;
        for(size_t i = 0; i < digits(); i++){
            T this_digit = data_[i];
            data_[i] = data_[i] * (B % 10) + carry;
            carry = ((B / 10) * this_digit) + (data_[i] / 10);
            data_[i] %= 10;
        }
        while(carry > 0){
            push_back(carry % 10);
            carry /= 10;
        }
        return *this;
    }
    bigNum& operator/=(T B){
        if(B == 0) throw std::invalid_argument("Input number is a zero.");
        if(*this == 0) return *this;
        T C = std::abs(B);
        if(B < 0) positive = !positive;
        T r = 0;
        for(size_t i = 0; i < digits(); i++){
            T temp =  r * 10 + data_[digits() - 1 - i];
            data_[digits() - 1 - i] = temp / B;
            r = temp % B;  
        }
        for(size_t i = digits() - 1; i != 0 && data_[i] == 0; i--) pop_back();
        return *this;
    }
    bigNum& operator%=(T B){
        if(B == 0) throw std::invalid_argument("Input number is a zero.");
        if(*this == 0) return *this;
        T res = 0;
        for(size_t i = 0; i < digits(); i++){
            res = (res * 10 + data_[i]) % B;
        }
        *this = res;
        return *this;
    }
    bigNum& operator++(){return *this += 1;}
    bigNum& operator--(){return *this -= 1;}
    bigNum operator++(int){
        bigNum temp = *this;
        ++(*this);
        return temp;
    }
    bigNum operator--(int){
        bigNum temp = *this;
        --(*this);
        return temp;
    }

    friend std::istream& operator>>(std::istream& is, bigNum& B){
        std::string s;
        is >> s;
        B = bigNum(s);
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, const bigNum& B){
        if(!B.positive) os << '-';
        for(size_t i = 0; i < B.digits(); i++) os << B.data_[B.digits() - 1 - i];
        return os;
    }

private:
    T* data_ = nullptr;
    T* num_end_ = nullptr;
    T* end_ = nullptr;
    bool positive = true;
    void reserve(size_t newcapcity){
        if(newcapcity <= capacity()) return;
        size_t last_digits = num_end_ - data_;
        size_t newalloc = (newcapcity + normal_size - 1) / normal_size;
        T* to = new T[newalloc * normal_size];
        std::memset(to, 0, newalloc * normal_size * sizeof(T));
        std::memmove(to, data_, last_digits * sizeof(T));
        delete[] data_;
        data_ = to;
        num_end_ = data_ + last_digits;
        end_ = data_ + newalloc * normal_size;
    }
    void expand(){
        size_t last_digits = num_end_ - data_;
        size_t last_capacity = end_ - data_;
        T* to = new T[2 * last_capacity];
        std::memset(to, 0, 2 * last_capacity * sizeof(T));
        std::memmove(to, data_, last_digits * sizeof(T));
        delete[] data_;
        data_ = to;
        num_end_ = data_ + last_digits;
        end_ = data_ + 2 * last_capacity;
    }
    void resize(size_t newsize){
        if(newsize > capacity()) reserve(newsize);
        num_end_ = data_ + newsize;
    }
    void push_back(T value = 0){
        if(digits() == capacity()) expand();
        *num_end_ = value;
        ++num_end_;
    }
    void pop_back(){
        if(data_ == num_end_) return;
        --num_end_;
    }
};
}
