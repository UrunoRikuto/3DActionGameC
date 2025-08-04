/*
* @file Player.h
* @brief �v���C���[�N���X�̃w�b�_�[�t�@�C��
* @author �F���엤�l
* @date 2025/08/04 �N���X�̒�`
*/
#pragma once

/* ���N���X�̃C���N���[�h */
#include "GameObject.h"

/// <summary>
/// �v���C���[�̃N���X
/// </summary>
class CPlayer : public CGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CPlayer();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~CPlayer();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update(void) override;

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw(void) override;

private:
	/// <summary>
	/// �ړ�����
	/// </summary>
	void Move(void);

	/// <summary>
	/// ���_�ړ�
	/// </summary>
	void LookRotation(void);

private:
	/// <summary>
	/// �v���C���[�̈ړ���
	/// </summary>
	XMFLOAT3 m_tMovePower;
};

