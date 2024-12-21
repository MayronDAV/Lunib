#pragma once
#include "Lunib/Core/base.h"

#include "detail.h"

#if defined(LUNIB_MATH_STRING_OPERATOR)
	// std
	#include <string>
#endif



namespace Lunib::Math
{
	template<typename T>
	struct Vec<3, T>
	{
		union { T x, r, s; };
		union { T y, g, t; };
		union { T z, b, p; };

		Vec() : x(T(0)), y(T(0)), z(T(0)) {}
		Vec(const Vec& p_v) = default;
		Vec(T p_x, T p_y, T p_z) : x(p_x), y(p_y), z(p_z) {}

		template<typename U>
		Vec(const Vec<2, U>& p_v, U p_z) : x(T(p_v.x)), y(T(p_v.y)), z(T(p_z))  {}
		template<typename U>
		Vec(const Vec<3, U>& p_v) : x(T(p_v.x)), y(T(p_v.y)), z(T(p_v.z))  {}
		template<typename U>
		Vec(const Vec<4, U>& p_v) : x(T(p_v.x)), y(T(p_v.y)), z(T(p_v.z))  {}

		template<typename U>
		inline constexpr Vec<3, T>& operator=(const Vec<3, U>& p_v)
		{
			this->x = static_cast<T>(p_v.x);
			this->y = static_cast<T>(p_v.y);
			this->z = static_cast<T>(p_v.z);
			return *this;
		}
		template<typename U>
		inline constexpr Vec<3, T>& operator+=(U p_scalar)
		{
			this->x += static_cast<T>(p_scalar);
			this->y += static_cast<T>(p_scalar);
			this->z += static_cast<T>(p_scalar);
			return *this;
		}
		template<typename U>
		inline constexpr Vec<3, T>& operator+=(const Vec<3, U>& p_v)
		{
			this->x += static_cast<T>(p_v.x);
			this->y += static_cast<T>(p_v.y);
			this->z += static_cast<T>(p_v.z);
			return *this;
		}
		template<typename U>
		inline constexpr Vec<3, T>& operator-=(U p_scalar)
		{
			this->x -= static_cast<T>(p_scalar);
			this->y -= static_cast<T>(p_scalar);
			this->z -= static_cast<T>(p_scalar);
			return *this;
		}
		template<typename U>
		inline constexpr Vec<3, T>& operator-=(const Vec<3, U>& p_v)
		{
			this->x -= static_cast<T>(p_v.x);
			this->y -= static_cast<T>(p_v.y);
			this->z -= static_cast<T>(p_v.z);
			return *this;
		}
		template<typename U>
		inline constexpr Vec<3, T>& operator*=(U p_scalar)
		{
			this->x *= static_cast<T>(p_scalar);
			this->y *= static_cast<T>(p_scalar);
			this->z *= static_cast<T>(p_scalar);
			return *this;
		}
		template<typename U>
		inline constexpr Vec<3, T>& operator*=(const Vec<3, U>& p_v)
		{
			this->x *= static_cast<T>(p_v.x);
			this->y *= static_cast<T>(p_v.y);
			this->z *= static_cast<T>(p_v.z);
			return *this;
		}
		template<typename U>
		inline constexpr Vec<3, T>& operator/=(U p_scalar)
		{
			this->x /= static_cast<T>(p_scalar);
			this->y /= static_cast<T>(p_scalar);
			this->z /= static_cast<T>(p_scalar);
			return *this;
		}
		template<typename U>
		inline constexpr Vec<3, T>& operator/=(const Vec<3, U>& p_v)
		{
			this->x /= static_cast<T>(p_v.x);
			this->y /= static_cast<T>(p_v.y);
			this->z /= static_cast<T>(p_v.z);
			return *this;
		}

		template<typename U>
		inline constexpr bool operator==(const Vec<3, U>& p_v) const
		{
			return x == T(p_v.x) && y == T(p_v.y) && z == T(p_v.z);
		}

		template<typename U>
		inline constexpr bool operator!=(const Vec<3, U>& p_v) const
		{
			return !(*this == p_v);
		}

		template<typename U>
		inline bool operator<( const Vec<3, U>& p_v) const { return x <  T(p_v.x) && y <  T(p_v.y) && z <  T(p_v.z); }
		template<typename U>
        inline bool operator<=(const Vec<3, U>& p_v) const { return x <= T(p_v.x) && y <= T(p_v.y) && z <= T(p_v.z); }
		template<typename U>
        inline bool operator>( const Vec<3, U>& p_v) const { return x >  T(p_v.x) && y >  T(p_v.y) && z >  T(p_v.z); }
		template<typename U>
        inline bool operator>=(const Vec<3, U>& p_v) const { return x >= T(p_v.x) && y >= T(p_v.y) && z >= T(p_v.z); }

	#if defined(LUNIB_MATH_STRING_OPERATOR)
		inline operator std::string() const {
            return "Vec3( " + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + " )";
        }
	#endif
	};

} // Lunib::Math
