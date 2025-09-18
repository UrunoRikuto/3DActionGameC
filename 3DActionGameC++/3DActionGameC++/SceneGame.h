/*
* @file SceneGame.h
* @brief ゲームシーンのクラスのヘッダーファイル
* @author 宇留野陸斗
* @date 2025/08/04 クラスの作成
*/

#pragma once

/* システム・要素のインクルード */
#include <memory>
#include "Collision.h"
#include "Weapon.h"
/* 基底クラスのインクルード */
#include "SceneBase.h"

/* 前方宣言 */
class CGameObject;
class CFieldObject;
class CPlayer;
class CNpcBase;

/// <summary>
/// ゲームシーンクラス
/// </summary>
class CSceneGame : public CSceneBase
{
private:
	// 闘技場ステージの初期化
	void InitArenaStage(void);
	// 平原ステージの初期化
	void InitPlainStage(void);

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

	/// <summary>
	/// すべてのフィールドオブジェクトを取得
	/// </summary>
	/// <returns>すべてのフィールドオブジェクトリスト</returns>
	std::vector<CGameObject*> GetAllFieldObjects(void);

	/// <summary>
	///  攻撃の生成
	/// </summary>
	void AttackCreate(AttackCollision In_CollisionInfo);

private:
	/// <summary>
	/// 当たり判定の衝突チェック
	/// </summary>
	void CollisionCheck(void);

	/// <summary>
	/// レイキャストのチェック
	/// </summary>
	void RayCastCheck(void);

	/// <summary>
	/// 攻撃の当たり判定チェック
	/// </summary>
	void AttackCollisionCheck(void);
private:
	// フィールドオブジェクト
	std::vector<std::unique_ptr<CFieldObject>> m_pFieldObject;
	// プレイヤーオブジェクトのポインタ
	std::unique_ptr<CPlayer> m_pPlayer;
	// NPCオブジェクトのポインタ
	std::vector<std::unique_ptr<CNpcBase>> m_pNpc;
	// 攻撃の当たり判定リスト
	std::vector<AttackCollision> m_vAttackCollisionInfos;
};
