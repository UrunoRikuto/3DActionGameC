/*=====================================================================
* @file Timer.h
* @brief �^�C�}�[��cpp�t�@�C��
=====================================================================*/

/* �w�b�_�[�̃C���N���[�h */
#include "Timer.h"

/* �V�X�e���E�v�f�̃C���N���[�h */
#include "Defines.h"
#include "VertexBuffer.h"
#include "DirectXTex/TextureLoad.h"
#include "Main.h"
#include "GameValues.h"

// �V���O���g���̃C���X�^���X�̏�����
CTimer* CTimer::m_pInstance = nullptr;


// @brief �R���X�g���N�^
CTimer::CTimer()
	:m_fElapsedTime(0.0f)
{
	HRESULT hr = E_FAIL;

	/// �w�i�f�[�^�̍쐬

	// Vertex�̐���
	Vertex vtx[4] = {
	{ {-GameValue::Timer::GAUGE_SIZE_X,-SCREEN_HEIGHT,0.0f},{0.0f,0.0f}},
	{ { GameValue::Timer::GAUGE_SIZE_X,-SCREEN_HEIGHT,0.0f},{1.0f,0.0f}},
	{ {-GameValue::Timer::GAUGE_SIZE_X, SCREEN_HEIGHT,0.0f},{0.0f,1.0f}},
	{ { GameValue::Timer::GAUGE_SIZE_X, SCREEN_HEIGHT,0.0f},{1.0f,1.0f}},
	};
	// ��������Vertex��Buffer�̃|�C���^�ϐ��ɐݒ�
	m_pGaugeBackVtx = CreateVertexBuffer(vtx, 4);
	// �w�i�e�N�X�`���̐ݒ�
	hr = LoadTextureFromFile(GetDevice(), TEXTURE_PATH("UI/TimerBack.png"), &m_pGaugeBackTex);


	/// �O�i�f�[�^�̍쐬

	// ��������Vertex��Buffer�̃|�C���^�ϐ��ɐݒ�
	m_pGaugeFrontVtx = CreateVertexBuffer(vtx, 4);

	// �O�i�e�N�X�`���̐ݒ�
	hr = LoadTextureFromFile(GetDevice(), TEXTURE_PATH("UI/TimerFront.png"), &m_pGaugeFrontTex);

}

// @brief �f�X�g���N�^
CTimer::~CTimer()
{
	// �o�b�t�@�[�|�C���^�̉��
	if (m_pGaugeBackVtx) m_pGaugeBackVtx->Release();
	if (m_pGaugeFrontVtx) m_pGaugeFrontVtx->Release();
	// �e�N�X�`���|�C���^�̉��
	if (m_pGaugeBackTex) m_pGaugeBackTex->Release();
	if (m_pGaugeFrontTex) m_pGaugeFrontTex->Release();
}

// @brief �^�C�}�[�̍X�V
bool CTimer::Update()
{
	m_fElapsedTime += 1.0f / fFPS;

	if (m_fElapsedTime >= m_fLimitTime)
	{
		m_fElapsedTime = m_fLimitTime;
		return true;
	}

	return false;
}

// @brief �^�C�}�[�`��
void CTimer::Draw()
{
	//�O�i�̕`��
	SetSpriteTexture(m_pGaugeFrontTex);

	SetSpritePos(-SCREEN_WIDTH + GameValue::Timer::GAUGE_SIZE_X, (SCREEN_HEIGHT / 2 * (1.0f - ((m_fLimitTime - m_fElapsedTime) / m_fLimitTime))) * 1.95f);
	SetSpriteScale(0.9f, ((m_fLimitTime - m_fElapsedTime) / m_fLimitTime));
	SetSpriteColor(1.0f, 1.0f, 1.0f, 1.0f);
	SetSpriteUVPos(0.0f, 0.0f);
	SetSpriteUVScale(1.0f, 1.0f);
	DrawSprite(m_pGaugeFrontVtx, sizeof(Vertex));
	//�w�i�̕`��
	SetSpriteTexture(m_pGaugeBackTex);

	SetSpritePos(-SCREEN_WIDTH + GameValue::Timer::GAUGE_SIZE_X, 0.0f);
	SetSpriteScale(1.0f, 1.0f);
	SetSpriteColor(1.0f, 1.0f, 1.0f, 1.0f);
	SetSpriteUVPos(0.0f, 0.0f);
	SetSpriteUVScale(1.0f, 1.0f);

	DrawSprite(m_pGaugeBackVtx, sizeof(Vertex));

}

// @brief �^�C�}�[�̃��Z�b�g
void CTimer::Reset()
{
	m_fElapsedTime = 0.0f;
}
