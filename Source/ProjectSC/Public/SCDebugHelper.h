#pragma once

namespace Debug
{
	static void Print(const FString& Msg, float DisplayTime = 3.f, const FColor& Color = FColor::MakeRandomColor(), int32 InKey = -1)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(InKey, DisplayTime, Color, Msg);

			UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);

		}
	}
}