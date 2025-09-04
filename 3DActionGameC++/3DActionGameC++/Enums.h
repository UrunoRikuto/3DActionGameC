/*=====================================================================
* @file Enums.h
* @brief 列挙型の定義ファイル
=====================================================================*/
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

/*
* @brief ステータスパラメータの種類
* @param 0：生命力
* @param 1：筋力
* @param 2：精神力
* @param 3：持久力
* @param 4：技量
*/
enum class StatusParameterType
{
	Vitality,	// 生命力
	Muscle,		// 筋  力
	Mental,		// 精神力
	Endurance,	// 持久力
	Skill,		// 技  量
	MAX,
};

/*
* @brief 攻撃の種類
* @param 0：斬る
* @param 1：刺す
* @param 2：打つ
* @param 3：撃つ
*/
enum class AttackType
{
	Slash,	// 斬る
	Stab,	// 刺す
	Blow,	// 打つ
	Shoot,	// 撃つ
};