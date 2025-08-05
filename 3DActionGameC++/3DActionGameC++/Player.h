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
	/// ���􏈗�
	/// </summary>
	void Jump(void);

	/// <summary>
	/// ���_�ړ�
	/// </summary>
	void LookRotation(void);

private:
	/// <summary>
	/// �v���C���[�̈ړ���
	/// </summary>
	XMFLOAT3 m_tMovePower;

	/// <summary>
	/// �n�ʂɗ����Ă��邩�̃t���O
	/// </summary>
	bool m_bGround;

	/// <summary>
	/// �W�����v�����ǂ����̃t���O
	/// </summary>
	bool m_bJumping;

	/// <summary>
	/// �W�����v�̌��݃t���[����
	/// </summary>
	int m_nJumpFrame;
};

