/*������������������������������������������������������������������������������������������������������������������������������
*
* file�FFade.cpp
*
* �T�v�F�t�F�[�h�������Ǘ�����t�@�C��
*
������������������������������������������������������������������������������������������������������������������������������*/

#include "Fade.h"
#include "DirectXTex/TextureLoad.h"
#include "VertexBuffer.h"
#include "Defines.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
CFade::CFade(float In_MaxFadeTime)
	: m_fAlpha(0.0f)
	, m_fTime(In_MaxFadeTime)
	, m_bFadeOut(true)
{
	//Vertex�̐���
	Vertex vtx[4] = {
	{ {-SCREEN_WIDTH,-SCREEN_HEIGHT,0.0f},{0.0f,0.0f}},
	{ { SCREEN_WIDTH,-SCREEN_HEIGHT,0.0f},{1.0f,0.0f}},
	{ {-SCREEN_WIDTH, SCREEN_HEIGHT,0.0f},{0.0f,1.0f}},
	{ { SCREEN_WIDTH, SCREEN_HEIGHT,0.0f},{1.0f,1.0f}},
	};

	//��������Vertex��Buffer�̃|�C���^�ϐ��ɐݒ�
	m_pVtx = CreateVertexBuffer(vtx, 4);

	HRESULT hr = E_FAIL;
	//�^�C�g���̔w�i�e�N�X�`���̐ݒ�
	hr = LoadTextureFromFile(GetDevice(), TEXTURE_PATH("Fade_BackGround.png"), &m_pTex);
	if (FAILED(hr)) {
		//---�f�o�b�N���[�h�̂ݏ���
#ifdef _DEBUG
		MessageBox(NULL, "�t�F�[�h�w�i�摜", "Error", MB_OK);
#endif
	}
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CFade::~CFade()
{
	SAFE_RELEASE(m_pVtx);
	SAFE_RELEASE(m_pTex);
}

/// <summary>
/// �X�V����
/// </summary>
void CFade::Update()
{
	// �t�F�[�h�A�E�g�t���O�������Ă���ꍇ�̓t�F�[�h�A�E�g�A�����łȂ���΃t�F�[�h�C��
	if (m_bFadeOut)
	{
		// �A���t�@�l��1.0f�����̏ꍇ�̓t�F�[�h�A�E�g
		if (m_fAlpha < 1.0f)
		{
			// �A���t�@�l�����X�ɑ��₷
			m_fAlpha += 1.0f / (fFPS * (m_fTime / 2.0f));
			// �A���t�@�l��1.0f�𒴂�����1.0f�ɐ������A�t�F�[�h�A�E�g�t���O������
			if (m_fAlpha >= 1.0f)
			{
				m_fAlpha = 1.0f;
				m_bFadeOut = false;
				// �t�F�[�h�A�E�g������������`�F���W�t���O�𗧂Ă�
				// ����ɂ��A���̃V�[���ւ̐؂�ւ����\�ɂȂ�
				m_bChange = true; 
			}
		}
	}
	// �t�F�[�h�A�E�g�t���O�������Ă��Ȃ��ꍇ�̓t�F�[�h�C��
	else
	{
		// �A���t�@�l��0.0f���傫���ꍇ�̓t�F�[�h�C��
		if (m_fAlpha > 0.0f)
		{
			// �A���t�@�l�����X�Ɍ��炷
			m_fAlpha -= 1.0f / (fFPS * (m_fTime / 2.0f));
			// �A���t�@�l��0.0f�����������0.0f�ɐ������A�t�F�[�h�����t���O�𗧂Ă�
			if (m_fAlpha <= 0.0f)
			{
				m_fAlpha = 0.0f;
				m_bEnd = true;
			}
		}
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void CFade::Draw()
{
	//�w�i�̕`��
	SetSpriteTexture(m_pTex);

	// �X�v���C�g�̐ݒ�
	SetSpritePos(0.0f, 0.0f);
	SetSpriteScale(1.0f, 1.0f);
	SetSpriteColor(1.0f, 1.0f, 1.0f, m_fAlpha);
	SetSpriteUVPos(0.0f, 0.0f);
	SetSpriteUVScale(1.0f, 1.0f);

	// �X�v���C�g�̕`��
	DrawSprite(m_pVtx, sizeof(Vertex));
}
