/*
* @file GameObject.h
* @brief ゲームオブジェクトの基底クラスのhファイル
* @author 宇留野陸斗
* @date 2025/08/04 クラスの作成
*/
#pragma once

/// <summary>
/// ゲームオブジェクトの基底クラス
/// </summary>
class CGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CGameObject();
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~CGameObject();

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw();
};

