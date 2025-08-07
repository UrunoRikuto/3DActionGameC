/*
* @file Player.h
* @brief �v���C���[�N���X�̃w�b�_�[�t�@�C��
* @author �F���엤�l
* @date 2025/08/04 �N���X�̒�`
*                  �ړ������̒�`
*                  ���_�ړ������̒�`
*            08/05 �W�����v�����̒�`
*            08/07 �v���C���[�̍s�����[�h�̒�`
*/
#pragma once

/* �V�X�e���E�v�f�̃C���N���[�h */
#include "Enums.h"

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

	/// <summary>
	/// �v���C���[�̐^���̒n�ʂ̍�����ݒ肷��֐�
	/// </summary>
	/// <param name="height">�ݒ肷��I�u�W�F�N�g��Y��</param>
	void SetUnderHeight(float height) { m_fUnderHeight = height + (m_tScale.y / 2.0f); }

private:
	/// <summary>
	/// �s�����[�h�̐؂�ւ�
	/// </summary>
	void ChangeActionMode(void);

	/// <summary>
	/// �ړ��A�N�V�����̍X�V����
	/// </summary>
	void MA_Update(void);

	/// <summary>
	///  �ړ��A�N�V�����̈ړ�����
	/// </summary>
	void MA_Move(void);

	/// <summary>
	///  �ړ��A�N�V�����̒��􏈗�
	/// </summary>
	void MA_Jump(void);

	/// <summary>
	///  �ړ��A�N�V�����̎��_�ړ�
	/// </summary>
	void MA_LookRotation(void);


	/// <summary>
	/// �_�����[�h�̍X�V����
	/// </summary>
	void SA_Update(void);

	/// <summary>
	/// �_�����[�h�̎��_�ړ�
	/// </summary>
	/// <param name=""></param>
	void SA_LookRotation(void);

private:
	/// <summary>
	/// �v���C���[�̍s�����[�h
	/// </summary>
	PlayerActionMode m_eActionMode;

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

	/// <summary>
	/// �^���̍�����ۑ�����ϐ�
	/// </summary>
	float m_fUnderHeight;
};

