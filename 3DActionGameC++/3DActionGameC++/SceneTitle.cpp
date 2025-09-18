/*
* @file SceneTitle.cpp
* @brief �^�C�g���V�[���̃N���X��Cpp�t�@�C��
* @author �F���엤�l
* @date 2025/08/04 �N���X�̎���
*/

#include "SceneBase.h"
#include "SceneTitle.h"
#include "DirectXTex/TextureLoad.h"
#include "Defines.h"
#include "VertexBuffer.h"
#include "Input.h"
#include "Mouse.h"
#include "Main.h"

// @brief �R���X�g���N�^
CSceneTitle::CSceneTitle()
{
	//Vertex�̐���
	Vertex vtx[4] = {
	{ {-SCREEN_WIDTH,-SCREEN_HEIGHT,0.0f},{0.0f,0.0f}},
	{ { SCREEN_WIDTH,-SCREEN_HEIGHT,0.0f},{1.0f,0.0f}},
	{ {-SCREEN_WIDTH, SCREEN_HEIGHT,0.0f},{0.0f,1.0f}},
	{ { SCREEN_WIDTH, SCREEN_HEIGHT,0.0f},{1.0f,1.0f}},
	};

	//��������Vertex��Buffer�̃|�C���^�ϐ��ɐݒ�
	m_pVtx = CreateVertexBuffer(vtx, 4);

	HRESULT hr = E_FAIL;
	//�^�C�g���̔w�i�e�N�X�`���̐ݒ�
	hr = LoadTextureFromFile(GetDevice(), TEXTURE_PATH("BackGround.png"), &m_pTex);
	if (FAILED(hr)) {
		//---�f�o�b�N���[�h�̂ݏ���
#ifdef _DEBUG
		MessageBox(NULL, "Title�w�i�摜", "Error", MB_OK);
#endif
	}
}

// @brief �f�X�g���N�^
CSceneTitle::~CSceneTitle()
{
	//�o�b�t�@�[�|�C���^�̉��
	if (m_pVtx) m_pVtx->Release();
	//�e�N�X�`���|�C���^�̉��
	if (m_pTex) m_pTex->Release();
}

// @brief �X�V����
void CSceneTitle::Update(void)
{
	if (IsKeyTrigger(VK_RETURN) || MouseInput::IsTrigger(MouseInput::MouseButton::Left))
	{
		//�V�[���؂�ւ�����
		ChangeScene(SceneType::QuestSelect, new CFade(2.0f));
	}
}

// @brief �`�揈��
void CSceneTitle::Draw(void)
{
	//�w�i�̕`��
	SetSpriteTexture(m_pTex);

	SetSpritePos(0.0f, 0.0f);
	SetSpriteScale(1.0f, 1.0f);
	SetSpriteColor(1.0f, 1.0f, 1.0f, 1.0f);
	SetSpriteUVPos(0.0f, 0.0f);
	SetSpriteUVScale(1.0f, 1.0f);

	DrawSprite(m_pVtx, sizeof(Vertex));
}
