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
	, m_bGround(true) // �n�ʂɗ����Ă��邩�̃t���O��������
	, m_fUnderHeight(0.0f) // �^���̍�����ۑ�����ϐ���������
{
	// ���f���̍쐬
	m_pModel = std::make_unique<Model>();
	// ���o���G�̍쐬
	m_pVisionSearch = std::make_unique<CVisionSearch>(this);

	// ���C�̍쐬
	m_pRay = std::make_unique<CRay>();
	m_pRay->SetParam(m_tPosition, XMFLOAT3(0.0f, -1.0f, 0.0f)); // ���C�̎n�_�ƕ�����ݒ�
}

// @brief �f�X�g���N�^
CNpcBase::~CNpcBase()
{
}

// @brief �ŏ��̕��ɍs�����ʍX�V����
void CNpcBase::BiginUpdate(void)
{
	// �j���t���O�������Ă���ꍇ�͍X�V���s��Ȃ�
	if (m_bDestroy)return;

	// ���G�V�X�e���̍X�V(���G)
	SetSearchState(m_pVisionSearch->Search(m_tPosition, m_eSearchState));

}

// @brief �Ō�̕��ɍs�����ʍX�V����
void CNpcBase::EndUpdate(void)
{
	// �n�ʔ���
	GroundCheck();

	// Hp�Q�[�W�̍X�V
	if (m_pHpGauge)m_pHpGauge->Updatde(m_tPosition, m_fHp);
	// ���C�̍X�V
	m_pRay->SetOrigin(m_tPosition); // ���C�̈ʒu���X�V
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

		// ���G��Ԃ𔭌���Ԃɂ���
		SetSearchState(VisionSearchState::Discovery);

		// �̗͂�0�ȉ��ɂȂ�����j���t���O�𗧂Ă�
		if (m_fHp <= 0.0f)
		{
			m_bDestroy = true;
			m_fHp = 0.0f;
		}
	}
}

// @brief �n�ʔ��菈��
void CNpcBase::GroundCheck(void)
{
	// �n�ʂɂ���ꍇ�͍�����0�ɂ���
	if (m_bGround)
	{
		m_tPosition.y = m_fUnderHeight + m_fAjustPositionY;
	}
	else
	{
		if (m_tPosition.y >= m_fUnderHeight + m_fAjustPositionY)
		{
			m_tPosition.y -= GRAVITY; // �d�͂�K�p
			if (m_tPosition.y < m_fUnderHeight + m_fAjustPositionY)
			{
				m_tPosition.y = m_fUnderHeight + m_fAjustPositionY; // �n�ʂ̍����ɍ��킹��
				m_bGround = true; // �n�ʂɂ����Ԃɂ���
			}
		}
		else if (m_tPosition.y < m_fUnderHeight + m_fAjustPositionY)
		{
			m_tPosition.y += 0.2f; // �n�ʂ̍����ɍ��킹��
			if (m_tPosition.y > m_fUnderHeight + m_fAjustPositionY)
			{
				m_tPosition.y = m_fUnderHeight + m_fAjustPositionY; // �n�ʂ̍����ɍ��킹��
				m_bGround = true; // �n�ʂɂ����Ԃɂ���
			}
		}
	}
}

// @brief ���݂̍��G��Ԃ̐ݒ�
// @param InState �ݒ肷����G���
void CNpcBase::SetSearchState(VisionSearchState InState)
{
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

// @brief �v���C���[�̐^���̒n�ʂ̍�����ݒ肷��
// @param height �v���C���[�̐^���̒n�ʂ̍���
void CNpcBase::SetUnderHeight(float height)
{
	if (m_fUnderHeight - m_fAjustPositionY != height)
	{
		m_fUnderHeight = height + m_fAjustPositionY;
		m_bGround = false;
	}
}
