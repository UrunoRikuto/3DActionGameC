/*=====================================================================
* @file SceneQuestSelect.cpp
* @brief クエスト選択シーンクラスのCppファイル
=====================================================================*/

/* ヘッダーのインクルード */
#include "SceneQuestSelect.h"

/* システム・要素のインクルード */
#include "Input.h"
#include "Mouse.h"
#include "GameValues.h"
#include "DirectXTex/TextureLoad.h"
#include "Defines.h"
#include "VertexBuffer.h"
#include "Main.h"
#include <string>

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
	// クエスト依頼書の選択
	Select();
	// クエスト依頼書の決定・キャンセル
	DECIDE();
}

// @brief 描画処理
void CSceneQuestSelect::Draw(void)
{
	SetRender2D();

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

// @brief クエスト依頼書の選択
void CSceneQuestSelect::Select()
{
	// 名前空間の使用
	using namespace InputKey::QuestSelect;

	// - キーボード入力処理 -
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

	// - マウス入力処理 -

	// マウスの座標を取得
	POINT mousePos = MouseInput::GetCurrentMousePos();

	// マウスの座標をスクリーン座標に変換
	DirectX::XMFLOAT2 fMousePos = DirectX::XMFLOAT2((float)mousePos.x, (float)mousePos.y);
	fMousePos.x -= (SCREEN_WIDTH / 2);
	fMousePos.y -= (SCREEN_HEIGHT / 2);

	fMousePos.x *= 2.0f;
	fMousePos.y *= 2.0f;

	
	// クエスト依頼書の選択
	if (!m_bSelectChack)
	{
		for (int i = 0, x = 0; i < m_QuestList.size(); x++, i++)
		{
			if (!(i % 5)) x = 0;
			// クエスト依頼書の範囲
			float questRectF[4] = {
				((x * 600.0f) - (600.0f * 2)) - 200.0f,
				((x * 600.0f) - (600.0f * 2)) + 200.0f,
				(m_RandPosY[i]) - 150.0f,
				(m_RandPosY[i]) + 150.0f,
			};
			
			// クエスト依頼書の範囲内にマウスがあるか
			if (questRectF[0] <= fMousePos.x && fMousePos.x <= questRectF[1] &&
				questRectF[2] <= fMousePos.y && fMousePos.y <= questRectF[3])
			{
				m_CurrentIndex = i;
			}
		}
	}
}

// @brief クエスト依頼書の決定・キャンセル
void CSceneQuestSelect::DECIDE()
{
	// クエスト依頼書の決定・キャンセル
	if (IsKeyTrigger(InputKey::QuestSelect::DECIDE) || MouseInput::IsTrigger(MouseInput::MouseButton::Left))
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
			// シーン切り替え処理
			ChangeScene(SceneType::Title, TransitionType::Fade);
		}
	}
}