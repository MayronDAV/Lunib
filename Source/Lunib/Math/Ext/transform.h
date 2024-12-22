#pragma once
#include "mat.h"
#include "Lunib/Math/Core/base.h"
#include "Lunib/Math/Core/common.h"


namespace Lunib::Math
{
	template<typename T>
	Mat<4, 4, T> Translate(const Vec<3, T>& p_v)
	{
		Mat<4, 4, T> result(T(1));
		result[3][0] = p_v.x;
		result[3][1] = p_v.y;
		result[3][2] = p_v.z;
		return result;
	}

	template<typename T>
	Mat<4, 4, T> Translate(const Mat<4, 4, T>& p_m, const Vec<3, T>& p_v)
	{
		Mat<4, 4, T> result(p_m);
		result[3] = Vec<4, T>(p_m[0] * p_v[0] + p_m[1] * p_v[1] + p_m[2] * p_v[2] + p_m[3]);
		return result;
	}

	template<typename T>
	Mat<4, 4, T> Scale(const Vec<3, T>& p_v)
	{
		Mat<4, 4, T> result(T(1));
		result[0] = p_v[0];
		result[1] = p_v[1];
		result[2] = p_v[2];
		return result;
	}

	template<typename T>
	Mat<4, 4, T> Scale(const Mat<4, 4, T>& p_m, const Vec<3, T>& p_v)
	{
		Mat<4, 4, T> result;
		result[0] = p_m[0] * p_v[0];
		result[1] = p_m[1] * p_v[1];
		result[2] = p_m[2] * p_v[2];
		result[3] = p_m[3];
		return result;
	}

	template<typename T>
	Mat<4, 4, T> ScaleSlow(const Mat<4, 4, T>& p_m, const Vec<3, T>& p_v)
	{
		Mat<4, 4, T> result(T(1));
		result[0][0] = p_v.x;
		result[1][1] = p_v.y;
		result[2][2] = p_v.z;
		return p_m * result;
	}

	template<typename T>
	Mat<4, 4, T> LookAtRH(const Vec<3, T>& p_eye, const Vec<3, T>& p_center, const Vec<3, T>& p_up)
	{
		const Vec<3, T> f = Normalize(p_center - p_eye);
		const Vec<3, T> s = Normalize(Cross(f, p_up));
		const Vec<3, T> u = Cross(s, f);

		Mat<4, 4, T> Result(T(1));
		Result[0][0] = s.x;
		Result[1][0] = s.y;
		Result[2][0] = s.z;
		Result[0][1] = u.x;
		Result[1][1] = u.y;
		Result[2][1] = u.z;
		Result[0][2] = -f.x;
		Result[1][2] = -f.y;
		Result[2][2] = -f.z;
		Result[3][0] = -Dot(s, p_eye);
		Result[3][1] = -Dot(u, p_eye);
		Result[3][2] =  Dot(f, p_eye);
		return Result;
	}

	template<typename T>
	Mat<4, 4, T> LookAtLH(const Vec<3, T>& p_eye, const Vec<3, T>& p_center, const Vec<3, T>& p_up)
	{
		const Vec<3, T> f = Normalize(p_center - p_eye);
		const Vec<3, T> s = Normalize(Cross(p_up, f));
		const Vec<3, T> u = Cross(f, s);

		Mat<4, 4, T> Result(T(1));
		Result[0][0] = s.x;
		Result[1][0] = s.y;
		Result[2][0] = s.z;
		Result[0][1] = u.x;
		Result[1][1] = u.y;
		Result[2][1] = u.z;
		Result[0][2] = f.x;
		Result[1][2] = f.y;
		Result[2][2] = f.z;
		Result[3][0] = -Dot(s, p_eye);
		Result[3][1] = -Dot(u, p_eye);
		Result[3][2] = -Dot(f, p_eye);
		return Result;
	}

	template<typename T>
	Mat<4, 4, T> LookAt(const Vec<3, T>& p_eye, const Vec<3, T>& p_center, const Vec<3, T>& p_up)
	{
		if (LUNIB_CONFIG_CLIP_CONTROL & LUNIB_CLIP_CONTROL_LH_BIT)
			return LookAtLH(p_eye, p_center, p_up);
		else
			return LookAtRH(p_eye, p_center, p_up);
	}


} // Lunib::Math
