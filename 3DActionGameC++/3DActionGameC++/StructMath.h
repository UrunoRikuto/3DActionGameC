/*=====================================================================
* @file StructMath.h
* @brief ���Z���s�����߂̃t�@�C��
=====================================================================*/

#pragma once
#include <DirectXMath.h>
#include <math.h>

using namespace DirectX;

namespace StructMath
{
	/*===========================================================
	* XMFLOAT3��XMFLOAT3�̉��Z
	===========================================================*/
	// ���Z
	inline XMFLOAT3 Add(XMFLOAT3 t1, XMFLOAT3 t2)
	{
		return XMFLOAT3(t1.x + t2.x, t1.y + t2.y, t1.z + t2.z);
	}
	// ���Z
	inline XMFLOAT3 Sub(XMFLOAT3 t1, XMFLOAT3 t2)
	{
		return XMFLOAT3(t1.x - t2.x, t1.y - t2.y, t1.z - t2.z);
	}
	// ��Z
	inline XMFLOAT3 Mul(XMFLOAT3 t1, XMFLOAT3 t2)
	{
		return XMFLOAT3(t1.x * t2.x, t1.y * t2.y, t1.z * t2.z);
	}
	// ���Z
	inline XMFLOAT3 Div(XMFLOAT3 t1, XMFLOAT3 t2)
	{
		return XMFLOAT3(t1.x / t2.x, t1.y / t2.y, t1.z / t2.z);
	}

	// ���K��
	inline XMFLOAT3 Normalize(XMFLOAT3 t1)
	{
		float length = sqrtf(t1.x * t1.x + t1.y * t1.y + t1.z * t1.z);
		if (length == 0.0f) return XMFLOAT3(0.0f, 0.0f, 0.0f);
		return XMFLOAT3(t1.x / length, t1.y / length, t1.z / length);
	}
	// ����
	inline float Length(XMFLOAT3 t1)
	{
		return sqrtf(t1.x * t1.x + t1.y * t1.y + t1.z * t1.z);
	}

	// ��Βl
	inline XMFLOAT3 Abs(XMFLOAT3 t1)
	{
		return XMFLOAT3(fabsf(t1.x), fabsf(t1.y), fabsf(t1.z));
	}
	// ����
	inline float Dot(XMFLOAT3 t1, XMFLOAT3 t2)
	{
		return t1.x * t2.x + t1.y * t2.y + t1.z * t2.z;
	}
	// �O��
	inline XMFLOAT3 Cross(XMFLOAT3 t1, XMFLOAT3 t2)
	{
		return XMFLOAT3(
			t1.y * t2.z - t1.z * t2.y,
			t1.z * t2.x - t1.x * t2.z,
			t1.x * t2.y - t1.y * t2.x
		);
	}

	// ������
	inline bool Equal(XMFLOAT3 t1, XMFLOAT3 t2)
	{
		return t1.x == t2.x && t1.y == t2.y && t1.z == t2.z;
	}
	// ����
	inline float Distance(XMFLOAT3 t1, XMFLOAT3 t2)
	{
		return sqrtf((t1.x - t2.x) * (t1.x - t2.x) + (t1.y - t2.y) * (t1.y - t2.y) + (t1.z - t2.z) * (t1.z - t2.z));
	}
	// ����
	inline XMFLOAT3 Direction(XMFLOAT3 t1, XMFLOAT3 t2)
	{
		XMFLOAT3 dir = Sub(t2, t1);
		return Normalize(dir);
	}


	/*===========================================================
	* XMFLOAT2��XMFLOAT2�̉��Z
	===========================================================*/
	// ���Z
	inline XMFLOAT2 Add(XMFLOAT2 t1, XMFLOAT2 t2)
	{
		return XMFLOAT2(t1.x + t2.x, t1.y + t2.y);
	}
	// ���Z
	inline XMFLOAT2 Sub(XMFLOAT2 t1, XMFLOAT2 t2)
	{
		return XMFLOAT2(t1.x - t2.x, t1.y - t2.y);
	}
	// ��Z
	inline XMFLOAT2 Mul(XMFLOAT2 t1, XMFLOAT2 t2)
	{
		return XMFLOAT2(t1.x * t2.x, t1.y * t2.y);
	}
	// ���Z
	inline XMFLOAT2 Div(XMFLOAT2 t1, XMFLOAT2 t2)
	{
		return XMFLOAT2(t1.x / t2.x, t1.y / t2.y);
	}
	// ������
	inline bool Equal(XMFLOAT2 t1, XMFLOAT2 t2)
	{
		return t1.x == t2.x && t1.y == t2.y;
	}


	/*===========================================================
	* XMFLOAT3��float�̉��Z
	===========================================================*/
	// ���Z
	inline XMFLOAT3 Add(XMFLOAT3 t1, float f)
	{
		return XMFLOAT3(t1.x + f, t1.y + f, t1.z + f);
	}
	// ���Z
	inline XMFLOAT3 Sub(XMFLOAT3 t1, float f)
	{
		return XMFLOAT3(t1.x - f, t1.y - f, t1.z - f);
	}
	// ��Z
	inline XMFLOAT3 Mul(XMFLOAT3 t1, float f)
	{
		return XMFLOAT3(t1.x * f, t1.y * f, t1.z * f);
	}
	// ���Z
	inline XMFLOAT3 Div(XMFLOAT3 t1, float f)
	{
		return XMFLOAT3(t1.x / f, t1.y / f, t1.z / f);
	}

	// �ȉ�
	inline bool LessEqual(XMFLOAT3 t1, float f)
	{
		return t1.x <= f && t1.y <= f && t1.z <= f;
	}
	// �ȏ�
	inline bool MoreEqual(XMFLOAT3 t1, float f)
	{
		return t1.x >= f && t1.y >= f && t1.z >= f;
	}


	/*===========================================================
	* XMFLOAT2��float�̉��Z
	===========================================================*/
	// ���Z
	inline XMFLOAT2 Add(XMFLOAT2 t1, float f)
	{
		return XMFLOAT2(t1.x + f, t1.y + f);
	}
	// ���Z
	inline XMFLOAT2 Sub(XMFLOAT2 t1, float f)
	{
		return XMFLOAT2(t1.x - f, t1.y - f);
	}
	// ��Z
	inline XMFLOAT2 Mul(XMFLOAT2 t1, float f)
	{
		return XMFLOAT2(t1.x * f, t1.y * f);
	}
	// ���Z
	inline XMFLOAT2 Div(XMFLOAT2 t1, float f)
	{
		return XMFLOAT2(t1.x / f, t1.y / f);
	}
	// �ȉ�
	inline bool LessEqual(XMFLOAT2 t1, float f)
	{
		return t1.x <= f && t1.y <= f;
	}
	// �ȏ�
	inline bool MoreEqual(XMFLOAT2 t1, float f)
	{
		return t1.x >= f && t1.y >= f;
	}


	/*===========================================================
	* float��XMFLOAT�̉��Z
	===========================================================*/
	// float��XMFLOAT2�ɕϊ�
	inline XMFLOAT2 FtoF2(float f)
	{
		return XMFLOAT2(f, f);
	}
	// float��XMFLOAT3�ɕϊ�
	inline XMFLOAT3 FtoF3(float f)
	{
		return XMFLOAT3(f, f, f);
	}
	// float��XMFLOAT4�ɕϊ�
	inline XMFLOAT4 FtoF4(float f)
	{
		return XMFLOAT4(f, f, f, f);
	}

	/*===========================================================
	* float�̉��Z(�d�l�̓���)
	===========================================================*/
	// ��Βl
	inline float Abs(float f)
	{
		return fabsf(f);
	}
}