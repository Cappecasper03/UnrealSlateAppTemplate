// Copyright Epic Games, Inc. All Rights Reserved.

#include "SMainWindow.h"

#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"

SMainWindow::SMainWindow() {}

void SMainWindow::Construct( const FArguments& InArgs )
{
	SWindow::Construct( SWindow::FArguments()
	                    .Title( FText::FromString( TEXT( "UnrealSlateAppTemplate" ) ) )
	                    .ClientSize( FVector2D( 800, 600 ) ) );

	SetContent(
		SNew( SBox )
		.HAlign( HAlign_Center )
		.VAlign( VAlign_Center )
		[
			SNew( STextBlock )
			.Text( FText::FromString( TEXT( "Welcome to UnrealSlateAppTemplate!" ) ) )
			.Font( FCoreStyle::GetDefaultFontStyle( "Regular", 20 ) )
		] );
}