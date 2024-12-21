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

} // Lunib::Math