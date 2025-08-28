/*
* @file Enums.h
* @brief 列挙型の定義ファイル
* @author 宇留野陸斗
*/
#pragma once

/*
* @brief シーンの種類
* @param 0：タイトル
* @param 1：ゲーム
*/
enum class SceneType
{
	Title,
	Game,
	MAX,
};

/*
* @brief プレイヤーの行動モード
* @param 0：移動モード
* @param 1：狙撃モード
*/
enum class PlayerActionMode
{
	Move,		// 移動モード
	Sniping,	// 狙撃モード
	MAX,
};


/*
* @brief 移動システムの種類
* @param 0：一回移動
* ...最終ポイントまで行ったら止まる
* @param 1：ループ移動
* ...最終ポイントまで行ったら最終ポイントから最初のポイントまで移動して再度移動 
* @param 2：反転移動
* ...最終ポイントまで行ったら反転して最初のポイントまで移動して移動
*/
enum class MoveSystemType
{
	Once,
	Loop,
	Reverse,
};

/*
* @brief フィールドの種類
* @param 0：平原
*/
enum class FieldType
{
	Plain,	// 平原
	MAX,
};

/*
* @brief 視覚索敵の状態
* @param 0：異常なし
* @param 1：疑問
* @param 2: 見失う
* @param 3：発見
*/
enum class VisionSearchState
{
	None,		// 異常なし
	Doubt,		// 疑問
	Lost,		// 見失う
	Discovery,	// 発見
	MAX,
};

/*
* @brief プレイヤーの姿勢の種類
* @param 0：立ち
* @param 1：しゃがみ
* @param 2：伏せ
* @param 3：潜伏
*/
enum class PlayerPosture
{
	Stand,		// 立ち
	Crouch,		// しゃがみ
	Prone,		// 伏せ
	Hide,		// 潜伏
	MAX,
};

/*
* @brief NPCの種類
* @param 0：通常NPC
* @param 1：ターゲットNPC
* @param 2：スナイパーNPC
* @param 3：巡回NPC
*/
enum class NpcType
{
	Normal,		// 通常NPC
	Target,		// ターゲットNPC
	Sniper,		// スナイパーNPC
	Patrol,		// 巡回NPC
	MAX,
};