// Fill out your copyright notice in the Description page of Project Settings.


#include "Gold.h"

AGold::AGold()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> SM_MESH
	(TEXT("/Script/Engine.StaticMesh'/Game/Woo/Cave/Ore/Ore07.Ore07'"));
	if (SM_MESH.Succeeded()) {
		mesh->SetStaticMesh(SM_MESH.Object);

	}
	light->SetLightColor(FLinearColor::Yellow);

	name = "Gold";

}


