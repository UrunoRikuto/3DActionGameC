/*
* @file Player.cpp
* @brief �v���C���[�N���X��Cpp�t�@�C��
* @author �F���엤�l
* @date 2025/08/04 �N���X�̎���
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
	, m_tMovePower(0.0f, 0.0f, 0.0f)	// �����ړ���
	, m_bGround(true) // �n�ʂɂ��邩�ǂ����̏����l
	, m_nJumpFrame(0) // �W�����v�t���[���̏����l
{
	// ���f���̐���
	m_pModel = std::make_unique<Model>();
	// ���f���̓ǂݍ���
	if (!m_pModel->Load(MODEL_PATH("Player.obj")))
	{
		MessageBox(NULL, "�v���C���[���f���̓ǂݍ��݂Ɏ��s���܂����B", "Error", MB_OK);
	}

	// �ʒu�A�X�P�[���A��]�̐ݒ�
	m_tScale = { 2.0f, 2.0f, 2.0f };
	m_tPosition = { 0.0f, 0.0f, 0.0f };
	m_tRotation = { 0.0f, 0.0f, 0.0f };
}

// @brief �f�X�g���N�^
CPlayer::~CPlayer()
{

}

// @brief �X�V����
void CPlayer::Update(void)
{
	// ���_�̈ړ�����
	LookRotation();
	// �ړ�����
	Move();
	// ���􏈗�
	Jump();
	// �J�����̍X�V����
	Camera::GetInstance()->Update(m_tPosition, m_tRotation);
}

// @brief �`�揈��
void CPlayer::Draw(void)
{
	// ���f���̕`��
	SetRender3D();
	CreateObject(
		m_tPosition,        // �ʒu
		m_tScale,			// �X�P�[��
		m_tRotation,		// ��]
		m_pModel.get(),			// ���f���|�C���^
		Camera::GetInstance(), // �J�����|�C���^
		true,					// ���邭���邩�ǂ���
		XMFLOAT3(0.5f, 0.5f, 0.5f)// �F
	);
}

// @brief �ړ�����
void CPlayer::Move(void)
{
	// �O
	if(IsKeyPress('W'))
	{
		m_tMovePower.x += PLAYER_MOVE_SPEED * sinf(TORAD(m_tRotation.y));
		m_tMovePower.z += PLAYER_MOVE_SPEED * cosf(TORAD(m_tRotation.y));
	}
	// ��
	if (IsKeyPress('S'))
	{
		m_tMovePower.x -= PLAYER_MOVE_SPEED * sinf(TORAD(m_tRotation.y));
		m_tMovePower.z -= PLAYER_MOVE_SPEED * cosf(TORAD(m_tRotation.y));
	}
	// ��
	if (IsKeyPress('A'))
	{
		m_tMovePower.x -= PLAYER_MOVE_SPEED * cosf(TORAD(m_tRotation.y));
		m_tMovePower.z += PLAYER_MOVE_SPEED * sinf(TORAD(m_tRotation.y));
	}
	// �E
	if (IsKeyPress('D'))
	{
		m_tMovePower.x += PLAYER_MOVE_SPEED * cosf(TORAD(m_tRotation.y));
		m_tMovePower.z -= PLAYER_MOVE_SPEED * sinf(TORAD(m_tRotation.y));
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
	if (IsKeyTrigger(VK_SPACE) && m_bGround) 
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
		float rad = (PI * m_nJumpFrame) / PLAYER_JUMP_DURATION;  // �΃��W�A�����g�������炩�ȃJ�[�u
		// �W�����v�̍������v�Z
		m_tPosition.y = sin(rad) * PLAYER_JUMP_HEIGHT;

		// �W�����v�t���[����i�߂�
		m_nJumpFrame++;

		// �W�����v�̑��t���[�����ɒB������
		if (m_nJumpFrame >= PLAYER_JUMP_DURATION) 
		{
			// �n�ʂ̍����ɖ߂�
			m_tPosition.y = 0.0f; 
			// �W�����v���t���O�����낷
			m_bJumping = false;
			// �n�ʂɂ����Ԃɂ���
			m_bGround = true;
		}
	}
	// �n�ʂɂ���ꍇ�͍�����0�ɂ���
	else if(m_bGround)
	{
		m_tPosition.y = 0.0f; 
	}
}

// @brief ���_�ړ�
void CPlayer::LookRotation(void)
{
	if (IsKeyPress(VK_LEFT))
	{
		m_tRotation.y -= PLAYER_ROTATION_SPEED; // ������
	}
	if (IsKeyPress(VK_RIGHT))
	{
		m_tRotation.y += PLAYER_ROTATION_SPEED; // �E����
	}
}
