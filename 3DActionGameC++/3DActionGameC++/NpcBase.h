/*
* @file NpcBase.h
* @brief NPC�̊��N���X�̃w�b�_�[�t�@�C��
* @author �F���엤�l
* @date 2025/08/04 NPC�̊��N���X�̒�`
*/

#pragma once

/* ���N���X�̃C���N���[�h */
#include "GameObject.h"

/// <summary>
/// NPC�̊��N���X
/// </summary>
class CNpcBase : public CGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CNpcBase() = default;
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~CNpcBase() = default;
	/// <summary>
	/// �X�V����
	/// </summary>
	virtual void Update(void) = 0;
};
