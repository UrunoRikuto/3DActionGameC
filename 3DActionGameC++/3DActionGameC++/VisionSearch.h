/*
* @file VisionSearch.h
* @brief VisionSearch�N���X�̃w�b�_�[�t�@�C��
* @author �F���엤�l
* @date 2025/08/19 �N���X�̒�`
*/
#pragma once

/* �V�X�e���E�v�f�̃C���N���[�h */
#include "StructMath.h"
#include "Enums.h"
#include "Player.h"
#include "NpcBase.h"

/// <summary>
/// ���o���G�N���X
/// </summary>
class CVisionSearch
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="In_Self">���g�̃I�u�W�F�N�g</param>
	CVisionSearch(CNpcBase* In_Self);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CVisionSearch();

	/// <summary>
	/// �p�����[�^�[�̏����ݒ�
	/// </summary>
	/// <param name="In_ViewDistance">���F����</param>
	/// <param name="In_TargetObject">���G�Ώۂ̃I�u�W�F�N�g</param>
	void InitParam(float In_ViewDistance, CPlayer* In_TargetObject);

	/// <summary>
	/// ���G����
	/// </summary>
	/// <param name="In_SelfPosition">���g�̈ʒu</param>
	/// <param name="In_CurrentSearchState">���݂̍��G���</param>
	/// <returns>�X�V��̍��G���</returns>
	VisionSearchState Search(const XMFLOAT3& In_SelfPosition, VisionSearchState In_CurrentSearchState);

	/// <summary>
	/// ���o���G�̕`�揈��
	/// </summary>
	void DebugDraw(void);

private:

	/// <summary>
	/// ���Ă������
	/// </summary>
	XMFLOAT3 m_tDirection;

	/// <summary>
	/// ���F����
	/// </summary>
	float m_fViewDistance;

	/// <summary>
	/// �����l
	/// </summary>
	float m_fDetectionValue;

	/// <summary>
	/// ��������ԂɂȂ�܂ł̌o�ߎ���
	/// </summary>
	float m_fLostTimer;

	/// <summary>
	/// ���G���s���Q�[���I�u�W�F�N�g
	/// </summary>
	CNpcBase* m_pSelfObject;

	/// <summary>
	/// ���G�Ώۂ̃Q�[���I�u�W�F�N�g
	/// </summary>
	CPlayer* m_pTargetObject;

public:// �A�N�Z�T
	/// <summary>
	/// ���Ă�������̐ݒ�
	/// </summary>
	/// <param name="direction">���Ă������</param>
	void SetDirection(const XMFLOAT3& direction) { m_tDirection = direction; }
	/// <summary>
	/// ���Ă�������̎擾
	/// </summary>
	/// <returns>���Ă������</returns>
	const XMFLOAT3& GetDirection(void) const { return m_tDirection; }
	/// <summary>
	/// �����l�̎擾
	/// </summary>
	/// <returns>�����l</returns>
	float GetDetectionValue(void) const { return m_fDetectionValue; }
};

