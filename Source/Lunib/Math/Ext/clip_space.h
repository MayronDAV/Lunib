#pragma once
#include "Lunib/Math/Core/base.h"
#include "mat.h"

// std
#include <limits>
#include <cmath>




namespace Lunib::Math
{
	template<typename T>
	Mat<4, 4, T> OrthoLH_ZO(T p_left, T p_right, T p_bottom, T p_top, T p_near, T p_far)
	{
		Mat<4, 4, T> result(T(1));
		result[0][0] = T(2) / (p_right - p_left);
		result[1][1] = T(2) / (p_top - p_bottom);
		result[2][2] = T(1) / (p_far - p_near);
		result[3][0] = -(p_right + p_left) / (p_right - p_left);
		result[3][1] = -(p_top + p_bottom) / (p_top - p_bottom);
		result[3][2] = - p_near / (p_far - p_near);
		return result;
	}

	template<typename T>
	Mat<4, 4, T> OrthoLH_NO(T p_left, T p_right, T p_bottom, T p_top, T p_near, T p_far)
	{
		Mat<4, 4, T> result(T(1));
		result[0][0] = T(2) / (p_right - p_left);
		result[1][1] = T(2) / (p_top - p_bottom);
		result[2][2] = T(2) / (p_far - p_near);
		result[3][0] = -(p_right + p_left) / (p_right - p_left);
		result[3][1] = -(p_top + p_bottom) / (p_top - p_bottom);
		result[3][2] = -(p_far + p_near) / (p_far - p_near);
		return result;
	}

	template<typename T>
	Mat<4, 4, T> OrthoRH_ZO(T p_left, T p_right, T p_bottom, T p_top, T p_near, T p_far)
	{
		Mat<4, 4, T> result(T(1));
		result[0][0] =  T(2) / (p_right - p_left);
		result[1][1] =  T(2) / (p_top - p_bottom);
		result[2][2] = -T(1) / (p_far - p_near);
		result[3][0] = -(p_right + p_left) / (p_right - p_left);
		result[3][1] = -(p_top + p_bottom) / (p_top - p_bottom);
		result[3][2] = - p_near / (p_far - p_near);
		return result;
	}

	template<typename T>
	Mat<4, 4, T> OrthoRH_NO(T p_left, T p_right, T p_bottom, T p_top, T p_near, T p_far)
	{
		Mat<4, 4, T> result(T(1));
		result[0][0] =  T(2) / (p_right - p_left);
		result[1][1] =  T(2) / (p_top - p_bottom);
		result[2][2] = -T(1) / (p_far - p_near);
		result[3][0] = -(p_right + p_left) / (p_right - p_left);
		result[3][1] = -(p_top + p_bottom) / (p_top - p_bottom);
		result[3][2] = -(p_far + p_near) / (p_far - p_near);
		return result;
	}

	template<typename T>
	Mat<4, 4, T> Ortho(T p_left, T p_right, T p_bottom, T p_top, T p_near, T p_far)
	{
		if (LUNIB_CONFIG_CLIP_CONTROL & LUNIB_CLIP_CONTROL_LH_BIT)
		{
			if (LUNIB_CONFIG_CLIP_CONTROL & LUNIB_CLIP_CONTROL_ZO_BIT)
				return OrthoLH_ZO(p_left, p_right, p_bottom, p_top, p_near, p_far);
			else
				return OrthoLH_NO(p_left, p_right, p_bottom, p_top, p_near, p_far);
		}
		else
		{
			if (LUNIB_CONFIG_CLIP_CONTROL & LUNIB_CLIP_CONTROL_ZO_BIT)
				return OrthoRH_ZO(p_left, p_right, p_bottom, p_top, p_near, p_far);
			else
				return OrthoRH_NO(p_left, p_right, p_bottom, p_top, p_near, p_far);
		}
	}

	template<typename T>
	Mat<4, 4, T> PerspectiveLH_ZO(T p_fovy, T p_aspect, T p_near, T p_far)
	{
		assert(abs(p_aspect - std::numeric_limits<T>::epsilon()) > T(0));

		const T tanHalfFovy = tan(p_fovy / T(2));

		Mat<4, 4, T> Result(T(0));
		Result[0][0] = T(1) / (p_aspect * tanHalfFovy);
		Result[1][1] = T(1) / (tanHalfFovy);
		Result[2][2] = p_far / (p_far - p_near);
		Result[2][3] = T(1);
		Result[3][2] = -(p_far * p_near) / (p_far - p_near);
		return Result;
	}

	template<typename T>
	Mat<4, 4, T> PerspectiveLH_NO(T p_fovy, T p_aspect, T p_near, T p_far)
	{
		assert(abs(p_aspect - std::numeric_limits<T>::epsilon()) > T(0));

		const T tanHalfFovy = tan(p_fovy / T(2));

		Mat<4, 4, T> Result(T(0));
		Result[0][0] = T(1) / (p_aspect * tanHalfFovy);
		Result[1][1] = T(1) / (tanHalfFovy);
		Result[2][2] = (p_far + p_near) / (p_far - p_near);
		Result[2][3] = T(1);
		Result[3][2] = - (T(2) * p_far * p_near) / (p_far - p_near);
		return Result;
	}

	template<typename T>
	Mat<4, 4, T> PerspectiveRH_ZO(T p_fovy, T p_aspect, T p_near, T p_far)
	{
		assert(abs(p_aspect - std::numeric_limits<T>::epsilon()) > T(0));

		const T tanHalfFovy = tan(p_fovy / T(2));

		Mat<4, 4, T> Result(T(0));
		Result[0][0] = T(1) / (p_aspect * tanHalfFovy);
		Result[1][1] = T(1) / (tanHalfFovy);
		Result[2][2] = p_far / (p_near - p_far);
		Result[2][3] = -T(1);
		Result[3][2] = -(p_far * p_near) / (p_far - p_near);
		return Result;
	}

	template<typename T>
	Mat<4, 4, T> PerspectiveRH_NO(T p_fovy, T p_aspect, T p_near, T p_far)
	{
		assert(abs(p_aspect - std::numeric_limits<T>::epsilon()) > T(0));

		const T tanHalfFovy = tan(p_fovy / T(2));

		Mat<4, 4, T> Result(T(0));
		Result[0][0] = T(1) / (p_aspect * tanHalfFovy);
		Result[1][1] = T(1) / (tanHalfFovy);
		Result[2][2] = -(p_far + p_near) / (p_far - p_near);
		Result[2][3] = -T(1);
		Result[3][2] = -(T(2) * p_far * p_near) / (p_far - p_near);
		return Result;
	}

	template<typename T>
	Mat<4, 4, T> Perspective(T p_fovy, T p_aspect, T p_near, T p_far)
	{
		if (LUNIB_CONFIG_CLIP_CONTROL & LUNIB_CLIP_CONTROL_LH_BIT)
		{
			if (LUNIB_CONFIG_CLIP_CONTROL & LUNIB_CLIP_CONTROL_ZO_BIT)
				return PerspectiveLH_ZO(p_fovy, p_aspect, p_near, p_far);
			else
				return PerspectiveLH_NO(p_fovy, p_aspect, p_near, p_far);
		}
		else
		{
			if (LUNIB_CONFIG_CLIP_CONTROL & LUNIB_CLIP_CONTROL_ZO_BIT)
				return PerspectiveRH_ZO(p_fovy, p_aspect, p_near, p_far);
			else
				return PerspectiveRH_NO(p_fovy, p_aspect, p_near, p_far);
		}
	}

} // Lunib::Math