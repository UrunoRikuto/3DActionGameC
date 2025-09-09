#include "SpriteDrawSetting.h"
#include "Defines.h"
#include "Geometory.h"

void CreateSpriteObject(DirectX::XMFLOAT3 Pos, DirectX::XMFLOAT3 Scale, DirectX::XMFLOAT3 Rotate, DirectX::XMFLOAT4 Color, Sprite* pSprite, Camera* Camera, bool IsBillborad)
{
	if (IsBillborad)
	{
		DirectX::XMMATRIX mCamInv = DirectX::XMMatrixIdentity();

		//カメラがあるか確認
		if (Camera)
		{
			//スプライト表示用の行列を設定
			Sprite::SetView(Camera->GetViewMatrix());
			Sprite::SetProjection(Camera->GetProjectionMatrix());

			//カメラの行列からビルボード行列を計算
			DirectX::XMFLOAT4X4 view = Camera->GetViewMatrix(false);
			mCamInv = DirectX::XMLoadFloat4x4(&view);
			mCamInv = DirectX::XMMatrixInverse(nullptr, mCamInv);
			DirectX::XMStoreFloat4x4(&view, mCamInv);
			view._41 = view._42 = view._43 = 0.0f; //移動部分の値を打ち消す
			mCamInv = DirectX::XMLoadFloat4x4(&view);

		}

		//ビルボード込のワールド行列を用意
		DirectX::XMMATRIX mWorld = mCamInv * DirectX::XMMatrixTranslation(Pos.x, Pos.y, Pos.z);
		mWorld = DirectX::XMMatrixTranspose(mWorld);

		//スプライトに設定するワールド行列を用意
		DirectX::XMFLOAT4X4 world;
		DirectX::XMStoreFloat4x4(&world, mWorld);

		//スプライトを描画
		Sprite::SetColor(Color);
		Sprite::SetOffset({ 0.0f, 0.0f });
		Sprite::SetSize({ Scale.x, Scale.z });
		Sprite::SetWorld(world);
	}
	else
	{
		//カメラがあるか確認
		if (Camera)
		{
			//スプライト表示用の行列を設定
			Sprite::SetView(Camera->GetViewMatrix());
			Sprite::SetProjection(Camera->GetProjectionMatrix());
		}
		//ワールド行列を用意
		DirectX::XMMATRIX mWorld = DirectX::XMMatrixIdentity();
		DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(Rotate.x, Rotate.y, Rotate.z);
		DirectX::XMMATRIX S = DirectX::XMMatrixScaling(Scale.x, Scale.z, Scale.y);
		DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(Pos.x, Pos.y, Pos.z);
		mWorld = S * R * T;
		mWorld = DirectX::XMMatrixTranspose(mWorld);
		//スプライトに設定するワールド行列を用意
		DirectX::XMFLOAT4X4 world;
		DirectX::XMStoreFloat4x4(&world, mWorld);
		Sprite::SetColor(Color);
		pSprite->SetWorld(world);
	}
}