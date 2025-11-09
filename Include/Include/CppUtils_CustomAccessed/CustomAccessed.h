// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <CppUtils_CustomAccessed/CustomAccessedBase.h>
#include <CppUtils_CustomAccessed/CommonAccessorPolicies.h>


namespace CppUtils
{
    /**
     * Property wrapper implementation.
     * TODO: We should support all special member functions.
     */
    template <
        class T,
        class AccessorPolicy = CppUtils::CommonAccessorPolicies::DefaultAccessorPolicy<T>
    >
    struct CustomAccessed : public CustomAccessedBase<T>
    {

        // Make parent members visible to the compiler.
        using CustomAccessedBase<T>::BackingValue;

    public:

        CustomAccessed() = default;

        CustomAccessed(T defaultValue)
        {
            SetValue(defaultValue);
        }
        
        const T& GetValue() const
        {
            return AccessorPolicy::Get(BackingValue);
        }

        void SetValue(const T& newValue)
        {
            AccessorPolicy::Set(BackingValue, newValue);
        }

#if 0 // Adds unnecesary complexity at this stage in development. We can decide on this later when development is finished.

        T& operator=(const T& newBackingValue)
        {
            CustomSetterFunc(newBackingValue);
        }

        // Implements implicit conversion from this struct to BackingValue's type. Allows you to treat this struct as its BackingValue's type in code.
        operator T() const
        {
            return GetValue();
        }
#endif

    };
}
