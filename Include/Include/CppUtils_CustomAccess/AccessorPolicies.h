// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <type_traits>
#include <CppUtils_CustomAccess/FunctionTraits.h>
#include <CppUtils_CustomAccess/AccessorPolicyCategories.h>
#include <CppUtils_CustomAccess/AccessorPolicyUtils.h>

/*
* Accessor policies are used to define custom accessor behavior (e.g. getters/setters).
* TODO: We need to support accessors that user other value categories and cv.
* TODO: How do we want to handle basic get and set accessor policies. If we have a basic policy, it should not assume T is copyable or moveabe.
*       This should be detectable, but at the end of the day, doing so would make it more of a black box for the user, so it's probable that this wouldn't be worth it.
*/
namespace CppUtils::AccessorPolicies
{
    template <auto T>
    concept TCallable = requires { typename CppUtils::CustomAccess::FunctionPointerTraits<decltype(T)>; };

#if 0
    // TODO: Finish implementation
    template <auto T>
    concept TSetterCallable = TCallable<T> && /* Only 1 arg */;
#endif

    template <class T>
    using TSetterFuncPtr = void (*)(T& value, const T& newValue);

    /*
    * Basic getter behavior, used as default behavior.
    */
    template <class T>
    struct BasicGetterAccessorPolicy
    {
        static inline const T& Get(const T& value) { return value; }
    };

    template <class T>
    struct PolicyCategoryTraits<T, PolicyCategory_Getter>
    {
        using FallbackPolicy = BasicGetterAccessorPolicy<T>;
    };

    template <class T>
    struct PolicyTraits<T, BasicGetterAccessorPolicy<T>>
    {
        using PolicyCategory_t = PolicyCategory_Getter<T, BasicGetterAccessorPolicy<T>>;
    };

    /*
    * Getter accessor policy for function definition externalization.
    * Static asserts for clear error messaging. Enforces the structure of the user's callable to meet the purpose of a getter.
    */
    template
    <
        auto UserCallablePtr
    >
    struct GenericGetterAccessorPolicy
    {
        static_assert(TCallable<UserCallablePtr>, "We expect a user deffined callable pointer as the non-type template argument.");

        using UserCallablePtrTraits = CppUtils::CustomAccess::FunctionPointerTraits<decltype(UserCallablePtr)>;
        
        static_assert(std::tuple_size_v<typename UserCallablePtrTraits::ArgsTuple> == 1, "Callable must have 1 argument.");

        using ReturnType = typename UserCallablePtrTraits::ReturnType;
        using FirstArg = std::tuple_element_t<0, typename UserCallablePtrTraits::ArgsTuple>;

        static_assert(std::is_same_v
        <
            std::remove_cvref_t<ReturnType>,
            std::remove_cvref_t<FirstArg>
        >,
        "Return value type must match first parameter value type, since the provided argument is the backing value. Note that cv and ref qualifiers don't impact value type.");

        static_assert(
            (!std::is_reference_v<FirstArg>)
            ||
            (std::is_reference_v<FirstArg> && CppUtils::CustomAccess::IsConstAfterRemovingRef<FirstArg>()),
            "Reference as the first argument is only allowed if its value type is made const, since the provided argument is the backing value.");

        static_assert(!std::is_rvalue_reference_v<FirstArg>, "First parameter should not be an rvalue reference. It does not make sense to steal the data of the backing value through a getter, nor does it make sense to prefer a const rvalue ref over a const lvalue ref.");

        //using ClassType  = UserCallablePtrTraits::ClassType; TODO: Support member function pointers so that we can support the outer object's functions.

        /*
        * Inline to avoid unnecesary copy in the case of non-ref parameter.
        * No need to account for perfect forwarding. No possible rvalue references to account for, given the enforced type of the user's callable.
        */
        static inline ReturnType Get(FirstArg value)
        {
            return UserCallablePtr(value);
        }
    };

    template
    <
        class T,
        auto UserCallablePtr
    >
    struct PolicyTraits<T, GenericGetterAccessorPolicy<UserCallablePtr>>
    {
        using PolicyCategory_t = PolicyCategory_Getter<T, GenericGetterAccessorPolicy<UserCallablePtr>>;
    };

    /*
    * Basic setter behavior, used as default behavior.
    */
    template <class T>
    struct BasicSetterAccessorPolicy
    {
        static inline void Set(T& value, const T& newValue) { value = newValue; }
    };

    template <class T>
    struct PolicyCategoryTraits<T, PolicyCategory_Setter>
    {
        using FallbackPolicy = BasicSetterAccessorPolicy<T>;
    };

    template <class T>
    struct PolicyTraits<T, BasicSetterAccessorPolicy<T>>
    {
        using PolicyCategory_t = PolicyCategory_Setter<T, BasicSetterAccessorPolicy<T>>;
    };

    /*
    * Option for `Set` policy function definition externalization.
    */
    template
    <
        auto SetterFuncPtr // TODO: We should make this variatic so user can define both copy and move. Only 2 possible args, but variatic for order agnostic.
    >
    requires (TCallable<SetterFuncPtr> /* TODO: Use TSetterCallable when implemented */)
    struct GenericSetterAccessorPolicy
    {
        using SetterFuncPtrTraits = CppUtils::CustomAccess::FunctionPointerTraits<decltype(SetterFuncPtr)>;
        using ReturnType = SetterFuncPtrTraits::ReturnType;
        //using ClassType  = SetterFuncPtrTraits::ClassType; TODO: Support member function pointers so that we can support the outer object's functions.
        using ArgsTuple = SetterFuncPtrTraits::ArgsTuple;
        using FirstArg  = std::tuple_element_t<0, ArgsTuple>;
        using SecondArg = std::tuple_element_t<1, ArgsTuple>;

        using FirstArgValueType = std::remove_cvref_t<FirstArg>;

        static consteval bool IsFirstArgValid()
        {
            return std::is_lvalue_reference_v<FirstArg> &&
                   !CppUtils::CustomAccess::IsConstAfterRemovingRef <FirstArg>();
        }

        // Copy sets.

        static inline void Set(FirstArgValueType& value, const FirstArgValueType& newValue)
            requires
            (
                IsFirstArgValid()                     &&
                std::is_lvalue_reference_v<SecondArg> &&
                CppUtils::CustomAccess::IsConstAfterRemovingRef  <SecondArg>()
            )
        {
            SetterFuncPtr(value, newValue);
        }

        static inline void Set(FirstArgValueType& value, FirstArgValueType newValue)
            requires
            (
                IsFirstArgValid()                    &&
                !std::is_reference_v     <SecondArg> &&
                !std::is_const_v<SecondArg>
            )
        {
            SetterFuncPtr(value, newValue);
        }

        // Move set.
        static inline void Set(FirstArgValueType& value, FirstArgValueType&& newValue)
            requires
            (
                IsFirstArgValid()                     &&
                std::is_rvalue_reference_v<SecondArg> &&
                !CppUtils::CustomAccess::IsConstAfterRemovingRef <SecondArg>()
            )
        {
            SetterFuncPtr(value, std::move(newValue));
        }
    };

    template
    <
        class T,
        auto SetterFuncPtr
    >
    struct PolicyTraits<T, GenericSetterAccessorPolicy<SetterFuncPtr>>
    {
        using PolicyCategory_t = PolicyCategory_Setter<T, GenericSetterAccessorPolicy<SetterFuncPtr>>;
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
