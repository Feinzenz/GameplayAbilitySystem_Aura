// Copyright Vinzenz Landl


#include "UI/WidgetController/MenuWidgetController.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Player/AuraPlayerState.h"

void UMenuWidgetController::BindCallbacksToDependencies()
{
	UAuraAttributeSet* AS = Cast<UAuraAttributeSet>(AttributeSet);
	for (auto& Pair : AS->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
		[this, Pair](const FOnAttributeChangeData& Data)
		{
			BroadcastAttributeInfo(Pair.Key, Pair.Value());
		}
		);
	}
	
	AAuraPlayerState* AuraPlayerState = CastChecked<AAuraPlayerState>(PlayerState);
	AuraPlayerState->OnAttributePointsChangedDelegate.AddLambda([this](int32 Points)
	{
		AttributePointsChangedDelegate.Broadcast(Points);
	});
	AuraPlayerState->OnSpellPointsChangedDelegate.AddLambda([this](int32 Points)
	{
		SpellPointsChangedDelegate.Broadcast(Points);
	});
}

void UMenuWidgetController::BroadcastInitialValues()
{
	UAuraAttributeSet* AS = Cast<UAuraAttributeSet>(AttributeSet);
	
	check(AttributeInfo)

	for (auto& Pair : AS->TagsToAttributes)
	{
		BroadcastAttributeInfo(Pair.Key, Pair.Value());
	}
	
	AAuraPlayerState* AuraPlayerState = CastChecked<AAuraPlayerState>(PlayerState);
	AttributePointsChangedDelegate.Broadcast(AuraPlayerState->GetAttributePoints());
	SpellPointsChangedDelegate.Broadcast(AuraPlayerState->GetSpellPoints());
}

void UMenuWidgetController::UpgradeAttribute(const FGameplayTag& AttributeTag)
{
	UAuraAbilitySystemComponent* AuraASC = CastChecked<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	AuraASC->UpgradeAttribute(AttributeTag);
}

void UMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag,
                                                   const FGameplayAttribute& Attribute) const
{
	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}
