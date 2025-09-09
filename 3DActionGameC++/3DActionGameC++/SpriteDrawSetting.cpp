#include "SpriteDrawSetting.h"
#include "Defines.h"
#include "Geometory.h"

void CreateSpriteObject(DirectX::XMFLOAT3 Pos, DirectX::XMFLOAT3 Scale, DirectX::XMFLOAT3 Rotate, DirectX::XMFLOAT4 Color, Sprite* pSprite, Camera* Camera, bool IsBillborad)
{
	if (IsBillborad)
	{
		DirectX::XMMATRIX mCamInv = DirectX::XMMatrixIdentity();

		//�J���������邩�m�F
		if (Camera)
		{
			//�X�v���C�g�\���p�̍s���ݒ�
			Sprite::SetView(Camera->GetViewMatrix());
			Sprite::SetProjection(Camera->GetProjectionMatrix());

			//�J�����̍s�񂩂�r���{�[�h�s����v�Z
			DirectX::XMFLOAT4X4 view = Camera->GetViewMatrix(false);
			mCamInv = DirectX::XMLoadFloat4x4(&view);
			mCamInv = DirectX::XMMatrixInverse(nullptr, mCamInv);
			DirectX::XMStoreFloat4x4(&view, mCamInv);
			view._41 = view._42 = view._43 = 0.0f; //�ړ������̒l��ł�����
			mCamInv = DirectX::XMLoadFloat4x4(&view);

		}

		//�r���{�[�h���̃��[���h�s���p��
		DirectX::XMMATRIX mWorld = mCamInv * DirectX::XMMatrixTranslation(Pos.x, Pos.y, Pos.z);
		mWorld = DirectX::XMMatrixTranspose(mWorld);

		//�X�v���C�g�ɐݒ肷�郏�[���h�s���p��
		DirectX::XMFLOAT4X4 world;
		DirectX::XMStoreFloat4x4(&world, mWorld);

		//�X�v���C�g��`��
		Sprite::SetColor(Color);
		Sprite::SetOffset({ 0.0f, 0.0f });
		Sprite::SetSize({ Scale.x, Scale.z });
		Sprite::SetWorld(world);
	}
	else
	{
		//�J���������邩�m�F
		if (Camera)
		{
			//�X�v���C�g�\���p�̍s���ݒ�
			Sprite::SetView(Camera->GetViewMatrix());
			Sprite::SetProjection(Camera->GetProjectionMatrix());
		}
		//���[���h�s���p��
		DirectX::XMMATRIX mWorld = DirectX::XMMatrixIdentity();
		DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(Rotate.x, Rotate.y, Rotate.z);
		DirectX::XMMATRIX S = DirectX::XMMatrixScaling(Scale.x, Scale.z, Scale.y);
		DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(Pos.x, Pos.y, Pos.z);
		mWorld = S * R * T;
		mWorld = DirectX::XMMatrixTranspose(mWorld);
		//�X�v���C�g�ɐݒ肷�郏�[���h�s���p��
		DirectX::XMFLOAT4X4 world;
		DirectX::XMStoreFloat4x4(&world, mWorld);
		Sprite::SetColor(Color);
		pSprite->SetWorld(world);
	}
}