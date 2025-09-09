/*=====================================================================
* @file GaugeUI.h
* @brief ゲージUIのファイル
=====================================================================*/
#pragma once

/* システム・要素のインクルード */
#include "StructMath.h"
#include "Sprite.h"
#include "Texture.h"
#include "Enums.h"
#include <memory>

// @brief ゲージUIのクラス
class CGaugeUI
{
public:
	// コンストラクタ
	CGaugeUI(float In_Value, bool In_GaugeMode, GaugeType In_Type);
	// デストラクタ
	~CGaugeUI();
	// 更新処理
	void Updatde(const XMFLOAT3& In_Position, float In_Value);
	// 描画処理
	void Draw(void);

	// パラメータの設定
	void SetParam(const XMFLOAT3& Scale = { 1.0f,1.0f,1.0f }, const XMFLOAT3& Rotate = { 0.0f,0.0f,0.0f }, const XMFLOAT3& AjustPosition = { 0.0f,0.0f,0.0f });
private:
	// 値
	float m_Value;
	// 最大値
	float m_MaxValue;

	//スプライトのポインタ
	std::unique_ptr<Sprite> m_pSprite;
	// テクスチャのポインタ
	std::unique_ptr<Texture> m_pTexture;

	// 位置補正値
	XMFLOAT3 m_AjustPosition;
	// 位置座標
	XMFLOAT3 m_Position;
	// サイズ
	float m_fBaseSizeX;
	XMFLOAT3 m_Size;
	// 回転
	XMFLOAT3 m_Rotate;
	// UV値
	XMFLOAT2 m_UV;
};
