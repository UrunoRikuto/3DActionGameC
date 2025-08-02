#pragma once

//シーンクラスのベースクラス
class CSceneBase
{
public:
	//コンストラクタ
	CSceneBase();
	//デストラクタ
	virtual ~CSceneBase();
	//更新処理
	virtual void Update(void) = 0;
	//描画処理
	virtual void Draw(void) = 0;

};