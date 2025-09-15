/*=====================================================================
* @file SceneQuestSelect.cpp
* @brief �N�G�X�g�I���V�[���N���X��Cpp�t�@�C��
=====================================================================*/

/* �w�b�_�[�̃C���N���[�h */
#include "SceneQuestSelect.h"

/* �V�X�e���E�v�f�̃C���N���[�h */
#include "Input.h"
#include "GameValues.h"
#include "DirectXTex/TextureLoad.h"
#include "Defines.h"
#include "VertexBuffer.h"
#include "Main.h"

// @brief �R���X�g���N�^
CSceneQuestSelect::CSceneQuestSelect()
	:CSceneBase()
	, m_CurrentIndex(0)
{
	//Vertex�̐���
	Vertex vtx[4] = {
	{ {-SCREEN_WIDTH,-SCREEN_HEIGHT,0.0f},{0.0f,0.0f}},
	{ { SCREEN_WIDTH,-SCREEN_HEIGHT,0.0f},{1.0f,0.0f}},
	{ {-SCREEN_WIDTH, SCREEN_HEIGHT,0.0f},{0.0f,1.0f}},
	{ { SCREEN_WIDTH, SCREEN_HEIGHT,0.0f},{1.0f,1.0f}},
	};

	//��������Vertex��Buffer�̃|�C���^�ϐ��ɐݒ�
	m_pBackGroundVtx = CreateVertexBuffer(vtx, 4);

	HRESULT hr = E_FAIL;
	//�^�C�g���̔w�i�e�N�X�`���̐ݒ�
	hr = LoadTextureFromFile(GetDevice(), TEXTURE_PATH("QuestBoard.png"), &m_pBackGroundTex);


	// �N�G�X�g�f�[�^�̓o�^
	m_QuestList.push_back(QuestData{ StageType::Arena, 300.0f, 3 });
}

// @brief �f�X�g���N�^
CSceneQuestSelect::~CSceneQuestSelect()
{
	//�o�b�t�@�[�|�C���^�̉��
	if (m_pBackGroundVtx) m_pBackGroundVtx->Release();
	//�e�N�X�`���|�C���^�̉��
	if (m_pBackGroundTex) m_pBackGroundTex->Release();
}

// @brief �X�V����
void CSceneQuestSelect::Update(void)
{
	// ���O��Ԃ̎g�p
	using namespace InputKey::QuestSelect;

	if (IsKeyTrigger(NEXT))
	{
		m_CurrentIndex++;
		if (m_CurrentIndex > m_QuestList.size() - 1)
		{
			m_CurrentIndex = m_QuestList.size() - 1;
		}
	}

	if (IsKeyTrigger(BEFORE))
	{
		m_CurrentIndex--;
		if (m_CurrentIndex < 0)
		{
			m_CurrentIndex = 0;
		}
	}

	if (IsKeyTrigger(DECIDE))
	{
		// �N�G�X�g�f�[�^�̐ݒ�
		CQuest::GetInstance()->SetQuestData(m_QuestList[m_CurrentIndex]);
		// �V�[���؂�ւ�����
		ChangeScene(SceneType::Game);
	}
}

// @brief �`�揈��
void CSceneQuestSelect::Draw(void)
{
	//�w�i�̕`��
	SetSpriteTexture(m_pBackGroundTex);

	SetSpritePos(0.0f, 0.0f);
	SetSpriteScale(1.0f, 1.0f);
	SetSpriteColor(1.0f, 1.0f, 1.0f, 1.0f);
	SetSpriteUVPos(0.0f, 0.0f);
	SetSpriteUVScale(1.0f, 1.0f);

	DrawSprite(m_pBackGroundVtx, sizeof(Vertex));
}
