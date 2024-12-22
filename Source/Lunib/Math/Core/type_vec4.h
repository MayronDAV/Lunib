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
	struct Vec<4, T>
	{
		typedef T value_type;

		union { T x, r, s; };
		union { T y, g, t; };
		union { T z, b, p; };
		union { T w, a, q; };

		Vec() : x(T(0)), y(T(0)), z(T(0)), w(T(0)) {}
		Vec(const Vec& p_v) = default;
		Vec(T p_scalar) : x(p_scalar), y(p_scalar), z(p_scalar), w(p_scalar) {}
		Vec(T p_x, T p_y, T p_z, T p_w) : x(p_x), y(p_y), z(p_z), w(p_w) {}

		template<typename U>
		Vec(const Vec<2, U>& p_v1, const Vec<2, U>& p_v2) : x(T(p_v1.x)), y(T(p_v1.y)), z(T(p_v2.x)), w(T(p_v2.y))  {}
		template<typename U>
		Vec(const Vec<2, U>& p_v1, U p_z, U p_w) : x(T(p_v1.x)), y(T(p_v1.y)), z(T(p_z)), w(T(p_w))  {}
		template<typename U>
		Vec(const Vec<3, U>& p_v, U p_w) : x(T(p_v.x)), y(T(p_v.y)), z(T(p_v.z)), w(T(p_w))  {}
		template<typename U>
		Vec(const Vec<4, U>& p_v) : x(T(p_v.x)), y(T(p_v.y)), z(T(p_v.z)), w(T(p_v.w))  {}

		inline constexpr T& operator[](length_t p_i)
		{
			assert(p_i >= 0 && p_i < 4);
			switch(p_i)
			{
				default:
				case 0: return x;
				case 1: return y;
				case 2: return z;
				case 3: return w;
			}
		}

		inline constexpr T& operator[](length_t p_i) const
		{
			assert(p_i >= 0 && p_i < 4);
			switch(p_i)
			{
				default:
				case 0: return x;
				case 1: return y;
				case 2: return z;
				case 3: return w;
			}
		}

		template<typename U>
		inline constexpr Vec<4, T>& operator=(const Vec<4, U>& p_v)
		{
			this->x = static_cast<T>(p_v.x);
			this->y = static_cast<T>(p_v.y);
			this->z = static_cast<T>(p_v.z);
			this->w = static_cast<T>(p_v.w);
			return *this;
		}
		template<typename U>
		inline constexpr Vec<4, T>& operator+=(U p_scalar)
		{
			this->x += static_cast<T>(p_scalar);
			this->y += static_cast<T>(p_scalar);
			this->z += static_cast<T>(p_scalar);
			this->w += static_cast<T>(p_scalar);
			return *this;
		}
		template<typename U>
		inline constexpr Vec<4, T>& operator+=(const Vec<4, U>& p_v)
		{
			this->x += static_cast<T>(p_v.x);
			this->y += static_cast<T>(p_v.y);
			this->z += static_cast<T>(p_v.z);
			this->w += static_cast<T>(p_v.w);
			return *this;
		}
		template<typename U>
		inline constexpr Vec<4, T>& operator-=(U p_scalar)
		{
			this->x -= static_cast<T>(p_scalar);
			this->y -= static_cast<T>(p_scalar);
			this->z -= static_cast<T>(p_scalar);
			this->w -= static_cast<T>(p_scalar);
			return *this;
		}
		template<typename U>
		inline constexpr Vec<4, T>& operator-=(const Vec<4, U>& p_v)
		{
			this->x -= static_cast<T>(p_v.x);
			this->y -= static_cast<T>(p_v.y);
			this->z -= static_cast<T>(p_v.z);
			this->w -= static_cast<T>(p_v.w);
			return *this;
		}
		template<typename U>
		inline constexpr Vec<4, T>& operator*=(U p_scalar)
		{
			this->x *= static_cast<T>(p_scalar);
			this->y *= static_cast<T>(p_scalar);
			this->z *= static_cast<T>(p_scalar);
			this->w *= static_cast<T>(p_scalar);
			return *this;
		}
		template<typename U>
		inline constexpr Vec<4, T>& operator*=(const Vec<4, U>& p_v)
		{
			this->x *= static_cast<T>(p_v.x);
			this->y *= static_cast<T>(p_v.y);
			this->z *= static_cast<T>(p_v.z);
			this->w *= static_cast<T>(p_v.w);
			return *this;
		}
		template<typename U>
		inline constexpr Vec<4, T>& operator/=(U p_scalar)
		{
			this->x /= static_cast<T>(p_scalar);
			this->y /= static_cast<T>(p_scalar);
			this->z /= static_cast<T>(p_scalar);
			this->w /= static_cast<T>(p_scalar);
			return *this;
		}
		template<typename U>
		inline constexpr Vec<4, T>& operator/=(const Vec<4, U>& p_v)
		{
			this->x /= static_cast<T>(p_v.x);
			this->y /= static_cast<T>(p_v.y);
			this->z /= static_cast<T>(p_v.z);
			this->w /= static_cast<T>(p_v.w);
			return *this;
		}

		template<typename U>
		inline constexpr bool operator==(const Vec<4, U>& p_v) const
		{
			return x == T(p_v.x) && y == T(p_v.y) && z == T(p_v.z) && w == T(p_v.w);
		}

		template<typename U>
		inline constexpr bool operator!=(const Vec<4, U>& p_v) const
		{
			return !(*this == p_v);
		}

		template<typename U>
		inline bool operator<( const Vec<4, U>& p_v) const { return x <  T(p_v.x) && y <  T(p_v.y) && z <  T(p_v.z) && w <  T(p_v.w); }
		template<typename U>
        inline bool operator<=(const Vec<4, U>& p_v) const { return x <= T(p_v.x) && y <= T(p_v.y) && z <= T(p_v.z) && w <= T(p_v.w); }
		template<typename U>
        inline bool operator>( const Vec<4, U>& p_v) const { return x >  T(p_v.x) && y >  T(p_v.y) && z >  T(p_v.z) && w >  T(p_v.w); }
		template<typename U>
        inline bool operator>=(const Vec<4, U>& p_v) const { return x >= T(p_v.x) && y >= T(p_v.y) && z >= T(p_v.z) && w >= T(p_v.w); }

	#if defined(LUNIB_MATH_STRING_OPERATOR)
		inline operator std::string() const {
            return "Vec4( " + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " + std::to_string(w) + " )";
        }
	#endif
	};

} // Lunib::Math
