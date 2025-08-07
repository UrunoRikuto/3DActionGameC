/*
* @file TargetNpc.h
* @brief �^�[�Q�b�gNPC�̃N���X�̃w�b�_�[�t�@�C��
* @author �F���엤�l
* * @date 2025/08/04 �^�[�Q�b�gNPC�̃N���X�̒�`
*/

#pragma once

/* ���N���X�̃C���N���[�h */
#include "NpcBase.h"

/// <summary>
/// �^�[�Q�b�gNPC�̃N���X
/// </summary>
class CTargetNpc : public CNpcBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CTargetNpc();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~CTargetNpc();
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update(void) override;
};

