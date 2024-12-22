#pragma once

#include "Lunib/Math/Core/type_mat4x4.h"
#include "Lunib/Math/Core/type_mat3x3.h"


namespace Lunib
{
	namespace Math
	{
		typedef Mat<4, 4, float> mat4x4;
        typedef Mat<3, 3, float> mat3x3;
	} // Math

	typedef Math::mat4x4 Mat4;
    typedef Math::mat3x3 Mat3;

} // Lunib