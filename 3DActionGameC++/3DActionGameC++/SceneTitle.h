#pragma once
#include "SceneBase.h"
#include "SpriteDrawer.h"

/*
* @brief �^�C�g���V�[���N���X
*/
class CSceneTitle : public CSceneBase
{
public:
	//�R���X�g���N�^
	CSceneTitle();
	//�f�X�g���N�^
	~CSceneTitle();
	//�X�V����
	void Update(void) override;
	//�`�揈��
	void Draw(void) override;
private:
	//2D�`��ɕK�v�ȃf�[�^
	ID3D11Buffer* m_pVtx;
	ID3D11ShaderResourceView* m_pTex;
};