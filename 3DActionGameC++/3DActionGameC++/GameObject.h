/*
* @file GameObject.h
* @brief �Q�[���I�u�W�F�N�g�̊��N���X��h�t�@�C��
* @author �F���엤�l
* @date 2025/08/04 �N���X�̍쐬
*                  ���f���̃|�C���^
*                  �ʒu���
*                  �X�P�[�����
*                  ��]���̒ǉ�
*            08/05 �����蔻����
*/
#pragma once

/* �V�X�e���E�v�f�̃C���N���[�h */
#include <memory>
#include "StructMath.h"
#include "Collision.h"

/* �O���錾 */
class Model;

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

protected:
	/// <summary>
	/// ���f���̃|�C���^
	/// </summary>
	std::unique_ptr<Model> m_pModel;

	/// <summary>
	/// �����蔻����
	/// </summary>
	std::vector<Collision::Info> m_tCollisionInfos;

	/// <summary>
	/// �ʒu���
	///	</summary>
	XMFLOAT3 m_tPosition;

	/// <summary>
	/// Y���̒����ʒu
	/// </summary>
	float m_fAjustPositionY;

	/// <summary>
	/// �傫�����
	/// </summary>
	XMFLOAT3 m_tScale;

	/// <summary>
	/// ��]���
	/// </summary>
	XMFLOAT3 m_tRotation;

public: // �����o�ϐ��̃A�N�Z�T

	/// <summary>
	/// �����蔻��̎擾
	/// </summary>
	/// <param name="InTag">�����蔻��̃^�O</param>
	/// <returns>�����蔻����</returns>
	Collision::Info GetCollisionInfo(Collision::Tag InTag);

	/// <summary>
	/// �ʒu���̎擾
	/// </summary>
	/// <returns>�ʒu���</returns>
	const XMFLOAT3& GetPosition() const { return m_tPosition; }

	/// <summary>
	/// �X�P�[�����̎擾
	/// </summary>
	/// <returns>�X�P�[�����</returns>
	const XMFLOAT3& GetScale() const { return m_tScale; }

	/// <summary>
	/// ��]���̎擾
	/// </summary>
	/// <returns>��]���</returns>
	const XMFLOAT3& GetRotation() const { return m_tRotation; }

};

