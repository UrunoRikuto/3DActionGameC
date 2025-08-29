/*=====================================================================
* @file Ray.h
* @brief ���C�̃w�b�_�[�t�@�C��
=====================================================================*/
#pragma once

/* �V�X�e���E�v�f�̃C���N���[�h */
#include "StructMath.h"
#include "Collision.h"


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
	/// <param name="In_TargetInfos">�^�[�Q�b�g�R���W����</param>
	/// <returns>���C���������Ă��邩�ǂ���</returns>
	bool Cast(std::vector<Collision::Info> In_TargetInfos);

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

public:
	/// <summary>
	/// ���C�̎n�_�̎擾
	/// </summary>
	/// <returns>���C�̎n�_</returns>
	const XMFLOAT3& GetOrigin() const { return m_tOrigin; }
	/// <summary>
	/// ���C�̕����̎擾
	/// </summary>
	/// <returns>���C�̕���</returns>
	const XMFLOAT3& GetDirection() const { return m_tDirection; }
	/// <summary>
	/// ���C�̕����̐ݒ�
	/// </summary>
	/// <param name="direction">�V�����ݒ肷�����</param>
	void SetDirection(const XMFLOAT3& direction) { m_tDirection = direction; }
};
