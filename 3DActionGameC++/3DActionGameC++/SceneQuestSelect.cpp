/*=====================================================================
* @file SceneQuestSelect.cpp
* @brief クエスト選択シーンクラスのCppファイル
=====================================================================*/

/* ヘッダーのインクルード */
#include "SceneQuestSelect.h"

/* システム・要素のインクルード */
#include "Input.h"
#include "GameValues.h"
#include "DirectXTex/TextureLoad.h"
#include "Defines.h"
#include "VertexBuffer.h"
#include "Main.h"

// @brief コンストラクタ
CSceneQuestSelect::CSceneQuestSelect()
	:CSceneBase()
	, m_CurrentIndex(0)
	, m_bSelectChack(false)
{
	//Vertexの生成
	Vertex vtx[4] = {
	{ {-SCREEN_WIDTH,-SCREEN_HEIGHT,0.0f},{0.0f,0.0f}},
	{ { SCREEN_WIDTH,-SCREEN_HEIGHT,0.0f},{1.0f,0.0f}},
	{ {-SCREEN_WIDTH, SCREEN_HEIGHT,0.0f},{0.0f,1.0f}},
	{ { SCREEN_WIDTH, SCREEN_HEIGHT,0.0f},{1.0f,1.0f}},
	};

	//生成したVertexをBufferのポインタ変数に設定
	m_pBackGroundVtx = CreateVertexBuffer(vtx, 4);

	HRESULT hr = E_FAIL;
	//タイトルの背景テクスチャの設定
	hr = LoadTextureFromFile(GetDevice(), TEXTURE_PATH("QuestBoard.png"), &m_pBackGroundTex);


	// クエストデータの登録
	m_QuestList.push_back(QuestData{ QuestType::ArenaNormal,StageType::Arena, 120.0f, 3 });
	m_QuestList.push_back(QuestData{ QuestType::ArenaNormal,StageType::Arena, 120.0f, 3 });
	m_QuestList.push_back(QuestData{ QuestType::ArenaNormal,StageType::Arena, 120.0f, 3 });
	m_QuestList.push_back(QuestData{ QuestType::ArenaNormal,StageType::Arena, 120.0f, 3 });
	m_QuestList.push_back(QuestData{ QuestType::ArenaNormal,StageType::Arena, 120.0f, 3 });
	m_QuestList.push_back(QuestData{ QuestType::ArenaNormal,StageType::Arena, 120.0f, 3 });
	m_QuestList.push_back(QuestData{ QuestType::ArenaNormal,StageType::Arena, 120.0f, 3 });
	m_QuestList.push_back(QuestData{ QuestType::ArenaNormal,StageType::Arena, 120.0f, 3 });
	m_QuestList.push_back(QuestData{ QuestType::ArenaNormal,StageType::Arena, 120.0f, 3 });
	m_QuestList.push_back(QuestData{ QuestType::ArenaNormal,StageType::Arena, 120.0f, 3 });

	Vertex noteVtx[4] = {
	{ {-400.0f,-300.0f,0.0f},{0.0f,0.0f}},
	{ { 400.0f,-300.0f,0.0f},{1.0f,0.0f}},
	{ {-400.0f, 300.0f,0.0f},{0.0f,1.0f}},
	{ { 400.0f, 300.0f,0.0f},{1.0f,1.0f}},
	};
	m_pQuestPaperVtx = CreateVertexBuffer(noteVtx, 4);

	hr = LoadTextureFromFile(GetDevice(), TEXTURE_PATH("QuestPaper_ArenaNormal.png"), &m_pQuestPaperTex[(int)QuestType::ArenaNormal]);

	// クエスト依頼書のY座標をランダムに設定
	for (int i = 0; i < m_QuestList.size(); i++)
	{
		m_RandPosY.push_back(RandomSelectPosY());
	}
}

// @brief デストラクタ
CSceneQuestSelect::~CSceneQuestSelect()
{
	//バッファーポインタの解放
	if (m_pBackGroundVtx) m_pBackGroundVtx->Release();
	//テクスチャポインタの解放
	if (m_pBackGroundTex) m_pBackGroundTex->Release();
}

// @brief 更新処理
void CSceneQuestSelect::Update(void)
{
	// 名前空間の使用
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
		if (!m_bSelectChack)
		{
			m_bSelectChack = true;
		}
		else
		{
			// クエストデータの設定
			CQuest::GetInstance()->SetQuestData(m_QuestList[m_CurrentIndex]);
			// シーン切り替え処理
			ChangeScene(SceneType::Game);
		}
	}

	if (IsKeyTrigger(CANCEL))
	{
		if (m_bSelectChack)
		{
			m_bSelectChack = false;
		}
		else
		{
			// シーン切り替え処理
			ChangeScene(SceneType::Title);
		}
	}
}

// @brief 描画処理
void CSceneQuestSelect::Draw(void)
{
	//背景の描画
	SetSpriteTexture(m_pBackGroundTex);

	SetSpritePos(0.0f, 0.0f);
	SetSpriteScale(1.0f, 1.0f);
	SetSpriteColor(1.0f, 1.0f, 1.0f, 1.0f);
	SetSpriteUVPos(0.0f, 0.0f);
	SetSpriteUVScale(1.0f, 1.0f);

	DrawSprite(m_pBackGroundVtx, sizeof(Vertex));

	//クエスト依頼書の描画
	for (int i = 0, x = 0; i < m_QuestList.size(); x++, i++)
	{
		if (!(i % 5)) x = 0;

		if (i == m_CurrentIndex && m_bSelectChack)continue;

		SetSpriteTexture(m_pQuestPaperTex[(int)m_QuestList[m_CurrentIndex].questType]);
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

// @brief クエスト依頼書のY座標をランダムに選択
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
		MessageBox(NULL, TEXT("労基に訴えます"), TEXT("クエスト多すぎ"), MB_OK | MB_ICONERROR);
	}


	// 重複しないようにする
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
