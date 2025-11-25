// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 */
class SMainWindow : public SWindow
{
public:
	SMainWindow();

	SLATE_BEGIN_ARGS( SMainWindow ) {}
	SLATE_END_ARGS()

	void Construct( const FArguments& InArgs );
};