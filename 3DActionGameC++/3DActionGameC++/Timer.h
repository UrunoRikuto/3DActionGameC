/*=====================================================================
* @file Timer.h
* @brief �^�C�}�[��h�t�@�C��
=====================================================================*/
#pragma once

/* �V�X�e���E�v�f�̃C���N���[�h */
#include "SpriteDrawer.h"

/// <summary>
/// �^�C�}�[�N���X
/// </summary>
class CTimer
{
private://�V���O���g���p�^�[��
	static CTimer* m_pInstance;
	// @brief �R���X�g���N�^
	CTimer();
public:
	// @brief �C���X�^���X�̎擾
	static CTimer* GetInstance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CTimer;
		}
		return m_pInstance;
	}
	// @brief �C���X�^���X�̍폜
	static void DeleteInstance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	// @brief �f�X�g���N�^
	~CTimer();
	// @brief �^�C�}�[�̍X�V
	// @return �������Ԃ𒴂�����
	bool Update();

	// @brief �^�C�}�[�`��
	void Draw();

	// @brief �^�C�}�[�̃��Z�b�g
	void Reset();

private:
	// @brief �o�ߎ���
	float m_fElapsedTime = 0.0f;
	// @brief ��������
	float m_fLimitTime = 0.0f;

	// 2D�`��ɕK�v�ȃf�[�^
	// �w�i
	ID3D11Buffer* m_pGaugeBackVtx;
	ID3D11ShaderResourceView* m_pGaugeBackTex;
	// �O�i
	ID3D11Buffer* m_pGaugeFrontVtx;
	ID3D11ShaderResourceView* m_pGaugeFrontTex;
public:
	// @brief �o�ߎ��Ԃ̎擾
	// @return �o�ߎ���
	float GetElapsedTime() const { return m_fElapsedTime; }
	// @brief �������Ԃ̎擾
	// @return ��������
	float GetLimitTime() const { return m_fLimitTime; }
	// @brief �������Ԃ̐ݒ�
	// @param In_LimitTime �ݒ肷�鐧������
	void SetLimitTime(float In_LimitTime) { m_fLimitTime = In_LimitTime; }
};

