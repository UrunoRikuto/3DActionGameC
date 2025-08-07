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
#include "TargetNpc.h"
/* �w�b�_�[�̃C���N���[�h */
#include "SceneGame.h"
/* �V�X�e���E�v�f�̃C���N���[�h */
#include "Camera.h"
#include "Defines.h"

/* �O���[�o���ϐ� */
std::vector<CGameObject*> g_vNullCheckList; // Null�`�F�b�N�p�̃Q�[���I�u�W�F�N�g�̃��X�g

// @brief �R���X�g���N�^
CSceneGame::CSceneGame()
	:CSceneBase()
{
	// �t�B�[���h�̐���
	m_pField = std::make_unique<CField>();
	// �v���C���[�̐���
	m_pPlayer = std::make_unique<CPlayer>();
	// NPC�̐����i�^�[�Q�b�gNPC�j
	m_pNpc = std::make_unique<CTargetNpc>();

	g_vNullCheckList.push_back(m_pField.get()); // �t�B�[���h��Null�`�F�b�N�p���X�g�ɒǉ�
	g_vNullCheckList.push_back(m_pPlayer.get()); // �v���C���[��Null�`�F�b�N�p���X�g�ɒǉ�
	g_vNullCheckList.push_back(m_pNpc.get()); // NPC��Null�`�F�b�N�p���X�g�ɒǉ�
}

// @brief �f�X�g���N�^
CSceneGame::~CSceneGame()
{

}

// @brief �X�V����
void CSceneGame::Update(void)
{
	for(auto& obj : g_vNullCheckList)
	{
		if (SafeNullCheck(obj))
		{
			obj->Update(); // Null�`�F�b�N���s���A�I�u�W�F�N�g���L���ȏꍇ�̂ݍX�V�������Ăяo��
		}
	}

	//// �t�B�[���h�̍X�V����
	//if (m_pField)m_pField->Update();
	//// �v���C���[�̍X�V����
	//if (m_pPlayer)m_pPlayer->Update();
	//// NPC�̍X�V����
	//if (m_pNpc)m_pNpc->Update();

	//(��)�v���C���[�̐^���̒n�ʂ̍�����ݒ�
	m_pPlayer->SetUnderHeight(m_pField->GetPosition().y + m_pField->GetScale().y / 2.0f);
}

// @brief �`�揈��
void CSceneGame::Draw(void)
{
	for (auto& obj : g_vNullCheckList)
	{
		if (SafeNullCheck(obj))
		{
			obj->Draw(); // Null�`�F�b�N���s���A�I�u�W�F�N�g���L���ȏꍇ�̂ݕ`�揈�����Ăяo��
		}
	}

	//// �t�B�[���h�̕`�揈��
	//m_pField->Draw();
	//// �v���C���[�̕`�揈��
	//m_pPlayer->Draw();
	//// NPC�̕`�揈��
	//m_pNpc->Draw();
}