/*
* @file SceneGame.cpp
* @brief �Q�[���V�[���̃N���X��Cpp�t�@�C��
* @author �F���엤�l
* @date 2025/08/04 �N���X�̎���
*/

/* �w�b�_�[�ŗ��p����V�X�e���̃C���N���[�h */
#include <memory>
/* �Q�[���I�u�W�F�N�g�̃C���N���[�h */
#include "Field.h"
#include "Player.h"
/* �w�b�_�[�̃C���N���[�h */
#include "SceneGame.h"
#include "Camera.h"

// @brief �R���X�g���N�^
CSceneGame::CSceneGame()
	:CSceneBase()
{
	// �t�B�[���h�̐���
	m_pField = std::make_unique<CField>();
	// �v���C���[�̐���
	m_pPlayer = std::make_unique<CPlayer>();
}

// @brief �f�X�g���N�^
CSceneGame::~CSceneGame()
{

}

// @brief �X�V����
void CSceneGame::Update(void)
{
	// �t�B�[���h�̍X�V����
	if (m_pField)m_pField->Update();
	// �v���C���[�̍X�V����
	if (m_pPlayer)m_pPlayer->Update();

	//(��)�v���C���[�̐^���̒n�ʂ̍�����ݒ�
	m_pPlayer->SetUnderHeight(m_pField->GetPosition().y + m_pField->GetScale().y / 2.0f);
}

// @brief �`�揈��
void CSceneGame::Draw(void)
{
	// �t�B�[���h�̕`�揈��
	m_pField->Draw();
	// �v���C���[�̕`�揈��
	m_pPlayer->Draw();
}