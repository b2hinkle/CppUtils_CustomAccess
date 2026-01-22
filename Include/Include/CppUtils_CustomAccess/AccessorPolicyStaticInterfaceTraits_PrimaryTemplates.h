// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <CppUtils_CustomAccess/AccessorPolicyStaticInterfaces.h>
#include <CppUtils_CustomAccess/AccessorPolicy_NullGetter.h>
#include <CppUtils_CustomAccess/AccessorPolicy_NullSetter.h>

namespace CppUtils
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
        using FallbackAccessorPolicy = AccessorPolicy_NullGetter<T>;
    };

    template <class T>
    struct AccessorPolicyStaticInterfaceTraits<T, AccessorPolicyStaticInterface_Setter>
    {
        using FallbackAccessorPolicy = AccessorPolicy_NullSetter<T>;
    };
}
