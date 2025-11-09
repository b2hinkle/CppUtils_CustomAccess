// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

// Accessor policies are used to define custom accessor behavior.
// TODO: We should provide default accessor behavior for all value categories and cv.
// TODO: If a policy doesn't specify a certain implementation/data, we need it to fall back on defaults (in DefaultAccessorPolicy).
namespace CppUtils::CommonAccessorPolicies
{
    template <class T>
    struct DefaultAccessorPolicy
    {
        static inline const T& Get(const T& value) { return value; }
    
        static inline void Set(T& value, const T& newValue) { value = newValue; }
    };

}

#if 0 // TODO: This should be a reusable broadcast on set function for convenience.
    // TODO: It would be nice to have another function that even broadcasts when valueRef is same.
    template <class T>
    void BroadcastOnSet(T& value, const T& newValue)
    {
        const T oldBackingValue = value;
        value = newBackingValue;

        if (newBackingValue != oldBackingValue)
        {
#if 0
            ValueChangeDelegate.Broadcast(oldBackingValue, newBackingValue);
#endif
        }
    }
#endif
