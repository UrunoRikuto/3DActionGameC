/*
* @file NpcBase.cpp
* @brief NPC�̊��N���X��Cpp�t�@�C��
* @author �F���엤�l
* @date 2025/08/04 NPC�̊��N���X�̎���
*/

/* �w�b�_�[�̃C���N���[�h */
#include "NpcBase.h"
/* �V�X�e���E�v�f�̃C���N���[�h */

/// <summary>
/// �`�揈��
/// </summary>
void CNpcBase::Draw(void)
{
	// �ړ��V�X�e���̃f�o�b�O�`��
	m_pMoveSystem->DebugDraw(XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));

	// ���N���X�̕`��
	CGameObject::Draw();
}

// @brief �����蔻��̏Փˎ��̏���
// @param InCollisionInfo �ՓˑΏ�
void CNpcBase::Hit(const Collision::Info& InCollisionInfo)
{
	// ���͉������Ȃ�
}
