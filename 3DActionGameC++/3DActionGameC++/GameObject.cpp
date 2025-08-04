/*
* @file GameObject.cpp
* @brief ゲームオブジェクトの基底クラスのCppファイル
* @author 宇留野陸斗
* @date 2025/08/04 クラスの実装
*/

/* ヘッダーで利用するシステム・要素のインクルード */
#include "Model.h"

/* ヘッダーのインクルード */
#include "GameObject.h"

// @brief コンストラクタ
CGameObject::CGameObject()
	: m_pModel(nullptr) // モデルポインタの初期化
	, m_tPosition(0.0f, 0.0f, 0.0f) // 初期位置
	, m_tScale(1.0f, 1.0f, 1.0f) // 初期スケール
	, m_tRotation(0.0f, 0.0f, 0.0f) // 初期回転
{
	
}

// @brief デストラクタ
CGameObject::~CGameObject()
{

}

// @brief 更新処理
void CGameObject::Update()
{

}

// @brief 描画処理
void CGameObject::Draw()
{

}
