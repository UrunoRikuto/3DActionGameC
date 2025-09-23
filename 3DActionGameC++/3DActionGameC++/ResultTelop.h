/*=====================================================================
* @file ResultTelop.h
* @brief リザルトテロップのhファイル
=====================================================================*/
#pragma once

/* 基底クラスのインクルード */
#include "TelopEffect.h"

/// <summary>
/// リザルトテロップのクラス
/// </summary>
class CResultTelop : public CTelopEffect
{
public:
	// コンストラクタ
	CResultTelop(bool IsWin);
	// デストラクタ
	~CResultTelop() override;
	// 更新処理
	bool Update() override;
	// 描画処理
	void Draw() override;
};

