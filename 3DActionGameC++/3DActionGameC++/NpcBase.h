/*
* @file NpcBase.h
* @brief NPC�̊��N���X�̃w�b�_�[�t�@�C��
* @author �F���엤�l
* @date 2025/08/04 NPC�̊��N���X�̒�`
*/

#pragma once

/* ���N���X�̃C���N���[�h */
#include "GameObject.h"

/* �V�X�e���E�v�f�̃C���N���[�h */
#include "MoveSystem.h"
#include "VisionSearch.h"

/// <summary>
/// NPC�̊��N���X
/// </summary>
class CNpcBase : public CGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CNpcBase(NpcType InType);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~CNpcBase();
	/// <summary>
	/// �X�V����
	/// </summary>
	virtual void Update(void);

	/// <summary>
	/// �`�揈��
	/// </summary>
	virtual void Draw(void);

	/// <summary>
	/// �����蔻��̏Փˎ��̏���
	/// </summary>
	/// <param name="InCollisionInfo">�ՓˑΏ�</param>
	void Hit(const Collision::Info& InCollisionInfo) override;

protected:

	/// <summary>
	/// NCP�̎��
	/// </summary>
	NpcType m_eNpcType;

	/// <summary>
	/// ���݂̍��G���
	/// </summary>
	VisionSearchState m_eSearchState;

	/// <summary>
	/// ���o���G�V�X�e��
	/// </summary>
	std::unique_ptr<CVisionSearch> m_pVisionSearch;

	/// <summary>
	/// �ړ��V�X�e��
	/// </summary>
	std::unique_ptr<CMoveSystem> m_pMoveSystem;

public:
	/// <summary>
	/// NPC�̎�ނ̎擾
	/// </summary>
	/// <returns> NCP�̎��</returns>
	NpcType GetNpcType(void) const { return m_eNpcType; }

	/// <summary>
	/// ���݂̍��G��Ԃ̎擾
	/// </summary>
	/// <returns>���݂̍��G���</returns>
	VisionSearchState GetSearchState(void) const { return m_eSearchState; }

	/// <summary>
	/// ���o���G�V�X�e���̎擾
	/// </summary>
	/// <returns>���o���G�V�X�e���̃|�C���^</returns>
	CVisionSearch* GetVisionSearch(void) { return m_pVisionSearch.get(); }

	/// <summary>
	/// �ړ��V�X�e���̎擾
	/// </summary>
	/// <returns>�ړ��V�X�e���̃|�C���^</returns>
	CMoveSystem* GetMoveSystem(void) { return m_pMoveSystem.get(); }
};
