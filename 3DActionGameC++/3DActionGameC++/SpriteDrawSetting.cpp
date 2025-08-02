#include "SpriteDrawSetting.h"
#include "Defines.h"
#include "Geometory.h"

void CreateSpriteObject(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 Scale, DirectX::XMFLOAT3 Rotate, Sprite* pSprite, Camera* Camera, bool IsBillborad)
{
	DirectX::XMFLOAT4X4 wvp[3];
	DirectX::XMMATRIX world;
	world = Setting(pos, Scale, Rotate);

	DirectX::XMStoreFloat4x4(&wvp[0], DirectX::XMMatrixTranspose(world));
	if (IsBillborad)
	{
		//ビルボードの実装
		//DirectX::XMMATRIX Mview;
		//DirectX::XMVECTOR Vview;
		//DirectX::XMFLOAT4X4 F4x4view = Camera->GetViewMatrix();
		//Mview = DirectX::XMLoadFloat4x4(&F4x4view);
		//Mview = DirectX::XMMatrixInverse(nullptr, Mview);
		//DirectX::XMStoreFloat4x4(&wvp[1], Mview);

		//wvp[1]._41 = 0.0f;
		//wvp[1]._42 = 0.0f;
		//wvp[1]._43 = 0.0f;
		wvp[1] = Camera->GetViewMatrix();
	}
	else
	{
		wvp[1] = Camera->GetViewMatrix();
	}

	wvp[2] = Camera->GetProjectionMatrix();

	pSprite->SetWorld(wvp[0]);
	pSprite->SetView(wvp[1]);
	pSprite->SetProjection(wvp[2]);
}