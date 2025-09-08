/*=====================================================================
* @file Sword.h
* @brief 剣クラス定義ファイル
=====================================================================*/
#pragma once

/* 基底クラスのインクルード */
#include "Weapon.h"

//@brief 剣クラス
class CSword : public CWeapon
{
public:
	// @brief コンストラクタ
	CSword();

	// @brief デストラクタ
	virtual ~CSword();

	// @brief 更新
	// @param In_Position キャラクターの位置
	void Update(XMFLOAT3 In_Position) override;

protected:

	// @brief パラメータの設定
	void SetParam(void) override;
};

