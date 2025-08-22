/*
* @file VisionSearch.cpp
* @brief VisionSensorクラスの実装ファイル
* @author 宇留野陸斗
* @date 2025/08/19 クラスの実装
*/



/* ヘッダーのインクルード */
#include "VisionSearch.h"

/* システム・要素のインクルード */
#include "Defines.h"

// @brief コンストラクタ
// @param In_Self 自分自身のオブジェクト
CVisionSearch::CVisionSearch(CNpcBase* In_Self)
	: m_tDirection(0.0f, 0.0f, 1.0f) // 初期方向をZ軸正方向に設定
	, m_fDetectionValue(0.0f) // 初期発見値を0に設定
	, m_fViewDistance(0.0f) // 視野距離をNPCの値から取得
	, m_pSelfObject(In_Self)// 索敵を行うオブジェクトを設定
	, m_pTargetObject(nullptr) // 索敵対象のオブジェクトを初期化
	, m_fLostTimer(0.0f) // 見失いタイマーを初期化
{
	m_pRay = new CRay(); // レイ(光線)のインスタンスを生成
}

// @brief デストラクタ
CVisionSearch::~CVisionSearch()
{

}

// @brief パラメーターの初期設定
// @param In_ViewDistance 視野距離
// @param In_TargetObject 索敵対象のオブジェクト
void CVisionSearch::InitParam(float In_ViewDistance, CPlayer* In_TargetObject)
{
	m_fViewDistance = In_ViewDistance; // 視野距離を設定
	m_pTargetObject = In_TargetObject; // 索敵対象のオブジェクトを設定
}

// @brief 索敵処理
// @param In_SelfPosition 自身の位置
// @param In_CurrentSearchState 現在の索敵状態
// @return 更新後の索敵状態
VisionSearchState CVisionSearch::Search(const XMFLOAT3& In_SelfPosition, VisionSearchState In_CurrentSearchState)
{
	// 名前空間の使用
	using namespace GameValue::Npc;
	using namespace GameValue::StealthCorrection;

	// NPCの種類を取得
	NpcType npcType = m_pSelfObject->GetNpcType();
	//  NPCの種類によって視認距離を調整
	switch (npcType)
	{
	case NpcType::Normal:
		m_fViewDistance = Normal::VIEW_DISTANCE; // 通常NPCの視野距離を設定
		break;
	case NpcType::Target:
		m_fViewDistance = Target::VIEW_DISTANCE; // ターゲットNPCの視野距離を設定
		break;
	case NpcType::Sniper:
		m_fViewDistance = Sniper::VIEW_DISTANCE; // スナイパーNPCの視野距離を設定
		break;
	case NpcType::Patrol:
		m_fViewDistance = Patrol::VIEW_DISTANCE; // 巡回NPCの視野距離を設定
		break;
	}

	// プレイヤーの姿勢状態を取得
	PlayerPosture playerPosture = m_pTargetObject->GetPosture();
	// プレイヤーの姿勢状態に応じて視認距離を調整
	switch (playerPosture)
	{
	case PlayerPosture::Stand:
		m_fViewDistance *= STAND_CORRECTION; // 立ち姿勢の視認距離はそのまま
		break;
	case PlayerPosture::Crouch:
		m_fViewDistance *= CROUCH_CORRECTION; // しゃがみ姿勢の視認距離を補正
		break;
	case PlayerPosture::Prone:
		m_fViewDistance *= PRONE_CORRECTION; // 伏せ姿勢の視認距離を補正
		break;
	case PlayerPosture::Hide:
		m_fViewDistance *= HIDE_CORRECTION; // 潜伏姿勢の視認距離を補正
		break;
	}

	// ターゲットの位置を取得
	XMFLOAT3 TargetPos = m_pTargetObject->GetPosition();

	// ターゲットとの距離を計算
	float distance = StructMath::Distance(In_SelfPosition, TargetPos);

	// ターゲットが視野距離内にいるかどうかをチェック
	if (distance < m_fViewDistance)
	{
		switch (In_CurrentSearchState)
		{
		case VisionSearchState::None:
			/// @Todo: 視野角の範囲内にターゲットがいるかどうかのチェック
			/// 三角形の内外判定を使用して、視野角の範囲内にターゲットがいるかどうかを確認する

			/// @Todo: ターゲットとの間に障害物があるかどうかのチェック
			/// レイキャストを使用してオブジェクトを検知する
			/// 検知できなかったら状態を疑問に変更
			/// 検知した場合何もしない
			
			// ターゲットのいる位置
			m_pRay->SetOrigin(In_SelfPosition);
			// ターゲットの方向を計算
			m_pRay->SetDirection(StructMath::Normalize(StructMath::Sub(TargetPos, In_SelfPosition)));

			// レイキャストを実行して、ターゲットとの間に障害物があるかどうかをチェック

			/// @Todo: フィールドオブジェクトのタグをもつオブジェクトをまとめる処理を作成する

			// if(m_pRay->Cast())

			return VisionSearchState::Doubt;
			break;
		case VisionSearchState::Doubt:
			/// @Todo: 視野角の範囲内にターゲットがいるかどうかのチェック
			/// 三角形の内外判定を使用して、視野角の範囲内にターゲットがいるかどうかを確認する

			/// @Todo: ターゲットとの間に障害物があるかどうかのチェック
			/// レイキャストを使用してオブジェクトを検知する
			/// 検知できなかったら発見値を進める
			/// 検知した場合、LostTimerを加算する
			m_fLostTimer += 1.0f / fFPS; // フレームレートに応じてタイマーを加算
			break;
		case VisionSearchState::Lost:
			/// @Todo: 視野角の範囲内にターゲットがいるかどうかのチェック
			/// 三角形の内外判定を使用して、視野角の範囲内にターゲットがいるかどうかを確認する
			/// 検知できなかった場合発見値を減少させる


			break;
		case VisionSearchState::Discovery:
			/// @Todo: 視認距離内なら常に発見状態
			/// @Todo: 視認距離外ならLostTimerを加算する
			m_fLostTimer += 1.0f / fFPS; // フレームレートに応じてタイマーを加算
			break;
		}
	}
	
	//switch (In_CurrentSearchState)
	//{
	//	// 索敵値をリセット
	//case VisionSearchState::None:
	//	m_fDetectionValue = 0.0f;
	//	break;
	//	// ターゲットが疑問の場合、索敵値を増加
	//case VisionSearchState::Doubt:
	//	float DetectionPower = 1.0f / fFPS * (m_fViewDistance / distance);
	//	m_fDetectionValue += DetectionPower;
	//	break;
	//	// ターゲットを見失った場合、索敵値を減少
	//case VisionSearchState::Lost:
	//	float DetectionPower = 1.0f / fFPS;
	//	m_fDetectionValue -= DetectionPower; 
	//	break;
	//	// ターゲットを発見した場合、索敵値を最大に設定
	//case VisionSearchState::Discovery:
	//	m_fDetectionValue = 1.0f; 
	//	break;
	//}

	//if (m_fDetectionValue > 1.0f)
	//{
	//	// 索敵値が最大値を超えた場合は1.0fに制限
	//	m_fDetectionValue = 1.0f;
	//	// ターゲットを発見した状態に遷移
	//	return VisionSearchState::Discovery;
	//}
	//else if (m_fDetectionValue < 0.0f)
	//{
	//	// 索敵値が0未満になった場合は0.0fに制限
	//	m_fDetectionValue = 0.0f;
	//	// ターゲットを見失った状態に遷移
	//	return VisionSearchState::None;
	//}
	
	return In_CurrentSearchState;
}

// @brief デバック描画処理
void CVisionSearch::DebugDraw(void)
{

}
