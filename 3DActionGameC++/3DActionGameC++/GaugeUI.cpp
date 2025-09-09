/*=====================================================================
* @file GaugeUI.cpp
* @brief ゲージUI のファイル
=====================================================================*/
#include "GaugeUI.h"
#include "GameValues.h"
#include "Main.h"
#include "SpriteDrawSetting.h"

// @brief コンストラクタ
CGaugeUI::CGaugeUI(float In_Value, bool In_GaugeMode, GaugeType In_Type)
	: m_fBaseSizeX(0.0f)
	, m_AjustPosition({ 0.0f,0.0f,0.0f })
{
	m_pTexture = std::make_unique<Texture>();
	switch (In_Type)
	{
	case GaugeType::Health:
		m_pTexture->Create(TexturePath::HP_GAUGE_PATH);
		break;
	case GaugeType::Detection:
		m_pTexture->Create(TexturePath::DETECTION_GAUGE_PATH);
		break;
	}

	if (In_GaugeMode)
	{
		m_Value = 0.0f;
		m_MaxValue = In_Value;
	}
	else
	{
		m_Value = In_Value;
		m_MaxValue = In_Value;
	}

	m_UV = XMFLOAT2(m_Value / m_MaxValue, 0.0f);

	m_pSprite = std::make_unique<Sprite>();
}

// @brief デストラクタ
CGaugeUI::~CGaugeUI()
{

}

// @brief 更新処理
void CGaugeUI::Updatde(const XMFLOAT3& In_Position, float In_Value)
{
	// 値の更新
	m_Value = In_Value;

	// UV値の更新
	m_UV = XMFLOAT2(m_Value / m_MaxValue, 0.0f);

	// サイズ調整
	m_Size.x = m_fBaseSizeX * m_UV.x;

	// 位置の更新
	m_Position = {
		In_Position.x - (m_fBaseSizeX - m_Size.x)
		,In_Position.y
		,In_Position.z
	};
}

// @brief 描画処理
void CGaugeUI::Draw(void)
{
	// 名前空間の使用
	using namespace StructMath;

	SetRender3D();

	// テクスチャの設定
	m_pSprite->SetTexture(m_pTexture.get());

	//色を設定
	m_pSprite->SetColor({ 1.0f,1.0f,1.0f,1.0f });
	//描画設定
	CreateSpriteObject(Add(m_Position, m_AjustPosition) , m_Size, m_Rotate, { 1.0f,1.0f,1.0f,1.0f }, m_pSprite.get(), Camera::GetInstance(), true);
	//UV位置を設定
	m_pSprite->SetUVPos(m_UV);
	//UVサイズを設定
	m_pSprite->SetUVScale({ 2.0f ,1.0f });
	//描画
	m_pSprite->Draw();
	//設定を初期化
	m_pSprite->ReSetSprite();
}

// @brief パラメータの設定
// @param Scale スケール
// @param Rotate 回転
void CGaugeUI::SetParam(const XMFLOAT3& Scale, const XMFLOAT3& Rotate, const XMFLOAT3& AjustPosition)
{
	m_fBaseSizeX = Scale.x;
	m_Size = Scale;
	m_Rotate = Rotate;
	m_AjustPosition = AjustPosition;
}
