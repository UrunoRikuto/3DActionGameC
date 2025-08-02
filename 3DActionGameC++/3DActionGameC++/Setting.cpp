#include "Setting.h"

DirectX::XMMATRIX Setting(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 Scale, DirectX::XMFLOAT3 Rotate)
{
	//�ړ��s��(Translation)
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslationFromVector(DirectX::XMVectorSet(pos.x, pos.y, pos.z, 0.0f));
	//�g��k���s��(Scaling)
	if (Scale.x == NULL)Scale.x = 1.0f;
	if (Scale.y == NULL)Scale.y = 1.0f;
	if (Scale.z == NULL)Scale.z = 1.0f;
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(Scale.x, Scale.y, Scale.z);
	//��]�s��(Rotation)
	DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYawFromVector(DirectX::XMVectorSet(DirectX::XMConvertToRadians(Rotate.x), DirectX::XMConvertToRadians(Rotate.y), DirectX::XMConvertToRadians(Rotate.z), 0.0f));
	//���ꂼ��̍s����|�����킹�Ċi�[
	DirectX::XMMATRIX mat = S * R * T;

	return mat;
}
