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
		return std::sqrt(p_v);
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
	T Length(const Vec<2, T>& p_v)
	{
		return std::sqrt(p_v.x * p_v.x + p_v.y * p_v.y);
	}

	template<typename T>
	T Length(const Vec<3, T>& p_v)
	{
		return std::sqrt(p_v.x * p_v.x + p_v.y * p_v.y +  p_v.z * p_v.z);
	}

	template<typename T>
	T Length(const Vec<4, T>& p_v)
	{
		return std::sqrt(p_v.x * p_v.x + p_v.y * p_v.y +  p_v.z * p_v.z + p_v.w * p_v.w);
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

	template<typename T>
	Mat<3, 3, T> Inverse(const Mat<3, 3, T>& p_m)
	{
		T oneOverDeterminant = static_cast<T>(1) / (
			+ p_m[0][0] * (p_m[1][1] * p_m[2][2] - p_m[2][1] * p_m[1][2])
			- p_m[1][0] * (p_m[0][1] * p_m[2][2] - p_m[2][1] * p_m[0][2])
			+ p_m[2][0] * (p_m[0][1] * p_m[1][2] - p_m[1][1] * p_m[0][2])
		);

		Mat<3, 3, T> inverse;
		inverse[0][0] = + (p_m[1][1] * p_m[2][2] - p_m[2][1] * p_m[1][2]) * oneOverDeterminant;
		inverse[1][0] = - (p_m[1][0] * p_m[2][2] - p_m[2][0] * p_m[1][2]) * oneOverDeterminant;
		inverse[2][0] = + (p_m[1][0] * p_m[2][1] - p_m[2][0] * p_m[1][1]) * oneOverDeterminant;
		inverse[0][1] = - (p_m[0][1] * p_m[2][2] - p_m[2][1] * p_m[0][2]) * oneOverDeterminant;
		inverse[1][1] = + (p_m[0][0] * p_m[2][2] - p_m[2][0] * p_m[0][2]) * oneOverDeterminant;
		inverse[2][1] = - (p_m[0][0] * p_m[2][1] - p_m[2][0] * p_m[0][1]) * oneOverDeterminant;
		inverse[0][2] = + (p_m[0][1] * p_m[1][2] - p_m[1][1] * p_m[0][2]) * oneOverDeterminant;
		inverse[1][2] = - (p_m[0][0] * p_m[1][2] - p_m[1][0] * p_m[0][2]) * oneOverDeterminant;
		inverse[2][2] = + (p_m[0][0] * p_m[1][1] - p_m[1][0] * p_m[0][1]) * oneOverDeterminant;

		return inverse;
	}

	template<typename T>
	Mat<4, 4, T> Inverse(const Mat<4, 4, T>& p_m)
	{
		T coef00 = p_m[2][2] * p_m[3][3] - p_m[3][2] * p_m[2][3];
		T coef02 = p_m[1][2] * p_m[3][3] - p_m[3][2] * p_m[1][3];
		T coef03 = p_m[1][2] * p_m[2][3] - p_m[2][2] * p_m[1][3];

		T coef04 = p_m[2][1] * p_m[3][3] - p_m[3][1] * p_m[2][3];
		T coef06 = p_m[1][1] * p_m[3][3] - p_m[3][1] * p_m[1][3];
		T coef07 = p_m[1][1] * p_m[2][3] - p_m[2][1] * p_m[1][3];

		T coef08 = p_m[2][1] * p_m[3][2] - p_m[3][1] * p_m[2][2];
		T coef10 = p_m[1][1] * p_m[3][2] - p_m[3][1] * p_m[1][2];
		T coef11 = p_m[1][1] * p_m[2][2] - p_m[2][1] * p_m[1][2];

		T coef12 = p_m[2][0] * p_m[3][3] - p_m[3][0] * p_m[2][3];
		T coef14 = p_m[1][0] * p_m[3][3] - p_m[3][0] * p_m[1][3];
		T coef15 = p_m[1][0] * p_m[2][3] - p_m[2][0] * p_m[1][3];

		T coef16 = p_m[2][0] * p_m[3][2] - p_m[3][0] * p_m[2][2];
		T coef18 = p_m[1][0] * p_m[3][2] - p_m[3][0] * p_m[1][2];
		T coef19 = p_m[1][0] * p_m[2][2] - p_m[2][0] * p_m[1][2];

		T coef20 = p_m[2][0] * p_m[3][1] - p_m[3][0] * p_m[2][1];
		T coef22 = p_m[1][0] * p_m[3][1] - p_m[3][0] * p_m[1][1];
		T coef23 = p_m[1][0] * p_m[2][1] - p_m[2][0] * p_m[1][1];

		Vec<4, T> fac0(coef00, coef00, coef02, coef03);
		Vec<4, T> fac1(coef04, coef04, coef06, coef07);
		Vec<4, T> fac2(coef08, coef08, coef10, coef11);
		Vec<4, T> fac3(coef12, coef12, coef14, coef15);
		Vec<4, T> fac4(coef16, coef16, coef18, coef19);
		Vec<4, T> fac5(coef20, coef20, coef22, coef23);

		Vec<4, T> vec0(p_m[1][0], p_m[0][0], p_m[0][0], p_m[0][0]);
		Vec<4, T> vec1(p_m[1][1], p_m[0][1], p_m[0][1], p_m[0][1]);
		Vec<4, T> vec2(p_m[1][2], p_m[0][2], p_m[0][2], p_m[0][2]);
		Vec<4, T> vec3(p_m[1][3], p_m[0][3], p_m[0][3], p_m[0][3]);

		Vec<4, T> inv0(vec1 * fac0 - vec2 * fac1 + vec3 * fac2);
		Vec<4, T> inv1(vec0 * fac0 - vec2 * fac3 + vec3 * fac4);
		Vec<4, T> inv2(vec0 * fac1 - vec1 * fac3 + vec3 * fac5);
		Vec<4, T> inv3(vec0 * fac2 - vec1 * fac4 + vec2 * fac5);

		Vec<4, T> signA(+1, -1, +1, -1);
		Vec<4, T> signB(-1, +1, -1, +1);
		Mat<4, 4, T> inverse(inv0 * signA, inv1 * signB, inv2 * signA, inv3 * signB);

		Vec<4, T> row0(inverse[0][0], inverse[1][0], inverse[2][0], inverse[3][0]);

		Vec<4, T> dot0(p_m[0] * row0);
		T Dot1 = (dot0.x + dot0.y) + (dot0.z + dot0.w);

		T oneOverDeterminant = static_cast<T>(1) / Dot1;

		return inverse * oneOverDeterminant;
	}

} // Lunib::Math