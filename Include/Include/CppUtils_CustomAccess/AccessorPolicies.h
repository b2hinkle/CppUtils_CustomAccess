// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <utility>

/*
* Accessor policies are used to define custom accessor behavior (e.g. getters/setters).
* TODO: We need to support accessors that user other value categories and cv.
*/
namespace CppUtils::AccessorPolicies
{
    template <class T>
    using TGetterFuncPtr = const T& (*)(const T& value);

    template <class T>
    using TSetterFuncPtr = void (*)(T& value, const T& newValue);

    template <
        class T,
        class TDerived
    >
    struct GetterAccessorPolicy_Interface
    {
        static inline const T& Get(const T& value) { return TDerived::Get(value); }
    };

    /*
    * Basic getter behavior, used as default behavior.
    */
    template <class T>
    struct BasicGetterAccessorPolicy : GetterAccessorPolicy_Interface<T, BasicGetterAccessorPolicy<T>>
    {
        static inline const T& Get(const T& value) { return value; }
    };

    /*
    * Option for `Get` policy function definition externalization.
    */
    template <
        class T,
        TGetterFuncPtr<T> GetterFuncPtr
        >
    struct GenericGetterAccessorPolicy : GetterAccessorPolicy_Interface<T, GenericGetterAccessorPolicy<T, GetterFuncPtr>>
    {
        static inline const T& Get(const T& value) { return GetterFuncPtr(value); }
    };

    template <
        class T,
        class TDerived
    >
    struct SetterAccessorPolicy_Interface
    {
        static inline void Set(T& value, const T& newValue) { return TDerived::Set(value); }
    };

    /*
    * Basic setter behavior, used as default behavior.
    */
    template <class T>
    struct BasicSetterAccessorPolicy : SetterAccessorPolicy_Interface<T, BasicSetterAccessorPolicy<T>>
    {
        static inline void Set(T& value, const T& newValue) { value = newValue; }
    };

    /*
    * Option for `Set` policy function definition externalization.
    */
    template <
        class T,
        TSetterFuncPtr<T> SetterFuncPtr
        >
    struct GenericSetterAccessorPolicy : SetterAccessorPolicy_Interface<T, GenericSetterAccessorPolicy<T, SetterFuncPtr>>
    {
        static inline void Set(T& value, const T& newValue) { SetterFuncPtr(value, newValue); }
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
