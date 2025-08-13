/*
* @file NpcBase.cpp
* @brief NPCの基底クラスのCppファイル
* @author 宇留野陸斗
* @date 2025/08/04 NPCの基底クラスの実装
*/

/* ヘッダーのインクルード */
#include "NpcBase.h"
/* システム・要素のインクルード */

/// <summary>
/// 描画処理
/// </summary>
void CNpcBase::Draw(void)
{
	// 移動システムのデバッグ描画
	m_pMoveSystem->DebugDraw(XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));

	// 基底クラスの描画
	CGameObject::Draw();
}

// @brief 当たり判定の衝突時の処理
// @param InCollisionInfo 衝突対象
void CNpcBase::Hit(const Collision::Info& InCollisionInfo)
{
	// 今は何もしない
}
