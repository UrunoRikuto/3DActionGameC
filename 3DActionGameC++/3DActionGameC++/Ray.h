/*
* @file Ray.h
* @brief ���C�̃N���X�̃w�b�_�[�t�@�C��
* @author �F���엤�l
* @date 2025/08/04 ���C�L���X�g�̃N���X�̒�`
*/
#pragma once

/* �V�X�e���E�v�f�̃C���N���[�h */
#include "StructMath.h"
#include "RayCastTarget.h"


/// <summary>
/// ���C(����)�N���X
/// </summary>
class CRay
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CRay();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CRay();

	/// <summary>
	/// ���C�L���X�g�̎��s
	/// </summary>
	/// <param name="InTarget">�^�[�Q�b�g�I�u�W�F�N�g</param>
	/// <returns>���C���������Ă��邩�ǂ���</returns>
	bool Cast(CRayCastTarget* InTarget);

	/// <summary>
	/// �p�����[�^�[�̐ݒ�
	/// </summary>
	/// <param name="origin">���C�̎n�_</param>
	/// <param name="direction">���C�̕���</param>
	void SetParam(const XMFLOAT3& origin, const XMFLOAT3& direction);

	/// <summary>
	/// ���C�̎n�_�̐ݒ�
	/// </summary>
	/// <param name="origin"></param>
	void SetOrigin(const XMFLOAT3& origin) { m_tOrigin = origin; }
private:
	/// <summary>
	/// ���C�̎n�_
	/// </summary>
	XMFLOAT3 m_tOrigin;
	/// <summary>
	/// ���C�̕���
	/// </summary>
	XMFLOAT3 m_tDirection;
};
