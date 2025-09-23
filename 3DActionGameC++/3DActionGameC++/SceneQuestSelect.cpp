/*=====================================================================
* @file SceneQuestSelect.cpp
* @brief �N�G�X�g�I���V�[���N���X��Cpp�t�@�C��
=====================================================================*/

/* �w�b�_�[�̃C���N���[�h */
#include "SceneQuestSelect.h"

/* �V�X�e���E�v�f�̃C���N���[�h */
#include "Input.h"
#include "Mouse.h"
#include "GameValues.h"
#include "DirectXTex/TextureLoad.h"
#include "Defines.h"
#include "VertexBuffer.h"
#include "Main.h"
#include <string>

// @brief �R���X�g���N�^
CSceneQuestSelect::CSceneQuestSelect()
	:CSceneBase()
	, m_CurrentIndex(0)
	, m_bSelectChack(false)
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
	m_QuestList.push_back(QuestData{ QuestType::ArenaNormal,StageType::Arena, 120.0f, 3 });
	m_QuestList.push_back(QuestData{ QuestType::PlainNormal,StageType::Plain, 120.0f, 3 });

	Vertex noteVtx[4] = {
	{ {-400.0f,-300.0f,0.0f},{0.0f,0.0f}},
	{ { 400.0f,-300.0f,0.0f},{1.0f,0.0f}},
	{ {-400.0f, 300.0f,0.0f},{0.0f,1.0f}},
	{ { 400.0f, 300.0f,0.0f},{1.0f,1.0f}},
	};
	m_pQuestPaperVtx = CreateVertexBuffer(noteVtx, 4);


	hr = LoadTextureFromFile(GetDevice(), TEXTURE_PATH("QuestPaper_ArenaNormal.png"), &m_pQuestPaperTex[(int)QuestType::ArenaNormal]);
	hr = LoadTextureFromFile(GetDevice(), TEXTURE_PATH("QuestPaper_PlainNormal.png"), &m_pQuestPaperTex[(int)QuestType::PlainNormal]);


	// �N�G�X�g�˗�����Y���W�������_���ɐݒ�
	for (int i = 0; i < m_QuestList.size(); i++)
	{
		m_RandPosY.push_back(RandomSelectPosY());
	}
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
	// �N�G�X�g�˗����̑I��
	Select();
	// �N�G�X�g�˗����̌���E�L�����Z��
	DECIDE();
}

// @brief �`�揈��
void CSceneQuestSelect::Draw(void)
{
	SetRender2D();

	//�w�i�̕`��
	SetSpriteTexture(m_pBackGroundTex);

	SetSpritePos(0.0f, 0.0f);
	SetSpriteScale(1.0f, 1.0f);
	SetSpriteColor(1.0f, 1.0f, 1.0f, 1.0f);
	SetSpriteUVPos(0.0f, 0.0f);
	SetSpriteUVScale(1.0f, 1.0f);

	DrawSprite(m_pBackGroundVtx, sizeof(Vertex));

	//�N�G�X�g�˗����̕`��
	for (int i = 0, x = 0; i < m_QuestList.size(); x++, i++)
	{
		if (!(i % 5)) x = 0;

		if (i == m_CurrentIndex && m_bSelectChack)continue;

		SetSpriteTexture(m_pQuestPaperTex[(int)m_QuestList[i].questType]);
		SetSpritePos((x * 600.0f) - (600.0f * 2), m_RandPosY[i]);
		SetSpriteScale(1.0f, 1.0f);
		SetSpriteColor(0.5f, 0.5f, 0.5f, 1.0f);
		if (m_CurrentIndex == i)SetSpriteColor(1.0f, 1.0f, 1.0f, 1.0f);
		SetSpriteUVPos(0.0f, 0.0f);
		SetSpriteUVScale(1.0f, 1.0f);
		DrawSprite(m_pQuestPaperVtx, sizeof(Vertex));
	}

	if (m_bSelectChack)
	{
		SetSpriteTexture(m_pQuestPaperTex[(int)m_QuestList[m_CurrentIndex].questType]);
		SetSpritePos(0.0f, 0.0f);
		SetSpriteScale(3.0f, 3.0f);
		SetSpriteColor(1.0f, 1.0f, 1.0f, 1.0f);
		SetSpriteUVPos(0.0f, 0.0f);
		SetSpriteUVScale(1.0f, 1.0f);
		DrawSprite(m_pQuestPaperVtx, sizeof(Vertex));
	}
}

// @brief �N�G�X�g�˗�����Y���W�������_���ɑI��
float CSceneQuestSelect::RandomSelectPosY()
{
	float Y  = 0;
	int i = m_RandPosY.size();

	if (m_QuestList.size() <= 5)Y = (rand() % 1000) - 500.0f;
	else if (m_QuestList.size() <= 10)
	{
		Y = ((rand() % 500) - 250.0f);
		Y += (int)(i / 5) ? 250.0f : -250.0f;
	}
	else
	{
		MessageBox(NULL, TEXT("�J��ɑi���܂�"), TEXT("�N�G�X�g������"), MB_OK | MB_ICONERROR);
	}


	// �d�����Ȃ��悤�ɂ���
	while (true)
	{
		if (m_RandPosY.empty())return Y;

		if (i - 5 < 0) break;

		if (m_RandPosY[i - 5] - 500.0f < Y && m_RandPosY[i - 5] + 500.0f > Y)
		{
			if (m_QuestList.size() <= 5)Y = (rand() % 1000) - 500.0f;
			else if (m_QuestList.size() <= 10)Y = ((rand() % 500) - 250.0f) + (500.0f * (int)(i / 5));
		}
		else break;
	}

	return Y;
}

// @brief �N�G�X�g�˗����̑I��
void CSceneQuestSelect::Select()
{
	// ���O��Ԃ̎g�p
	using namespace InputKey::QuestSelect;

	// - �L�[�{�[�h���͏��� -
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

	// - �}�E�X���͏��� -

	// �}�E�X�̍��W���擾
	POINT mousePos = MouseInput::GetCurrentMousePos();

	// �}�E�X�̍��W���X�N���[�����W�ɕϊ�
	DirectX::XMFLOAT2 fMousePos = DirectX::XMFLOAT2((float)mousePos.x, (float)mousePos.y);
	fMousePos.x -= (SCREEN_WIDTH / 2);
	fMousePos.y -= (SCREEN_HEIGHT / 2);

	fMousePos.x *= 2.0f;
	fMousePos.y *= 2.0f;

	
	// �N�G�X�g�˗����̑I��
	if (!m_bSelectChack)
	{
		for (int i = 0, x = 0; i < m_QuestList.size(); x++, i++)
		{
			if (!(i % 5)) x = 0;
			// �N�G�X�g�˗����͈̔�
			float questRectF[4] = {
				((x * 600.0f) - (600.0f * 2)) - 200.0f,
				((x * 600.0f) - (600.0f * 2)) + 200.0f,
				(m_RandPosY[i]) - 150.0f,
				(m_RandPosY[i]) + 150.0f,
			};
			
			// �N�G�X�g�˗����͈͓̔��Ƀ}�E�X�����邩
			if (questRectF[0] <= fMousePos.x && fMousePos.x <= questRectF[1] &&
				questRectF[2] <= fMousePos.y && fMousePos.y <= questRectF[3])
			{
				m_CurrentIndex = i;
			}
		}
	}
}

// @brief �N�G�X�g�˗����̌���E�L�����Z��
void CSceneQuestSelect::DECIDE()
{
	// �N�G�X�g�˗����̌���E�L�����Z��
	if (IsKeyTrigger(InputKey::QuestSelect::DECIDE) || MouseInput::IsTrigger(MouseInput::MouseButton::Left))
	{
		if (!m_bSelectChack)
		{
			m_bSelectChack = true;
		}
		else
		{
			// �N�G�X�g�f�[�^�̐ݒ�
			CQuest::GetInstance()->SetQuestData(m_QuestList[m_CurrentIndex]);
			// �V�[���؂�ւ�����
			ChangeScene(SceneType::Game, TransitionType::Fade);
		}
	}
	if (IsKeyTrigger(InputKey::QuestSelect::CANCEL) || MouseInput::IsTrigger(MouseInput::MouseButton::Right))
	{
		if (m_bSelectChack)
		{
			m_bSelectChack = false;
		}
		else
		{
			// �V�[���؂�ւ�����
			ChangeScene(SceneType::Title, TransitionType::Fade);
		}
	}
}