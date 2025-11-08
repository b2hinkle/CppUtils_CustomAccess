// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#include <CppUtils_CustomAccessed/CustomAccessed.h>

int main(int argc, char** argv)
{
    CppUtils::CustomAccessed<int> myCustomAccessedInt;

    myCustomAccessedInt = myCustomAccessedInt + 1;

    return 0;
}
