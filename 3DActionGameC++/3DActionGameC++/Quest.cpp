/*=====================================================================
* @file Quest.cpp
* @brief クエスト管理クラスの実装ファイル
=====================================================================*/

/* ヘッダーのインクルード */
#include "Quest.h"

/* システム・要素のインクルード */
#include "Timer.h"
#include "Main.h"

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

void CQuest::DeleteInstance()
{
	if (m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
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
	// クエストデータの設定
	m_QuestData = In_QuestData;
	// 制限時間の設定
	CTimer::GetInstance()->SetLimitTime(m_QuestData.limitTime);
	CTimer::GetInstance()->Reset();
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

// @brief 死亡可能回数の減少
void CQuest::SubPossibleDeathCount(void)
{
	// 死亡可能回数の減少
	m_QuestData.PossibleDeathCount--;
	if (m_QuestData.PossibleDeathCount < 0)
	{
		// クエスト失敗のテロップを表示
		// 仮でクエスト選択シーンに以降
		ChangeScene(SceneType::QuestSelect, TransitionType::Fade);
	}
}
