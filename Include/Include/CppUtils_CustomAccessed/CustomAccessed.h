// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <CppUtils_CustomAccessed/CustomAccessedBase.h>


namespace CppUtils
{
    /**
     * Property wrapper implementation.
     * TODO: We should support all special member functions.
     */
    template <class T>
    struct CustomAccessed : public CustomAccessedBase<T>
    {

        // Make parent members visible to the compiler.
        using CustomAccessedBase<T>::Value;
        using CustomAccessedBase<T>::GetValue;

    public:

        CustomAccessed() = default;

        CustomAccessed(T defaultValue)
        {
            operator=(defaultValue);
        }

        // Broadcasts ValueChangeDelegate
        // TODO: It would be nice to expose ability to broadcast even when value is same.
        T& operator=(const T& newValue)
        {
            const T oldValue = Value;
            Value = newValue;

            if (newValue != oldValue)
            {
    #if 0
                ValueChangeDelegate.Broadcast(oldValue, newValue);
    #endif
            }

            return Value;
        }

        // Implements implicit conversion from this struct to Value's type. Allows you to treat this struct as its Value's type in code.
        operator T() const
        {
            return GetValue();
        }

    #if 0
        // TODO: Must have generic solution for this that doesn't care about any delegate.
        // Change event.
        TMulticastDelegate<void(const T&, const T&)> ValueChangeDelegate;
    #endif

    };
}
