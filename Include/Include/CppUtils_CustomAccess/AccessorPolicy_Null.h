// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <cstddef>

namespace CppUtils
{
    /*
    * Used to indicate the absence of an accessor policy.
    * [todo][techdebt] I don't like how we have to have any using declaratives for this null policy.
    *                  They only exist to make the compiler happy during the parsing phase of
    *                  `CustomAccessed`'s api in cases of no function generation. I belive we can
    *                  use SFINAE in place of requires clause for the function generation to avoid
    *                  the compiler bugging us about this.
    */
    struct AccessorPolicy_Null
    {
        using ReturnType = std::nullptr_t;
        using FirstArg   = std::nullptr_t;
        using SecondArg  = std::nullptr_t;
    };
}
