/*
* @file Bullet.h
* @brief �e�ۃN���X�̃w�b�_�[�t�@�C��
* @author �F���엤�l
* * @date 2025/08/16 �N���X�̒�`
*/
#pragma once

/* ���N���X�̃C���N���[�h */
#include "GameObject.h"

/// <summary>
/// @brief �e�ۃN���X
/// </summary>
class CBullet : public CGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CBullet();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CBullet();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update(void) override;

	/// <summary>
	/// �p�����[�^�[�̐ݒ�
	/// </summary>
	/// <param name="direction"></param>
	/// <param name="movePower"></param>
	void SetParam(const XMFLOAT3& direction, float movePower);

	/// <summary>
	/// �����蔻��̏Փˎ��̏���
	/// </summary>
	/// <param name="InCollisionInfo">�ՓˑΏ�</param>
	void Hit(const Collision::Info& InCollisionInfo) override;

private:

	/// <summary>
	/// �i�s����
	/// </summary>
	XMFLOAT3 m_tDirection;

	/// <summary>
	/// �ړ���
	/// </summary>
	float m_fMovePower;

	/// <summary>
	/// �e�̐�������
	/// </summary>
	float m_fLifeTime;

public: // �A�N�Z�T
	/// <summary>
	/// �i�s�����̎擾
	/// </summary>
	/// <returns>�i�s����</returns>
	const XMFLOAT3& GetDirection() const { return m_tDirection; }

	/// <summary>
	/// �ړ��͂̎擾
	/// </summary>
	const float& GetMovePower() const { return m_fMovePower; }
};

