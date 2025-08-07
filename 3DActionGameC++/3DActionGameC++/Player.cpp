/*
* @file Player.cpp
* @brief �v���C���[�N���X��Cpp�t�@�C��
* @author �F���엤�l
* @date 2025/08/04 �N���X�̎���
*                  �ړ������̒ǉ�
*                  ���_�ړ������̒ǉ�
*            08/05 �W�����v�����̒ǉ�
*            08/07 �v���C���[�̍s�����[�h�̎���
*                  ����L�[��Defines.h�ňꊇ�Ǘ���
*/

/* �w�b�_�[�ŗ��p����V�X�e���E�v�f�̃C���N���[�h */

/* �w�b�_�[�̃C���N���[�h */
#include "Player.h"
/* �V�X�e���E�v�f�̃C���N���[�h */
#include "Model.h"
#include "Defines.h"
#include "Main.h"
#include "ModelDrawSetting.h"
#include "Camera.h"
#include "Input.h"

// @brief �R���X�g���N�^
CPlayer::CPlayer()
	:CGameObject()// ���N���X�̃R���X�g���N�^���Ăяo��
	, m_eActionMode(PlayerActionMode::Move) // �v���C���[�̍s�����[�h���ړ����[�h�ɐݒ�
	, m_tMovePower(0.0f, 0.0f, 0.0f)	// �����ړ���
	, m_bGround(true) // �n�ʂɂ��邩�ǂ����̏����l
	, m_bJumping(false) // �W�����v�����ǂ����̏����l
	, m_nJumpFrame(0) // �W�����v�t���[���̏����l
	, m_fUnderHeight(0.0f) // �v���C���[�̐^���̒n�ʂ̍����̏����l
	, m_fSnipingZoom(-1.0f) // �_�����[�h�̃Y�[���{���̏����l
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
}

// @brief �f�X�g���N�^
CPlayer::~CPlayer()
{

}

// @brief �X�V����
void CPlayer::Update(void)
{
	// �s�����[�h�̐؂�ւ�����
	ChangeActionMode();

	// �v���C���[�̍s�����[�h�ɂ���čX�V�����𕪊�
	switch (m_eActionMode)
	{
	case PlayerActionMode::Move: // �ړ����[�h
		MA_Update();
		break;
	case PlayerActionMode::Sniping: // �_�����[�h
		SA_Update();
		break;
	default:
		break;
	}
}

// @brief �`�揈��
void CPlayer::Draw(void)
{
	switch (m_eActionMode)
	{
	case PlayerActionMode::Move:
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
			m_tRotation,		// ��]
			m_pModel.get(),			// ���f���|�C���^
			Camera::GetInstance(), // �J�����|�C���^
			true,					// ���邭���邩�ǂ���
			XMFLOAT3(0.5f, 0.5f, 0.5f)// �F
		);
		break;
	case PlayerActionMode::Sniping:
		break;
	}
}

// @brief �s�����[�h�̐؂�ւ�
void CPlayer::ChangeActionMode(void)
{
	using namespace InputKey::Player;
	// �s�����[�h�̐؂�ւ��L�[�������ꂽ��
	if (IsKeyTrigger(CHANGE_ACTIONMODE))
	{
		switch (m_eActionMode)
		{
		case PlayerActionMode::Move:
			// �ړ����[�h����_�����[�h�ɐ؂�ւ�
			m_eActionMode = PlayerActionMode::Sniping;
			// �_�����[�h�̃Y�[���{����ݒ�
			m_fSnipingZoom = 1.0f;
			// �J�����̎���p��_�����[�h�ɐݒ�
			Camera::GetInstance()->SetFov(1.0f);
			break;
		case PlayerActionMode::Sniping:
			// �_�����[�h����ړ����[�h�ɐ؂�ւ�
			m_eActionMode = PlayerActionMode::Move;
			// �J�����̎���p���ړ����[�h�ɐݒ�
			Camera::GetInstance()->SetFov(20.0f);
			// �v���C���[�̉�]�����Z�b�g
			m_tRotation = StructMath::FtoF3(0.0f);
			break;
		}
	}
}

// @brief �ړ��A�N�V�����̍X�V����
void CPlayer::MA_Update(void)
{
	// ���_�̈ړ�����
	MA_LookRotation();
	// �ړ�����
	MA_Move();
	// ���􏈗�
	MA_Jump();
	// �J�����̍X�V����
	Camera::GetInstance()->Update(m_tPosition, m_tRotation);
	// �����蔻��̍X�V
	m_tCollisionInfos[0].box.center = m_tPosition; // �����蔻��̒��S�ʒu���X�V
}

// @brief  �ړ��A�N�V�����̈ړ�����
void CPlayer::MA_Move(void)
{
	// ���O��Ԃ̎g�p�錾
	using namespace InputKey::Player::MoveAction;
	using namespace GameValue::Player::MoveAction;

	// �O
	if(IsKeyPress(MOVE_FORWARD))
	{
		m_tMovePower.x += MOVE_SPEED * sinf(TORAD(m_tRotation.y));
		m_tMovePower.z += MOVE_SPEED * cosf(TORAD(m_tRotation.y));
	}
	// ��
	if (IsKeyPress(MOVE_BACKWARD))
	{
		m_tMovePower.x -= MOVE_SPEED * sinf(TORAD(m_tRotation.y));
		m_tMovePower.z -= MOVE_SPEED * cosf(TORAD(m_tRotation.y));
	}
	// ��
	if (IsKeyPress(MOVE_LEFT))
	{
		m_tMovePower.x -= MOVE_SPEED * cosf(TORAD(m_tRotation.y));
		m_tMovePower.z += MOVE_SPEED * sinf(TORAD(m_tRotation.y));
	}
	// �E
	if (IsKeyPress(MOVE_RIGHT))
	{
		m_tMovePower.x += MOVE_SPEED * cosf(TORAD(m_tRotation.y));
		m_tMovePower.z -= MOVE_SPEED * sinf(TORAD(m_tRotation.y));
	}

	// �ړ��ʂ�K�p
	m_tPosition = StructMath::Add(m_tPosition, m_tMovePower);
	// �ړ��ʂ����Z�b�g
	m_tMovePower = { 0.0f, 0.0f, 0.0f }; 
}

// @brief  �ړ��A�N�V�����̒��􏈗�
void CPlayer::MA_Jump(void)
{
	// ���O��Ԃ̎g�p�錾
	using namespace InputKey::Player::MoveAction;
	using namespace GameValue::Player::MoveAction;

	// �X�y�[�X�L�[�������ꂽ��
	if (IsKeyTrigger(JUMP) && m_bGround)
	{
		// �W�����v���t���O�𗧂Ă�
		m_bJumping = true; 
		// �W�����v�t���[�������Z�b�g
		m_nJumpFrame = 0;
		// �n�ʂɂ��Ȃ���Ԃɂ���
		m_bGround = false;
	}
	// �W�����v���̏���
	if (m_bJumping) 
	{
		// sin�g���g���ăW�����v�̍������v�Z
		float rad = (PI * m_nJumpFrame) / JUMP_DURATION;  // �΃��W�A�����g�������炩�ȃJ�[�u
		// �W�����v�̍������v�Z
		m_tPosition.y = (sin(rad) * JUMP_HEIGHT) + m_fUnderHeight + m_fAjustPositionY;

		// �W�����v�t���[����i�߂�
		m_nJumpFrame++;

		// �W�����v�̑��t���[�����ɒB������
		if (m_nJumpFrame >= JUMP_DURATION)
		{
			// �n�ʂ̍����ɖ߂�
			m_tPosition.y = m_fUnderHeight + m_fAjustPositionY;
			// �W�����v���t���O�����낷
			m_bJumping = false;
			// �n�ʂɂ����Ԃɂ���
			m_bGround = true;
		}
	}
	// �n�ʂɂ���ꍇ�͍�����0�ɂ���
	else if(m_bGround)
	{
		m_tPosition.y = m_fUnderHeight + m_fAjustPositionY;
	}
}

// @brief  �ړ��A�N�V�����̎��_�ړ�
void CPlayer::MA_LookRotation(void)
{
	// ���O��Ԃ̎g�p�錾
	using namespace InputKey::Player::MoveAction;
	using namespace GameValue::Player::MoveAction;
	// ����]
	if (IsKeyPress(LOOK_LEFT))
	{
		m_tRotation.y -= ROTATION_SPEED;
	}
	// �E��]
	if (IsKeyPress(LOOK_RIGHT))
	{
		m_tRotation.y += ROTATION_SPEED; // �E����
	}
}

// @brief �_�����[�h�̍X�V����
void CPlayer::SA_Update(void)
{
	// �Y�[���A�N�V�����̏���
	SA_ZoomAction();
	// ���_�̈ړ�����
	SA_LookRotation();
}

// @brief �_�����[�h�̎��_�ړ�
void CPlayer::SA_LookRotation(void)
{
	// ���O��Ԃ̎g�p�錾
	using namespace InputKey::Player::SnipingAction;
	using namespace GameValue::Player::SnipingAction;

	if (IsKeyPress(SNIPING_LOOK_LEFT))
	{
		m_tRotation.y -= LOOK_SPEED_HORIZONTAL; // ������
	}
	if (IsKeyPress(SNIPING_LOOK_RIGHT))
	{
		m_tRotation.y += LOOK_SPEED_HORIZONTAL; // �E����
	}
	if (IsKeyPress(SNIPING_LOOK_UP))
	{
		m_tRotation.x -= LOOK_SPEED_VERTICAL; // �����
	}
	if (IsKeyPress(SNIPING_LOOK_DOWN))
	{
		m_tRotation.x += LOOK_SPEED_VERTICAL; // ������
	}

	// �J�����̎��_�ʒu���v�Z
	XMFLOAT3 CameraLookPos = XMFLOAT3(
		m_tPosition.x + sinf(TORAD(m_tRotation.y)) * (m_fSnipingZoom * 10.0f),
		m_tPosition.y,
		m_tPosition.z + cosf(TORAD(m_tRotation.y)) * (m_fSnipingZoom * 10.0f)
	);

	// �J�����̍X�V����
	Camera::GetInstance()->Update(CameraLookPos, m_tRotation);
}

void CPlayer::SA_ZoomAction(void)
{
	// ���O��Ԃ̎g�p�錾
	using namespace InputKey::Player::SnipingAction;
	using namespace GameValue::Player::SnipingAction;

	if (IsKeyPress(SNIPING_ZOOM_IN)) //�Y�[���C��
	{
		m_fSnipingZoom += ZOOM_POWER;
	}
	if (IsKeyPress(SNIPING_ZOOM_OUT)) //�Y�[���A�E�g
	{
		m_fSnipingZoom -= ZOOM_POWER;
	}
	// �Y�[���{���̐���
	//(��)���킲�ƂɃY�[���������쐬����
	//(��)1.0f�ȏ�5.0f�ȉ��ɐ���
	if (m_fSnipingZoom < 1.0f)
	{
		m_fSnipingZoom = 1.0f; // �ŏ��Y�[���{��
	}
	else if (m_fSnipingZoom > 10.0f)
	{
		m_fSnipingZoom = 10.0f; // �ő�Y�[���{��
	}
}
