/*=====================================================================
* @file GameObject.h
* @brief �Q�[���I�u�W�F�N�g�̊��N���X��h�t�@�C��
=====================================================================*/
#pragma once

/* �V�X�e���E�v�f�̃C���N���[�h */
#include <memory>
#include "StructMath.h"
#include "Collision.h"
#include "Main.h"
#include "SceneGame.h"

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

	/// <summary>
	/// �����蔻��̏Փˎ��̏���
	/// </summary>
	/// <param name="InCollisionInfo">�ՓˑΏ�</param>
	virtual void Hit(const Collision::Info& InCollisionInfo) = 0;
	/// <summary>
	/// �����蔻��̏Փˎ��̏���(�U���p)
	/// </summary>
	/// <param name="InCollisionInfo">�ՓˑΏ�</param>
	/// <param name="In_Attack">����̍U����</param>
	virtual void Hit(const Collision::Info& InCollisionInfo,float In_Attack) = 0;

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

	/// <summary>
	/// �I�u�W�F�N�g���j������邩�ǂ����̃t���O
	/// </summary>
	bool m_bDestroy;

public: // �����o�ϐ��̃A�N�Z�T

	/// <summary>
	/// �����蔻��̎擾
	/// </summary>
	/// <param name="InTag">�����蔻��̃^�O</param>
	/// <returns>�����蔻����</returns>
	std::vector<Collision::Info> GetCollisionInfo(Collision::Tag InTag = Collision::Tag::All);

	/// <summary>
	/// �ʒu���̐ݒ�
	/// </summary>
	/// <param name="position">�V�����ʒu���</param>
	void SetPosition(const XMFLOAT3& position);

	/// <summary>
	/// �ʒu���̎擾
	/// </summary>
	/// <returns>�ʒu���</returns>
	const XMFLOAT3& GetPosition() const { return m_tPosition; }

	/// <summary>
	/// �X�P�[�����̐ݒ�
	/// </summary>
	/// <param name="scale">�V�����X�P�[�����</param>
	void SetScale(const XMFLOAT3& scale);

	/// <summary>
	/// �X�P�[�����̎擾
	/// </summary>
	/// <returns>�X�P�[�����</returns>
	const XMFLOAT3& GetScale() const { return m_tScale; }

	/// <summary>
	/// ��]���̐ݒ�
	/// </summary>
	/// <param name="rotation">�V������]���</param>
	void SetRotation(const XMFLOAT3& rotation) { m_tRotation = rotation; }

	/// <summary>
	/// ��]���̎擾
	/// </summary>
	/// <returns>��]���</returns>
	const XMFLOAT3& GetRotation() const { return m_tRotation; }

	/// <summary>
	/// �I�u�W�F�N�g���j������邩�ǂ����̃t���O�̎擾
	/// </summary>
	/// <returns>�I�u�W�F�N�g���j������邩�ǂ���</returns>
	bool IsDestroy() const { return m_bDestroy; }
};

