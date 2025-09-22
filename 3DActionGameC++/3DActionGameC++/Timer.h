/*=====================================================================
* @file Timer.h
* @brief タイマーのhファイル
=====================================================================*/
#pragma once

/* システム・要素のインクルード */
#include "SpriteDrawer.h"

/// <summary>
/// タイマークラス
/// </summary>
class CTimer
{
private://シングルトンパターン
	static CTimer* m_pInstance;
	// @brief コンストラクタ
	CTimer();
public:
	// @brief インスタンスの取得
	static CTimer* GetInstance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CTimer;
		}
		return m_pInstance;
	}
	// @brief インスタンスの削除
	static void DeleteInstance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	// @brief デストラクタ
	~CTimer();
	// @brief タイマーの更新
	// @return 制限時間を超えたか
	bool Update();

	// @brief タイマー描画
	void Draw();

	// @brief タイマーのリセット
	void Reset();

private:
	// @brief 経過時間
	float m_fElapsedTime = 0.0f;
	// @brief 制限時間
	float m_fLimitTime = 0.0f;

	// 2D描画に必要なデータ
	// 背景
	ID3D11Buffer* m_pGaugeBackVtx;
	ID3D11ShaderResourceView* m_pGaugeBackTex;
	// 前景
	ID3D11Buffer* m_pGaugeFrontVtx;
	ID3D11ShaderResourceView* m_pGaugeFrontTex;
public:
	// @brief 経過時間の取得
	// @return 経過時間
	float GetElapsedTime() const { return m_fElapsedTime; }
	// @brief 制限時間の取得
	// @return 制限時間
	float GetLimitTime() const { return m_fLimitTime; }
	// @brief 制限時間の設定
	// @param In_LimitTime 設定する制限時間
	void SetLimitTime(float In_LimitTime) { m_fLimitTime = In_LimitTime; }
};

