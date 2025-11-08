// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#if 0

/**
 * Expected to implement specializations of this type for wrapper structs.
 */
template <class T>
struct TGCPropertyWrapperValueTypeTrait;

/**
 * Convenient typedef for getting the value type of a certain property wrapper.
 */
template <class T>
using TGCPropertyWrapperValueTypeTrait_T = typename TGCPropertyWrapperValueTypeTrait<T>::FValueType;

/**
 * Property wrapper implementation.
 */
template <class TWrapperType>
struct TGCPropertyWrapper
{

private:

    using FValueType = TGCPropertyWrapperValueTypeTrait_T<TWrapperType>;

public:

    // Provide default ctr to support potential UStructs users. Automatically use type's default value.
    TGCPropertyWrapper()
        : TGCPropertyWrapper(FValueType{})
    {
    }

    // TODO: We should support other overloads as well.
    TGCPropertyWrapper(FValueType defaultValue)
    {
        GetValue() = defaultValue;
    }

    // CRTP usage here.
    FORCEINLINE TWrapperType& GetWrapper()
    {
        return static_cast<TWrapperType&>(*this);
    }

    FORCEINLINE FValueType& GetValue()
    {
        return GetWrapper().Value;
    }

    // Implements implicit conversion from this struct to Value's type. Allows you to treat this struct as its Value's type in code.
    operator FValueType() const
    {
        return GetValue();
    }

    // Broadcasts ValueChangeDelegate TODO: We should support other overloads as well.
    // TODO: It would be nice to expose ability to broadcast even when value is same.
    FValueType& operator=(const FValueType& newValue)
    {
        const FValueType oldValue = GetValue();
        GetValue() = newValue;

        if (newValue != oldValue)
        {
            ValueChangeDelegate.Broadcast(oldValue, newValue);
        }

        return GetValue();
    }

    // Change event.
    TMulticastDelegate<void(const FValueType&, const FValueType&)> ValueChangeDelegate;


};

#endif