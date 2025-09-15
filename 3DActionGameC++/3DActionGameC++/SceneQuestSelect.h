/*=====================================================================
* @file SceneQuestSelect.h
* @brief クエスト選択シーンクラスのヘッダーファイル
=====================================================================*/

#pragma once

/* 基底クラスのインクルード */
#include "SceneBase.h"

/* システム・要素のインクルード */
#include <vector>
#include "Quest.h"
#include "SpriteDrawer.h"

/// <summary>
/// クエスト選択シーンクラス
/// </summary>
class CSceneQuestSelect : public CSceneBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CSceneQuestSelect();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~CSceneQuestSelect();
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(void)override;
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(void)override;

private:

	// @brief 現在選択中のインデックス
	int m_CurrentIndex;

	// @brief クエストのリスト
	std::vector<QuestData> m_QuestList;

	//2D描画に必要なデータ
	ID3D11Buffer* m_pBackGroundVtx;
	ID3D11ShaderResourceView* m_pBackGroundTex;
};

