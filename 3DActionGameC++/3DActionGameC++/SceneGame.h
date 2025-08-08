/*
* @file SceneGame.h
* @brief ゲームシーンのクラスのヘッダーファイル
* @author 宇留野陸斗
* @date 2025/08/04 クラスの作成
*/

#pragma once

/* システム・要素のインクルード */
#include <memory>
/* 基底クラスのインクルード */
#include "SceneBase.h"

/* 前方宣言 */
class CField;
class CPlayer;
class CNpcBase;

/// <summary>
/// ゲームシーンクラス
/// </summary>
class CSceneGame : public CSceneBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CSceneGame();
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~CSceneGame();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(void)override;
	
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(void)override;

private:
	/// <summary>
	/// 当たり判定の衝突チェック
	/// </summary>
	void CollisionCheck(void);

	/// <summary>
	/// レイキャストのチェック
	/// </summary>
	void RayCastCheck(void);

private:
	// フィールドオブジェクトのポインタ
	std::vector<std::unique_ptr<CField>> m_pField;
	// プレイヤーオブジェクトのポインタ
	std::unique_ptr<CPlayer> m_pPlayer;
	// NPCオブジェクトのポインタ
	std::unique_ptr<CNpcBase> m_pNpc;
};

