#include "Model.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

/*
* @brief ���b�V�������擾
* @return ���b�V����
*/
unsigned int Model::GetMeshNum()
{
	return static_cast<int>(m_meshes.size());
}

/*
* @brief ���b�V�������擾
* @param[in] index �擾���郁�b�V���ԍ�
* @return ���b�V�����
*/
const Model::Mesh* Model::GetMesh(unsigned int index)
{
	if (index < GetMeshNum())
		return &m_meshes[index];
	return nullptr;
}

/*
* @brief �}�e���A�������擾
* @return �}�e���A����
*/
unsigned int Model::GetMaterialNum()
{
	return static_cast<int>(m_materials.size());
}

/*
* @brief �}�e���A�������擾
* @param[in] index �擾����}�e���A���ԍ�
* @return �}�e���A�����
*/
const Model::Material* Model::GetMaterial(unsigned int index)
{
	if (index < GetMaterialNum())
		return &m_materials[index];
	return nullptr;
}

/*
* @brief �A�j���[�V������̕ϊ��s��擾
* @param[in] index �{�[���ԍ�
* @return �Y���{�[���̕ϊ��s��
*/
DirectX::XMMATRIX Model::GetBoneMatrix(NodeIndex index)
{
	if (index < m_nodes.size())
		return m_nodes[index].mat;
	return DirectX::XMMatrixIdentity();
}

/*
* @brief �A�j���[�V�����Đ�����
* @param[in] no �A�j���[�V�����ԍ�
* @return �Đ���
*/
bool Model::IsAnimePlay(AnimeNo no)
{
	// �A�j���[�V�����`�F�b�N
	if (!CheckAnimeNo(no)) { return false; }

	// �p�����g���b�N�͍������̃A�j������ɔ��f
	if (no == PARAMETRIC_ANIME) { no = m_parametric[0]; }

	// �Đ����Ԃ̔���
	if (m_animes[no].info.totalTime < m_animes[no].info.nowTime) { return false; }

	// ���ꂼ��̍Đ��ԍ��ɐݒ肳��Ă��邩�m�F
	if (m_playNo == no) { return true; }
	if (m_blendNo == no) { return true; }
	if (m_playNo == PARAMETRIC_ANIME || m_blendNo == PARAMETRIC_ANIME)
	{
		if (m_parametric[0] == no) { return true; }
		if (m_parametric[1] == no) { return true; }
	}

	// �Đ����łȂ�
	return false;
}

/*
* @brief �Đ����̔ԍ��̎擾
* @return �A�j���ԍ�
*/
Model::AnimeNo Model::GetAnimePlayNo()
{
	return m_playNo;
}

/*
* @brief �Đ����̃u�����h�A�j���̎擾
* @return �A�j���ԍ�
*/
Model::AnimeNo Model::GetAnimeBlendNo()
{
	return m_blendNo;
}

/*
* @brief �A�j���[�V�������擾
* @return �A�j���[�V�������
*/
const Model::AnimePlayInfo* Model::GetPlayAnimeInfo()
{
	AnimeNo no = GetAnimePlayNo();
	if (!CheckAnimeNo(no)) { return nullptr; }
	return &m_animes[no].info;
}

/*
* @brief �f�B���N�g�����̎擾
* @param[in] file �t�@�C���p�X
* @return �f�B���N�g�������̏��
*/
std::string Model::GetDirectory(const char* file)
{
	// �f�B���N�g���̓ǂݎ��
	std::string directory = file;
	auto strIt = directory.begin();
	while (strIt != directory.end()) {
		if (*strIt == '/')
			*strIt = '\\';
		++strIt;
	}
	directory = directory.substr(0, directory.find_last_of('\\') + 1);
	return directory;
}