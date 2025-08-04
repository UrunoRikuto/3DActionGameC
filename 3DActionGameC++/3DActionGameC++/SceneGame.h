/*
* @file SceneGame.h
* @brief �Q�[���V�[���̃N���X�̃w�b�_�[�t�@�C��
* @author �F���엤�l
* @date 2025/08/04 �N���X�̍쐬
*/

#pragma once

/* ���N���X�̃C���N���[�h */
#include "SceneBase.h"

/* �O���錾 */
class CField;

/// <summary>
/// �Q�[���V�[���N���X
/// </summary>
class CSceneGame : public CSceneBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CSceneGame();
	
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CSceneGame();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update(void)override;
	
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw(void)override;

private:
	// �t�B�[���h�I�u�W�F�N�g�̃|�C���^
	std::unique_ptr<CField> m_pField;
};

