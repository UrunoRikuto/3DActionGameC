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
CNpcBase::CNpcBase(NpcType InType)
	:CGameObject() // ���N���X�̃R���X�g���N�^���Ăяo��
	,m_eNpcType(InType) // NPC�̎�ނ�ݒ�
	, m_eSearchState(VisionSearchState::None) // ���G��Ԃ�������
{
	// ���f���̍쐬
	m_pModel = std::make_unique<Model>();

	// ���o���G�̍쐬
	m_pVisionSearch = std::make_unique<CVisionSearch>(this);
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

	// ���G�V�X�e���̍X�V(���G)
	m_eSearchState = m_pVisionSearch->Search(m_tPosition, m_eSearchState);

	// �ړ�
	XMFLOAT3 movePoint = m_pMoveSystem->GetMovePoint(m_tPosition);
	XMFLOAT3 moveDir = Direction(m_tPosition, movePoint);
	SetPosition(Add(m_tPosition, Mul(moveDir, m_pMoveSystem->GetMoveSpeed())));
	// �����̍X�V
	m_tRotation.y = TODEG(atan2f(-moveDir.z, moveDir.x));

	// ���G��Ԃɂ�鏈��
	switch (m_eSearchState)
	{
	case VisionSearchState::None:
		break;
	case VisionSearchState::Doubt:
		break;
	case VisionSearchState::Lost:
		break;
	case VisionSearchState::Discovery:
		break;
	}
}

// @brief �`�揈��
void CNpcBase::Draw(void)
{
	// �j���t���O�������Ă���ꍇ�͍X�V���s��Ȃ�
	if (m_bDestroy)return;
	
	// �ړ��V�X�e���̃f�o�b�O�`��
	m_pMoveSystem->DebugDraw(XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
	// ���G�V�X�e���̃f�o�b�O�`��
	m_pVisionSearch->DebugDraw();

	// ���N���X�̕`��
	CGameObject::Draw();
}

// @brief �����蔻��̏Փˎ��̏���
// @param InCollisionInfo �ՓˑΏ�
void CNpcBase::Hit(const Collision::Info& InCollisionInfo)
{
	// ���͉������Ȃ�
}
