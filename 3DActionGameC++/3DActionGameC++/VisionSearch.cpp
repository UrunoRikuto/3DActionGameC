/*=====================================================================
* @file VisionSearch.cpp
* @brief 視覚索敵の実装ファイル
=====================================================================*/


/* ヘッダーで使用するインクルード */
#include "NpcBase.h"
#include "Ray.h"

/* ヘッダーのインクルード */
#include "VisionSearch.h"

/* システム・要素のインクルード */
#include "Defines.h"
#include "GameValues.h"
#include "Main.h"
#include "SceneGame.h"
#include "Geometory.h"

// @brief コンストラクタ
// @param In_Self 自分自身のオブジェクト
CVisionSearch::CVisionSearch(CNpcBase* In_Self)
	: m_tDirection(0.0f, 0.0f, 1.0f) // 初期方向をZ軸正方向に設定
	, m_fDetectionValue(0.0f) // 初期発見値を0に設定
	, m_pSelfObject(In_Self)// 索敵を行うオブジェクトを設定
	, m_fLostTimer(0.0f) // 見失いタイマーを初期化
	, m_TrianglePoint{} // 三角形の頂点ポイントを初期化
	, m_pDetectionGauge(nullptr) // 索敵ゲージを初期化
{
	m_pRay = new CRay(); // レイ(光線)のインスタンスを生成
}

// @brief デストラクタ
CVisionSearch::~CVisionSearch()
{

}

// @brief 索敵処理
// @param In_SelfPosition 自身の位置
// @param In_CurrentSearchState 現在の索敵状態
// @return 更新後の索敵状態
VisionSearchState CVisionSearch::Search(const XMFLOAT3& In_SelfPosition, VisionSearchState In_CurrentSearchState)
{
	// 名前空間の使用
	using namespace GameValue::Npc;
	using namespace GameValue::VisionSearch;
	using namespace StructMath;

	// 視野角の更新
	UpdateViewAngle();

	// NPCの種類を取得
	NpcType npcType = m_pSelfObject->GetNpcType();
	//  NPCの種類によって視認距離を調整
	switch (npcType)
	{
	case NpcType::Normal:
		m_fViewDistance = Normal::VIEW_DISTANCE; // 通常NPCの視野距離を設定
		break;
	}

	// プレイヤーの姿勢状態を取得
	CPlayer* pTarget = m_pSelfObject->GetTarget();
	PlayerPosture playerPosture = pTarget->GetPosture();
	// プレイヤーの姿勢状態に応じて視認距離を調整
	switch (playerPosture)
	{
	case PlayerPosture::Stand:
		m_fViewDistance *= StealthCorrection::STAND; // 立ち姿勢の視認距離はそのまま
		break;
	case PlayerPosture::Crouch:
		m_fViewDistance *= StealthCorrection::CROUCH; // しゃがみ姿勢の視認距離を補正
		break;
	case PlayerPosture::Prone:
		m_fViewDistance *= StealthCorrection::PRONE; // 伏せ姿勢の視認距離を補正
		break;
	case PlayerPosture::Hide:
		m_fViewDistance *= StealthCorrection::HIDE; // 潜伏姿勢の視認距離を補正
		break;
	}

	// ターゲットの位置を取得
	XMFLOAT3 TargetPos = pTarget->GetPosition();

	// ターゲットとの距離を計算
	float distance = Distance(In_SelfPosition, TargetPos);

	// 索敵状態によって処理を分岐
	switch (In_CurrentSearchState)
	{
	case VisionSearchState::None:
		// ターゲットが視野距離内にいるかどうかをチェック
		if (distance < m_fViewDistance)
		{
			// ターゲットのいる位置
			m_pRay->SetOrigin(In_SelfPosition);
			// ターゲットの方向を計算
			m_pRay->SetDirection(Normalize(Sub(TargetPos, In_SelfPosition)));

			// 視野角内にターゲットがいるかどうかのチェック
			if (CheckTargetInViewAngle())
			{
				// ターゲットとの間に障害物があるかどうかのチェック
				if (CheckObstacle())
				{
					// ターゲットとの間に障害物がある場合は、異常なし状態を維持
					return VisionSearchState::None;
				}
				// 視認距離内にターゲットがいて、障害物がない場合は疑問状態に遷移
				return VisionSearchState::Doubt;
			}
		}
		break;
	case VisionSearchState::Doubt:
		// ターゲットが視野距離内にいるかどうかをチェック
		if (distance < m_fViewDistance)
		{
			// 視野角内にターゲットがいるかどうかのチェック
			if (CheckTargetInViewAngle())
			{
				// ターゲットとの間に障害物があるかどうかのチェック
				if (CheckObstacle())
				{
					// LostTimerを加算
					m_fLostTimer += 1.0f / fFPS;
				}
				else
				{
					// 発見値を増加
					// 発見値を増加させる。距離が近いほど増加量が大きくなるように調整
					m_fDetectionValue += 1.0f / fFPS * (m_fViewDistance / distance);
					
					// LostTimerをリセット
					m_fLostTimer = 0.0f;
				}

				// 見失い値が一定時間を超えた場合は見失い状態に遷移
				if (m_fLostTimer > LOST_TIME)
				{
					// LostTimerが一定時間を超えた場合は見失い状態に遷移
					// 発見値を一定割合減少させる
					m_fDetectionValue *= LOST_DETECTION_RATE;
					// LostTimerをリセット
					m_fLostTimer = 0.0f;

					return VisionSearchState::Lost;
				}
				// 発見値が最大値を超えた場合は発見状態に遷移
				if (m_fDetectionValue > MAX_DETECTION_TIME)
				{
					m_fDetectionValue = MAX_DETECTION_TIME; // 発見値を最大値に制限
					return VisionSearchState::Discovery; // 発見状態に遷移
				}
			}
		}
		// ゲージUIが生成されていない場合は生成
		if (m_pDetectionGauge == nullptr)
		{
			m_pDetectionGauge = new CGaugeUI(1.0f, true, GaugeType::Detection);
			// ゲージUIのパラメータ設定
			m_pDetectionGauge->SetParam({ 3.0f,2.0f,1.0f });
		}
		else
		{
			// ゲージUIの更新
			m_pDetectionGauge->Updatde(
				Add(In_SelfPosition, XMFLOAT3(0.0f, 3.0f, 0.0f)), // 自身の位置の少し上に表示
				m_fDetectionValue); // 発見値の割合を設定
		}

		break;
	case VisionSearchState::Lost:
		// ターゲットが視野距離内にいるかどうかをチェック
		if (distance < m_fViewDistance)
		{
			// 視野角内にターゲットがいるかどうかのチェック
			if (CheckTargetInViewAngle())
			{
				// ターゲットとの間に障害物があるかどうかのチェック
				if (CheckObstacle())
				{
					// LostTimerを加算
					m_fLostTimer += 1.0f / fFPS;
				}
				else
				{
					// 発見値を増加
					m_fDetectionValue += 1.0f / fFPS * (m_fViewDistance / distance);
				}
			}
		}
		else
		{
			// LostTimerを加算
			m_fLostTimer += 1.0f / fFPS;
			// 発見値をリセット
			m_fDetectionValue = 0.0f;
		}

		// 見失い値が一定時間を超えた場合は異常なし状態に遷移
		if (m_fLostTimer > LOST_TIME)
		{
			// LostTimerをリセット
			m_fLostTimer = 0.0f;
			// 発見値をリセット
			m_fDetectionValue = 0.0f;

			return VisionSearchState::None;
		}
		// 発見値が最大値を超えた場合は発見状態に遷移
		if (m_fDetectionValue > MAX_DETECTION_TIME)
		{
			// 発見値を最大値に制限
			m_fDetectionValue = MAX_DETECTION_TIME;
			// 発見状態に遷移
			return VisionSearchState::Discovery;
			// ゲージUIの削除
			if (m_pDetectionGauge != nullptr)
			{
				delete m_pDetectionGauge;
				m_pDetectionGauge = nullptr;
			}
		}
		break;
	case VisionSearchState::Discovery:
		// ターゲットが視野距離内にいるかどうかをチェック
		if (distance < m_fViewDistance)
		{
			return VisionSearchState::Discovery; // 発見状態を維持
		}
		else
		{
			// ターゲットが視野距離外に出た場合は見失い状態に遷移
			return VisionSearchState::Lost; // 見失い状態に遷移
		}
		break;

	}

	return In_CurrentSearchState;
}

// @brief デバック描画処理
void CVisionSearch::DebugDraw(void)
{
#ifdef _DEBUG

	SetRender3D();
	// 視野角(三角形)の描画
	// 三角形の頂点を結ぶ線を作成
	Geometory::AddLine(m_TrianglePoint[0], m_TrianglePoint[1], XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f));
	Geometory::AddLine(m_TrianglePoint[1], m_TrianglePoint[2], XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f));
	Geometory::AddLine(m_TrianglePoint[2], m_TrianglePoint[0], XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f));

	// ターゲットとの距離
	XMFLOAT3 selfPos = m_pSelfObject->GetPosition();
	XMFLOAT3 targetPos = m_pSelfObject->GetTarget()->GetPosition();
	XMFLOAT4 Color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	// 視認距離内にいる場合は赤色、いない場合は緑色で線を描画
	if (StructMath::Distance(selfPos, targetPos) < m_fViewDistance)
	{
		Color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	}
	Geometory::AddLine(selfPos, targetPos, Color);

	// 線の描画
	Geometory::DrawLines();

#endif // _DEBUG
}

// @brief 視野角の更新
void CVisionSearch::UpdateViewAngle(void)
{
	// 名前空間の使用
	using namespace GameValue::Npc;

	// 視野角
	float viewAngle = 60.0f;
	// 視野距離
	float viewDistance = 20.0f;

	// NPCの種類を取得
	NpcType npcType = m_pSelfObject->GetNpcType();
	//  NPCの種類によって視認距離と視野角を調整
	switch (npcType)
	{
	case NpcType::Normal:
		viewAngle = Normal::VIEW_ANGLE;
		viewDistance = Normal::VIEW_DISTANCE;
		break;
	}

	// 計算
	float angle = viewAngle / 2.0f;
	float height = viewDistance;

	// 索敵者の位置
	XMFLOAT3 selfPos = m_pSelfObject->GetPosition();
	XMVECTOR basePos = XMLoadFloat3(&selfPos);

	// 視野角の端をローカルで定義
	XMFLOAT3 limitPos[2] = {
		{height, 0.0f,  tanf(TORAD(angle)) * height},
		{height, 0.0f, -tanf(TORAD(angle)) * height}
	};

	// 視野角の端をワールド座標に変換
	float RotY = m_pSelfObject->GetRotation().y;
	// Y軸回転行列の作成
	XMMATRIX rotationMatrix = XMMatrixRotationY(TORAD(RotY));

	// 2つの頂点を変換
	for (int i = 0; i < 2; ++i)
	{
		XMVECTOR pos = XMLoadFloat3(&limitPos[i]);

		// 自キャラの位置を原点とした相対座標に変換して回転
		pos = XMVector3Transform(pos, rotationMatrix);

		// ワールド座標に戻す
		pos += basePos;

		XMStoreFloat3(&limitPos[i], pos);
	}

	// ターゲットの座標が視野角の範囲内にあるかどうかをチェック
	// 三角形の内外判定を使用して、視野角の範囲内にターゲットがいるかどうかを確認する
	m_TrianglePoint[0] = selfPos;
	m_TrianglePoint[1] = limitPos[0];
	m_TrianglePoint[2] = limitPos[1];
}

// @brief ターゲットが視認距離内にいるかどうかをチェック
// @return あった場合trueなかった場合false
bool CVisionSearch::CheckObstacle(void) const
{
	// 現在のシーンを取得
	CSceneGame* pSceneGame = static_cast<CSceneGame*>(GetCurrentScene());

	// フィールドオブジェクトのリストを取得
	for (auto object : pSceneGame->GetAllFieldObjects())
	{
		// オブジェクトのコリジョン情報を取得
		if (m_pRay->Cast(object->GetCollisionInfo(Collision::Tag::FieldObject)))
		{
			// 障害物があることを示す
			return true;
		}
	}

	// 障害物がないことを示す
	return false;
}

// @brief 視野角の範囲内にターゲットがいるかどうかをチェック
// @return 居た場合trueいなかった場合場合false
bool CVisionSearch::CheckTargetInViewAngle(void)
{
	// ターゲットの位置を取得
	XMFLOAT3 targetPos = m_pSelfObject->GetTarget()->GetPosition();

	// ターゲットが視野角の範囲内にあるかどうかをチェック
	if (CheckPointInTriangle(targetPos))
	{
		// ポイントが三角形の範囲内にあることを示す
		return true;
	}


	// ターゲットが視野角の範囲内にいないことを示す
	return false;
}

// @brief 視野角の範囲内にポイントがあるかどうかのチェック
// @param P 確認するポイント
// @param A 三角形の頂点
// @param B 三角形の頂点
// @param C 三角形の頂点
bool CVisionSearch::CheckPointInTriangle(const XMFLOAT3& Point) const
{
	// 名前空間の使用
	using namespace StructMath;

	// ベクトルの計算
	XMFLOAT3 v0 = Sub(m_TrianglePoint[1], m_TrianglePoint[0]);
	XMFLOAT3 v1 = Sub(m_TrianglePoint[2], m_TrianglePoint[0]);
	XMFLOAT3 v2 = Sub(Point, m_TrianglePoint[0]);
	// 内積の計算
	float dot00 = Dot(v0, v0);
	float dot01 = Dot(v0, v1);
	float dot02 = Dot(v0, v2);
	float dot11 = Dot(v1, v1);
	float dot12 = Dot(v1, v2);
	// バリューの計算
	float invDenom = 1.0f / (dot00 * dot11 - dot01 * dot01);
	float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
	float v = (dot00 * dot12 - dot01 * dot02) * invDenom;
	// ポイントが三角形の範囲内にあるかどうかをチェック
	if ((u >= 0) && (v >= 0) && (u + v <= 1))
	{
		// ポイントが三角形の範囲内にあることを示す
		return true;
	}
	return false;
}
