/*
* @file SceneGame.h
* @brief �Q�[���V�[���̃N���X�̃w�b�_�[�t�@�C��
* @author �F���엤�l
* @date 2025/08/04 �N���X�̍쐬
*/

#pragma once

/* �V�X�e���E�v�f�̃C���N���[�h */
#include <memory>
#include "Collision.h"
/* ���N���X�̃C���N���[�h */
#include "SceneBase.h"

/* �O���錾 */
class CGameObject;
class CFieldObject;
class CPlayer;
class CNpcBase;

// �U���̓����蔻����
struct AttackCollision
{
	// �����蔻����
	Collision::Info CollisionInfo;
	// �����t���[��
	float DurationFrame;
	// �U����
	float AttackPower;

	bool operator==(const AttackCollision& other) const
	{
		return &CollisionInfo == &other.CollisionInfo && &DurationFrame == &other.DurationFrame;
	}
};

/// <summary>
/// �Q�[���V�[���N���X
/// </summary>
class CSceneGame : public CSceneBase
{
private:
	// ���Z��X�e�[�W�̏�����
	void InitArenaStage(void);
	// �����X�e�[�W�̏�����
	void InitPlainStage(void);

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

	/// <summary>
	/// ���ׂẴt�B�[���h�I�u�W�F�N�g���擾
	/// </summary>
	/// <returns>���ׂẴt�B�[���h�I�u�W�F�N�g���X�g</returns>
	std::vector<CGameObject*> GetAllFieldObjects(void);

	/// <summary>
	///  �U���̐���
	/// </summary>
	void AttackCreate(AttackCollision In_CollisionInfo);

private:
	/// <summary>
	/// �����蔻��̏Փ˃`�F�b�N
	/// </summary>
	void CollisionCheck(void);

	/// <summary>
	/// ���C�L���X�g�̃`�F�b�N
	/// </summary>
	void RayCastCheck(void);

	/// <summary>
	/// �U���̓����蔻��`�F�b�N
	/// </summary>
	void AttackCollisionCheck(void);
private:
	// �t�B�[���h�I�u�W�F�N�g
	std::vector<std::unique_ptr<CFieldObject>> m_pFieldObject;
	// �v���C���[�I�u�W�F�N�g�̃|�C���^
	std::unique_ptr<CPlayer> m_pPlayer;
	// NPC�I�u�W�F�N�g�̃|�C���^
	std::vector<std::unique_ptr<CNpcBase>> m_pNpc;
	// �U���̓����蔻�胊�X�g
	std::vector<AttackCollision> m_vAttackCollisionInfos;
};
