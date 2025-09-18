/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
* file：Fade.h
*
* 概要：フェード処理を管理するファイル
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/

#pragma once
#include "Transition.h"

/// <summary>
/// フェード処理を管理するクラス
/// </summary>
class CFade : public CTransition
{
public:
	// コンストラクタ
	CFade(float In_MaxFadeTime);
	// デストラクタ
	~CFade() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;
private:
	// アルファ値
	float m_fAlpha;
	// フェードインアウトの時間
	float m_fTime;
	// フェードアウトフラグ
	bool m_bFadeOut; // trueならフェードアウト、falseならフェードイン
};

