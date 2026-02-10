// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <CppUtils_CustomAccess/AccessorPolicyStaticInterfaces.h>

namespace CppUtils
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
}
