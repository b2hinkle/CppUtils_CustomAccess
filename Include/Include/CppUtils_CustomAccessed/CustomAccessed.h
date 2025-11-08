// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#if 0

USTRUCT(BlueprintType)
struct GAMECORE_API FGCFloatPropertyWrapper : public FGCPropertyWrapperBase
{
    GENERATED_BODY()

    GC_PROPERTY_WRAPPER_CHILD_BODY(FGCFloatPropertyWrapper, float, 0.f);

    virtual FString ToString() const override { return FString::SanitizeFloat(Value); }

protected:
    /** The actual value of this float property */
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float Value;
};

template <>
struct TStructOpsTypeTraits<FGCFloatPropertyWrapper> : public TStructOpsTypeTraits<FGCFloatPropertyWrapper>
{
    enum
    {
        WithSerializer = true, // required for the property wrapper
        WithNetSerializer = true // required for the property wrapper
    };
};


USTRUCT(BlueprintType)
struct GAMECORE_API FGCInt32PropertyWrapper : public FGCPropertyWrapperBase
{
    GENERATED_BODY()

    GC_PROPERTY_WRAPPER_CHILD_BODY(FGCInt32PropertyWrapper, int32, 0);

    virtual FString ToString() const override { return FString::FromInt(Value); }

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 Value;
};

template <>
struct TStructOpsTypeTraits<FGCInt32PropertyWrapper> : public TStructOpsTypeTraits<FGCInt32PropertyWrapper>
{
    enum
    {
        WithSerializer = true,
        WithNetSerializer = true
    };
};

#endif