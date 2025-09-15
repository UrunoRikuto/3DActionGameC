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
	m_QuestList.push_back(QuestData{ StageType::Arena, 300.0f, 3 });
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
		// クエストデータの設定
		CQuest::GetInstance()->SetQuestData(m_QuestList[m_CurrentIndex]);
		// シーン切り替え処理
		ChangeScene(SceneType::Game);
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
}
