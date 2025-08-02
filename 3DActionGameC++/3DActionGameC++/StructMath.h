#pragma once
#include <DirectXMath.h>

using namespace DirectX;

namespace StructMath
{
	/*===========================================================
	* XMFLOAT3��XMFLOAT3�̉��Z
	===========================================================*/
	//���Z
	inline XMFLOAT3 Add(XMFLOAT3 t1, XMFLOAT3 t2)
	{
		return XMFLOAT3(t1.x + t2.x, t1.y + t2.y, t1.z + t2.z);
	}
	//���Z
	inline XMFLOAT3 Sub(XMFLOAT3 t1, XMFLOAT3 t2)
	{
		return XMFLOAT3(t1.x - t2.x, t1.y - t2.y, t1.z - t2.z);
	}
	//��Z
	inline XMFLOAT3 Mul(XMFLOAT3 t1, XMFLOAT3 t2)
	{
		return XMFLOAT3(t1.x * t2.x, t1.y * t2.y, t1.z * t2.z);
	}
	//���Z
	inline XMFLOAT3 Div(XMFLOAT3 t1, XMFLOAT3 t2)
	{
		return XMFLOAT3(t1.x / t2.x, t1.y / t2.y, t1.z / t2.z);
	}
	//������
	inline bool Equal(XMFLOAT3 t1, XMFLOAT3 t2)
	{
		return t1.x == t2.x && t1.y == t2.y && t1.z == t2.z;
	}
	//�ȉ�
	inline bool LessEqual(XMFLOAT3 t1, XMFLOAT3 t2)
	{
		return t1.x <= t2.x && t1.y <= t2.y && t1.z <= t2.z;
	}
	//�ȏ�
	inline bool MoreEqual(XMFLOAT3 t1, XMFLOAT3 t2)
	{
		return t1.x >= t2.x && t1.y >= t2.y && t1.z >= t2.z;
	}

	/*===========================================================
	* XMFLOAT3��float�̉��Z
	===========================================================*/
	inline XMFLOAT3 Add(XMFLOAT3 t1, float f)
	{
		return XMFLOAT3(t1.x + f, t1.y + f, t1.z + f);
	}

	inline XMFLOAT3 Sub(XMFLOAT3 t1, float f)
	{
		return XMFLOAT3(t1.x - f, t1.y - f, t1.z - f);
	}

	inline XMFLOAT3 Mul(XMFLOAT3 t1, float f)
	{
		return XMFLOAT3(t1.x * f, t1.y * f, t1.z * f);
	}

	inline XMFLOAT3 Div(XMFLOAT3 t1, float f)
	{
		return XMFLOAT3(t1.x / f, t1.y / f, t1.z / f);
	}
}