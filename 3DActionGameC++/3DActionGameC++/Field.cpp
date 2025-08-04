/*
* @file Field.cpp
* @brief �t�B�[���h�I�u�W�F�N�g�̃N���X��Cpp�t�@�C��
* @author �F���엤�l
* @date 2025/08/04 �N���X�̎���
*/


/* �w�b�_�[�ŗ��p����V�X�e���̃C���N���[�h */
#include <memory>
/* �R���|�[�l���g�̃C���N���[�h */
#include "Model.h"
/* �w�b�_�[�̃C���N���[�h */
#include "Field.h"
/* �V�X�e���̃C���N���[�h */
#include "Main.h"
#include "ModelDrawSetting.h"
#include "StructMath.h"

// @brief �R���X�g���N�^
CField::CField()
{
	// ���f���̐���
	m_pModel = std::make_unique<Model>();
	// ���f���̓ǂݍ���
	if (!m_pModel->Load(MODEL_PATH("BattleStage_Field.obj")))
	{
		MessageBox(NULL, "�t�B�[���h���f���̓ǂݍ��݂Ɏ��s���܂����B", "Error", MB_OK);
	}
}

// @brief �f�X�g���N�^
CField::~CField()
{

}

// @brief �X�V����
void CField::Update(void)
{

}

// @brief �`�揈��
void CField::Draw(void)
{
	// ���f���̕`��
	SetRender3D();
	CreateObject(
		XMFLOAT3(0.0f,0.0f,0.0f), // �ʒu
		XMFLOAT3(100.0f,1.0f,100.0f), // �X�P�[��
		XMFLOAT3(0.0f,0.0f,0.0f), // ��]
		XMFLOAT3(1.0f,1.0f,1.0f), // �F
		m_pModel.get(),       // ���f���|�C���^
		Camera::GetInstance(),// �J�����|�C���^
		false                 // ���邭���邩�ǂ���
	);

}
