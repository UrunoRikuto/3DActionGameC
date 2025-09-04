/*=====================================================================
* @file StructMath.h
* @brief ‰‰Z‚ğs‚¤‚½‚ß‚Ìƒtƒ@ƒCƒ‹
=====================================================================*/

#pragma once
#include <DirectXMath.h>
#include <math.h>

using namespace DirectX;

namespace StructMath
{
	/*===========================================================
	* XMFLOAT3‚ÆXMFLOAT3‚Ì‰‰Z
	===========================================================*/
	// ‰ÁZ
	inline XMFLOAT3 Add(XMFLOAT3 t1, XMFLOAT3 t2)
	{
		return XMFLOAT3(t1.x + t2.x, t1.y + t2.y, t1.z + t2.z);
	}
	// Œ¸Z
	inline XMFLOAT3 Sub(XMFLOAT3 t1, XMFLOAT3 t2)
	{
		return XMFLOAT3(t1.x - t2.x, t1.y - t2.y, t1.z - t2.z);
	}
	// æZ
	inline XMFLOAT3 Mul(XMFLOAT3 t1, XMFLOAT3 t2)
	{
		return XMFLOAT3(t1.x * t2.x, t1.y * t2.y, t1.z * t2.z);
	}
	// œZ
	inline XMFLOAT3 Div(XMFLOAT3 t1, XMFLOAT3 t2)
	{
		return XMFLOAT3(t1.x / t2.x, t1.y / t2.y, t1.z / t2.z);
	}

	// ³‹K‰»
	inline XMFLOAT3 Normalize(XMFLOAT3 t1)
	{
		float length = sqrtf(t1.x * t1.x + t1.y * t1.y + t1.z * t1.z);
		if (length == 0.0f) return XMFLOAT3(0.0f, 0.0f, 0.0f);
		return XMFLOAT3(t1.x / length, t1.y / length, t1.z / length);
	}
	// ’·‚³
	inline float Length(XMFLOAT3 t1)
	{
		return sqrtf(t1.x * t1.x + t1.y * t1.y + t1.z * t1.z);
	}

	// â‘Î’l
	inline XMFLOAT3 Abs(XMFLOAT3 t1)
	{
		return XMFLOAT3(fabsf(t1.x), fabsf(t1.y), fabsf(t1.z));
	}
	// “àÏ
	inline float Dot(XMFLOAT3 t1, XMFLOAT3 t2)
	{
		return t1.x * t2.x + t1.y * t2.y + t1.z * t2.z;
	}
	// ŠOÏ
	inline XMFLOAT3 Cross(XMFLOAT3 t1, XMFLOAT3 t2)
	{
		return XMFLOAT3(
			t1.y * t2.z - t1.z * t2.y,
			t1.z * t2.x - t1.x * t2.z,
			t1.x * t2.y - t1.y * t2.x
		);
	}

	// “™‚µ‚¢
	inline bool Equal(XMFLOAT3 t1, XMFLOAT3 t2)
	{
		return t1.x == t2.x && t1.y == t2.y && t1.z == t2.z;
	}
	// ‹——£
	inline float Distance(XMFLOAT3 t1, XMFLOAT3 t2)
	{
		return sqrtf((t1.x - t2.x) * (t1.x - t2.x) + (t1.y - t2.y) * (t1.y - t2.y) + (t1.z - t2.z) * (t1.z - t2.z));
	}
	// •ûŒü
	inline XMFLOAT3 Direction(XMFLOAT3 t1, XMFLOAT3 t2)
	{
		XMFLOAT3 dir = Sub(t2, t1);
		return Normalize(dir);
	}


	/*===========================================================
	* XMFLOAT2‚ÆXMFLOAT2‚Ì‰‰Z
	===========================================================*/
	// ‰ÁZ
	inline XMFLOAT2 Add(XMFLOAT2 t1, XMFLOAT2 t2)
	{
		return XMFLOAT2(t1.x + t2.x, t1.y + t2.y);
	}
	// Œ¸Z
	inline XMFLOAT2 Sub(XMFLOAT2 t1, XMFLOAT2 t2)
	{
		return XMFLOAT2(t1.x - t2.x, t1.y - t2.y);
	}
	// æZ
	inline XMFLOAT2 Mul(XMFLOAT2 t1, XMFLOAT2 t2)
	{
		return XMFLOAT2(t1.x * t2.x, t1.y * t2.y);
	}
	// œZ
	inline XMFLOAT2 Div(XMFLOAT2 t1, XMFLOAT2 t2)
	{
		return XMFLOAT2(t1.x / t2.x, t1.y / t2.y);
	}
	// “™‚µ‚¢
	inline bool Equal(XMFLOAT2 t1, XMFLOAT2 t2)
	{
		return t1.x == t2.x && t1.y == t2.y;
	}


	/*===========================================================
	* XMFLOAT3‚Æfloat‚Ì‰‰Z
	===========================================================*/
	// ‰ÁZ
	inline XMFLOAT3 Add(XMFLOAT3 t1, float f)
	{
		return XMFLOAT3(t1.x + f, t1.y + f, t1.z + f);
	}
	// Œ¸Z
	inline XMFLOAT3 Sub(XMFLOAT3 t1, float f)
	{
		return XMFLOAT3(t1.x - f, t1.y - f, t1.z - f);
	}
	// æZ
	inline XMFLOAT3 Mul(XMFLOAT3 t1, float f)
	{
		return XMFLOAT3(t1.x * f, t1.y * f, t1.z * f);
	}
	// œZ
	inline XMFLOAT3 Div(XMFLOAT3 t1, float f)
	{
		return XMFLOAT3(t1.x / f, t1.y / f, t1.z / f);
	}

	// ˆÈ‰º
	inline bool LessEqual(XMFLOAT3 t1, float f)
	{
		return t1.x <= f && t1.y <= f && t1.z <= f;
	}
	// ˆÈã
	inline bool MoreEqual(XMFLOAT3 t1, float f)
	{
		return t1.x >= f && t1.y >= f && t1.z >= f;
	}


	/*===========================================================
	* XMFLOAT2‚Æfloat‚Ì‰‰Z
	===========================================================*/
	// ‰ÁZ
	inline XMFLOAT2 Add(XMFLOAT2 t1, float f)
	{
		return XMFLOAT2(t1.x + f, t1.y + f);
	}
	// Œ¸Z
	inline XMFLOAT2 Sub(XMFLOAT2 t1, float f)
	{
		return XMFLOAT2(t1.x - f, t1.y - f);
	}
	// æZ
	inline XMFLOAT2 Mul(XMFLOAT2 t1, float f)
	{
		return XMFLOAT2(t1.x * f, t1.y * f);
	}
	// œZ
	inline XMFLOAT2 Div(XMFLOAT2 t1, float f)
	{
		return XMFLOAT2(t1.x / f, t1.y / f);
	}
	// ˆÈ‰º
	inline bool LessEqual(XMFLOAT2 t1, float f)
	{
		return t1.x <= f && t1.y <= f;
	}
	// ˆÈã
	inline bool MoreEqual(XMFLOAT2 t1, float f)
	{
		return t1.x >= f && t1.y >= f;
	}


	/*===========================================================
	* float‚ÆXMFLOAT‚Ì‰‰Z
	===========================================================*/
	// float‚ğXMFLOAT2‚É•ÏŠ·
	inline XMFLOAT2 FtoF2(float f)
	{
		return XMFLOAT2(f, f);
	}
	// float‚ğXMFLOAT3‚É•ÏŠ·
	inline XMFLOAT3 FtoF3(float f)
	{
		return XMFLOAT3(f, f, f);
	}
	// float‚ğXMFLOAT4‚É•ÏŠ·
	inline XMFLOAT4 FtoF4(float f)
	{
		return XMFLOAT4(f, f, f, f);
	}

	/*===========================================================
	* float‚Ì‰‰Z(d—l‚Ì“ˆê)
	===========================================================*/
	// â‘Î’l
	inline float Abs(float f)
	{
		return fabsf(f);
	}
}