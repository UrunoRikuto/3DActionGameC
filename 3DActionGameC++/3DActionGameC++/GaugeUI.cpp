/*=====================================================================
* @file GaugeUI.cpp
* @brief �Q�[�WUI �̃t�@�C��
=====================================================================*/
#include "GaugeUI.h"
#include "GameValues.h"
#include "Main.h"
#include "SpriteDrawSetting.h"

// @brief �R���X�g���N�^
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

// @brief �f�X�g���N�^
CGaugeUI::~CGaugeUI()
{

}

// @brief �X�V����
void CGaugeUI::Updatde(const XMFLOAT3& In_Position, float In_Value)
{
	// �l�̍X�V
	m_Value = In_Value;

	// UV�l�̍X�V
	m_UV = XMFLOAT2(m_Value / m_MaxValue, 0.0f);

	// �T�C�Y����
	m_Size.x = m_fBaseSizeX * m_UV.x;

	// �ʒu�̍X�V
	m_Position = {
		In_Position.x - (m_fBaseSizeX - m_Size.x)
		,In_Position.y
		,In_Position.z
	};
}

// @brief �`�揈��
void CGaugeUI::Draw(void)
{
	// ���O��Ԃ̎g�p
	using namespace StructMath;

	SetRender3D();

	// �e�N�X�`���̐ݒ�
	m_pSprite->SetTexture(m_pTexture.get());

	//�F��ݒ�
	m_pSprite->SetColor({ 1.0f,1.0f,1.0f,1.0f });
	//�`��ݒ�
	CreateSpriteObject(Add(m_Position, m_AjustPosition) , m_Size, m_Rotate, { 1.0f,1.0f,1.0f,1.0f }, m_pSprite.get(), Camera::GetInstance(), true);
	//UV�ʒu��ݒ�
	m_pSprite->SetUVPos(m_UV);
	//UV�T�C�Y��ݒ�
	m_pSprite->SetUVScale({ 2.0f ,1.0f });
	//�`��
	m_pSprite->Draw();
	//�ݒ��������
	m_pSprite->ReSetSprite();
}

// @brief �p�����[�^�̐ݒ�
// @param Scale �X�P�[��
// @param Rotate ��]
void CGaugeUI::SetParam(const XMFLOAT3& Scale, const XMFLOAT3& Rotate, const XMFLOAT3& AjustPosition)
{
	m_fBaseSizeX = Scale.x;
	m_Size = Scale;
	m_Rotate = Rotate;
	m_AjustPosition = AjustPosition;
}
