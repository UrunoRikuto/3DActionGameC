/*
* @file SceneGame.h
* @brief �Q�[���V�[���̃N���X�̃w�b�_�[�t�@�C��
* @author �F���엤�l
* @date 2025/08/04 �N���X�̍쐬
*/

#pragma once

/* �V�X�e���E�v�f�̃C���N���[�h */
#include <memory>
/* ���N���X�̃C���N���[�h */
#include "SceneBase.h"

/* �O���錾 */
class CField;
class CPlayer;
class CNpcBase;

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
	/// <summary>
	/// �����蔻��̏Փ˃`�F�b�N
	/// </summary>
	void CollisionCheck(void);

	/// <summary>
	/// ���C�L���X�g�̃`�F�b�N
	/// </summary>
	void RayCastCheck(void);

private:
	// �t�B�[���h�I�u�W�F�N�g�̃|�C���^
	std::vector<std::unique_ptr<CField>> m_pField;
	// �v���C���[�I�u�W�F�N�g�̃|�C���^
	std::unique_ptr<CPlayer> m_pPlayer;
	// NPC�I�u�W�F�N�g�̃|�C���^
	std::unique_ptr<CNpcBase> m_pNpc;
};

