/*
* @file MoveSystem.h
* @brief �ړ��V�X�e���̒�`�t�@�C��
* @author �F���엤�l
* @date 2025/08/13 �ړ��V�X�e���N���X�̒�`
*            08/14 Y���W�̒����l��ǉ�
*/
#pragma once

/* �V�X�e���E�v�f�̃C���N���[�h */
#include <memory>
#include <vector>
#include "StructMath.h"
#include "Enums.h"
#include "MovePointManager.h"

/// <summary>
/// �����p�̕ۑ��\����
/// </summary>
struct MovePointListMemory
{
	std::vector<XMFLOAT3> MovePointList = {};
	MoveSystemType MoveType = MoveSystemType::Once;
};

/// <summary>
/// �ړ��V�X�e���N���X
/// </summary>
class CMoveSystem
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="In_Type">�ړ��V�X�e���̎��</param>
	/// <param name="In_MoveSpeed">�ړ����x</param>
	CMoveSystem(MoveSystemType In_Type, float In_MoveSpeed);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CMoveSystem();

	/// <summary>
	/// �f�o�b�N�`�揈��(�ړ����[�g�̕`��)
	/// </summary>
	/// <param name="In_Color">�`�悷����̐F</param>
	void DebugDraw(XMFLOAT4 In_Color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	
	/// <summary>
	/// �ړ��|�C���g�̎擾
	/// </summary>
	/// <param name="In_CurrentPos">���݂̈ʒu</param>
	/// <returns>���Ɉړ�����ړ��|�C���g</returns>
	XMFLOAT3 GetMovePoint(const XMFLOAT3& In_CurrentPos);

	/// <summary>
	/// �ړ��|�C���g�̒ǉ�
	/// </summary>
	/// <param name="In_MovePoint">�ǉ�����ړ��|�C���g</param>
	void AddMovePoint(const XMFLOAT3& In_MovePoint);

	/// <summary>
	/// �����̈ړ��|�C���g��ǉ�
	/// </summary>
	/// <param name="In_MovePoints">�ǉ�����ړ��|�C���g���X�g(���т͂��̂܂�)</param>
	void AddMovePoints(const std::vector<XMFLOAT3>& In_MovePoints);

	/// <summary>
	/// �ړ��|�C���g�̃��X�g��V�����ݒ�
	/// </summary>
	/// <param name="In_MovePoints">�ݒ肷��ړ��|�C���g</param>
	/// <param name="In_CurrentPos">���݂̈ʒu</param>
	void SetMovePoints(const std::vector<XMFLOAT3>& In_MovePoints , const XMFLOAT3& In_CurrentPos);

	/// <summary>
	/// �ړ��|�C���g�̃��X�g�̃��[�g����
	/// </summary>
	/// <param name="In_CurrentPos">���݂̈ʒu</param>
	void RestorationMovePoints(XMFLOAT3 In_CurrentPos);

	/// <summary>
	/// �ړ��|�C���g�𕜌��p�ɕۑ����ă��X�g���N���A
	/// </summary>
	void SaveAndClearMovePoints();

	/// <summary>
	/// �ړ��|�C���g�̃��X�g���N���A
	/// </summary>
	void ClearMovePoints() { m_vtMovePointList.clear(); }
private:
	/// <summary>
	/// �ړ��V�X�e���̎��
	/// </summary>
	MoveSystemType m_eMoveSystemType;

	/// <summary>
	/// �ړ��|�C���g�̃��X�g
	/// </summary>
	std::vector<XMFLOAT3> m_vtMovePointList;

	/// <summary>
	/// ���[�g�����p�̕ۑ�
	/// </summary>
	MovePointListMemory m_vOldRouteMemory;

	/// <summary>
	/// �ړ���
	/// </summary>
	float m_fMoveSpeed;

	/// <summary>
	/// ���݂̃|�C���g�̃C���f�b�N�X
	/// </summary>
	int m_nCurrentPointIndex;

	/// <summary>
	/// �ŏI�ʒu�ɓ��B�������ǂ����̃t���O
	/// </summary>
	bool m_bIsEndPoint;

	/// <summary>
	/// Y���̒����l
	/// </summary>
	float m_fAdjustY;

public:// �A�N�Z�T�[

	/// <summary>
	/// �ړ��ʂ��擾
	/// </summary>
	/// <returns>�ړ���</returns>
	float GetMoveSpeed() const { return m_fMoveSpeed; }

	/// <summary>
	/// �ړ��|�C���g�̃��X�g���擾
	/// </summary>
	/// <returns>�ړ��|�C���g�̃��X�g</returns>
	const std::vector<XMFLOAT3>& GetMovePointList() const { return m_vtMovePointList; }

	/// <summary>
	/// Y���W�̒����l���擾
	/// </summary>
	/// <param name="In_AdjustY">�����l</param>
	void SetAdjustY(float In_AdjustY) { m_fAdjustY = In_AdjustY; }

	/// <summary>
	/// �ړ��V�X�e���̎�ނ�ݒ�
	/// </summary>
	/// <param name="In_Type">�ݒ肷��ړ��V�X�e��</param>
	void SetMoveSystemType(MoveSystemType In_Type) { m_eMoveSystemType = In_Type; }
};
