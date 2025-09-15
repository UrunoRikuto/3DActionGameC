/*=====================================================================
* @file Quest.h
* @brief クエスト管理クラスのヘッダーファイル
=====================================================================*/

#pragma once

/* システム・要素のインクルード */
#include "Enums.h"

// @brief クエストデータ構造体
// @param stageType ステージの種類
// @param limitTime 制限時間
// @param maxDeathCount 最大死亡可能回数
struct QuestData
{
	// ステージの種類
	StageType stageType;
	// 制限時間
	float limitTime;
	// 最大死亡可能回数
	int maxDeathCount;
};


//@brief クエスト管理クラス
class CQuest
{
	// シングルトンパターン
private:
	static CQuest* m_pInstance;

public:
	// @brief インスタンスの取得
	// @return インスタンスのポインタ
	static CQuest* GetInstance();

private:
	// @brief コンストラクタ
	CQuest();

public:
	// @brief デストラクタ
	~CQuest();

	// @brief クエストデータの設定
	void SetQuestData(const QuestData& In_QuestData);

	// @brief クエストデータの取得
	// @return クエストデータの参照
	const QuestData& GetQuestData(void);

	// @brief クエストデータのクリア
	void ClearQuestData(void);

private:
	// @brief クエストデータ
	QuestData m_QuestData;
};