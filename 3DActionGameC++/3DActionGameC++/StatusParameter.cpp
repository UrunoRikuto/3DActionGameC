/*=====================================================================
* @file StatusParameter.cpp
* @brief ステータスパラメーターの実装ファイル
=====================================================================*/

/* ヘッダーのインクルード */
#include "StatusParameter.h"

// @brief コンストラクタ
CStatusParameter::CStatusParameter()
	: m_nVitalityLevel(1)	// 生命力の初期値
	, m_nMuscleLevel(1)		// 筋力の初期値
	, m_nMentalLevel(1)		// 精神力の初期値
	, m_nEnduranceLevel(1)	// 持久力の初期値
	, m_nSkillLevel(1)		// 技量の初期値
{

}

// @brief デストラクタ
CStatusParameter::~CStatusParameter()
{

}

// @brief ステータスの初期化処理
void CStatusParameter::InitStatus(void)
{
	// すべてのステータスレベルを1に設定
	m_nVitalityLevel = 1;
	m_nMuscleLevel = 1;
	m_nMentalLevel = 1;
	m_nEnduranceLevel = 1;
	m_nSkillLevel = 1;
}

// @brief ステータスデータの読み込み処理
// @param In_DataPath データのフォルダパス
void CStatusParameter::LoadStatus(const std::string In_DataPath)
{
	// 今は未実装
	// 将来的にファイルからステータスデータを読み込む処理を実装する予定
	// JSONでの読み込みを想定
}

// @brief ステータスデータの保存処理
// @param In_DataPath 保存先のフォルダパス
void CStatusParameter::SaveStatus(const std::string In_DataPath)
{
	// 今は未実装
	// 将来的にファイルにステータスデータを保存する処理を実装する予定
	// JSONでの保存を想定
}

// @brief レベルアップ処理
// @param InType レベルアップさせる項目
void CStatusParameter::LevelUp(StatusParameterType InType)
{
	switch (InType)
	{
	case StatusParameterType::Vitality:		// 生命力
		m_nVitalityLevel++;
		break;
	case StatusParameterType::Muscle:		// 筋力
		m_nMuscleLevel++;
		break;
	case StatusParameterType::Mental:		// 精神力
		m_nMentalLevel++;
		break;
	case StatusParameterType::Endurance:	// 持久力
		m_nEnduranceLevel++;
		break;
	case StatusParameterType::Skill:		// 技量
		m_nSkillLevel++;
		break;
	}
}
