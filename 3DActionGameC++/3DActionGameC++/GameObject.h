/*=====================================================================
* @file GameObject.h
* @brief ゲームオブジェクトの基底クラスのhファイル
=====================================================================*/
#pragma once

/* システム・要素のインクルード */
#include <memory>
#include "StructMath.h"
#include "Collision.h"
#include "Main.h"
#include "SceneGame.h"

/* 前方宣言 */
class Model;

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

	/// <summary>
	/// 当たり判定の衝突時の処理
	/// </summary>
	/// <param name="InCollisionInfo">衝突対象</param>
	virtual void Hit(const Collision::Info& InCollisionInfo) = 0;
	/// <summary>
	/// 当たり判定の衝突時の処理(攻撃用)
	/// </summary>
	/// <param name="InCollisionInfo">衝突対象</param>
	/// <param name="In_Attack">相手の攻撃力</param>
	virtual void Hit(const Collision::Info& InCollisionInfo,float In_Attack) = 0;

protected:
	/// <summary>
	/// モデルのポインタ
	/// </summary>
	std::unique_ptr<Model> m_pModel;

	/// <summary>
	/// 当たり判定情報
	/// </summary>
	std::vector<Collision::Info> m_tCollisionInfos;

	/// <summary>
	/// 位置情報
	///	</summary>
	XMFLOAT3 m_tPosition;

	/// <summary>
	/// Y軸の調整位置
	/// </summary>
	float m_fAjustPositionY;

	/// <summary>
	/// 大きさ情報
	/// </summary>
	XMFLOAT3 m_tScale;

	/// <summary>
	/// 回転情報
	/// </summary>
	XMFLOAT3 m_tRotation;

	/// <summary>
	/// オブジェクトが破棄されるかどうかのフラグ
	/// </summary>
	bool m_bDestroy;

public: // メンバ変数のアクセサ

	/// <summary>
	/// 当たり判定の取得
	/// </summary>
	/// <param name="InTag">当たり判定のタグ</param>
	/// <returns>当たり判定情報</returns>
	std::vector<Collision::Info> GetCollisionInfo(Collision::Tag InTag = Collision::Tag::All);

	/// <summary>
	/// 位置情報の設定
	/// </summary>
	/// <param name="position">新しい位置情報</param>
	void SetPosition(const XMFLOAT3& position);

	/// <summary>
	/// 位置情報の取得
	/// </summary>
	/// <returns>位置情報</returns>
	const XMFLOAT3& GetPosition() const { return m_tPosition; }

	/// <summary>
	/// スケール情報の設定
	/// </summary>
	/// <param name="scale">新しいスケール情報</param>
	void SetScale(const XMFLOAT3& scale);

	/// <summary>
	/// スケール情報の取得
	/// </summary>
	/// <returns>スケール情報</returns>
	const XMFLOAT3& GetScale() const { return m_tScale; }

	/// <summary>
	/// 回転情報の設定
	/// </summary>
	/// <param name="rotation">新しい回転情報</param>
	void SetRotation(const XMFLOAT3& rotation) { m_tRotation = rotation; }

	/// <summary>
	/// 回転情報の取得
	/// </summary>
	/// <returns>回転情報</returns>
	const XMFLOAT3& GetRotation() const { return m_tRotation; }

	/// <summary>
	/// オブジェクトが破棄されるかどうかのフラグの取得
	/// </summary>
	/// <returns>オブジェクトが破棄されるかどうか</returns>
	bool IsDestroy() const { return m_bDestroy; }
};

