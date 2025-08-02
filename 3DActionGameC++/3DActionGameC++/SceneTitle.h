#pragma once
#include "SceneBase.h"
#include "SpriteDrawer.h"

/*
* @brief タイトルシーンクラス
*/
class CSceneTitle : public CSceneBase
{
public:
	//コンストラクタ
	CSceneTitle();
	//デストラクタ
	~CSceneTitle();
	//更新処理
	void Update(void) override;
	//描画処理
	void Draw(void) override;
private:
	//2D描画に必要なデータ
	ID3D11Buffer* m_pVtx;
	ID3D11ShaderResourceView* m_pTex;
};