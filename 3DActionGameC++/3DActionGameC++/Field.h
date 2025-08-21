/*
* @file Field.h
* @brief �t�B�[���h�I�u�W�F�N�g�̃N���X�̃w�b�_�[�t�@�C��
* @author �F���엤�l
* @date 2025/08/04 �N���X�̍쐬
*/
#pragma once

/* ���N���X�̃C���N���[�h */
#include "GameObject.h"

/// <summary>
/// �t�B�[���h�I�u�W�F�N�g�̃N���X
/// </summary>
class CField : public CGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CField();
	
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CField();
	
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update(void) override;

	/// <summary>
	/// �����蔻��̏Փˎ��̏���
	/// </summary>
	/// <param name="InCollisionInfo">�ՓˑΏ�</param>
	void Hit(const Collision::Info& InCollisionInfo) override;

};
