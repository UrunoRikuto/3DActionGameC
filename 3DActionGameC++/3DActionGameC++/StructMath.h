#pragma once
#include <DirectXMath.h>

using namespace DirectX;

namespace StructMath
{
	/*===========================================================
	* XMFLOAT3Ç∆XMFLOAT3ÇÃââéZ
	===========================================================*/
	//â¡éZ
	inline XMFLOAT3 Add(XMFLOAT3 t1, XMFLOAT3 t2)
	{
		return XMFLOAT3(t1.x + t2.x, t1.y + t2.y, t1.z + t2.z);
	}
	//å∏éZ
	inline XMFLOAT3 Sub(XMFLOAT3 t1, XMFLOAT3 t2)
	{
		return XMFLOAT3(t1.x - t2.x, t1.y - t2.y, t1.z - t2.z);
	}
	//èÊéZ
	inline XMFLOAT3 Mul(XMFLOAT3 t1, XMFLOAT3 t2)
	{
		return XMFLOAT3(t1.x * t2.x, t1.y * t2.y, t1.z * t2.z);
	}
	//èúéZ
	inline XMFLOAT3 Div(XMFLOAT3 t1, XMFLOAT3 t2)
	{
		return XMFLOAT3(t1.x / t2.x, t1.y / t2.y, t1.z / t2.z);
	}
	//ìôÇµÇ¢
	inline bool Equal(XMFLOAT3 t1, XMFLOAT3 t2)
	{
		return t1.x == t2.x && t1.y == t2.y && t1.z == t2.z;
	}
	//à»â∫
	inline bool LessEqual(XMFLOAT3 t1, XMFLOAT3 t2)
	{
		return t1.x <= t2.x && t1.y <= t2.y && t1.z <= t2.z;
	}
	//à»è„
	inline bool MoreEqual(XMFLOAT3 t1, XMFLOAT3 t2)
	{
		return t1.x >= t2.x && t1.y >= t2.y && t1.z >= t2.z;
	}

	/*===========================================================
	* XMFLOAT3Ç∆floatÇÃââéZ
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