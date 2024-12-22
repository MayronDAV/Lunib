#pragma once

#include "Lunib/Math/Core/type_mat4x4.h"
#include "Lunib/Math/Core/type_mat3x3.h"


namespace Lunib
{
	namespace Math
	{
		typedef Mat<4, 4, float> 		mat4x4;
		typedef Mat<4, 4, double> 		dmat4x4;
		typedef Mat<4, 4, int> 			imat4x4;
		typedef Mat<4, 4, unsigned int> umat4x4;

        typedef Mat<3, 3, float> 		mat3x3;
		typedef Mat<3, 3, double> 		dmat3x3;
		typedef Mat<3, 3, int> 			imat3x3;
		typedef Mat<3, 3, unsigned int> umat3x3;
		
	} // Math

	typedef Math::mat4x4   Mat4;
	typedef Math::dmat4x4 DMat4;
	typedef Math::imat4x4 IMat4;
	typedef Math::umat4x4 UMat4;

    typedef Math::mat3x3   Mat3;
	typedef Math::dmat3x3 DMat3;
	typedef Math::imat3x3 IMat3;
	typedef Math::umat3x3 UMat3;

} // Lunib