// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <CppUtils_CustomAccess/AccessorPolicies.h>

namespace CppUtils::CustomAccess::AccessorPolicyUtils
{
    template
    <
        class T,
        class Policy
    >
    using GetPolicyCategoryType_t = CppUtils::AccessorPolicies::PolicyTraits<T, Policy>::PolicyCategory_t;
    
    template
    <
        class T,
        class Policy,
        class PolicyCategory
    >
    consteval bool IsPolicyOfPolicyCategory() { return std::is_same_v<GetPolicyCategoryType_t<T, Policy>, PolicyCategory>; }
}

namespace CppUtils::CustomAccess::AccessorPolicyUtils::Detail
{
    template
    <
        class T,
        template <class, class>
        class PolicyCategory,
        class... Policies
    >
    struct FindAccessorPolicy;

    template
    <
        class T,
        template <class, class>
        class PolicyCategory,
        class First,
        class... Rest
    >
    struct FindAccessorPolicy<T, PolicyCategory, First, Rest...>
    {
        using PolicyType = std::conditional_t
        <
            IsPolicyOfPolicyCategory<T, First, PolicyCategory<T, First>>(),
            First,
            typename FindAccessorPolicy<T, PolicyCategory, Rest...>::PolicyType
        >;
    };

    template
    <
        class T,
        template <class, class>
        class PolicyCategory
    >
    struct FindAccessorPolicy<T, PolicyCategory>
    {
        using PolicyType = CppUtils::AccessorPolicies::PolicyCategoryTraits<T, PolicyCategory>::FallbackPolicy; // No policy found
    };
}

namespace CppUtils::CustomAccess::AccessorPolicyUtils
{
    /*
    * Finds the first accessor policy of category `PolicyCategory` in the provided `AccessorPolicies...`. Returns category's `FallbackPolicy` if no such policy is found.
    */
    template
    <
        class T,
        template <class, class>
        class PolicyCategory,
        class... AccessorPolicies
    >
    using GetAccessorPolicyByCategory_T = Detail::FindAccessorPolicy<T, PolicyCategory, AccessorPolicies...>::PolicyType;

    /*
    * Builds the static interface for dispatching calls to the correct accessor policy in `AccessorPolicies...`.
    */
    template
    <
        class T,
        template <class, class>
        class PolicyCategory,
        class... AccessorPolicies
    >
    using GetAccessorPolicyCategory_T = PolicyCategory
    <
        T,
        GetAccessorPolicyByCategory_T<T, PolicyCategory, AccessorPolicies...>
    >;
}
