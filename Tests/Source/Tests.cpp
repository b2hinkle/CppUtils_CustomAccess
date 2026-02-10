// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#include <CppUtils_CustomAccess/CustomAccessed.h>

/*
* [todo] This file is more of a developer sandbox at this point rather then concrete tests.
*        Take time to create proper tests.
*/
int main(int argc, char** argv)
{
    //MyStruct_InstanceTest instance;

    CppUtils::CustomAccessed
    <
        int,
        CppUtils::Get<[](const int& value) {return value + 8;}>,
        CppUtils::Set<[](int& value, const int& newValue) {value = newValue;}>
    >
    myCustomAccessedInt;
    myCustomAccessedInt.SetValue(10);
    //myCustomAccessedInt.SetValue(2);
    const int currentValue = myCustomAccessedInt.GetValue();
//
//#if 0 // TODO: Add support for this kind of syntax.
//    myCustomAccessedInt = myCustomAccessedInt + 1;
//#endif

    const bool isSuccess = myCustomAccessedInt.GetValue() == 18;
    return isSuccess
        ? 0
        : 1;
}