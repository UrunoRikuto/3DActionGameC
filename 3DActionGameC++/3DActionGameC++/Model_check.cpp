#include "Model.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#ifdef _DEBUG
#include "Geometory.h"
#endif


/*
* @brief �G���[���b�Z�[�W�擾
* @returnn �G���[���b�Z�[�W
*/
std::string Model::GetError()
{
#ifdef _DEBUG
	return m_errorStr;
#else
	return "";
#endif
}

/*
* @brief �{�[���̃f�o�b�O�\��
* @param[in] world ���[���h�s��
*/
void Model::DrawBone(DirectX::XMMATRIX world)
{
#ifdef _DEBUG
	// �ċA����
	std::function<void(int, DirectX::XMFLOAT3)> FuncDrawBone =
		[&FuncDrawBone, this, &world](int idx, DirectX::XMFLOAT3 parent)
	{
		// �e�m�[�h���猻�݈ʒu�܂ŕ`��
		DirectX::XMFLOAT3 pos;
		DirectX::XMStoreFloat3(&pos, DirectX::XMVector3TransformCoord(DirectX::XMVectorZero(), m_nodes[idx].mat * world));
		Geometory::AddLine(parent, pos, DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));

		// �q�m�[�h�̕`��
		auto it = m_nodes[idx].children.begin();
		while (it != m_nodes[idx].children.end())
		{
			FuncDrawBone(*it, pos);
			++it;
		}
	};

	// �`����s
	FuncDrawBone(0, DirectX::XMFLOAT3());
	Geometory::DrawLines();
#endif
}


/*
* @brief �A�j���[�V�����̃��[�v�`�F�b�N
* @param[in, out] info �Đ����
*/
void Model::CheckAnimePlayLoop(AnimePlayInfo& info)
{
	if (info.isLoop) {
		while (info.nowTime >= info.totalTime)
		{
			info.nowTime -= info.totalTime;
		}
	}
}

/*
* @brief �G���[���b�Z�[�W���A�G���[�`�F�b�N
* @param[in] condition �G���[����
* @param[in] messege �G���[���b�Z�[�W
* @return �G���[����
*/
bool Model::IsError(bool condition, std::string message)
{
	if(condition)
		SetErrorMessage(message);
	return condition;
}

/*
* @brief �G���[���b�Z�[�W�̐ݒ�
* @param[in] message ���b�Z�[�W���e
*/
void Model::SetErrorMessage(std::string message)
{
#ifdef _DEBUG
	m_errorStr += message + "\n";
#endif
}


/*
* @brief �G���[���b�Z�[�W�̕\��
* @param[in] caption �^�C�g���o�[�\�����b�Z�[�W
* @param[in] isWarning �x���t���O
*/
void Model::ShowErrorMessage(const char* caption, bool isWarning)
{
#ifdef _DEBUG
	std::string msg = GetError();
	if (msg.empty()) { return; }
	if(isWarning)
		MessageBox(NULL, msg.c_str(), (std::string("Warning - ") + caption).c_str(), MB_OK | MB_ICONWARNING);
	else
		MessageBox(NULL, msg.c_str(), (std::string("Error - ") + caption).c_str(), MB_OK | MB_ICONERROR);
#endif
}

/*
* @brief �m�[�h�̒T��
* @param[in] name �T���m�[�h��
* @return �m�[�h�ԍ�
*/
Model::NodeIndex Model::FindNode(const char* name)
{
	// �\�z�ς݂̃{�[���m�[�h����Y���m�[�h���擾
	Model::Nodes::iterator it = std::find_if(m_nodes.begin(), m_nodes.end(),
		[name](const Node& val) {
			return val.name == name;
		});
	if (it == m_nodes.end()) {
		return NODE_NONE;
	}

	return static_cast<NodeIndex>(it - m_nodes.begin());
}

/*
* @brief �t���[�Y�ς݃��b�V���`�F�b�N
* @param[in] ptr aiScene�ւ̃|�C���^
* @return �`�F�b�N����
*/
bool Model::CheckMeshFreeze(const void* ptr)
{
	// �ċA������Assimp�̃m�[�h����ǂݎ��
	std::function<bool(std::string& name, aiNode*)> FuncFreezeCheck =
		[&FuncFreezeCheck, this](std::string& name, aiNode* assimpNode)
	{
		std::string nodeName = assimpNode->mName.data;
		if (nodeName.find(name) != std::string::npos)
		{
			if (fabsf(assimpNode->mTransformation.a4) > FLT_EPSILON) { return false; }
			if (fabsf(assimpNode->mTransformation.b4) > FLT_EPSILON) { return false; }
			if (fabsf(assimpNode->mTransformation.c4) > FLT_EPSILON) { return false; }

			return true;
		}

		for (UINT i = 0; i < assimpNode->mNumChildren; ++i)
		{
			if (!FuncFreezeCheck(name, assimpNode->mChildren[i]))
				return false;
		}
		return true;
	};

	const aiScene* pScene = reinterpret_cast<const aiScene*>(ptr);
	bool result = true;
	for (unsigned int i = 0; i < pScene->mNumMeshes; ++i) {
		std::string meshName = pScene->mMeshes[i]->mName.data;

		// �m�[�h����T��
		if (!FuncFreezeCheck(meshName, pScene->mRootNode)) {
			SetErrorMessage("no mesh freeze. [" + meshName + "]");
			result = false;
		}
	}

	return result;
}

/*
* @brief �A�j���[�V�����ԍ��̃`�F�b�N
* @param[in] no �A�j���[�V�����ԍ�
* @return �L���ȃA�j���[�V�����ԍ����ǂ���
*/
bool Model::CheckAnimeNo(AnimeNo no)
{
	// �p�����g���b�N�A�j���[�V�����m�F
	if (no == PARAMETRIC_ANIME)
	{
		// �p�����g���b�N�p�̃f�[�^�������������ݒ肳��Ă��邩
		return
			m_parametric[0] != ANIME_NONE &&
			m_parametric[1] != ANIME_NONE;
	}

	// ���Ȃ��A�j���[�V�����ԍ����ǂ���
	return 0 <= no && no < m_animes.size();
}