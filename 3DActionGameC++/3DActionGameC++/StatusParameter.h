/*=====================================================================
* @file StatusParameter.h
* @brief ステータスパラメーターのヘッダーファイル
=====================================================================*/
#pragma once

/* システム・要素のインクルード */
#include "Enums.h"
#include "Defines.h"
#include "GameValues.h"
#include <string>

/// <summary>
/// ステータスパラメーターのクラス
/// </summary>
class CStatusParameter
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CStatusParameter();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~CStatusParameter();

	/// <summary>
	/// ステータスの初期化処理
	/// </summary>
	void InitStatus(void);

	/// <summary>
	/// ステータスデータの読み込み処理
	/// </summary>
	/// <param name="In_DataPath">データのファイルパス</param>
	void LoadStatus(const std::string In_DataPath);

	/// <summary>
	/// ステータスデータの保存処理
	/// </summary>
	/// <param name="In_DataPath">保存先のファイルパス</param>
	void SaveStatus(const std::string In_DataPath);

	/// <summary>
	/// レベルアップ処理
	/// </summary>
	/// <param name="InType">レベルアップさせる項目</param>
	void LevelUp(StatusParameterType InType);

private:

	/// <summary>
	/// 生命力
	/// </summary>
	int m_nVitalityLevel;

	/// <summary>
	/// 筋力
	/// </summary>
	int m_nMuscleLevel;

	/// <summary>
	/// 精神力
	/// </summary>
	int m_nMentalLevel;

	/// <summary>
	/// 持久力
	/// </summary>
	int m_nEnduranceLevel;

	/// <summary>
	/// 技量
	/// </summary>
	int m_nSkillLevel;

public: // メンバ変数のアクセサ

	/// <summary>
	/// 生命力レベルの取得
	/// </summary>
	/// <returns>生命力レベル</returns>
	int GetVitalityLevel(void) const { return m_nVitalityLevel; };

	/// <summary>
	/// 筋力レベルの取得
	/// </summary>
	/// <returns>筋力レベル</returns>
	int GetMuscleLevel(void) const { return m_nMuscleLevel; };

	/// <summary>
	/// 精神力レベルの取得
	/// </summary>
	/// <returns>精神力レベル</returns>
	int GetMentalLevel(void) const { return m_nMentalLevel; };

	/// <summary>
	/// 持久力レベルの取得
	/// </summary>
	/// <returns>持久力レベル</returns>
	int GetEnduranceLevel(void) const { return m_nEnduranceLevel; };

	/// <summary>
	/// 技量レベルの取得
	/// </summary>
	/// <returns>技量レベル</returns>
	int GetSkillLevel(void) const { return m_nSkillLevel; };
};
