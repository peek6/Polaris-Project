#pragma once
#include "CoreMinimal.h"
#include "LobbyNetwork.generated.h"

USTRUCT(BlueprintType)
struct FLobbyNetwork {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<int32> _servers;
    
    POLARIS_API FLobbyNetwork();
};

