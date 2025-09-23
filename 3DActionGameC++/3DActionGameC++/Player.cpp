/*=====================================================================
* @file Player.cpp
* @brief �v���C���[�̎����t�@�C��
=====================================================================*/


/* �w�b�_�[�̃C���N���[�h */
#include "Player.h"
/* �V�X�e���E�v�f�̃C���N���[�h */
#include "Model.h"
#include "GameValues.h"
#include "Defines.h"
#include "Main.h"
#include "ModelDrawSetting.h"
#include "Camera.h"
#include "Input.h"
#include "Mouse.h"
#include "Quest.h"

// @brief �R���X�g���N�^
CPlayer::CPlayer()
	:CGameObject()// ���N���X�̃R���X�g���N�^���Ăяo��
	, m_tMovePower(0.0f, 0.0f, 0.0f)	// �����ړ���
	, m_bGround(true) // �n�ʂɂ��邩�ǂ����̏����l
	, m_bJumping(false) // �W�����v�����ǂ����̏����l
	, m_nJumpFrame(GameValue::Player::JUMP_DURATION) // �W�����v�t���[���̏����l
	, m_fUnderHeight(0.0f) // �v���C���[�̐^���̒n�ʂ̍����̏����l
	, m_ePosture(PlayerPosture::Stand) // �v���C���[�̎p����Ԃ𗧂��Ă����Ԃɐݒ�
	, m_fAttackCD(0.0f) // �U���̃N�[���^�C���̏����l
	, m_fHp(GameValue::Player::MAX_HP) // �̗͂̏����l
{
	// ���f���̐���
	m_pModel = std::make_unique<Model>();
	// ���f���̓ǂݍ���
	if (!m_pModel->Load(MODEL_PATH("Player.obj")))
	{
		MessageBox(NULL, "�v���C���[���f���̓ǂݍ��݂Ɏ��s���܂����B", "Error", MB_OK);
	}

	// �ʒu�A�␳�����A�X�P�[���A��]�̐ݒ�
	m_tScale = { 2.0f, 2.0f, 2.0f };
	m_fAjustPositionY = (m_tScale.y * 2) / 2.0f; // �v���C���[�̐^���̒n�ʂ̍�����ݒ�
	m_tPosition = { 0.0f, m_fAjustPositionY, 0.0f };
	m_tRotation = { 0.0f, 0.0f, 0.0f };

	// ���C�̐���
	m_pRay = std::make_unique<CRay>();
	m_pRay->SetParam(m_tPosition, XMFLOAT3(0.0f, -1.0f, 0.0f)); // ���C�̎n�_�ƕ�����ݒ�

	// �����蔻��̐ݒ�
	// �����蔻����̃T�C�Y��1�ɐݒ�
	m_tCollisionInfos.resize(1);
	// �����蔻��̎�ނ�ݒ�
	m_tCollisionInfos[0].type = Collision::eBox;
	// �^�O��ǉ�
	m_tCollisionInfos[0].tag.push_back(Collision::Tag::Player);
	// ���S�ʒu��ݒ�
	m_tCollisionInfos[0].box.center = m_tPosition;
	// �{�b�N�X�̑傫����ݒ�
	m_tCollisionInfos[0].box.size = StructMath::Add(m_tScale, XMFLOAT3(0.0f, m_tScale.y * 2, 0.0f));

	// ����̐���
	m_pWeapon = new CFist();
	// ����̓����蔻��Ƀv���C���[�^�O��ǉ�
	for (auto& AttackRange : m_pWeapon->GetAttackRanges())
	{
		AttackRange.tag.push_back(Collision::Tag::Player);
	}
}

// @brief �f�X�g���N�^
CPlayer::~CPlayer()
{

}

// @brief �X�V����
void CPlayer::Update(void)
{
	// �j���t���O�������Ă���ꍇ�͍X�V���s��Ȃ�
	if (m_bDestroy)return;

	// ���݂̈ʒu��O�̈ʒu�Ƃ��ĕۑ�
	m_tOldPosition = m_tPosition; 

	// ���_�̈ړ�����
	LookRotation();
	// �ړ�����
	Move();
	// ���􏈗�
	Jump();
	// �U������
	Attack();
	// �J�����̍X�V����
	Camera::GetInstance()->Update(m_tPosition, m_tRotation);
	// �����蔻��̍X�V
	m_tCollisionInfos[0].box.center = m_tPosition; // �����蔻��̒��S�ʒu���X�V

	// ���C�̍X�V
	m_pRay->SetOrigin(m_tPosition); // ���C�̈ʒu���X�V
}

// @brief �`�揈��
void CPlayer::Draw(void)
{
	// �j���t���O�������Ă���ꍇ�͍X�V���s��Ȃ�
	if (m_bDestroy)return;

	SetRender3D();

#ifdef _DEBUG
	// �����蔻��̕`��
	for (const auto& collisionInfo : m_tCollisionInfos)
	{
		Collision::DrawCollision(collisionInfo); // �����蔻��̕`��i�f�o�b�O�p�j
	}
#endif // _DEBUG

	// ���f���̕`��
	CreateObject(
		m_tPosition,        // �ʒu
		m_tScale,			// �X�P�[��
		{ 0.0f,m_tRotation.y,0.0f },		// ��]
		m_pModel.get(),			// ���f���|�C���^
		Camera::GetInstance(), // �J�����|�C���^
		true,					// ���邭���邩�ǂ���
		XMFLOAT3(0.5f, 0.5f, 0.5f)// �F
	);
}

// @brief �v���C���[�̐^���̒n�ʂ̍�����ݒ肷��
// @param height �v���C���[�̐^���̒n�ʂ̍���
void CPlayer::SetUnderHeight(float height)
{
	if (m_fUnderHeight - m_fAjustPositionY != height )
	{
		m_fUnderHeight = height + m_fAjustPositionY; 
		m_bGround = false;
	}
}

// @brief �����蔻��̏Փˎ��̏���
// @param InCollisionInfo �ՓˑΏ�
void CPlayer::Hit(const Collision::Info& InCollisionInfo)
{
	for (auto& tag : InCollisionInfo.tag)
	{
		switch (tag)
		{
		case Collision::Tag::FieldGround:
		case Collision::Tag::FieldWall:
		case Collision::Tag::FieldObject:
			if (InCollisionInfo.box.center.y - m_tPosition.y > -0.1f)
			{
				m_tPosition = m_tOldPosition; // �v���C���[�̈ʒu��O�̈ʒu�ɖ߂�
				m_pRay->SetOrigin(m_tPosition); // ���C�̈ʒu���X�V
				m_tCollisionInfos[0].box.center = m_tPosition; // �����蔻��̒��S�ʒu���X�V
				Camera::GetInstance()->Update(m_tPosition,m_tRotation); // �J�����̈ʒu���X�V
			}
			break;
		}
	}
}

// @brief �����蔻��̏Փˎ��̏���(�U���p)
// @param InCollisionInfo �ՓˑΏ�
// @param In_Attack ����̍U����
void CPlayer::Hit(const Collision::Info& InCollisionInfo, float In_Attack)
{
	int IsNpcAttackCheck = 0;

	// NPC�̍U���ɓ����������ǂ����𔻒�
	// NPC�^�O�ƍU���^�O�̗����������NPC�̍U���ɓ��������Ɣ���
	for (auto& tag : InCollisionInfo.tag)
	{
		switch (tag)
		{
		case Collision::Tag::Npc:
			IsNpcAttackCheck++;
			break;
		case Collision::Tag::Attack:
			IsNpcAttackCheck++;
			break;
		}
	}

	// NPC�̍U���ɓ��������ꍇ
	if (IsNpcAttackCheck >= 2)
	{
		// �̗͂����炷
		m_fHp -= In_Attack;

		// �̗͂�0�ȉ��ɂȂ�����j���t���O�𗧂Ă�
		if (m_fHp <= 0.0f)
		{
			m_fHp = GameValue::Player::MAX_HP;
			CQuest::GetInstance()->SubPossibleDeathCount();
			m_tPosition = GameValue::Field::PLAYER_SPOWN_POINT[static_cast<int>(CQuest::GetInstance()->GetQuestData().stageType)];
		}
	}
}

// @brief �U������
void CPlayer::Attack(void)
{
	// �����ݒ肵�Ă��Ȃ��ꍇ�͉������Ȃ�
	if (!m_pWeapon)return;

	// ����̍X�V����
	// �������l�����čX�V
	XMFLOAT3 FrontDir = { sinf(TORAD(m_tRotation.y)),0.0f,cosf(TORAD(m_tRotation.y)) };

	XMFLOAT3 attackDir = StructMath::Direction(m_tPosition, StructMath::Add(m_tPosition, FrontDir));

	XMFLOAT3 attackRangeSize = m_pWeapon->GetAttackRange().box.size;

	m_pWeapon->Update(StructMath::Add(m_tPosition, StructMath::Mul(attackDir, std::max(attackRangeSize.x, attackRangeSize.z))));

	// �N�[���^�C�����c���Ă���ꍇ�̓N�[���^�C�������炷
	if (m_fAttackCD > 0.0f)
	{
		m_fAttackCD -= 1.0f / fFPS;
		if (m_fAttackCD < 0.0f)m_fAttackCD = 0.0f;
	}
	else
	{
		// �R���{�P�\���Ԃ̍X�V
		m_pWeapon->ComboTimerUpdate(); 

		// �U���L�[�������ꂽ��
		if (MouseInput::IsTrigger(MouseInput::MouseButton::Left))
		{
			// �V�[���̎擾
			auto scene = (CSceneGame*)GetCurrentScene();

			// �V�[�����Ȃ���Ή������Ȃ�
			if (scene == nullptr)return;

			// �U���𐶐�
			scene->AttackCreate(m_pWeapon->CreateAttack(m_tRotation.y));

			// �N�[���^�C����ݒ�
			m_fAttackCD = m_pWeapon->GetAttackSpeed();
		}
	}
}

// @brief �ړ�����
void CPlayer::Move(void)
{
	// �O
	if(IsKeyPress(InputKey::Player::MOVE_FORWARD))
	{
		m_tMovePower.x += GameValue::Player::MOVE_SPEED * sinf(TORAD(m_tRotation.y));
		m_tMovePower.z += GameValue::Player::MOVE_SPEED * cosf(TORAD(m_tRotation.y));
	}
	// ��
	if (IsKeyPress(InputKey::Player::MOVE_BACKWARD))
	{
		m_tMovePower.x -= GameValue::Player::MOVE_SPEED * sinf(TORAD(m_tRotation.y));
		m_tMovePower.z -= GameValue::Player::MOVE_SPEED * cosf(TORAD(m_tRotation.y));
	}
	// ��
	if (IsKeyPress(InputKey::Player::MOVE_LEFT))
	{
		m_tMovePower.x -= GameValue::Player::MOVE_SPEED * cosf(TORAD(m_tRotation.y));
		m_tMovePower.z += GameValue::Player::MOVE_SPEED * sinf(TORAD(m_tRotation.y));
	}
	// �E
	if (IsKeyPress(InputKey::Player::MOVE_RIGHT))
	{
		m_tMovePower.x += GameValue::Player::MOVE_SPEED * cosf(TORAD(m_tRotation.y));
		m_tMovePower.z -= GameValue::Player::MOVE_SPEED * sinf(TORAD(m_tRotation.y));
	}

	// �ړ��ʂ�K�p
	m_tPosition = StructMath::Add(m_tPosition, m_tMovePower);
	// �ړ��ʂ����Z�b�g
	m_tMovePower = { 0.0f, 0.0f, 0.0f }; 
}

// @brief ���􏈗�
void CPlayer::Jump(void)
{
	// �X�y�[�X�L�[�������ꂽ��
	if (IsKeyTrigger(InputKey::Player::JUMP) && m_bGround)
	{
		// �W�����v���t���O�𗧂Ă�
		m_bJumping = true; 
		// �W�����v�t���[�������Z�b�g
		m_nJumpFrame = 0;
		// �n�ʂɂ��Ȃ���Ԃɂ���
		m_bGround = false;
		// �v���C���[�̐^���̒n�ʂ̍�����ۑ�
		m_fBeforeJumpUnderHeight = m_fUnderHeight;
	}

	// �W�����v���̏���
	if (m_bJumping) 
	{
		// sin�g���g���ăW�����v�̍������v�Z
		float rad = (PI * m_nJumpFrame) / GameValue::Player::JUMP_DURATION;  // �΃��W�A�����g�������炩�ȃJ�[�u
		// �W�����v�̍������v�Z
		m_tPosition.y = (sinf(rad) * GameValue::Player::JUMP_HEIGHT) + m_fBeforeJumpUnderHeight + m_fAjustPositionY;

		// �W�����v�t���[����i�߂�
		m_nJumpFrame++;

		// �W�����v�̑��t���[�����ɒB������
		if (m_nJumpFrame >= GameValue::Player::JUMP_DURATION || m_tPosition.y < m_fUnderHeight + m_fAjustPositionY)
		{
			m_nJumpFrame = GameValue::Player::JUMP_DURATION; // �W�����v�t���[�����ő�l�ɐݒ�
			// �W�����v���t���O�����낷
			m_bJumping = false;
		}
	}
	// �n�ʂɂ���ꍇ�͍�����0�ɂ���
	if(m_bGround)
	{
		m_tPosition.y = m_fUnderHeight + m_fAjustPositionY;
	}
	else
	{
		if (m_tPosition.y >= m_fUnderHeight + m_fAjustPositionY)
		{
			if (m_nJumpFrame >= GameValue::Player::JUMP_DURATION / 2)
			{
				m_tPosition.y -= GRAVITY; // �d�͂�K�p
				if (m_tPosition.y < m_fUnderHeight + m_fAjustPositionY)
				{
					m_tPosition.y = m_fUnderHeight + m_fAjustPositionY; // �n�ʂ̍����ɍ��킹��
					m_bGround = true; // �n�ʂɂ����Ԃɂ���
				}
			}
		}
		else if(m_tPosition.y < m_fUnderHeight + m_fAjustPositionY)
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

// @brief ���_�ړ�
void CPlayer::LookRotation(void)
{
	// ����]
	if (MouseInput::IsMove(MouseInput::MouseMove::Left))
	{
		m_tRotation.y -= GameValue::Player::ROTATION_SPEED;
	}
	// �E��]
	if (MouseInput::IsMove(MouseInput::MouseMove::Right))
	{
		m_tRotation.y += GameValue::Player::ROTATION_SPEED;
	}
	// ���]
	if (MouseInput::IsMove(MouseInput::MouseMove::Up))
	{
		m_tRotation.x -= GameValue::Player::ROTATION_SPEED;
		if (m_tRotation.x < -89.9f)m_tRotation.x = -89.9f; // �����ݒ�
	}
	// ����]
	if (MouseInput::IsMove(MouseInput::MouseMove::Down))
	{
		m_tRotation.x += GameValue::Player::ROTATION_SPEED;
		if (m_tRotation.x > 89.9f)m_tRotation.x = 89.9f; // ������ݒ�
	}
}