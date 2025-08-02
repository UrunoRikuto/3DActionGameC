#include "Setting.h"

DirectX::XMMATRIX Setting(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 Scale, DirectX::XMFLOAT3 Rotate)
{
	//à⁄ìÆçsóÒ(Translation)
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslationFromVector(DirectX::XMVectorSet(pos.x, pos.y, pos.z, 0.0f));
	//ägëÂèkè¨çsóÒ(Scaling)
	if (Scale.x == NULL)Scale.x = 1.0f;
	if (Scale.y == NULL)Scale.y = 1.0f;
	if (Scale.z == NULL)Scale.z = 1.0f;
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(Scale.x, Scale.y, Scale.z);
	//âÒì]çsóÒ(Rotation)
	DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYawFromVector(DirectX::XMVectorSet(DirectX::XMConvertToRadians(Rotate.x), DirectX::XMConvertToRadians(Rotate.y), DirectX::XMConvertToRadians(Rotate.z), 0.0f));
	//ÇªÇÍÇºÇÍÇÃçsóÒÇä|ÇØçáÇÌÇπÇƒäiî[
	DirectX::XMMATRIX mat = S * R * T;

	return mat;
}
