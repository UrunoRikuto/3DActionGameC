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
/* �w�b�_�[�̃C���N���[�h */
#include "SceneGame.h"
#include "Camera.h"

// @brief �R���X�g���N�^
CSceneGame::CSceneGame()
	:CSceneBase()
{
	m_pField = std::make_unique<CField>();
}

// @brief �f�X�g���N�^
CSceneGame::~CSceneGame()
{

}

// @brief �X�V����
void CSceneGame::Update(void)
{
	Camera::GetInstance()->Update();
	m_pField->Update();
}

// @brief �`�揈��
void CSceneGame::Draw(void)
{
	m_pField->Draw();
}