#pragma once

#include "Lunib/Math/Core/type_vec2.h"
#include "Lunib/Math/Core/type_vec3.h"
#include "Lunib/Math/Core/type_vec4.h"



namespace Lunib
{
	namespace Math
	{
		typedef Vec<2, float>           vec2;
		typedef Vec<2, int>             ivec2;
		typedef Vec<2, double>          dvec2;
		typedef Vec<2, unsigned int>    uvec2;

		typedef Vec<3, float>           vec3;
		typedef Vec<3, int>             ivec3;
		typedef Vec<3, double>          dvec3;
		typedef Vec<3, unsigned int>    uvec3;

		typedef Vec<4, float>           vec4;
		typedef Vec<4, int>             ivec4;
		typedef Vec<4, double>          dvec4;
		typedef Vec<4, unsigned int>    uvec4;
	} // Math

	typedef Math::vec2   Vec2;
	typedef Math::ivec2 IVec2;
	typedef Math::dvec2 DVec2;
	typedef Math::uvec2 UVec2;

	typedef Math::vec3   Vec3;
    typedef Math::ivec3 IVec3;
    typedef Math::dvec3 DVec3;
    typedef Math::uvec3 UVec3;

	typedef Math::vec4   Vec4;
    typedef Math::ivec4 IVec4;
    typedef Math::dvec4 DVec4;
    typedef Math::uvec4 UVec4;

} // Lunib