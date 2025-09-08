/*=====================================================================
* @file GuardNpc.cpp
* @brief ��qNPC�̃N���X�̎����t�@�C��
=====================================================================*/

/* �w�b�_�[�̃C���N���[�h */
#include "GuardNpc.h"
/* �V�X�e���E�v�f�̃C���N���[�h */
#include "Model.h"
#include "Defines.h"
#include "GameValues.h"

// @brief�R���X�g���N�^
// @param FirstMovePoint �ŏ��̈ړ��|�C���g
// @param NpcType NPC�̎��
CGuardNpc::CGuardNpc(XMFLOAT3 FirstMovePoint, NpcType NpcType)
	:CNpcBase(NpcType) // ���N���X�̃R���X�g���N�^���Ăяo��
{
	// ���f���̓ǂݍ���
	if (!m_pModel->Load(ModelPath::GUARD_NPC_PATH))
	{
		MessageBox(NULL, "�^�[�Q�b�gNPC���f���̓ǂݍ��݂Ɏ��s���܂����B", "Error", MB_OK);
	}

	// �傫���̐ݒ�
	m_tScale = { 2.0f,2.0f,2.0f };

	// �ړ��V�X�e���̏�����
	m_pMoveSystem = std::make_unique<CMoveSystem>(MoveSystemType::Loop, 0.1f);
	// Y���W�̒����l��ݒ�
	m_pMoveSystem->SetAdjustY(m_tScale.y / 2.0f); // NPC�̍����̔����𒲐��l�ɐݒ�
	// �ړ��|�C���g�̒ǉ�
	m_pMoveSystem->AddMovePoint(FirstMovePoint);

	// �ʒu
	m_tPosition = m_pMoveSystem->GetMovePointList()[0];
	// ��]
	m_tRotation = { 0.0f, 0.0f, 0.0f };

	// �����蔻��̐ݒ�
	// �����蔻����̃T�C�Y��3�ɐݒ�
	m_tCollisionInfos.resize(3);
	//--- ���̓����蔻����̏�����
	// �����蔻��̎�ނ�ݒ�
	m_tCollisionInfos[0].type = Collision::eBox;
	// �^�O��ǉ�
	m_tCollisionInfos[0].tag.push_back(Collision::Tag::TargetNpc);
	m_tCollisionInfos[0].tag.push_back(Collision::Tag::Head);
	// ���S�ʒu��ݒ�
	m_tCollisionInfos[0].box.center = StructMath::Add(m_tPosition, XMFLOAT3(0.0f, m_tScale.y, 0.0f));
	m_tCollisionInfos[0].AdjustCenter = XMFLOAT3(0.0f, m_tScale.y, 0.0f); // ���S�ʒu�̒���
	// �{�b�N�X�̑傫����ݒ�
	m_tCollisionInfos[0].box.size = m_tScale;
	//--- �̂̓����蔻����̏�����
	// �����蔻��̎�ނ�ݒ�
	m_tCollisionInfos[1].type = Collision::eBox;
	// �^�O��ǉ�
	m_tCollisionInfos[1].tag.push_back(Collision::Tag::TargetNpc);
	m_tCollisionInfos[1].tag.push_back(Collision::Tag::Body);
	// ���S�ʒu��ݒ�
	m_tCollisionInfos[1].box.center = m_tPosition;
	// �{�b�N�X�̑傫����ݒ�
	m_tCollisionInfos[1].box.size = m_tScale;
	//--- ���̓����蔻����̏�����
	// �����蔻��̎�ނ�ݒ�
	m_tCollisionInfos[2].type = Collision::eBox;
	// �^�O��ǉ�
	m_tCollisionInfos[2].tag.push_back(Collision::Tag::TargetNpc);
	// �^�O��ǉ�
	m_tCollisionInfos[2].tag.push_back(Collision::Tag::Foot);
	// ���S�ʒu��ݒ�
	m_tCollisionInfos[2].box.center = StructMath::Sub(m_tPosition, XMFLOAT3(0.0f, m_tScale.y, 0.0f));
	m_tCollisionInfos[2].AdjustCenter = XMFLOAT3(0.0f, -m_tScale.y, 0.0f); // ���S�ʒu�̒���
	// �{�b�N�X�̑傫����ݒ�
	m_tCollisionInfos[2].box.size = m_tScale;

	// ����̐���
	m_pWeapon = new CSword();

}

// @brief�f�X�g���N�^
CGuardNpc::~CGuardNpc()
{

}

// @brief �X�V����
void CGuardNpc::Update(void)
{
	// �j���t���O�������Ă���ꍇ�͍X�V���s��Ȃ�
	if (m_bDestroy)return;

	// ���N���X�̍X�V����(NPC���ʏ���)
	CNpcBase::Update();

	// �ړ�
	Move();

	// �U��
	Attack();
}

// @brief �ړ�����
void CGuardNpc::Move(void)
{

	// ���O��Ԃ̎g�p
	using namespace StructMath;

	XMFLOAT3 movePoint = XMFLOAT3();

	switch (m_eSearchState)
	{
	case VisionSearchState::None:
	case VisionSearchState::Doubt:
	case VisionSearchState::Lost:
		movePoint = m_pMoveSystem->GetMovePoint(m_tPosition);
		break;
	case VisionSearchState::Discovery:
		movePoint = m_pTargetObject->GetPosition();
		break;
	}

	XMFLOAT3 moveDir = Direction(m_tPosition, movePoint);

	// �U�����łȂ��ꍇ�͈ړ��ʂ�K�p
	if (!m_bAttack)SetPosition(Add(m_tPosition, Mul(moveDir, m_pMoveSystem->GetMoveSpeed())));
	// �����̍X�V
	m_tRotation.y = TODEG(atan2f(-moveDir.z, moveDir.x));
}

// @brief �U������
void CGuardNpc::Attack(void)
{
	// ���O��Ԃ̎g�p�錾
	using namespace StructMath;

	// �N�[���^�C�����c���Ă���ꍇ�̓N�[���^�C�������炷
	if (m_fAttackCD > 0.0f)
	{
		m_fAttackCD -= 1.0f / fFPS;
		if (m_fAttackCD < 0.0f)m_fAttackCD = 0.0f;
	}
	else
	{
		// ���G��Ԃ������ȊO�Ȃ牽�����Ȃ�
		if (m_eSearchState != VisionSearchState::Discovery)return;

		// �v���C���[���U���͈͓��ɂ��邩�ǂ����𔻒�
		// �v���C���[�̈ʒu���擾
		XMFLOAT3 playerPos = m_pTargetObject->GetPosition();
		// �U���͈͊O�Ȃ牽�����Ȃ�
		XMFLOAT3 weaponCollisionSize = m_pWeapon->GetAttackRange().box.size;

		if (StructMath::Abs(StructMath::Sub(playerPos, m_tPosition)).x > weaponCollisionSize.x * 2 ||
			StructMath::Abs(StructMath::Sub(playerPos, m_tPosition)).z > weaponCollisionSize.z * 2)
		{
			m_bAttack = false;
			return;
		}

		// ���킪����΍U��
		if (m_pWeapon == nullptr)return;
		// ����̍X�V����
		// �������Q�Ƃ��đO�ɏo��
		XMFLOAT3 attackDir = StructMath::Direction(m_tPosition, playerPos);

		m_pWeapon->Update(Add(m_tPosition, Mul(attackDir, m_pWeapon->GetAttackRange().box.size.x)));

		// �V�[���̎擾
		auto scene = (CSceneGame*)GetCurrentScene();

		// �V�[�����Ȃ��ꍇ�͉������Ȃ�
		if (scene == nullptr)return;

		// �U���𐶐�
		scene->AttackCreate({ m_pWeapon->GetAttackRange(), m_pWeapon->GetAttackDurationFrame() });

		// �N�[���^�C����ݒ�
		m_fAttackCD = m_pWeapon->GetAttackSpeed();

		// �U�����t���O�𗧂Ă�
		m_bAttack = true;
	}
}
