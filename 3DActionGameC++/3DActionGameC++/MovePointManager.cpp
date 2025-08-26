/*
* @file MovePointManager.cpp
* @brief �ړ��|�C���g�Ǘ��N���X�̎����t�@�C��
* @author �F���엤�l
* @date 2025/08/14 �ړ��|�C���g�Ǘ��N���X�̍쐬
*/

/* �w�b�_�[�̃C���N���[�h */
#include "MovePointManager.h"
/* �V�X�e���E�v�f�̃C���N���[�h */
#include "Model.h"
#include "Defines.h"
#include "GameValues.h"
#include "ModelDrawSetting.h"
#include "Main.h"

// �C���X�^���X�̏�����
std::unique_ptr<CMovePointManager> CMovePointManager::m_pInstance = nullptr;

// @brief �ړ��|�C���g�̍쐬
void CMovePointManager::CreateData(FieldType In_Type)
{
	// �t�B�[���h�̎�ނɉ����Ĉړ��|�C���g��ݒ�
	switch (In_Type)
	{
	case FieldType::Plain:
		// �����̈ړ��|�C���g��ݒ�
		m_MovePoints.push_back(XMFLOAT3(100.0f, 1.0f,100.0f));
		m_MovePoints.push_back(XMFLOAT3(100.0f, 1.0f,200.0f));
		m_MovePoints.push_back(XMFLOAT3(200.0f, 1.0f,100.0f));
		m_MovePoints.push_back(XMFLOAT3(300.0f, 1.0f,100.0f));
		m_MovePoints.push_back(XMFLOAT3(300.0f, 1.0f,200.0f));
		break;
	}

	m_pMovePointModels.resize(m_MovePoints.size());

	for (auto& model : m_pMovePointModels)
	{
		model = std::make_unique<Model>();
		model->Load(ModelPath::MOVE_POINT_PATH);
	}
}

// @brief �C���X�^���X���擾����֐�
// @details �C���X�^���X�����݂��Ȃ��ꍇ�͐V���ɍ쐬����
// @return �C���X�^���X�̃|�C���^
CMovePointManager* CMovePointManager::GetInstance(void)
{
	// �C���X�^���X�����݂��Ȃ��ꍇ�͐V���ɍ쐬
	if (!m_pInstance)
	{
		m_pInstance = std::make_unique<CMovePointManager>();
	}
	// �C���X�^���X�̃|�C���^��Ԃ�
	return m_pInstance.get();
}

// @brief �R���X�g���N�^
CMovePointManager::CMovePointManager()
{

}

// @brief �f�X�g���N�^
CMovePointManager::~CMovePointManager()
{

}

// @brief �f�o�b�N�`�揈��
void CMovePointManager::DebugDraw(void)
{
#ifdef _DEBUG
	SetRender3D();
	for (int i = 0; i < m_pMovePointModels.size(); i++)
	{
		CreateObject(
			m_MovePoints[i],			// �ʒu
			StructMath::FtoF3(1.0f),// �X�P�[��
			StructMath::FtoF3(0.0f),// ��]
			m_pMovePointModels[i].get(),			// ���f���|�C���^
			Camera::GetInstance(),	// �J�����|�C���^
			true,					// ���邭���邩�ǂ���
			XMFLOAT3(0.5f, 0.5f, 0.5f) // ���C�e�B���O�F
		);
	}
#endif // _DEBUG
}
