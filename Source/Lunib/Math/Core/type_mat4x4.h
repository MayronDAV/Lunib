#pragma once

#include "detail.h"

// std
#include <cassert>



namespace Lunib::Math
{
	template<typename T>
	struct Mat<4, 4, T>
	{
		typedef T value_type;
		typedef Vec<4, T> col_type;

		private:
			col_type m_Value[4];

		public:
			Mat() : m_Value{col_type(1, 0, 0, 0), col_type(0, 1, 0, 0), col_type(0, 0, 1, 0), col_type(0, 0, 0, 1)} {}
			Mat(T p_scalar) : m_Value{col_type(p_scalar, 0, 0, 0), col_type(0, p_scalar, 0, 0), col_type(0, 0, p_scalar, 0), col_type(0, 0, 0, p_scalar)} {}
			Mat(const Mat<4, 4, T>& p_m) = default;
			Mat(const col_type& p_c0, const col_type& p_c1, const col_type& p_c2, const col_type& p_c3) : m_Value{p_c0, p_c1, p_c2, p_c3} {}
			Mat(
				const T& p_x0, const T& p_y0, const T& p_z0, const T& p_w0,
				const T& p_x1, const T& p_y1, const T& p_z1, const T& p_w1,
				const T& p_x2, const T& p_y2, const T& p_z2, const T& p_w2,
				const T& p_x3, const T& p_y3, const T& p_z3, const T& p_w3)
			: m_Value{  col_type(p_x0, p_y0, p_z0, p_w0), col_type(p_x1, p_y1, p_z1, p_w1),
					col_type(p_x2, p_y2, p_z2, p_w2), col_type(p_x3, p_y3, p_z3, p_w3) } {}

			inline col_type& operator[](length_t p_i) { assert(p_i >= 0 && p_i < 4); return m_Value[p_i]; }
			inline const col_type& operator[](length_t p_i) const { assert(p_i >= 0 && p_i < 4); return m_Value[p_i]; }

			template<typename U>
			inline Mat<4, 4, T>& operator=(const Mat<4, 4, U>& p_m)
			{
				m_Value[0] = p_m.m_Value[0];
				m_Value[1] = p_m.m_Value[1];
				m_Value[2] = p_m.m_Value[2];
				m_Value[3] = p_m.m_Value[3];
				return *this;
			}

			template<typename U>
			inline Mat<4, 4, T>& operator+=(const Mat<4, 4, U>& p_m)
			{
				m_Value[0] += p_m.m_Value[0];
				m_Value[1] += p_m.m_Value[1];
				m_Value[2] += p_m.m_Value[2];
				m_Value[3] += p_m.m_Value[3];
				return *this;
			}

			template<typename U>
			inline Mat<4, 4, T>& operator-=(const Mat<4, 4, U>& p_m)
			{
				m_Value[0] -= p_m[0];
				m_Value[1] -= p_m[1];
				m_Value[2] -= p_m[2];
				m_Value[3] -= p_m[3];
				return *this;
			}

			template<typename U>
			inline Mat<4, 4, T>& operator*=(U p_scalar)
			{
				m_Value[0] *= T(p_scalar);
				m_Value[1] *= T(p_scalar);
				m_Value[2] *= T(p_scalar);
				m_Value[3] *= T(p_scalar);
				return *this;
			}

			template<typename U>
			inline Mat<4, 4, T>& operator*=(const Mat<4, 4, U>& p_m)
			{
				m_Value[0] *= p_m.m_Value[0];
				m_Value[1] *= p_m.m_Value[1];
				m_Value[2] *= p_m.m_Value[2];
				m_Value[3] *= p_m.m_Value[3]; 
				return *this;
			}

			template<typename U>
			inline Mat<4, 4, T>& operator/=(U p_scalar)
			{
				m_Value[0] /= T(p_scalar);
				m_Value[1] /= T(p_scalar);
				m_Value[2] /= T(p_scalar);
				m_Value[3] /= T(p_scalar);  
				return *this;
			}

			template<typename U>
			inline Mat<4, 4, T>& operator/=(const Mat<4, 4, U>& p_m)
			{
				m_Value[0] /= p_m.m_Value[0];
				m_Value[1] /= p_m.m_Value[1];
				m_Value[2] /= p_m.m_Value[2];
				m_Value[3] /= p_m.m_Value[3]; 
				return *this;
			}

			template<typename U>
			inline Mat<4, 4, T> operator+(const Mat<4, 4, U>& p_m) const
			{
				Mat<4, 4, T> result;
				for (size_t i = 0; i < 4; ++i)
					for (size_t j = 0; j < 4; ++j)
						result[i][j] = m_Value[i][j] + p_m[i][j];
				return result;
			}

			template<typename U>
			inline Mat<4, 4, T> operator-(const Mat<4, 4, U>& p_m) const
			{
				Mat<4, 4, T> result;
				for (size_t i = 0; i < 4; ++i)
					for (size_t j = 0; j < 4; ++j)
						result[i][j] = m_Value[i][j] - p_m[i][j];
				return result;
			}

			template<typename U>
			inline Mat<4, 4, T> operator*(U p_scalar) const
			{
				Mat<4, 4, T> result;
				for (size_t i = 0; i < 4; ++i)
					for (size_t j = 0; j < 4; ++j)
						result[i][j] = m_Value[i][j] * T(p_scalar);
				return result;
			}

			template<typename U>
			inline bool operator==(const Mat<4, 4, U>& p_m) const
			{
				for (size_t i = 0; i < 4; ++i)
					for (size_t j = 0; j < 4; ++j)
						if (m_Value[i][j] != p_m[i][j])
							return false;
				return true;
			}

			template<typename U>
			inline bool operator!=(const Mat<4, 4, U>& p_m) const
			{
				return !(*this == p_m);
			}

	};

} // Lunib::Math
