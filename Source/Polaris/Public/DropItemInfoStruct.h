#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DropItemInfoStruct.generated.h"

class APolarisItemBaseActor;

USTRUCT(BlueprintType)
struct POLARIS_API FDropItemInfoStruct {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float DropItemImpulsePower;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool IsDropItemImpulseDirEnable;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector DropItemImpulseDir;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    APolarisItemBaseActor* DropItemActor;
    
    FDropItemInfoStruct();
};

