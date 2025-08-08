/*
* @file RayCastTarget.h
* @brief レイキャストのターゲットクラスのヘッダーファイル
* @author 宇留野陸斗
* @date 2025/08/04 レイキャストのターゲットクラスの定義
*/
#pragma once

/* システム・要素のインクルード */
#include "StructMath.h"

/// <summary>
/// レイキャストのターゲットクラス
/// </summary>
class CRayCastTarget
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CRayCastTarget();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~CRayCastTarget();

	/// <summary>
	/// パラメーターの設定
	/// </summary>
	void SetParam(const XMFLOAT3& position, const XMFLOAT3& scale);
private:

	/// <summary>
	/// ターゲットの位置
	/// </summary>
	XMFLOAT3 m_tPosition;

	/// <summary>
	/// ターゲットのスケール
	/// </summary>
	XMFLOAT3 m_tScale;

public: //メンバ変数のアクセサ
	/// <summary>
	/// ターゲットの位置の設定
	/// </summary>
	/// <param name="position"></param>
	void SetPosition(const XMFLOAT3& position) { m_tPosition = position; }
	/// <summary>
	/// ターゲットの位置の取得
	/// </summary>
	/// <returns>ターゲットの位置</returns>
	const XMFLOAT3& GetPosition() const { return m_tPosition; }

	/// <summary>
	/// ターゲットのスケールの設定
	/// </summary>
	/// <param name="scale">スケール情報</param>
	void SetScale(const XMFLOAT3& scale) { m_tScale = scale; }

	/// <summary>
	/// ターゲットのスケールの取得
	/// </summary>
	/// <returns>ターゲットのスケール</returns>
	const XMFLOAT3& GetScale() const { return m_tScale; }
};

