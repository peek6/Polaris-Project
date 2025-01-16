#pragma once
#include "CoreMinimal.h"
#include "EffectUserParameterInt.generated.h"

USTRUCT(BlueprintType)
struct FEffectUserParameterInt {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString ParameterName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 ParameterInt;
    
    POLARIS_API FEffectUserParameterInt();
};

