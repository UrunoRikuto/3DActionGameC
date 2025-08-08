/*
* @file RayCastTarget.h
* @brief ���C�L���X�g�̃^�[�Q�b�g�N���X�̃w�b�_�[�t�@�C��
* @author �F���엤�l
* @date 2025/08/04 ���C�L���X�g�̃^�[�Q�b�g�N���X�̒�`
*/
#pragma once

/* �V�X�e���E�v�f�̃C���N���[�h */
#include "StructMath.h"

/// <summary>
/// ���C�L���X�g�̃^�[�Q�b�g�N���X
/// </summary>
class CRayCastTarget
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CRayCastTarget();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CRayCastTarget();

	/// <summary>
	/// �p�����[�^�[�̐ݒ�
	/// </summary>
	void SetParam(const XMFLOAT3& position, const XMFLOAT3& scale);
private:

	/// <summary>
	/// �^�[�Q�b�g�̈ʒu
	/// </summary>
	XMFLOAT3 m_tPosition;

	/// <summary>
	/// �^�[�Q�b�g�̃X�P�[��
	/// </summary>
	XMFLOAT3 m_tScale;

public: //�����o�ϐ��̃A�N�Z�T
	/// <summary>
	/// �^�[�Q�b�g�̈ʒu�̐ݒ�
	/// </summary>
	/// <param name="position"></param>
	void SetPosition(const XMFLOAT3& position) { m_tPosition = position; }
	/// <summary>
	/// �^�[�Q�b�g�̈ʒu�̎擾
	/// </summary>
	/// <returns>�^�[�Q�b�g�̈ʒu</returns>
	const XMFLOAT3& GetPosition() const { return m_tPosition; }

	/// <summary>
	/// �^�[�Q�b�g�̃X�P�[���̐ݒ�
	/// </summary>
	/// <param name="scale">�X�P�[�����</param>
	void SetScale(const XMFLOAT3& scale) { m_tScale = scale; }

	/// <summary>
	/// �^�[�Q�b�g�̃X�P�[���̎擾
	/// </summary>
	/// <returns>�^�[�Q�b�g�̃X�P�[��</returns>
	const XMFLOAT3& GetScale() const { return m_tScale; }
};

