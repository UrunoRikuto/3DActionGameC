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
		m_tMovePower.x += PLAYER_SPEED * sinf(TORAD(m_tRotation.y));
		m_tMovePower.z += PLAYER_SPEED * cosf(TORAD(m_tRotation.y));
	}
	// ��
	if (IsKeyPress('S'))
	{
		m_tMovePower.x -= PLAYER_SPEED * sinf(TORAD(m_tRotation.y));
		m_tMovePower.z -= PLAYER_SPEED * cosf(TORAD(m_tRotation.y));
	}
	// ��
	if (IsKeyPress('A'))
	{
		m_tMovePower.x -= PLAYER_SPEED * cosf(TORAD(m_tRotation.y));
		m_tMovePower.z += PLAYER_SPEED * sinf(TORAD(m_tRotation.y));
	}
	// �E
	if (IsKeyPress('D'))
	{
		m_tMovePower.x += PLAYER_SPEED * cosf(TORAD(m_tRotation.y));
		m_tMovePower.z -= PLAYER_SPEED * sinf(TORAD(m_tRotation.y));
	}

	// �ړ��ʂ�K�p
	m_tPosition = StructMath::Add(m_tPosition, m_tMovePower);

	m_tMovePower = { 0.0f, 0.0f, 0.0f }; // �ړ��ʂ����Z�b�g
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
