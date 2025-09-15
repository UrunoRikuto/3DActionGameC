/*=====================================================================
* @file Quest.cpp
* @brief クエスト管理クラスの実装ファイル
=====================================================================*/

/* ヘッダーのインクルード */
#include "Quest.h"

// シングルトンのインスタンスの初期化
CQuest* CQuest::m_pInstance = nullptr;

// @brief インスタンスの取得
CQuest* CQuest::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new CQuest();
	}

	return m_pInstance;
}

// @brief コンストラクタ
CQuest::CQuest()
	: m_QuestData{}
{

}

// @brief デストラクタ
CQuest::~CQuest()
{
	if (m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

// @brief クエストデータの設定
// @param In_QuestData 設定するクエストデータ
void CQuest::SetQuestData(const QuestData& In_QuestData)
{
	m_QuestData = In_QuestData;
}

// @brief クエストデータの取得
// @return クエストデータの参照
const QuestData& CQuest::GetQuestData(void)
{
	return m_QuestData;
}

// @brief クエストデータのクリア
void CQuest::ClearQuestData(void)
{
	m_QuestData = QuestData{};
}
