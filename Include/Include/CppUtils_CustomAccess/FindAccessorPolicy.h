// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <CppUtils_CustomAccess/AccessorPolicies.h>

namespace CppUtils::CustomAccess::AccessorPolicyUtils::Detail
{
    template <
        class T,
        template <class, class>
        class PolicyToFind,
        class FallbackPolicy,
        class... Policies>
    struct FindAccessPolicy;

    template <
        class T,
        template <class, class>
        class PolicyToFind,
        class FallbackPolicy,
        class First,
        class... Rest>
    struct FindAccessPolicy<T, PolicyToFind, FallbackPolicy, First, Rest...>
    {
        using type = std::conditional_t
        <
            std::is_base_of_v
            <
                PolicyToFind<T, First>,
                First
            >,
            First,
            typename FindAccessPolicy<T, PolicyToFind, FallbackPolicy, Rest...>::type
        >;
    };

    template <
        class T,
        template <class, class>
        class PolicyToFind,
        class FallbackPolicy>
    struct FindAccessPolicy<T, PolicyToFind, FallbackPolicy>
    {
        using type = FallbackPolicy; // No policy found
    };
}

namespace CppUtils::CustomAccess::AccessorPolicyUtils
{
    /*
    * Finds the first accessor policy of type `PolicyToFind` in the provided `AccessorPolicies...`. Returns `FallbackPolicy` if no such policy is found.
    */
    template <
        class T,
        template <class, class>
        class PolicyToFind,
        class    FallbackPolicy,
        class... AccessorPolicies>
    using FindAccessPolicyWithFallback_T = Detail::FindAccessPolicy<T, PolicyToFind, FallbackPolicy, AccessorPolicies...>::type;

    /*
    * Finds the first accessor policy of type `PolicyToFind` in the provided `AccessorPolicies...`. Returns `void` if no such policy is found.
    */
    template <
        class T,
        template <class, class>
        class PolicyToFind,
        class... AccessorPolicies>
    using FindAccessPolicy_T = FindAccessPolicyWithFallback_T<T, PolicyToFind, void, AccessorPolicies...>::type;

}