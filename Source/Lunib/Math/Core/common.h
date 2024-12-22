#pragma once

namespace Lunib::Math
{
	template<typename type>
	constexpr type Min(type p_a, type p_b)
	{
		return (p_a < p_b) ? p_a : p_b;
	}

	template<typename type>
	constexpr type Max(type p_a, type p_b)
	{
		return (p_a > p_b) ? p_a : p_b;
	}

	template<typename T>
	constexpr T Clamp(T p_value, T p_min, T p_max)
	{
		return Min(Max(p_value, p_min), p_max);
	}

	template<typename T>
	constexpr T Lerp(T p_a, T p_b, T p_t)
	{
		return p_a + (p_b - p_a) * p_t;
	}

	template<typename T>
	constexpr T Radians(T p_degrees)
	{
		return p_degrees * T(0.017453292519943295769236907684886);
	}

	template<typename T>
	constexpr T Degrees(T p_radians)
	{
		return p_radians * T(57.295779513082320876798154814105);
	}

	template<typename T>
	constexpr T Abs(T p_value)
	{
		return (p_value >= T(0)) ? p_value : -p_value;
	}

	template<typename T>
	typename T::type Dot(const T& p_v1, const T& p_v2)
	{
		return p_v1 * p_v2;
	}

	template<typename T>
	typename T::type Sqrt(const T& p_v)
	{
		return sqrt(p_v);
	}

	template<typename T>
	Vec<2, T> Sqrt(const Vec<2, T>& p_v)
	{
		return Vec<2, T>(sqrt(p_v.x), sqrt(p_v.y));
	}

	template<typename T>
	Vec<3, T> Sqrt(const Vec<3, T>& p_v)
	{
		return Vec<3, T>(sqrt(p_v.x), sqrt(p_v.y), sqrt(p_v.z));
	}

	template<typename T>
	Vec<4, T> Sqrt(const Vec<4, T>& p_v)
	{
		return Vec<4, T>(sqrt(p_v.x), sqrt(p_v.y), sqrt(p_v.z), sqrt(p_v.w));
	}

	template<typename T>
	typename T::type Length(const T& p_v)
	{
		return Sqrt(Dot(p_v, p_v));
	}

	template<typename T>
	typename T::type Length2(const T& p_v)
	{
		return Dot(p_v, p_v);
	}

	template<typename T>
	typename T::type Distance(const T& p_v1, const T& p_v2)
	{
		return Length(p_v1 - p_v2);
	}

	template<typename T>
	typename T::type Normalize(const T& p_v)
	{
		return p_v / Length(p_v);
	}

	template<typename T>
	Vec<3, T> Cross(const Vec<3, T>& p_v1, const Vec<3, T>& p_v2)
	{
		return Vec<3, T>(
			p_v1.y * p_v2.z - p_v1.z * p_v2.y,
			p_v1.z * p_v2.x - p_v1.x * p_v2.z,
			p_v1.x * p_v2.y - p_v1.y * p_v2.x
		);
	}

	template<typename T>
	Vec<4, T> Cross(const Vec<4, T>& p_v1, const Vec<4, T>& p_v2)
	{
		return Vec<4, T>(
			p_v1.y * p_v2.z - p_v1.z * p_v2.y,
			p_v1.z * p_v2.x - p_v1.x * p_v2.z,
			p_v1.x * p_v2.y - p_v1.y * p_v2.x,
			T(0)
		);
	}

} // Lunib::Math