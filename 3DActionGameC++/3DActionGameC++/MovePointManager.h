/*=====================================================================
* @file MovePointManager.h
* @brief �ړ��|�C���g�Ǘ��N���X�̃w�b�_�[�t�@�C��
=====================================================================*/

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
	void CreateData(StageType In_Type);

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

	/// <summary>
	/// �߂��̈ړ��|�C���g���擾
	/// </summary>
	/// <param name="In_Point">�w��ʒu</param>
	/// <returns>�w��ʒu�̋߂��̈ړ��|�C���g</returns>
	XMFLOAT3 NearMovePoint(const XMFLOAT3& In_Point) const;

	/// <summary>
	/// �w������Ɍ��肵���߂��̈ړ��|�C���g���擾
	/// </summary>
	/// <param name="In_Point">�w��ʒu</param>
	/// <param name="In_Dir">�w�����</param>
	/// <returns>�w������Ɍ��肵���߂��̈ړ��|�C���g</returns>
	XMFLOAT3 NearMovePointDir(const XMFLOAT3& In_Point, const XMFLOAT3& In_Dir) const;

	/// <summary>
	/// �ړ����[�g�̍쐬
	/// </summary>
	/// <param name="In_CurrentPoint">���݂̈ʒu</param>
	/// <param name="In_TargetPoint">�ړI�n</param>
	/// <returns>���݈ʒu����ړI�n�܂ł̈ړ����[�g</returns>
	std::vector<XMFLOAT3> CreateMoveRoute(const XMFLOAT3& In_CurrentPoint, const XMFLOAT3& In_TargetPoint) const;

private:

	/// <summary>
	/// �_�Ɛ����̋������v�Z
	/// </summary>
	/// <param name="In_Point">�_</param>
	/// <param name="In_SegmentStart">�����̊J�n�_</param>
	/// <param name="In_SegmentEnd">�����̍ŏI�_</param>
	/// <returns>�_�Ɛ����̋���</returns>
	float DistancePointSegment(const XMFLOAT3& In_Point, const XMFLOAT3& In_SegmentStart, const XMFLOAT3& In_SegmentEnd) const;

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

