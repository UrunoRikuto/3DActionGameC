/*
* @file MovePointManager.h
* @brief �ړ��|�C���g�Ǘ��N���X�̃w�b�_�[�t�@�C��
* @author �F���엤�l
* @date 2025/08/14 �ړ��|�C���g�Ǘ��N���X�̍쐬
*/

#pragma once

/* �V�X�e���E�v�f�̃C���N���[�h */
#include <vector>
#include <memory>
#include "Enums.h"
#include "StructMath.h"
#include "Model.h"

/// <summary>
/// �ړ��|�C���g�Ǘ��N���X
/// </summary>
class CMovePointManager
{
private:
	/// <summary>
	/// �Ǘ��N���X�̃C���X�^���X
	/// </summary>
	static std::unique_ptr<CMovePointManager> m_pInstance;
public:
	
	/// <summary>
	/// �ړ��|�C���g�ƃC���X�^���X�̍쐬
	/// </summary>
	/// <param name="In_Type">�t�B�[���h�̎��</param>
	void CreateData(FieldType In_Type);

	/// <summary>
	/// �C���X�^���X���擾
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static CMovePointManager* GetInstance(void);

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CMovePointManager();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CMovePointManager();

	/// <summary>
	/// �f�o�b�N�`�揈��
	/// </summary>
	void DebugDraw(void);

private:
	/// <summary>
	/// �ړ��|�C���g�̍��W
	/// </summary>
	std::vector<XMFLOAT3> m_MovePoints;

	/// <summary>
	/// �ړ��|�C���g�̃��f��
	/// </summary>
	std::vector<std::unique_ptr<Model>> m_pMovePointModels;

public:// �A�N�Z�T
	/// <summary>
	/// �ړ��|�C���g�̍��W���擾
	/// </summary>
	/// <returns>�ړ��|�C���g�̍��W</returns>
	const std::vector<XMFLOAT3>& GetMovePoints(void) const { return m_MovePoints; }
};

