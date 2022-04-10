// Fill out your copyright notice in the Description page of Project Settings.


#include "FIleLoader.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

void UFIleLoader::loadFile(FString path, TArray<FString>&OutNames, TArray<int>& OutType, TArray<FVector>& OutPosition, TArray<FVector>& OutScale, TArray<FRotator>& OutRotation, TArray<bool>& OutRigidBody)
{
	FString output;
	FFileHelper::LoadFileToString(output, *path);
	int index = 0;
	TArray<FString> temp;
	output.ParseIntoArray(temp, TEXT("\n"));
	for (int i = 0; i < temp.Num(); i++) {
		if (index == 0) {
			TArray<FString> name;
			temp[i].ParseIntoArray(name, TEXT(" "));
			OutType.Add(FCString::Atoi(*name[1]));
			index++;
		}
		else if (index == 1) {
			OutNames.Add(temp[i]);
			index++;
		}
		else if (index == 2) {
			TArray<FString> pos;
			temp[i].ParseIntoArray(pos, TEXT(" "));
			OutPosition.Add(FVector(FCString::Atof(*pos[1])*100.0f, FCString::Atof(*pos[3]) * 100.0f, FCString::Atof(*pos[2]) * 100.0f));
			index++;
		}
		else if (index == 3) {
			TArray<FString> rot;
			temp[i].ParseIntoArray(rot, TEXT(" "));
			OutRotation.Add(FRotator::MakeFromEuler(FVector(FCString::Atof(*rot[1]), FCString::Atof(*rot[3]), FCString::Atof(*rot[2]))));
			index++;
		}
		else if (index == 4) {
			TArray<FString> scale;
			temp[i].ParseIntoArray(scale, TEXT(" "));
			OutScale.Add(FVector(FCString::Atof(*scale[1]), FCString::Atof(*scale[3]), FCString::Atof(*scale[2])));
			index++;
		}
		else if (index == 5) {
			OutRigidBody.Add((bool)FCString::Atoi(*temp[i]));
			index = 0;
		}
	}
}
void UFIleLoader::saveFile(TArray<AActor*> actors,TArray<bool> rb, FString filePath) {
	FString input;
	for (int i = 0; i < actors.Num(); i++) {
		if (actors[i]->ActorHasTag("Cube")) {
			input.Append("Type: 1\n");
			input.Append(actors[i]->GetActorLabel() + "\n");
			input.Append("Position: " + FString::SanitizeFloat(actors[i]->GetActorLocation().X / 100.0f) + " " + FString::SanitizeFloat(actors[i]->GetActorLocation().Z / 100.0f) + " " + FString::SanitizeFloat(actors[i]->GetActorLocation().Y / 100.0f) + "\n");
			input.Append("Rotation: " + FString::SanitizeFloat(actors[i]->GetActorRotation().Euler().X) + " " + FString::SanitizeFloat(actors[i]->GetActorRotation().Euler().Z) + " " + FString::SanitizeFloat(actors[i]->GetActorRotation().Euler().Y) + "\n");
			input.Append("Scale: " + FString::SanitizeFloat(actors[i]->GetActorScale().X) + " " + FString::SanitizeFloat(actors[i]->GetActorScale().Z) + " " + FString::SanitizeFloat(actors[i]->GetActorScale().Y) + "\n");
			if (rb[i]) {
				input.Append("1\n");
			}
			else {
				input.Append("0\n");
			}
		}
		else if (actors[i]->ActorHasTag("Plane")) {
			input.Append("Type: 2\n");
			input.Append(actors[i]->GetActorLabel() + "\n");
			input.Append("Position: " + FString::SanitizeFloat(actors[i]->GetActorLocation().X / 100.0f) + " " + FString::SanitizeFloat(actors[i]->GetActorLocation().Z / 100.0f) + " " + FString::SanitizeFloat(actors[i]->GetActorLocation().Y / 100.0f) + "\n");
			input.Append("Rotation: " + FString::SanitizeFloat(actors[i]->GetActorRotation().Euler().X) + " " + FString::SanitizeFloat(actors[i]->GetActorRotation().Euler().Z) + " " + FString::SanitizeFloat(actors[i]->GetActorRotation().Euler().Y) + "\n");
			input.Append("Scale: " + FString::SanitizeFloat(actors[i]->GetActorScale().X) + " " + FString::SanitizeFloat(actors[i]->GetActorScale().Z) + " " + FString::SanitizeFloat(actors[i]->GetActorScale().Y) + "\n");
			if (rb[i]) {
				input.Append("1\n");
			}
			else {
				input.Append("0\n");
			}
		}
		else if (actors[i]->ActorHasTag("Sphere")) {
			input.Append("Type: 3\n");
			input.Append(actors[i]->GetActorLabel() + "\n");
			input.Append("Position: " + FString::SanitizeFloat(actors[i]->GetActorLocation().X / 100.0f) + " " + FString::SanitizeFloat(actors[i]->GetActorLocation().Z / 100.0f) + " " + FString::SanitizeFloat(actors[i]->GetActorLocation().Y / 100.0f) + "\n");
			input.Append("Rotation: " + FString::SanitizeFloat(actors[i]->GetActorRotation().Euler().X) + " " + FString::SanitizeFloat(actors[i]->GetActorRotation().Euler().Z) + " " + FString::SanitizeFloat(actors[i]->GetActorRotation().Euler().Y) + "\n");
			input.Append("Scale: " + FString::SanitizeFloat(actors[i]->GetActorScale().X) + " " + FString::SanitizeFloat(actors[i]->GetActorScale().Z) + " " + FString::SanitizeFloat(actors[i]->GetActorScale().Y) + "\n");
			if (rb[i]) {
				input.Append("1\n");
			}
			else {
				input.Append("0\n");
			}
		}
		else if (actors[i]->ActorHasTag("Cylinder")) {
			input.Append("Type: 5\n");
			input.Append(actors[i]->GetActorLabel() + "\n");
			input.Append("Position: " + FString::SanitizeFloat(actors[i]->GetActorLocation().X / 100.0f) + " " + FString::SanitizeFloat(actors[i]->GetActorLocation().Z / 100.0f) + " " + FString::SanitizeFloat(actors[i]->GetActorLocation().Y / 100.0f) + "\n");
			input.Append("Rotation: " + FString::SanitizeFloat(actors[i]->GetActorRotation().Euler().X) + " " + FString::SanitizeFloat(actors[i]->GetActorRotation().Euler().Z) + " " + FString::SanitizeFloat(actors[i]->GetActorRotation().Euler().Y) + "\n");
			input.Append("Scale: " + FString::SanitizeFloat(actors[i]->GetActorScale().X) + " " + FString::SanitizeFloat(actors[i]->GetActorScale().Z) + " " + FString::SanitizeFloat(actors[i]->GetActorScale().Y) + "\n");
			if (rb[i]) {
			input.Append("1\n");
			}
			else {
				input.Append("0\n");
			}

		}
		else if (actors[i]->ActorHasTag("Capsule")) {
			input.Append("Type: 4\n");
			input.Append(actors[i]->GetActorLabel() + "\n");
			input.Append("Position: " + FString::SanitizeFloat(actors[i]->GetActorLocation().X / 100.0f) + " " + FString::SanitizeFloat(actors[i]->GetActorLocation().Z / 100.0f) + " " + FString::SanitizeFloat(actors[i]->GetActorLocation().Y / 100.0f) + "\n");
			input.Append("Rotation: " + FString::SanitizeFloat(actors[i]->GetActorRotation().Euler().X) + " " + FString::SanitizeFloat(actors[i]->GetActorRotation().Euler().Z) + " " + FString::SanitizeFloat(actors[i]->GetActorRotation().Euler().Y) + "\n");
			input.Append("Scale: " + FString::SanitizeFloat(actors[i]->GetActorScale().X) + " " + FString::SanitizeFloat(actors[i]->GetActorScale().Z) + " " + FString::SanitizeFloat(actors[i]->GetActorScale().Y) + "\n");
			if (rb[i]) {
				input.Append("1\n");
			}
			else {
				input.Append("0\n");
			}
		}
		
	}
	FFileHelper::SaveStringToFile(input, *filePath);
}
