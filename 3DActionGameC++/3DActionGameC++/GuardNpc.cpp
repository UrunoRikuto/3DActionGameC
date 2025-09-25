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

#undef max

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

	// �␳����
	m_fAjustPositionY = (m_tScale.y * 2) / 2.0f;
	// �ʒu
	m_tPosition = StructMath::Add(m_pMoveSystem->GetMovePointList()[0], XMFLOAT3(0.0f, m_fAjustPositionY, 0.0f));
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
	m_tCollisionInfos[0].box.center = StructMath::Add(m_tPosition, XMFLOAT3(0.0f, m_tScale.y, 0.0f));
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
	m_tCollisionInfos[2].box.center = StructMath::Sub(m_tPosition, XMFLOAT3(0.0f, m_tScale.y, 0.0f));
	m_tCollisionInfos[2].AdjustCenter = XMFLOAT3(0.0f, -m_tScale.y, 0.0f); // ���S�ʒu�̒���
	// �{�b�N�X�̑傫����ݒ�
	m_tCollisionInfos[2].box.size = m_tScale;

	// ����̐���
	m_pWeapon = new CSword();
	// ����̓����蔻���NPC�^�O��ǉ�
	for (auto& AttackRange : m_pWeapon->GetAttackRanges())
	{
		AttackRange.tag.push_back(Collision::Tag::Npc);
	}

	// �̗͂̐ݒ�
	//m_fHp = GameValue::Npc::MAX_HP;

	// �̗̓Q�[�W�̍쐬
	m_pHpGauge = new CGaugeUI(m_fHp, false, GaugeType::Health);
	// �̗̓Q�[�W�̃p�����[�^�ݒ�
	m_pHpGauge->SetParam({ 5.0f,2.0f,1.0f }, { 0.0f,0.0f,0.0f }, { 0.0f, 5.0f, 0.0f });
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
	CNpcBase::BiginUpdate();

	if (m_eSearchState != VisionSearchState::Discovery)
	{
		// �ړ�
		Move();
	}
	else
	{
		// �������̍X�V
		DiscoveryUpdate();
	}

	// ���N���X�̍X�V����(NPC���ʏ���)
	CNpcBase::EndUpdate();
}

// @brief �������̍X�V����
void CGuardNpc::DiscoveryUpdate(void)
{
	switch (m_eActionMode)
	{
	case EnemyAction::Select:
		// �s���^�C�}�[�����Z�b�g
		m_fActionTimer = 0.0f;
		// �s���������_���Ɍ���
		m_eActionMode = static_cast<EnemyAction>((rand() % (static_cast<int>(EnemyAction::Max) - 1)) + 1);
		break;
	case EnemyAction::Move:
		Move();
		// ��莞�Ԉړ�������s����I���ɖ߂�
		if (m_fActionTimer > 3.0f)
		{
			m_eActionMode = EnemyAction::Select;
		}
		break;
	case EnemyAction::Attack:
		Move();
		Attack();
		if (m_bAttack || m_fActionTimer > 5.0f)
		{
			// �U�����I�������s����I���ɖ߂�
			m_eActionMode = EnemyAction::Select;
			// �U�����t���O�����낷
			m_bAttack = false;
		}
		break;
	}
	m_fActionTimer += 1.0f / fFPS;
}

// @brief �ړ�����
void CGuardNpc::Move(void)
{
	XMFLOAT3 movePoint = XMFLOAT3();
	float distance = 0.0f;
	switch (m_eSearchState)
	{
	case VisionSearchState::None:
	case VisionSearchState::Doubt:
	case VisionSearchState::Lost:
		movePoint = m_pMoveSystem->GetMovePoint(m_tPosition);
		break;
	case VisionSearchState::Discovery:
		switch (m_eActionMode)
		{
		case EnemyAction::Move:
			if (m_fActionTimer == 0.0f)
			{
				m_bClockwise = rand() % 2; // ���v���Ɉړ����邩�ǂ����������_���Ɍ���
			}
			// �v���C���[�̈ʒu���擾
			XMFLOAT3 targetPoint = m_pTargetObject->GetPosition();
			// �v���C���[�����苗����ۂ��č��E�ړ�(���v���or�����v���)����
			distance = 30.0f; // �v���C���[����̋���
			if (m_bClockwise)
			{
				// ���v���
				static float angle = 0.0f;
				angle += 1.0f;
				if (angle >= 360.0f)angle = 0.0f;
				movePoint = { targetPoint.x + distance * cosf(TORAD(angle)), m_tPosition.y, targetPoint.z + distance * sinf(TORAD(angle)) };
			}
			else
			{
				// �����v���
				static float angle = 180.0f;
				angle -= 1.0f;
				if (angle < 0.0f)angle = 360.0f;
				movePoint = { targetPoint.x + distance * cosf(TORAD(angle)), m_tPosition.y, targetPoint.z + distance * sinf(TORAD(angle)) };
			}
			break;
		case EnemyAction::Attack:
			XMFLOAT3 playerPos = m_pTargetObject->GetPosition();
			movePoint = { playerPos.x,m_tPosition.y,playerPos.z };
			break;
		}
		break;
	}

	XMFLOAT3 moveDir = StructMath::Direction(m_tPosition, movePoint);
	// �U�����łȂ��ꍇ�͈ړ��ʂ�K�p
	if (!m_bAttack)SetPosition(StructMath::Add(m_tPosition, StructMath::Mul(moveDir, m_pMoveSystem->GetMoveSpeed())));
	// �����̍X�V
	if (m_eSearchState != VisionSearchState::Discovery)
	{
		m_tRotation.y = TODEG(atan2f(-moveDir.z, moveDir.x));
	}
	else
	{
		// �v���C���[�̈ʒu���擾
		XMFLOAT3 targetPoint = m_pTargetObject->GetPosition();
		XMFLOAT3 lookDir = StructMath::Direction(m_tPosition, targetPoint);
		m_tRotation.y = TODEG(atan2f(-lookDir.z, lookDir.x));
	}
}

// @brief �U������
void CGuardNpc::Attack(void)
{
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

		// ���킪����΍U��
		if (m_pWeapon == nullptr)return;
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
		// �������Q�Ƃ��đO�ɏo��
		XMFLOAT3 attackDir = StructMath::Direction(m_tPosition, playerPos);

		m_pWeapon->Update(StructMath::Add(m_tPosition, StructMath::Mul(attackDir, maxAttackRange)));

		/// @todo �����ōU���^�C�~���O�̔�����s��(����(�m���͎Q�Ƃ��邽�тɏ㏸))

		m_pWeapon->ComboTimerUpdate(); // �R���{�P�\���Ԃ̍X�V

		// �V�[���̎擾
		auto scene = (CSceneGame*)GetCurrentScene();

		// �V�[�����Ȃ��ꍇ�͉������Ȃ�
		if (scene == nullptr)return;

		// �U���𐶐�
		scene->AttackCreate(m_pWeapon->CreateAttack(m_tRotation.y));

		// �N�[���^�C����ݒ�
		m_fAttackCD = m_pWeapon->GetAttackSpeed();

		// �U�����t���O�𗧂Ă�
		m_bAttack = true;
	}
}
