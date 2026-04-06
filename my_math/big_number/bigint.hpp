#pragma once
#include<concepts>
#include<vector>
#include<string>
#include<compare>
#include<iostream>

namespace mymath{
	namespace some_constant_number{
		static constexpr unsigned long long num_p1 = 119ULL * (1ULL << 23ULL) + 1;
		static constexpr unsigned long long num_p2 = 479ULL * (1ULL << 21ULL) + 1;
		static constexpr unsigned long long num_p3 = 7ULL * (1ULL << 26ULL) + 1;
		static constexpr unsigned long long num_g = 3;
	}

	template<size_t Base_of_Bits>
	requires(Base_of_Bits == 8 || Base_of_Bits == 16 || Base_of_Bits == 32 || Base_of_Bits == 64)
	struct dights_of_bits_type;

	template<> struct dights_of_bits_type<8> {using bits_type = unsigned char; static constexpr size_t bits_max = (1 << 8) - 1; };
	template<> struct dights_of_bits_type<16> {using bits_type = unsigned short; static constexpr size_t bits_max = (1 << 16) - 1; };
	template<> struct dights_of_bits_type<32> {using bits_type = unsigned int; static constexpr size_t bits_max = (1ULL << 32ULL) - 1; };
	template<> struct dights_of_bits_type<64> {using bits_type = unsigned long long; static constexpr size_t bits_max = (1ULL << 63ULL) - 1 + (1ULL << 63ULL); };
	
	template<size_t Base_of_Bits>
	requires(Base_of_Bits == 8 || Base_of_Bits == 16 || Base_of_Bits == 32 || Base_of_Bits == 64)
	class biguint final{
	public:
		using base_bits_type = dights_of_bits_type<Base_of_Bits>::bits_type;
		using base_number = dights_of_bits_type<Base_of_Bits>::bits_max;

		biguint() noexcept = default;
		biguint(std::unsigned_integral auto value) {}
		biguint(const std::string& input) {}

		size_t dights() const noexcept { return data_value_dights.size(); }

		biguint& operator+=(const biguint& other){
			data_value_dights.resize(std::max(dights(), other.dights()));

		}
		biguint& operator-=(const biguint& other){}
		biguint& operator*=(const biguint& other){}
		biguint& operator/=(const biguint& other){}
		biguint& operator%=(const biguint& other){}
		biguint& operator^=(const biguint& other){}
		biguint& operator&=(const biguint& other){}
		biguint& operator>>=(const biguint& other){}
		biguint& operator<<=(const biguint& other){}
		biguint& operator|=(const biguint& other){}
		
		auto operator<=>(const biguint& other) const noexcept = default;

		biguint& operator+=(std::unsigned_integral auto value) {}
		biguint& operator-=(std::unsigned_integral auto value) {}
		biguint& operator*=(std::unsigned_integral auto value) {}
		biguint& operator/=(std::unsigned_integral auto value) {}
		biguint& operator%=(std::unsigned_integral auto value) {}
		biguint& operator^=(std::unsigned_integral auto value) {}
		biguint& operator&=(std::unsigned_integral auto value) {}
		biguint& operator>>=(std::unsigned_integral auto value) {}
		biguint& operator<<=(std::unsigned_integral auto value) {}
		biguint& operator|=(std::unsigned_integral auto value) {}

		auto operator<=>(std::unsigned_integral auto value) const noexcept{}
		bool operator==(std::unsigned_integral auto value) const noexcept{}

		biguint& operator++() noexcept{ return *this += 1; }
		biguint operator++(int) noexcept { biguint temp = *this; *this += 1; return temp;}
		biguint& operator--() noexcept { return *this -= 1; }
		biguint operator--(int) noexcept { biguint temp = *this; *this -= 1; return temp; }
		biguint operator-() const noexcept { biguint temp = *this; temp.number_sign_of_value = !temp.number_sign_of_value; return temp; }
		biguint operator~() const noexcept {
			biguint temp = *this;
			return -(temp + 1);
		}

		friend std::istream& operator>>(std::istream& is, biguint& a);
		friend std::ostream& operator<<(std::ostream& os, biguint& a);
		friend biguint operator+(biguint a, const biguint& b) { return a += b; }
		friend biguint operator-(biguint a, const biguint& b) { return a -= b; }
		friend biguint operator*(biguint a, const biguint& b) { return a *= b;}
		friend biguint operator/(biguint a, const biguint& b) { return a /= b;}
		friend biguint operator%(biguint a, const biguint& b) { return a %= b;}
		friend biguint operator&(biguint a, const biguint& b) { return a &= b;}
		friend biguint operator^(biguint a, const biguint& b) { return a ^= b;}
		friend biguint operator|(biguint a, const biguint& b) { return a |= b;}
		friend biguint operator>>(biguint a, const biguint& b) { return a >>= b; }
		friend biguint operator<<(biguint a, const biguint& b) { return a <<= b; }

		friend biguint operator+(biguint a, std::unsigned_integral auto value) { return a += value; }
		friend biguint operator-(biguint a, std::unsigned_integral auto value) { return a -= value; }
		friend biguint operator*(biguint a, std::unsigned_integral auto value) { return a *= value; }
		friend biguint operator/(biguint a, std::unsigned_integral auto value) { return a /= value; }
	 	friend biguint operator%(biguint a, std::unsigned_integral auto value) { return a %= value; }
		friend biguint operator^(biging a, std::unsigned_integral auto value) { return a ^= value; }
		friend biguint operator&(biguint a, std::unsigned_integral auto value) { return a &= value; }
		friend biguint operator>>(biguint a, std::unsigned_integral auto value) { return a >>= value; }
		friend biguint operator<<(bigint a, std::unsigned_integral auto value) { return a <<= value; }
		friend bigint operator|(bigint a, std::unsigned_integral auto value) { return a |= value; }

		friend void inner_NTT<base_bits_type>(std::vector<base_bits_type>& data_, size_t size, int operation);
	private:
		std::vector<base_bits_type> data_value_dights;
	};

	template<size_t Base_of_Bits>
	requires(Base_of_Bits == 8 || Base_of_Bits == 16 || Base_of_Bits == 32 || Base_of_Bits == 64)
	class bigint final{
	public:
		using base_bits_type = dights_of_bits_type<Base_of_Bits>::bits_type;
		using base_number = dights_of_bits_type<Base_of_Bits>::bits_max;

		bigint() noexcept = default;
		bigint(std::integral auto value) {}
		bigint(const std::string& input) {}

		size_t dights() const noexcept { return data_value_dights.size(); }

		bigint& operator+=(const bigint& other){
			data_value_dights.resize(std::max(dights(), other.dights()));

		}
		bigint& operator-=(const bigint& other){}
		bigint& operator*=(const bigint& other){}
		bigint& operator/=(const bigint& other){}
		bigint& operator%=(const bigint& other){}
		bigint& operator^=(const bigint& other){}
		bigint& operator&=(const bigint& other){}
		bigint& operator>>=(const bigint& other){}
		bigint& operator<<=(const bigint& other){}
		bigint& operator|=(const bigint& other){}
		
		auto operator<=>(const bigint& other) const noexcept{}
		bool operator==(const bigint& other) const noexcept{}

		bigint& operator+=(std::integral auto value) {}
		bigint& operator-=(std::integral auto value) {}
		bigint& operator*=(std::integral auto value) {}
		bigint& operator/=(std::integral auto value) {}
		bigint& operator%=(std::integral auto value) {}
		bigint& operator^=(std::integral auto value) {}
		bigint& operator&=(std::integral auto value) {}
		bigint& operator>>=(std::integral auto value) {}
		bigint& operator<<=(std::integral auto value) {}
		bigint& operator|=(std::integral auto value) {}

		auto operator<=>(std::integral auto value) const noexcept{}
		bool operator==(std::integral auto value) const noexcept{}

		bigint& operator++() noexcept{ return *this += 1; }
		bigint operator++(int) noexcept { bigint temp = *this; *this += 1; return temp;}
		bigint& operator--() noexcept { return *this -= 1; }
		bigint operator--(int) noexcept { bigint temp = *this; *this -= 1; return temp; }
		bigint operator-() const noexcept { bigint temp = *this; temp.number_positive_of_value = !temp.number_positive_of_value; return temp; }
		bigint operator~() const noexcept {
			bigint temp = *this;
			return -(temp + 1);
		}

		friend std::istream& operator>>(std::istream& is, bigint& a);
		friend std::ostream& operator<<(std::ostream& os, bigint& a);
		friend bigint operator+(bigint a, const bigint& b) { return a += b; }
		friend bigint operator-(bigint a, const bigint& b) { return a -= b; }
		friend bigint operator*(bigint a, const bigint& b) { return a *= b;}
		friend bigint operator/(bigint a, const bigint& b) { return a /= b;}
		friend bigint operator%(bigint a, const bigint& b) { return a %= b;}
		friend bigint operator&(bigint a, const bigint& b) { return a &= b;}
		friend bigint operator^(bigint a, const bigint& b) { return a ^= b;}
		friend bigint operator|(bigint a, const bigint& b) { return a |= b;}
		friend bigint operator>>(bigint a, const bigint& b) { return a >>= b; }
		friend bigint operator<<(bigint a, const bigint& b) { return a <<= b; }

		friend bigint operator+(bigint a, std::integral auto value) { return a += value; }
		friend bigint operator-(bigint a, std::integral auto value) { return a -= value; }
		friend bigint operator*(bigint a, std::integral auto value) { return a *= value; }
		friend bigint operator/(bigint a, std::integral auto value) { return a /= value; }
	 	friend bigint operator%(bigint a, std::integral auto value) { return a %= value; }
		friend bigint operator^(biging a, std::integral auto value) { return a ^= value; }
		friend bigint operator&(bigint a, std::integral auto value) { return a &= value; }
		friend bigint operator>>(bigint a, std::integral auto value) { return a >>= value; }
		friend bigint operator<<(bigint a, std::integral auto value) { return a <<= value; }
		friend bigint operator|(bigint a, std::integral auto value) { return a |= value; }

		friend void inner_NTT<base_bits_type>(std::vector<base_bits_type>& data_, size_t size, int operation);
	private:
		bool number_positive_of_value;
		std::vector<base_bits_type> data_value_dights;
	};


	template<size_t Base>
	bigint<Base> abs(bigint<Base> a) { return a >= 0 ? a : -a; }
	template<size_t Base>
	bigint<Base> gcd(bigint<Base> a, const bigint<Base>& b) { }
	template<size_t Base>
	bigint<Base> lcm(bigint<Base> a, const bigint<Base>& b) { }
	template<size_t Base>
	bigint<Base> gcd(bigint<Base> a, std::integral auto value) { }
	template<size_t Base>
	bigint<Base> lcm(bigint<Base> a, std::integral auto value) { }
	template<size_t Base>
	bigint<Base> gcd(std::integral auto value, bigint<Base> a) { }
	template<size_t Base>
	bigint<Base> lcm(std::integral auto value, bigint<Base> a) { }
}