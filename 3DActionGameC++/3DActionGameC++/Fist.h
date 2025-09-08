/*=====================================================================
* @file Fist.h
* @brief 拳クラスヘッダーファイル
=====================================================================*/
#pragma once

/* 基底クラスのインクルード */
#include "Weapon.h"

//@brief 拳クラス
class CFist : public CWeapon
{
public:
	// @brief コンストラクタ
	CFist();

	// @brief デストラクタ
	virtual ~CFist();

	// @brief 更新
	// @param In_Position キャラクターの位置
	void Update(XMFLOAT3 In_Position) override;

protected:

	// @brief パラメータの設定
	void SetParam(void) override;
};

