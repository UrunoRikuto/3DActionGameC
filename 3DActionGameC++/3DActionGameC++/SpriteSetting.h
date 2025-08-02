#pragma once

class CSpriteSetting
{
public:
	//コンストラクタ
	CSpriteSetting();
	//デストラクタ
	~CSpriteSetting();
	//更新処理
	void Update(float InUV[][4], int InFrameTime, int InResetFrame, int InMaxFrame);
	//値のリセット
	void Reset(float InUV[][4]);
private:
	int   m_nAnimeFrame;	// アニメーション切り替えフレーム
	int	  m_nAnimeNo;		// 現在のUV配列の番号
	float m_fAnimeU;		// 現在のU値
	float m_fAnimeV;		// 現在のV値
public:
	//U値のGet
	float GetU(void) { return m_fAnimeU; }
	//V値のGet
	float GetV(void) { return m_fAnimeV; }
};