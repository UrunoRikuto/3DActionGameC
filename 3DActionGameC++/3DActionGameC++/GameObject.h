/*
* @file GameObject.h
* @brief �Q�[���I�u�W�F�N�g�̊��N���X��h�t�@�C��
* @author �F���엤�l
* @date 2025/08/04 �N���X�̍쐬
*/
#pragma once

/// <summary>
/// �Q�[���I�u�W�F�N�g�̊��N���X
/// </summary>
class CGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CGameObject();
	
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~CGameObject();

	/// <summary>
	/// �X�V����
	/// </summary>
	virtual void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	virtual void Draw();
};

