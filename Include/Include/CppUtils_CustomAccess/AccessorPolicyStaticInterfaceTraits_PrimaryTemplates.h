// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <CppUtils_CustomAccess/AccessorPolicyStaticInterfaces.h>
#include <CppUtils_CustomAccess/AccessorPolicy_Null.h>

/*
* NOTE: This only still exists in case we want traits for our interfaces, but we no longer technically need it as of now.
*/
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
        
    };

    template <class T>
    struct AccessorPolicyStaticInterfaceTraits<T, AccessorPolicyStaticInterface_Setter>
    {
        
    };
}
