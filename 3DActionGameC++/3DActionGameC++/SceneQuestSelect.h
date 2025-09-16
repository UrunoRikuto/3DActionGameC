/*=====================================================================
* @file SceneQuestSelect.h
* @brief �N�G�X�g�I���V�[���N���X�̃w�b�_�[�t�@�C��
=====================================================================*/

#pragma once

/* ���N���X�̃C���N���[�h */
#include "SceneBase.h"

/* �V�X�e���E�v�f�̃C���N���[�h */
#include <vector>
#include "Quest.h"
#include "SpriteDrawer.h"

/// <summary>
/// �N�G�X�g�I���V�[���N���X
/// </summary>
class CSceneQuestSelect : public CSceneBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CSceneQuestSelect();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CSceneQuestSelect();
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update(void)override;
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw(void)override;

private:
	// @brief Y���W�̃����_���I��
	float RandomSelectPosY();

private:

	// @brief ���ݑI�𒆂̃C���f�b�N�X
	int m_CurrentIndex;

	// @brief �N�G�X�g�̃��X�g
	std::vector<QuestData> m_QuestList;

	//2D�`��ɕK�v�ȃf�[�^
	// �w�i
	ID3D11Buffer* m_pBackGroundVtx;
	ID3D11ShaderResourceView* m_pBackGroundTex;
	// �N�G�X�g�˗���
	ID3D11Buffer* m_pQuestPaperVtx;
	ID3D11ShaderResourceView* m_pQuestPaperTex[(int)QuestType::MAX];

	std::vector<float> m_RandPosY;
};
