/*
* @file NpcBase.cpp
* @brief NPC�̊��N���X��Cpp�t�@�C��
* @author �F���엤�l
* @date 2025/08/04 NPC�̊��N���X�̎���
*/

/* �w�b�_�[�̃C���N���[�h */
#include "NpcBase.h"
/* �V�X�e���E�v�f�̃C���N���[�h */
#include "Model.h"

// @brief �R���X�g���N�^
CNpcBase::CNpcBase()
{
	// ���f���̍쐬
	m_pModel = std::make_unique<Model>();
}

// @brief �f�X�g���N�^
CNpcBase::~CNpcBase()
{
}

// @brief �X�V����
void CNpcBase::Update(void)
{
	// �j���t���O�������Ă���ꍇ�͍X�V���s��Ȃ�
	if (m_bDestroy)return;
	
	using namespace StructMath;

	// �ړ�
	XMFLOAT3 movePoint = m_pMoveSystem->GetMovePoint(m_tPosition);
	SetPosition(Add(m_tPosition, Mul(Direction(m_tPosition, movePoint), m_pMoveSystem->GetMoveSpeed())));
}

// @brief �`�揈��
void CNpcBase::Draw(void)
{
	// �j���t���O�������Ă���ꍇ�͍X�V���s��Ȃ�
	if (m_bDestroy)return;
	
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
