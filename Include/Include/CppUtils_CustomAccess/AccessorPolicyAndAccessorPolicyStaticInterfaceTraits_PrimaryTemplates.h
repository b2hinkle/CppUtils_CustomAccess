// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <CppUtils_CustomAccess/AccessorPolicyStaticInterfaces.h>
#include <CppUtils_CustomAccess/NullGetterAccessorPolicy.h>
#include <CppUtils_CustomAccess/NullSetterAccessorPolicy.h>

namespace CppUtils::AccessorPolicies
{
    template
    <
        class T,
        template <class, class>
        class TAccessorPolicyInterface
    >
    struct AccessorPolicyStaticInterfaceTraits
    {
        // Write the condition to be dependent on a template parameter, to avoid the static assertion being evaluated during the parsing phase of this template struct.
        static_assert(sizeof(T) && false, "No traits defined. You must define a (partial) specialization of this struct for your accessor policy type.");
    };

    template <class T>
    struct AccessorPolicyStaticInterfaceTraits<T, AccessorPolicyStaticInterface_Getter>
    {
        using FallbackAccessorPolicy = NullGetterAccessorPolicy<T>;
    };

    template <class T>
    struct AccessorPolicyStaticInterfaceTraits<T, AccessorPolicyStaticInterface_Setter>
    {
        using FallbackAccessorPolicy = NullSetterAccessorPolicy<T>;
    };
}

namespace CppUtils::AccessorPolicies
{
    template 
    <
        class T,
        class AccessorPolicy
    >
    struct AccessorPolicyTraits
    {
        static_assert(sizeof(T) && false, "No specialization defined for accessor policy. You must define a (partial) specialization of this struct for your accessor policy type. This way you can assign a static interface to your accessor policy via `AccessorPolicyStaticInterface_t` declaration, allowing us to search for you.");
    };
    
    template <class T>
    struct AccessorPolicyTraits<T, NullGetterAccessorPolicy<T>>
    {
        using AccessorPolicyStaticInterface_t = AccessorPolicyStaticInterface_Getter<T, NullGetterAccessorPolicy<T>>;
    };

    template <class T>
    struct AccessorPolicyTraits<T, NullSetterAccessorPolicy<T>>
    {
        using AccessorPolicyStaticInterface_t = AccessorPolicyStaticInterface_Setter<T, NullSetterAccessorPolicy<T>>;
    };
}
