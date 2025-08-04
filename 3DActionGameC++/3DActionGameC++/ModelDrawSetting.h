#pragma once

#include "Camera.h"

class Model;

void CreateObject(
	DirectX::XMFLOAT3 pos = { 0.0f,0.0f,0.0f }, 
	DirectX::XMFLOAT3 Scale = { 0.0f,0.0f,0.0f }, 
	DirectX::XMFLOAT3 Rotate = { 0.0f,0.0f,0.0f }, 
	Model* Model = nullptr, Camera* Camera = nullptr, 
	bool IsLighting = false,
	DirectX::XMFLOAT3 LightingColor = { 0.6f,0.6f,0.6f });

void CreateAnimationObject(
	DirectX::XMFLOAT3 pos = { 0.0f,0.0f,0.0f },
	DirectX::XMFLOAT3 Scale = { 0.0f,0.0f,0.0f },
	DirectX::XMFLOAT3 Rotate = { 0.0f,0.0f,0.0f },
	Model* Model = nullptr, Camera* Camera = nullptr,
	bool IsLighting = false,
	DirectX::XMFLOAT3 LightingColor = { 0.6f,0.6f,0.6f });