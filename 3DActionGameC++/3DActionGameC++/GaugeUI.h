/*=====================================================================
* @file GaugeUI.h
* @brief �Q�[�WUI�̃t�@�C��
=====================================================================*/
#pragma once

/* �V�X�e���E�v�f�̃C���N���[�h */
#include "StructMath.h"
#include "Sprite.h"
#include "Texture.h"
#include "Enums.h"
#include <memory>

// @brief �Q�[�WUI�̃N���X
class CGaugeUI
{
public:
	// �R���X�g���N�^
	CGaugeUI(float In_Value, bool In_GaugeMode, GaugeType In_Type);
	// �f�X�g���N�^
	~CGaugeUI();
	// �X�V����
	void Updatde(const XMFLOAT3& In_Position, float In_Value);
	// �`�揈��
	void Draw(void);

	// �p�����[�^�̐ݒ�
	void SetParam(const XMFLOAT3& Scale = { 1.0f,1.0f,1.0f }, const XMFLOAT3& Rotate = { 0.0f,0.0f,0.0f }, const XMFLOAT3& AjustPosition = { 0.0f,0.0f,0.0f });
private:
	// �l
	float m_Value;
	// �ő�l
	float m_MaxValue;

	//�X�v���C�g�̃|�C���^
	std::unique_ptr<Sprite> m_pSprite;
	// �e�N�X�`���̃|�C���^
	std::unique_ptr<Texture> m_pTexture;

	// �ʒu�␳�l
	XMFLOAT3 m_AjustPosition;
	// �ʒu���W
	XMFLOAT3 m_Position;
	// �T�C�Y
	float m_fBaseSizeX;
	XMFLOAT3 m_Size;
	// ��]
	XMFLOAT3 m_Rotate;
	// UV�l
	XMFLOAT2 m_UV;
};
