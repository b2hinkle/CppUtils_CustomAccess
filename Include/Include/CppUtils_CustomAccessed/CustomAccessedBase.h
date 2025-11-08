// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

namespace CppUtils
{
    /**
     * Base exists to improve the template api. Separates T argument from any extra template arg functionality. 
     */
    template <class T>
    struct CustomAccessedBase
    {

    protected:

        const T& GetValue() const
        {
            return Value;
        }
    
        T Value = T{};

    };
}
