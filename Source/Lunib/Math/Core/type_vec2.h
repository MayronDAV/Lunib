#pragma once
#include "Lunib/Core/base.h"

#include "detail.h"

#if defined(LUNIB_MATH_STRING_OPERATOR)
	// std
	#include <string>
#endif

// std
#include <cassert>


namespace Lunib::Math
{
	template<typename T>
	struct Vec<2, T>
	{
		typedef T value_type;
		typedef Vec<2, T> type;

		union { T x, r, s; };
		union { T y, g, t; };

		Vec() : x(T(0)), y(T(0)) {}
		Vec(const Vec& p_v) = default;
		Vec(T p_scalar) : x(p_scalar), y(p_scalar) {}
		Vec(T p_x, T p_y) : x(p_x), y(p_y) {}

		template<typename U>
		Vec(const Vec<2, U>& p_v) : x(T(p_v.x)), y(T(p_v.y)) {}
		template<typename U>
		Vec(const Vec<3, U>& p_v) : x(T(p_v.x)), y(T(p_v.y)) {}
		template<typename U>
		Vec(const Vec<4, U>& p_v) : x(T(p_v.x)), y(T(p_v.y)) {}

		inline T& operator[](length_t p_i)
		{
			assert(p_i >= 0 && p_i < 2);
			switch(p_i)
			{
				default:
				case 0: return x;
				case 1: return y;
			}
		}
		inline const T& operator[](length_t p_i) const
		{
			assert(p_i >= 0 && p_i < 2);
			switch(p_i)
			{
				default:
				case 0: return x;
				case 1: return y;
			}
		}

		template<typename U>
		inline constexpr Vec<2, T>& operator=(const Vec<2, U>& p_v)
		{
			this->x = static_cast<T>(p_v.x);
			this->y = static_cast<T>(p_v.y);
			return *this;
		}
		template<typename U>
		inline constexpr Vec<2, T>& operator+=(U p_scalar)
		{
			this->x += static_cast<T>(p_scalar);
			this->y += static_cast<T>(p_scalar);
			return *this;
		}
		template<typename U>
		inline constexpr Vec<2, T>& operator+=(const Vec<2, U>& p_v)
		{
			this->x += static_cast<T>(p_v.x);
			this->y += static_cast<T>(p_v.y);
			return *this;
		}
		template<typename U>
		inline constexpr Vec<2, T>& operator-=(U p_scalar)
		{
			this->x -= static_cast<T>(p_scalar);
			this->y -= static_cast<T>(p_scalar);
			return *this;
		}
		template<typename U>
		inline constexpr Vec<2, T>& operator-=(const Vec<2, U>& p_v)
		{
			this->x -= static_cast<T>(p_v.x);
			this->y -= static_cast<T>(p_v.y);
			return *this;
		}
		template<typename U>
		inline constexpr Vec<2, T>& operator*=(U p_scalar)
		{
			this->x *= static_cast<T>(p_scalar);
			this->y *= static_cast<T>(p_scalar);
			return *this;
		}
		template<typename U>
		inline constexpr Vec<2, T>& operator*=(const Vec<2, U>& p_v)
		{
			this->x *= static_cast<T>(p_v.x);
			this->y *= static_cast<T>(p_v.y);
			return *this;
		}
		template<typename U>
		inline constexpr Vec<2, T>& operator/=(U p_scalar)
		{
			this->x /= static_cast<T>(p_scalar);
			this->y /= static_cast<T>(p_scalar);
			return *this;
		}
		template<typename U>
		inline constexpr Vec<2, T>& operator/=(const Vec<2, U>& p_v)
		{
			this->x /= static_cast<T>(p_v.x);
			this->y /= static_cast<T>(p_v.y);
			return *this;
		}

		template<typename U>
		inline constexpr bool operator==(const Vec<2, U>& p_v) const
		{
			return x == T(p_v.x) && y == T(p_v.y);
		}

		template<typename U>
		inline constexpr bool operator!=(const Vec<2, U>& p_v) const
		{
			return !(*this == p_v);
		}

		template<typename U>
		inline bool operator<( const Vec<2, U>& p_v) { return x <  T(p_v.x) && y <  T(p_v.y); }
		template<typename U>
        inline bool operator<=(const Vec<2, U>& p_v) { return x <= T(p_v.x) && y <= T(p_v.y); }
		template<typename U>
        inline bool operator>( const Vec<2, U>& p_v) { return x >  T(p_v.x) && y >  T(p_v.y); }
		template<typename U>
        inline bool operator>=(const Vec<2, U>& p_v) { return x >= T(p_v.x) && y >= T(p_v.y); }

	#if defined(LUNIB_MATH_STRING_OPERATOR)
		inline operator std::string() const {
            return "( " + std::to_string(x) + ", " + std::to_string(y) + " )";
        }
	#endif
	};

	// -- Unary operators --

	template<typename T>
	constexpr Vec<2, T> operator+(const Vec<2, T>& p_v)
	{
		return p_v;
	}

	template<typename T>
	constexpr Vec<2, T> operator-(const Vec<2, T>& p_v)
	{
		return Vec<2, T>(-p_v.x, -p_v.y);
	}

	// -- Binary operators --

	template<typename T>
	constexpr Vec<2, T> operator+(const Vec<2, T>& p_v, T p_scalar)
	{
		return Vec<2, T>(p_v.x + p_scalar, p_v.y + p_scalar);
	}

	template<typename T>
	constexpr Vec<2, T> operator+(T p_scalar, const Vec<2, T>& p_v)
	{
		return Vec<2, T>(p_scalar + p_v.x, p_scalar + p_v.y);
	}

	template<typename T>
	constexpr Vec<2, T> operator+(const Vec<2, T>& p_v1, const Vec<2, T>& p_v2)
	{
		return Vec<2, T>(p_v1.x + p_v2.x, p_v1.y + p_v2.y);
	}

	template<typename T>
	constexpr Vec<2, T> operator-(const Vec<2, T>& p_v, T scalar)
	{
		return Vec<2, T>(p_v.x - scalar, p_v.y - scalar);
	}

	template<typename T>
	constexpr Vec<2, T> operator-(T scalar, const Vec<2, T>& p_v)
	{
		return Vec<2, T>(scalar - p_v.x, scalar - p_v.y);
	}

	template<typename T>
	constexpr Vec<2, T> operator-(const Vec<2, T>& p_v1, const Vec<2, T>& p_v2)
	{
		return Vec<2, T>(p_v1.x - p_v2.x, p_v1.y - p_v2.y);
	}

	template<typename T>
	constexpr Vec<2, T> operator*(const Vec<2, T>& p_v, T scalar)
	{
		return Vec<2, T>(p_v.x * scalar, p_v.y * scalar);
	}

	template<typename T>
	constexpr Vec<2, T> operator*(T scalar, const Vec<2, T>& p_v)
	{
		return Vec<2, T>(scalar * p_v.x, scalar * p_v.y);
	}

	template<typename T>
	constexpr Vec<2, T> operator*(const Vec<2, T>& p_v1, const Vec<2, T>& p_v2)
	{
		return Vec<2, T>(p_v1.x * p_v2.x, p_v1.y * p_v2.y);
	}

	template<typename T>
	constexpr Vec<2, T> operator/(const Vec<2, T>& p_v, T scalar)
	{
		return Vec<2, T>(p_v.x / scalar, p_v.y / scalar);
	}

	template<typename T>
	constexpr Vec<2, T> operator/(T scalar, const Vec<2, T>& p_v)
	{
		return Vec<2, T>(scalar / p_v.x, scalar / p_v.y);
	}

	template<typename T>
	constexpr Vec<2, T> operator/(const Vec<2, T>& p_v1, const Vec<2, T>& p_v2)
	{
		return Vec<2, T>(p_v1.x / p_v2.x, p_v1.y / p_v2.y);
	}


} // Lunib::Math
