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
* @param 0：ループ移動
* ...最終ポイントまで行ったら最終ポイントから最初のポイントまで移動して再度移動 
* @param 1：反転移動
* ...最終ポイントまで行ったら反転して最初のポイントまで移動して移動
*/
enum class MoveSystemType
{
	Loop,
	Reverse,
};