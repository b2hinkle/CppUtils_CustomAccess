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

        // TODO: Make calls to this class actually forward its call to child rather than doing nothing.
        // TODO: Support all value categories.
    public:

        const T& GetValue() const
        {
            //static_cast<CustomAccessed>(this)->;
        }

        void SetValue(const T& newValue)
        {
            
        }

    protected:
    
        T BackingValue = T{};

    };
}
