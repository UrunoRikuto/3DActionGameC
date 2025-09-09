/*=====================================================================
* @file NpcBase.cpp
* @brief NPC�̊��N���X��Cpp�t�@�C��
=====================================================================*/

/* �w�b�_�[�̃C���N���[�h */
#include "NpcBase.h"
/* �V�X�e���E�v�f�̃C���N���[�h */
#include "Model.h"

// @brief �R���X�g���N�^
// @param InType NPC�̎��
CNpcBase::CNpcBase(NpcType InType)
	:CGameObject() // ���N���X�̃R���X�g���N�^���Ăяo��
	, m_eNpcType(InType) // NPC�̎�ނ�ݒ�
	, m_eSearchState(VisionSearchState::None) // ���G��Ԃ�������
	, m_fAttackCD(0.0f) // �U���̃N�[���^�C����������
	, m_bAttack(false) // �U�������ǂ����̏�����
	, m_pHpGauge(nullptr) // �̗̓Q�[�W�̏�����
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
	SetSearchState(m_pVisionSearch->Search(m_tPosition, m_eSearchState));

	// Hp�Q�[�W�̍X�V
	if (m_pHpGauge)m_pHpGauge->Updatde(m_tPosition, m_fHp);
}

// @brief �`�揈��
void CNpcBase::Draw(void)
{
	// �j���t���O�������Ă���ꍇ�͍X�V���s��Ȃ�
	if (m_bDestroy)return;

	// �̗̓Q�[�W�̕`��
	m_pHpGauge->Draw();
	
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

// @brief �����蔻��̏Փˎ��̏���(�U���p)
// @param InCollisionInfo �ՓˑΏ�
// @param In_Attack ����̍U����
void CNpcBase::Hit(const Collision::Info& InCollisionInfo, float In_Attack)
{
	int IsPlayerAttackCheck = 0;

	// �v���C���[�̍U���ɓ����������ǂ����𔻒�
	// �v���C���[�^�O�ƍU���^�O�̗���������΃v���C���[�̍U���ɓ��������Ɣ���
	for (auto& tag : InCollisionInfo.tag)
	{
		switch (tag)
		{
		case Collision::Tag::Player:
			IsPlayerAttackCheck++;
			break;
		case Collision::Tag::Attack:
			IsPlayerAttackCheck++;
			break;
		}
	}

	// �v���C���[�̍U���ɓ��������ꍇ
	if (IsPlayerAttackCheck >= 2)
	{
		// �̗͂����炷
		m_fHp -= In_Attack;
		// �̗͂�0�ȉ��ɂȂ�����j���t���O�𗧂Ă�
		if (m_fHp <= 0.0f)
		{
			m_bDestroy = true;
			m_fHp = 0.0f;
		}
	}
}

// @brief ���݂̍��G��Ԃ̐ݒ�
// @param InState �ݒ肷����G���
void CNpcBase::SetSearchState(VisionSearchState InState)
{
	/// @Todo ���G��Ԃɉ�����������ǉ�����
	/// ��: None�����Ԃ��ω������ꍇ��MoveSystem�̈ړ��|�C���g�����ۑ����Ă����Ȃ�
	/// (����None�ɖ߂����Ƃ��ɓ������[�g������悤��)

	// ��Ԃ��ω����Ă��Ȃ��ꍇ�͉������Ȃ�
	if (m_eSearchState == InState)return;

	// ���݂̏�Ԃɂ�鏈��
	switch (m_eSearchState)
	{
	case VisionSearchState::None:
		/// �ړ����[�g��ۑ����ăN���A
		m_pMoveSystem->SaveAndClearMovePoints();
		break;
	case VisionSearchState::Doubt:
		/// �ړ����[�g���N���A
		m_pMoveSystem->ClearMovePoints();
		break;
	case VisionSearchState::Lost:
		break;
	case VisionSearchState::Discovery:
		break;
	}

	// ��Ԃ̍X�V
	m_eSearchState = InState;

	// �V������Ԃɂ�鏈��
	switch (InState)
	{
	case VisionSearchState::None:
		/// �ړ����[�g�𕜌�
		m_pMoveSystem->RestorationMovePoints(m_tPosition);
		break;
	case VisionSearchState::Doubt:
		/// �v���C���[�̈ʒu�܂ł̈ړ����[�g��ݒ�
		m_pMoveSystem->SetMovePoints(CMovePointManager::GetInstance()->CreateMoveRoute(m_tPosition, m_pTargetObject->GetPosition()), m_tPosition);
		m_pMoveSystem->SetMoveSystemType(MoveSystemType::Once);
		break;
	case VisionSearchState::Lost:
		break;
	case VisionSearchState::Discovery:
		break;
	}
}
