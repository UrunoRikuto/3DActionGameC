/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
* file：Transition.h
*
* 概要：トランジションの基底クラスを管理するファイル
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/

#pragma once
#include "SpriteDrawer.h"

/// <summary>
/// トランジションの基底クラス
/// </summary>
class CTransition
{
public:
	// コンストラクタ
	CTransition() = default;
	// デストラクタ
	virtual ~CTransition() = default;
	// 更新
	virtual void Update() = 0;
	// 描画
	virtual void Draw() = 0;
protected:
	// 2D描画に必要なデータ
	ID3D11Buffer* m_pVtx;
	ID3D11ShaderResourceView* m_pTex;
	// フェード完了フラグ
	bool m_bEnd = false;
	// チェンジフラグ(切り替えしのタイミング)
	bool m_bChange = false;
public:
	// フェード完了フラグの取得
	bool IsEnd() const { return m_bEnd; }
	// チェンジフラグの取得
	bool IsChange() const { return m_bChange; }
	// チェンジフラグの設定
	void SetChange(bool change) { m_bChange = change; }
};

