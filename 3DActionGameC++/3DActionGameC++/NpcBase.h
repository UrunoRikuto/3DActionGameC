/*=====================================================================
* @file NpcBase.h
* @brief NPC�̊��N���X�̃w�b�_�[�t�@�C��
=====================================================================*/

#pragma once

/* ���N���X�̃C���N���[�h */
#include "GameObject.h"

/* �V�X�e���E�v�f�̃C���N���[�h */
#include "MoveSystem.h"
#include "VisionSearch.h"
#include "Player.h"
#include "WeaponInclude.h"


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
	/// �ړ�����
	/// </summary>
	virtual void Move(void) = 0;

	/// <summary>
	/// �U������
	/// </summary>
	virtual void Attack(void) = 0;

protected:

	/// <summary>
	/// �������Ă��镐��
	/// </summary>
	CWeapon* m_pWeapon;

	/// <summary>
	/// �U���̃N�[���^�C��
	/// </summary>
	float m_fAttackCD;

	/// <summary>
	/// �U�������ǂ���
	/// </summary>
	bool m_bAttack;

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

	/// <summary>
	/// �W�I�Ώۂ̃Q�[���I�u�W�F�N�g
	/// </summary>
	CPlayer* m_pTargetObject;

public:

	/// <summary>
	/// �������Ă��镐��̎擾
	/// </summary>
	/// <returns>�������Ă��镐��</returns>
	CWeapon* GetWeapon(void) const { return m_pWeapon; }

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
	/// ���݂̍��G��Ԃ̐ݒ�
	/// </summary>
	/// <param name="InState"></param>
	void SetSearchState(VisionSearchState InState);

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

	/// <summary>
	/// �^�[�Q�b�g�̐ݒ�
	/// </summary>
	/// <param name="In_TargetObject">���G�Ώۂ̃I�u�W�F�N�g</param>
	void SetTarget(CPlayer* In_TargetObject) { m_pTargetObject = In_TargetObject; }

	/// <summary>
	/// �^�[�Q�b�g�̎擾
	/// </summary>
	/// <returns>�^�[�Q�b�g�̃|�C���^</returns>
	CPlayer* GetTarget(void) { return m_pTargetObject; }
};
