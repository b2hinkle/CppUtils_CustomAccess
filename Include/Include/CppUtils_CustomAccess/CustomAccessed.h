// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <type_traits>
#include <CppUtils_CustomAccess/AccessorPolicies.h>
#include <CppUtils_CustomAccess/FindAccessorPolicy.h>
#include <CppUtils/Misc/TypeTraits.h>


namespace CppUtils
{
    /**
     * Property wrapper implementation.
     * User generates access behavior by providing accessor policy classes as template arguments. Generic accessor policies are most common, as they simply forward execution to users' external function definitions. Default behavior exists where user doesn't specify behavior.
-    * User functions are specified via packed template type parameters. This way, "argument" order of accessor policies is up to the user and there are no forced argument situations.
     * [todo] We should support all special member functions.
     * [todo] Provide a default value constructor, to support pr value sematics.
     * [todo] I want users to be able to directly call the policies' api, rather than an api that forwards to the policies' api. Can achieve this via inheritence of the policies.
     */
    template <
        class T,
        class... AccessorPolicies
    >
    struct CustomAccessed
    {
        
    public:

        using AccessorPolicyStaticInterface_Getter = AccessorPolicyUtils::CompleteAccessorPolicyStaticInterface
         <
            AccessorPolicyStaticInterface_Getter,
            T,
            AccessorPolicies...
         >::type;

        using AccessorPolicyStaticInterface_Setter = AccessorPolicyUtils::CompleteAccessorPolicyStaticInterface
         <
            AccessorPolicyStaticInterface_Setter,
            T,
            AccessorPolicies...
         >::type;

    public:

        CustomAccessed() = default;

        /*
        * In the case of copy return value, cpp 17 prvalue semantics gives us guaranteed copy elision.
        * Since we're able to avoid decltype(auto) return type, we do. This is because its deduction phase can trigger unnecessary errors when our accessor policy isn't defined correctly.
        */
        inline typename AccessorPolicyStaticInterface_Getter::ReturnType GetValue() const
            requires ( requires(T dummyBackingValue) { AccessorPolicyStaticInterface_Getter::Get(dummyBackingValue); } )
        {
            return AccessorPolicyStaticInterface_Getter::Get(m_BackingValue);
        }

        inline void SetValue(typename AccessorPolicyStaticInterface_Setter::SecondArg newValue)
            requires ( requires(T dummyBackingValue, T dummyNewValue) { AccessorPolicyStaticInterface_Setter::Set(dummyBackingValue, dummyNewValue); } )
        {
            if constexpr (std::is_rvalue_reference_v<typename AccessorPolicyStaticInterface_Setter::SecondArg>)
            {
                // Non-const rvalue reference. Non-const because that's already been asserted.
                AccessorPolicyStaticInterface_Setter::Set(m_BackingValue, std::move(newValue));
            }
            else
            {
                // Either const lvalue reference or const/non-const copy.
                AccessorPolicyStaticInterface_Setter::Set(m_BackingValue, newValue);
            }
        }

    private:
    
        // TODO: Would be good to support no backing value instantiations for particular use cases.
        T m_BackingValue{};

    };
}