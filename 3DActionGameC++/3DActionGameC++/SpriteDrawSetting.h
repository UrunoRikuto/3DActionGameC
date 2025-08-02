#pragma once
#include "Setting.h"

#include "Camera.h"
#include "Texture.h"
#include "Sprite.h"


void CreateSpriteObject(
	DirectX::XMFLOAT3 pos = { 0.0f,0.0f,0.0f },
	DirectX::XMFLOAT3 Scale = { 0.0f,0.0f,0.0f },
	DirectX::XMFLOAT3 Rotate = { 0.0f,0.0f,0.0f },
	Sprite* pSprite = nullptr,
	Camera* Camera = nullptr,
	bool IsBillborad = false);