/*=====================================================================
* @file ResultTelop.cpp
* @brief ���U���g�e���b�v�̎����t�@�C��
=====================================================================*/

/* �w�b�_�[�̃C���N���[�h */
#include "ResultTelop.h"

/* �V�X�e���E�v�f�̃C���N���[�h */
#include "DirectXTex/TextureLoad.h"
#include "VertexBuffer.h"
#include "SpriteDrawer.h"
#include "Texture.h"
#include "Input.h"
#include "Mouse.h"
#include "GameValues.h"
#include <string>
#include "Main.h"


// @brief �R���X�g���N�^
CResultTelop::CResultTelop(bool IsWin)
{
	// �e���b�v�̕\�����Ԃ�ݒ�
	m_fDisplayTime = GameValue::Telop::RESULTTELOP_DISPLAY_TIME;
	// �o�ߎ��Ԃ�������
	m_fElapsedTime = 0.0f;
	// ���_�o�b�t�@�̍쐬
	Vertex vtx[] =
	{
		//�w�i�\���̍��W
		{{-1500, -800, 0.0f}, {0.0f, 0.0f}},
		{{ 1500, -800, 0.0f}, {1.0f, 0.0f}},
		{{-1500,  800, 0.0f}, {0.0f, 1.0f}},
		{{ 1500,  800, 0.0f}, {1.0f, 1.0f}},
	};
	m_pVertexBuffer = CreateVertexBuffer(vtx, 4);

	HRESULT hr = NULL;
	std::string telopFileName;
	// �e�N�X�`���̐���
	if (IsWin)
	{
		telopFileName = TEXTURE_PATH("Telop/QuestClear.png");
	}
	else
	{
		telopFileName = TEXTURE_PATH("Telop/QuestFailed.png");
	}
	// �e���b�v�̃e�N�X�`����ǂݍ���
	hr = LoadTextureFromFile(GetDevice(), telopFileName.c_str(), &m_pTexture);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT(telopFileName.c_str(), "�e���b�v�̓ǂݍ��݂Ɏ��s���܂���"), TEXT("�G���["), MB_OK);
	}
}

// @brief �f�X�g���N�^
CResultTelop::~CResultTelop()
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pTexture);
}

// @brief �X�V����
bool CResultTelop::Update()
{
	// �o�ߎ��Ԃ��X�V
	m_fElapsedTime += 1.0f / fFPS;
	// �\�����Ԃ𒴂�����e���b�v���\���ɂ���
	if (m_fElapsedTime >= m_fDisplayTime || 
		IsKeyTrigger(InputKey::TelopEffect::SKIP) || 
		MouseInput::IsTrigger(MouseInput::MouseButton::Left))
	{
		ChangeScene(SceneType::QuestSelect, TransitionType::Fade); // �V�[�����N�G�X�g�I���ɕύX
		return true; // true��Ԃ��āA�e���b�v���폜����
	}
	return false;
}

// @brief �`�揈��
void CResultTelop::Draw()
{
	// �w�i�̕`��
	SetSpriteTexture(m_pTexture);

	// �X�v���C�g�̐ݒ�
	SetSpritePos(0.0f, 0.0f);
	SetSpriteScale(1.0f, 1.0f);
	SetSpriteColor(1.0f, 1.0f, 1.0f, 1.0f);
	SetSpriteUVPos(0.0f, 0.0f);
	SetSpriteUVScale(1.0f, 1.0f);

	// �X�v���C�g�̕`��
	DrawSprite(m_pVertexBuffer, sizeof(Vertex));
}
