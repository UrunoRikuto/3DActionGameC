/*=====================================================================
* @file TargetNpc.cpp
* @brief �^�[�Q�b�gNPC�̃N���X��Cpp�t�@�C��
=====================================================================*/

/* �w�b�_�[�̃C���N���[�h */
#include "TargetNpc.h"
/* �V�X�e���E�v�f�̃C���N���[�h */
#include "Model.h"
#include "Defines.h"
#include "GameValues.h"
#include "MoveSystem.h"

#undef max

// @brief �R���X�g���N�^
// @param FirstMovePoint �ŏ��̈ړ��|�C���g
// @param NpcType NPC�̎��
CTargetNpc::CTargetNpc(XMFLOAT3 FirstMovePoint, NpcType NpcType)
	: CNpcBase(NpcType) // ���N���X�̃R���X�g���N�^���Ăяo��
{
	// ���O��Ԃ̎g�p
	using namespace StructMath;

	// ���f���̓ǂݍ���
	if (!m_pModel->Load(ModelPath::TARGET_NPC_PATH))
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

	// �␳����
	m_fAjustPositionY = (m_tScale.y * 2) / 2.0f;
	// �ʒu
	m_tPosition = Add(m_pMoveSystem->GetMovePointList()[0], XMFLOAT3(0.0f, m_fAjustPositionY, 0.0f));
	// ��]
	m_tRotation = { 0.0f, 0.0f, 0.0f };

	// �����蔻��̐ݒ�
	// �����蔻����̃T�C�Y��3�ɐݒ�
	m_tCollisionInfos.resize(3); 
	//--- ���̓����蔻����̏�����
	// �����蔻��̎�ނ�ݒ�
	m_tCollisionInfos[0].type = Collision::eBox;
	// �^�O��ǉ�
	m_tCollisionInfos[0].tag.push_back(Collision::Tag::Npc);
	m_tCollisionInfos[0].tag.push_back(Collision::Tag::Head);
	// ���S�ʒu��ݒ�
	m_tCollisionInfos[0].box.center = Add(m_tPosition, XMFLOAT3(0.0f, m_tScale.y, 0.0f));
	m_tCollisionInfos[0].AdjustCenter = XMFLOAT3(0.0f, m_tScale.y, 0.0f); // ���S�ʒu�̒���
	// �{�b�N�X�̑傫����ݒ�
	m_tCollisionInfos[0].box.size = m_tScale;
	//--- �̂̓����蔻����̏�����
	// �����蔻��̎�ނ�ݒ�
	m_tCollisionInfos[1].type = Collision::eBox;
	// �^�O��ǉ�
	m_tCollisionInfos[1].tag.push_back(Collision::Tag::Npc);
	m_tCollisionInfos[1].tag.push_back(Collision::Tag::Body);
	// ���S�ʒu��ݒ�
	m_tCollisionInfos[1].box.center = m_tPosition;
	// �{�b�N�X�̑傫����ݒ�
	m_tCollisionInfos[1].box.size = m_tScale;
	//--- ���̓����蔻����̏�����
	// �����蔻��̎�ނ�ݒ�
	m_tCollisionInfos[2].type = Collision::eBox;
	// �^�O��ǉ�
	m_tCollisionInfos[2].tag.push_back(Collision::Tag::Npc);
	// �^�O��ǉ�
	m_tCollisionInfos[2].tag.push_back(Collision::Tag::Foot);
	// ���S�ʒu��ݒ�
	m_tCollisionInfos[2].box.center = Sub(m_tPosition, XMFLOAT3(0.0f, m_tScale.y, 0.0f));
	m_tCollisionInfos[2].AdjustCenter = XMFLOAT3(0.0f, -m_tScale.y, 0.0f); // ���S�ʒu�̒���
	// �{�b�N�X�̑傫����ݒ�
	m_tCollisionInfos[2].box.size = m_tScale;

	switch (m_eNpcType)
	{
	case NpcType::ArenaTarget:
		// ����̐���
		m_pWeapon = new CSword();
		// ����̓����蔻���NPC�^�O��ǉ�
		for (auto& AttackRange : m_pWeapon->GetAttackRanges())
		{
			AttackRange.tag.push_back(Collision::Tag::Npc);
		}
		// �̗͂̐ݒ�
		m_fHp = GameValue::Npc::ArenaTarget::MAX_HP;
		break;
	}

	// �̗̓Q�[�W�̍쐬
	m_pHpGauge = new CGaugeUI(m_fHp, false, GaugeType::Health);
	// �̗̓Q�[�W�̃p�����[�^�ݒ�
	m_pHpGauge->SetParam({ 5.0f,2.0f,1.0f }, { 0.0f,0.0f,0.0f }, { 0.0f, 5.0f, 0.0f });
}

// @brief �f�X�g���N�^
CTargetNpc::~CTargetNpc()
{

}

// @brief �X�V����
void CTargetNpc::Update(void)
{
	// �j���t���O�������Ă���ꍇ�͍X�V���s��Ȃ�
	if (m_bDestroy)
	{
		ChangeScene(SceneType::QuestSelect, TransitionType::Fade); // �V�[�����N�G�X�g�I���ɕύX
	}
	else
	{

		// ���N���X�̍X�V����(NPC���ʏ���)
		CNpcBase::BiginUpdate();

		// �U��
		Attack();
		// �ړ�
		Move();

		// ���N���X�̍X�V����(NPC���ʏ���)
		CNpcBase::EndUpdate();
	}
}

// @brief �ړ�����
void CTargetNpc::Move(void)
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
		XMFLOAT3 playerPos = m_pTargetObject->GetPosition();
		movePoint = { playerPos.x,m_tPosition.y,playerPos.z };
		break;
	}

	XMFLOAT3 moveDir = Direction(m_tPosition, movePoint);
	// �U�����łȂ��ꍇ�͈ړ��ʂ�K�p
	if (!m_bAttack)SetPosition(Add(m_tPosition, Mul(moveDir, m_pMoveSystem->GetMoveSpeed())));
	// �����̍X�V
	m_tRotation.y = TODEG(atan2f(-moveDir.z, moveDir.x));
}

// @brief �U������
void CTargetNpc::Attack(void)
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

		// ���킪����΍U��
		if (m_pWeapon == nullptr)return;

		// �v���C���[���U���͈͓��ɂ��邩�ǂ����𔻒�
		// �v���C���[�̈ʒu���擾
		XMFLOAT3 playerPos = m_pTargetObject->GetPosition();
		// �U���͈͊O�Ȃ牽�����Ȃ�
		XMFLOAT3 weaponCollisionSize = m_pWeapon->GetAttackRange().box.size;
		float maxAttackRange = std::max(weaponCollisionSize.x, weaponCollisionSize.z); // �U���͈͂̍ő�l���v�Z

		if (StructMath::Abs(StructMath::Sub(playerPos, m_tPosition)).x > maxAttackRange * 2.0f ||
			StructMath::Abs(StructMath::Sub(playerPos, m_tPosition)).z > maxAttackRange * 2.0f)
		{
			m_bAttack = false;
			return;
		}



		// ����̍X�V����
		// �������l�����Ĉʒu�𒲐�
		XMFLOAT3 attackDir = StructMath::Direction(m_tPosition, playerPos);

		m_pWeapon->Update(Add(m_tPosition, Mul(attackDir, maxAttackRange)));

		/// @todo �����ōU���^�C�~���O�̔�����s��(����(�m���͎Q�Ƃ��邽�тɏ㏸))

		m_pWeapon->ComboTimerUpdate(); // �R���{�P�\���Ԃ̍X�V

		// �V�[���̎擾
		auto scene = (CSceneGame*)GetCurrentScene();

		// �V�[�����Ȃ���Ή������Ȃ�
		if (scene == nullptr)return;

		// �U���𐶐�
		scene->AttackCreate(m_pWeapon->CreateAttack(m_tRotation.y));

		// �N�[���^�C����ݒ�
		m_fAttackCD = m_pWeapon->GetAttackSpeed();

		// �U�����t���O�𗧂Ă�
		m_bAttack = true;
	}
}
