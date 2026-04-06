#pragma once
#include<concepts>
#include<iostream>
#include<numeric>
#include<compare>
#include<exception>

namespace mymath{
	template<std::integral T>
	class fract final{
	public:
		constexpr fract(T a = T{0}, T b = T{1}) noexcept
		: x(std::abs(a)), y(std::abs(b) == 0 ? 1 : std::abs(b)), negative((a < 0) ^ (b < 0)) { reduce(); }
		friend std::istream& operator>>(std::istream& is, fract& a) noexcept { 
			is >> a.x >> a.y;
			a.negative = (a.x < 0) ^ (a.y < 0);
			a.reduce();
			return is; 
		}
		friend std::ostream& operator<<(std::ostream& os, const fract& a) noexcept {
			if(a.negative) os << '-'; 
			os << a.x << '/' << a.y;
			return os;
		}

		constexpr T& get_x() noexcept {return x;}
		constexpr const T& get_x() const noexcept {return x;}
		constexpr T& get_y() noexcept {return y;}
		constexpr const T& get_y() const noexcept {return y;}

		constexpr operator bool() noexcept { return x == T{0}; }
		constexpr operator char() noexcept { return (negative ? -1 : 1) * static_cast<char>(x / y); }
		constexpr operator short() noexcept { return (negative ? -1 : 1) * static_cast<short>(x / y); }
		constexpr operator int() noexcept { return (negative ? -1 : 1) * static_cast<int>(x / y); }
		constexpr operator long() noexcept { return (negative ? -1 : 1) * static_cast<long>(x / y); }
		constexpr operator long long() noexcept { return (negative ? -1 : 1) * static_cast<long long>(x / y); }
		constexpr operator unsigned char() noexcept { return static_cast<unsigned char>(x / y); }
		constexpr operator unsigned short() noexcept { return static_cast<unsigned short>(x / y); }
		constexpr operator unsigned int() noexcept { return static_cast<unsigned int>(x / y); }
		constexpr operator unsigned long long() noexcept { return static_cast<unsigned long long>(x / y); }
		constexpr operator float() noexcept { return (negative ? -1 : 1) * static_cast<float>(x * 1.0f / y); }
		constexpr operator double() noexcept { return (negative ? -1 : 1) * static_cast<double>(x * 1.0 / y); }
		constexpr operator long double() noexcept { return (negative ? -1 : 1) * static_cast<long double>(x * 1.0l / y); }

		constexpr fract operator-() noexcept { auto temp = *this; temp.negative = !negative; return temp; }
		constexpr bool operator==(const fract& other) const noexcept { return negative == other.negative && x == other.x && y == other.y; }
		constexpr fract& operator+=(const fract& other) noexcept {
			if(negative != other.negative) return *this -= -other;
			T temp1_ = std::gcd()
		}
		constexpr fract& operator-=(const fract& other) noexcept {
			if(negative != other.negative) return *this += -other;
		}
		constexpr fract& operator*=(const fract& other) noexcept {
			negative = negative != other.negative;
			T temp1_ = std::gcd(y, other.x), temp2_ = std::gcd(x, other.y);
			T result1_ = (x / temp2_) * (other.x / temp1_), result2 = (y / temp1_) * (other.y / temp2_);
			x = result1_, y = result2;
			return *this;			
		}
		constexpr fract& operator/=(const fract& other) {
			if(other.x == 0) throw std::invalid_argument("Never put zero in division!");
			negative = negative != other.negative;
			T temp1_ = std::gcd(y, other.y), temp2_ = std::gcd(x, other.x);
			T result1_ = (x / temp2_) * (other.y / temp1_), result2 = (y / temp1_) * (other.x / temp2_);
			x = result1_, y = result2;
			return *this;
		}
		template<std::integral U>
		constexpr fract& operator^=(U power) {
			if(x == 0 && power < 1) throw std::invalid_argument("Never put zero in division!");

		}
	private:
		T x, y;
		bool negative;
		constexpr void reduce() noexcept { T temp = std::gcd(x, y); x /= temp, y /= temp;}
	};
}