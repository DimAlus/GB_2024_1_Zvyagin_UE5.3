// Fill out your copyright notice in the Description page of Project Settings.


#include "./Typing.h"
DEFINE_LOG_CATEGORY(LogTemplateComponents);

float VectorsAngle(const FVector& v1, const FVector& v2) {
	float moduls = v1.Length() * v2.Length();
	return moduls > 0 ? acosf(v1.Dot(v2) / moduls) : 0;
}
