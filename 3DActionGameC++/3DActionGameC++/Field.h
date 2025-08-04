/*
* @file Field.h
* @brief �t�B�[���h�I�u�W�F�N�g�̃N���X�̃w�b�_�[�t�@�C��
* @author �F���엤�l
* @date 2025/08/04 �N���X�̍쐬
*/
#pragma once

/* ���N���X�̃C���N���[�h */
#include "GameObject.h"

/* �O���錾 */
class Model;

/// <summary>
/// �t�B�[���h�I�u�W�F�N�g�̃N���X
/// </summary>
class CField : public CGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CField();
	
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CField();
	
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update(void) override;

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw(void) override;

private:
	// ���f���̃|�C���^
	std::unique_ptr<Model> m_pModel; // �t�B�[���h�̃��f��
};

