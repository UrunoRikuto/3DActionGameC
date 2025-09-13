/*=====================================================================
* @file FieldObject.h
* @brief �t�B�[���h�I�u�W�F�N�g�̃w�b�_�[�t�@�C��
=====================================================================*/

#pragma once
#include "GameObject.h"
#include "Enums.h"

/// <summary>
/// �t�B�[���h�I�u�W�F�N�g�̃N���X
/// </summary>
class CFieldObject : public CGameObject
{
public:
	// �R���X�g���N�^
	CFieldObject(FieldObjectType In_Type);
	// �f�X�g���N�^
	virtual ~CFieldObject();
	// �X�V����
	void Update(void) override;
	// �����蔻��̏Փˎ��̏���
	void Hit(const Collision::Info& InCollisionInfo) override;
};

