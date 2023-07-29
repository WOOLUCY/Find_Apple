// Fill out your copyright notice in the Description page of Project Settings.


#include "Sapphire.h"

ASapphire::ASapphire()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> SM_MESH
	(TEXT("/Script/Engine.StaticMesh'/Game/Woo/Cave/Ore/Ore01.Ore01'"));
	if (SM_MESH.Succeeded()) {
		mesh->SetStaticMesh(SM_MESH.Object);

	}
	light->SetLightColor(FLinearColor::Red);

	name = "Sapphire";

}
