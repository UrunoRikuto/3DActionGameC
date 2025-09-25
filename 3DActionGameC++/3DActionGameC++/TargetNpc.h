/*=====================================================================
* @file TargetNpc.h
* @brief �^�[�Q�b�gNPC�̃N���X�̃w�b�_�[�t�@�C��
=====================================================================*/

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
	/// <param name="FirstMovePoint">�ŏ��̈ړ��|�C���g</param>
	/// <param name="NpcType">NPC�̎��</param>
	CTargetNpc(XMFLOAT3 FirstMovePoint, NpcType NpcType);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~CTargetNpc();
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update(void) override;

	/// <summary>
	/// �����蔻��̏Փˎ��̏���(�U���p)
	/// </summary>
	/// <param name="InCollisionInfo">�ՓˑΏ�</param>
	/// <param name="In_Attack">����̍U����</param>
	void Hit(const Collision::Info& InCollisionInfo, float In_Attack) override;

private:

	/// <summary>
	/// �������̍X�V����
	/// </summary>
	void DiscoveryUpdate(void) override;

	/// <summary>
	/// �ړ�����
	/// </summary>
	void Move(void) override;
	/// <summary>
	/// �U������
	/// </summary>
	void Attack(void) override;
};

