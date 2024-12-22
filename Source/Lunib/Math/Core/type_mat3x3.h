#pragma once

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
	struct Mat<3, 3, T>
	{
		typedef T value_type;
		typedef Mat<3, 3, T> type;
		typedef Vec<3, T> col_type;

	private:
		col_type m_Value[3];

	public:
		Mat() : m_Value{col_type(1, 0, 0), col_type(0, 1, 0), col_type(0, 0, 1)} {}
		Mat(T p_scalar) : m_Value{col_type(p_scalar, 0, 0), col_type(0, p_scalar, 0), col_type(0, 0, p_scalar)} {}
		Mat(const Mat<3, 3, T>& p_m) = default;
		Mat(const col_type& p_c0, const col_type& p_c1, const col_type& p_c2) : m_Value{p_c0, p_c1, p_c2} {}
		Mat(
			const T& p_x0, const T& p_y0, const T& p_z0,
			const T& p_x1, const T& p_y1, const T& p_z1,
			const T& p_x2, const T& p_y2, const T& p_z2)
		: m_Value{col_type(p_x0, p_y0, p_z0), col_type(p_x1, p_y1, p_z1), col_type(p_x2, p_y2, p_z2)} {}
		Mat(const Mat<4, 4, T>& p_m) : m_Value{col_type(p_m[0]), col_type(p_m[1]), col_type(p_m[2])} {}

		inline col_type& operator[](length_t p_i) { assert(p_i >= 0 && p_i < 3); return m_Value[p_i]; }
		inline const col_type& operator[](length_t p_i) const { assert(p_i >= 0 && p_i < 3); return m_Value[p_i]; }

		template<typename U>
		inline Mat<3, 3, T>& operator=(const Mat<3, 3, U>& p_m)
		{
			m_Value[0] = p_m.m_Value[0];
			m_Value[1] = p_m.m_Value[1];
			m_Value[2] = p_m.m_Value[2];
			return *this;
		}

		template<typename U>
		inline Mat<3, 3, T>& operator+=(const Mat<3, 3, U>& p_m)
		{
			m_Value[0] += p_m.m_Value[0];
			m_Value[1] += p_m.m_Value[1];
			m_Value[2] += p_m.m_Value[2];
			return *this;
		}

		template<typename U>
		inline Mat<3, 3, T>& operator-=(const Mat<3, 3, U>& p_m)
		{
			m_Value[0] -= p_m[0];
			m_Value[1] -= p_m[1];
			m_Value[2] -= p_m[2];
			return *this;
		}

		template<typename U>
		inline Mat<3, 3, T>& operator*=(U p_scalar)
		{
			m_Value[0] *= T(p_scalar);
			m_Value[1] *= T(p_scalar);
			m_Value[2] *= T(p_scalar);
			return *this;
		}

		template<typename U>
		inline Mat<3, 3, T>& operator*=(const Mat<3, 3, U>& p_m)
		{
			m_Value[0] *= p_m.m_Value[0];
			m_Value[1] *= p_m.m_Value[1];
			m_Value[2] *= p_m.m_Value[2];
			return *this;
		}

		template<typename U>
		inline Mat<3, 3, T>& operator/=(U p_scalar)
		{
			m_Value[0] /= T(p_scalar);
			m_Value[1] /= T(p_scalar);
			m_Value[2] /= T(p_scalar);
			return *this;
		}

		template<typename U>
		inline Mat<3, 3, T>& operator/=(const Mat<3, 3, U>& p_m)
		{
			m_Value[0] /= p_m.m_Value[0];
			m_Value[1] /= p_m.m_Value[1];
			m_Value[2] /= p_m.m_Value[2];
			return *this;
		}


		template<typename U>
		inline bool operator==(const Mat<3, 3, U>& p_m) const
		{
			for (size_t i = 0; i < 3; ++i)
				for (size_t j = 0; j < 3; ++j)
					if (m_Value[i][j] != p_m[i][j])
						return false;
			return true;
		}

		template<typename U>
		inline bool operator!=(const Mat<3, 3, U>& p_m) const
		{
			return !(*this == p_m);
		}

		#if defined(LUNIB_MATH_STRING_OPERATOR)
			inline operator std::string() const {
				return "( " + std::string(m_Value[0]) + ", " + std::string(m_Value[1]) + ", " + std::string(m_Value[2]) + " )";
			}
		#endif
	};

	// -- Unary operators --

	template<typename T>
	constexpr Mat<3, 3, T> operator+(const Mat<3, 3, T>& p_m)
	{
		return p_m;
	}

	template<typename T>
	constexpr Mat<3, 3, T> operator-(const Mat<3, 3, T>& p_m)
	{
		return Mat<3, 3, T>(
			-p_m[0][0], -p_m[0][1], -p_m[0][2],
			-p_m[1][0], -p_m[1][1], -p_m[1][2],
			-p_m[2][0], -p_m[2][1], -p_m[2][2]
		);
	}

	// -- Binary operators --

	template<typename T>
	constexpr Mat<3, 3, T> operator+(const Mat<3, 3, T>& p_m, T p_scalar)
	{
		return Mat<3, 3, T>(
			p_m[0][0] + p_scalar, p_m[0][1] + p_scalar, p_m[0][2] + p_scalar,
			p_m[1][0] + p_scalar, p_m[1][1] + p_scalar, p_m[1][2] + p_scalar,
			p_m[2][0] + p_scalar, p_m[2][1] + p_scalar, p_m[2][2] + p_scalar
		);
	}

	template<typename T>
	constexpr Mat<3, 3, T> operator+(const Mat<3, 3, T>& p_m1, const Mat<3, 3, T>& p_m2)
	{
		return Mat<3, 3, T>(
			p_m1[0][0] + p_m2[0][0], p_m1[0][1] + p_m2[0][1], p_m1[0][2] + p_m2[0][2],
			p_m1[1][0] + p_m2[1][0], p_m1[1][1] + p_m2[1][1], p_m1[1][2] + p_m2[1][2],
			p_m1[2][0] + p_m2[2][0], p_m1[2][1] + p_m2[2][1], p_m1[2][2] + p_m2[2][2]
		);
	}

	template<typename T>
	constexpr Mat<3, 3, T> operator-(const Mat<3, 3, T>& p_m, T p_scalar)
	{
		return Mat<3, 3, T>(
			p_m[0][0] - p_scalar, p_m[0][1] - p_scalar, p_m[0][2] - p_scalar,
			p_m[1][0] - p_scalar, p_m[1][1] - p_scalar, p_m[1][2] - p_scalar,
			p_m[2][0] - p_scalar, p_m[2][1] - p_scalar, p_m[2][2] - p_scalar
		);
	}

	template<typename T>
	constexpr Mat<3, 3, T> operator-(const Mat<3, 3, T>& p_m1, const Mat<3, 3, T>& p_m2)
	{
		return Mat<3, 3, T>(
			p_m1[0][0] - p_m2[0][0], p_m1[0][1] - p_m2[0][1], p_m1[0][2] - p_m2[0][2],
			p_m1[1][0] - p_m2[1][0], p_m1[1][1] - p_m2[1][1], p_m1[1][2] - p_m2[1][2],
			p_m1[2][0] - p_m2[2][0], p_m1[2][1] - p_m2[2][1], p_m1[2][2] - p_m2[2][2]
		);
	}

	template<typename T>
	constexpr Mat<3, 3, T> operator*(const Mat<3, 3, T>& p_m, T p_scalar)
	{
		return Mat<3, 3, T>(
			p_m[0][0] * p_scalar, p_m[0][1] * p_scalar, p_m[0][2] * p_scalar,
			p_m[1][0] * p_scalar, p_m[1][1] * p_scalar, p_m[1][2] * p_scalar,
			p_m[2][0] * p_scalar, p_m[2][1] * p_scalar, p_m[2][2] * p_scalar
		);
	}

	template<typename T>
	constexpr Mat<3, 3, T> operator*(const Mat<3, 3, T>& p_m1, const Mat<3, 3, T>& p_m2)
	{
		Mat<3, 3, T> result;
		for (size_t i = 0; i < 3; ++i)
			for (size_t j = 0; j < 3; ++j)
				result[i][j] = p_m1[i][0] * p_m2[0][j] + p_m1[i][1] * p_m2[1][j] + p_m1[i][2] * p_m2[2][j];
		return result;
	}

	template<typename T>
	constexpr Mat<3, 3, T> operator/(const Mat<3, 3, T>& p_m, T p_scalar)
	{
		return Mat<3, 3, T>(
			p_m[0][0] / p_scalar, p_m[0][1] / p_scalar, p_m[0][2] / p_scalar,
			p_m[1][0] / p_scalar, p_m[1][1] / p_scalar, p_m[1][2] / p_scalar,
			p_m[2][0] / p_scalar, p_m[2][1] / p_scalar, p_m[2][2] / p_scalar
		);
	}

	template<typename T>
	constexpr Mat<3, 3, T> operator/(const Mat<3, 3, T>& p_m1, const Mat<3, 3, T>& p_m2)
	{
		return Mat<3, 3, T>(
			p_m1[0][0] / p_m2[0][0], p_m1[0][1] / p_m2[0][1], p_m1[0][2] / p_m2[0][2],
			p_m1[1][0] / p_m2[1][0], p_m1[1][1] / p_m2[1][1], p_m1[1][2] / p_m2[1][2],
			p_m1[2][0] / p_m2[2][0], p_m1[2][1] / p_m2[2][1], p_m1[2][2] / p_m2[2][2]
		);
	}

} // Lunib::Math