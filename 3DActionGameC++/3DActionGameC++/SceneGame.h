#pragma once
#include "SceneBase.h"
#include "Enums.h"
#include "Camera.h"

/*
* @brief ゲームシーンクラス
*/
class CSceneGame : public CSceneBase
{
public:
	//コンストラクタ
	CSceneGame();
	//デストラクタ
	~CSceneGame();
	//更新処理
	void Update(void)override;
	//描画処理
	void Draw(void)override;
private:
	//通常モードの更新処理
	void NormalUpdate(void);
	//通常モードの描画処理
	void NormalDraw(void);

private:
};

