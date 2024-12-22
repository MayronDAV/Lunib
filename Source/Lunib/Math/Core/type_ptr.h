#pragma once
#include "Lunib/Core/base.h"

#include "type_mat4x4.h"
#include "type_vec2.h"
#include "type_vec3.h"
#include "type_vec4.h"



namespace Lunib::Math
{
    template<typename T>
    LUNIB_API const typename T::value_type* ValuePtr(const T& p_v)  { return &(p_v.x);      }


    template<typename T>
    LUNIB_API const T* ValuePtr(const Mat<4, 4, T>& p_m)            { return &(p_m[0].x);   }
    template<typename T>
    LUNIB_API const T* ValuePtr(const Mat<3, 3, T>& p_m)            { return &(p_m[0].x);   }

    template<typename T>
    LUNIB_API const T* ValuePtr(const Vec<2, T>& p_v)               { return &(p_v.x);      }
    template<typename T>
    LUNIB_API const T* ValuePtr(const Vec<3, T>& p_v)               { return &(p_v.x);      }
    template<typename T>
    LUNIB_API const T* ValuePtr(const Vec<4, T>& p_v)               { return &(p_v.x);      }


    template<typename T>
	LUNIB_API Vec<2, T> MakeVec2(const T* p_ptr)
    {
        return Vec<2, T>(p_ptr[0], p_ptr[1]);
    }

	template<typename T>
	LUNIB_API Vec<3, T> MakeVec3(const T* p_ptr)
    {
        return Vec<3, T>(p_ptr[0], p_ptr[1], p_ptr[2]);
    }

	template<typename T>
	LUNIB_API Vec<4, T> MakeVec4(const T* p_ptr)
    {
        return Vec<4, T>(p_ptr[0], p_ptr[1], p_ptr[2], p_ptr[3]);
    }

    template<typename T>
    LUNIB_API Mat<4, 4, T> MakeMat4(const T* p_ptr)
    {
        return Mat<4, 4, T>(
            p_ptr[0 ], p_ptr[1 ], p_ptr[2 ], p_ptr[3 ],
            p_ptr[4 ], p_ptr[5 ], p_ptr[6 ], p_ptr[7 ],
            p_ptr[8 ], p_ptr[9 ], p_ptr[10], p_ptr[11],
            p_ptr[12], p_ptr[13], p_ptr[14], p_ptr[15]
        );
    }

    template<typename T>
    LUNIB_API Mat<3, 3, T> MakeMat3(const T* p_ptr)
    {
        return Mat<3, 3, T>(
            p_ptr[0 ], p_ptr[1 ], p_ptr[2 ],
            p_ptr[4 ], p_ptr[5 ], p_ptr[6 ],
            p_ptr[8 ], p_ptr[9 ], p_ptr[10],
        );
    }

} // Lunib::Math