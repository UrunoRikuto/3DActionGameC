/*
* @file Bullet.cpp
* @brief 弾丸クラスの実装ファイル
* @author 宇留野陸斗
* * @date 2025/08/16 クラスの実装
*/

/* ヘッダーのインクルード */
#include "Bullet.h"
/* システム・要素のインクルード */
#include "Model.h"

// @brief コンストラクタ
CBullet::CBullet()
	:CGameObject() // 基底クラスのコンストラクタを呼び出す
	, m_tDirection(0.0f, 0.0f, 0.0f) // 初期進行方向を設定
	, m_fMovePower(0.1f) // 初期移動力を設定
	, m_fLifeTime(0.0f) // 弾の生存時間を設定
{
	// モデルの生成
	m_pModel = std::make_unique<Model>();
	// モデルの読み込み
	if (!m_pModel->Load(MODEL_PATH("Bullet.obj"), 0.01f))
	{
		MessageBox(NULL, "弾丸モデルの読み込みに失敗しました。", "Error", MB_OK);
	}

	// 位置、スケール、回転の設定
	m_tScale = { 1.0f, 1.0f, 1.0f };
	m_tPosition = { 0.0f, 0.0f - (m_tScale.y / 2), 0.0f };
	m_tRotation = { 0.0f, 0.0f, 0.0f };

	// 当たり判定情報の初期化
	// 当たり判定情報のサイズを1に設定
	m_tCollisionInfos.resize(1);
	// 当たり判定の種類を設定
	m_tCollisionInfos[0].type = Collision::Type::eBox;
	// タグを追加
	m_tCollisionInfos[0].tag.push_back(Collision::Tag::Field);
	// 中心位置を設定
	m_tCollisionInfos[0].box.center = m_tPosition;
	// ボックスの大きさを設定
	m_tCollisionInfos[0].box.size = m_tScale;
}

// @brief デストラクタ
CBullet::~CBullet()
{

}

// @brief 更新処理
void CBullet::Update(void)
{
	// 名前空間の仕様
	using namespace GameValue::Bullet;

	// 弾丸の位置を進行方向に沿って更新
	m_tPosition = StructMath::Add(m_tPosition, StructMath::Mul(m_tDirection, m_fMovePower));

	// 生存時間を更新
	m_fLifeTime += 1.0f / fFPS;

	// 生存時間が一定時間を超えたら弾丸を削除
	if (m_fLifeTime > LIFE_TIME) // 5秒で弾丸を削除
	{
		// 自分を削除
		delete this; // メモリリークを防ぐために自分自身を削除
		return;
	}
}

// @brief パラメーターの設定
// @param direction 進行方向
// @param movePower 移動力
void CBullet::SetParam(const XMFLOAT3& direction, float movePower)
{
	m_tDirection = direction; // 進行方向を設定
	m_fMovePower = movePower; // 移動力を設定
}

// @brief 当たり判定の衝突時の処理
// @param InCollisionInfo 衝突対象
void CBullet::Hit(const Collision::Info& InCollisionInfo)
{
	// 衝突した場合、弾丸を削除
	delete this; // メモリリークを防ぐために自分自身を削除
}
