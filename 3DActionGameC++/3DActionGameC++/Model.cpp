#include "Model.h"
#include "DirectXTex/TextureLoad.h"
#include <algorithm>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#if _MSC_VER >= 1930
#ifdef _DEBUG
#pragma comment(lib, "assimp-vc143-mtd.lib")
#else
#pragma comment(lib, "assimp-vc143-mt.lib")
#endif
#elif _MSC_VER >= 1920
#ifdef _DEBUG
#pragma comment(lib, "assimp-vc142-mtd.lib")
#else
#pragma comment(lib, "assimp-vc142-mt.lib")
#endif
#elif _MSC_VER >= 1910
#ifdef _DEBUG
#pragma comment(lib, "assimp-vc141-mtd.lib")
#else
#pragma comment(lib, "assimp-vc141-mt.lib")
#endif
#endif

// static�����o�ϐ���`
VertexShader*	Model::m_pDefVS		= nullptr;
PixelShader*	Model::m_pDefPS		= nullptr;
unsigned int	Model::m_shaderRef	= 0;
#ifdef _DEBUG
std::string		Model::m_errorStr	= "";
#endif

// �v���g�^�C�v�錾
DirectX::XMMATRIX GetMatrixFromAssimpMatrix(aiMatrix4x4 M);
void MakeModelDefaultShader(VertexShader** vs, PixelShader** ps);

/*
* @brief �R���X�g���N�^
*/
Model::Model()
	: m_loadScale(1.0f)
	, m_loadFlip(None)
	, m_morphPlayNo(ANIME_NONE)
	, m_playNo(ANIME_NONE)
	, m_blendNo(ANIME_NONE)
	, m_parametric{ANIME_NONE, ANIME_NONE}
	, m_blendTime(0.0f)
	, m_blendTotalTime(0.0f)
	, m_parametricBlend(0.0f)
{
	// �f�t�H���g�V�F�[�_�[�̓K�p
	if (m_shaderRef == 0)
	{
		MakeModelDefaultShader(&m_pDefVS, &m_pDefPS);
	}
	m_pVS = m_pDefVS;
	m_pPS = m_pDefPS;
	++m_shaderRef;
}

/*
* @brief �f�X�g���N�^
*/
Model::~Model()
{
	Reset();
	--m_shaderRef;
	if (m_shaderRef <= 0)
	{
		delete m_pDefPS;
		delete m_pDefVS;
	}
}

/*
* @brief �����f�[�^�폜
*/
void Model::Reset()
{
	// ���b�V���f�[�^�폜
	auto meshIt = m_meshes.begin();
	while (meshIt != m_meshes.end())
	{
		if (meshIt->pMesh) delete meshIt->pMesh;
		++meshIt;
	}

	// �}�e���A���f�[�^�폜
	auto matIt = m_materials.begin();
	while (matIt != m_materials.end())
	{
		if (matIt->pTexture) delete matIt->pTexture;
		++matIt;
	}

	// �m�[�h�f�[�^�폜
	m_nodes.clear();
}

/*
* @brief ���_�V�F�[�_�[�ݒ�
*/
void Model::SetVertexShader(Shader* vs)
{
	if (vs && typeid(VertexShader) == typeid(*vs))
		m_pVS = static_cast<VertexShader*>(vs);
	else
		m_pVS = m_pDefVS;
}

/*
* @brief �s�N�Z���V�F�[�_�[�ݒ�
*/
void Model::SetPixelShader(Shader* ps)
{
	if (ps && typeid(PixelShader) == typeid(*ps))
		m_pPS = static_cast<PixelShader*>(ps);
	else
		m_pPS = m_pDefPS;
}

/*
* @brief ���f���f�[�^�̓ǂݍ���
* @param[in] file �ǂݍ��ݐ�p�X
* @param[in] scale �g�嗦
* @param[in] flip ���]�ݒ�
* @return �ǂݍ��݌���
*/
bool Model::Load(const char* file, float scale, Flip flip)
{
	Reset();

	// �ǂݍ��ݎ��̐ݒ��ۑ�
	m_loadScale = scale;
	m_loadFlip = flip;

	// Assimp���œǂݍ��݂����s
	const aiScene* pScene = static_cast<const aiScene*>(LoadAssimpScene(file));
	if (!pScene) { return false; }

	// �t���[�Y�`�F�b�N
#ifdef _DEBUG
	CheckMeshFreeze(pScene);
#endif

	// �m�[�h�̍쐬
	MakeNodes(pScene);
	// ���b�V���쐬
	MakeMesh(pScene);
	// �}�e���A���̍쐬
	MakeMaterial(pScene, GetDirectory(file));

#if MODEL_FORCE_ERROR
	ShowErrorMessage(file, true);
#endif
	return true;
}

/*
* @brief �X�V����
* @param[in] tick �o�ߎ���(�b)
*/
void Model::Step(float tick)
{
	StepAnime(tick);
	StepMorph(tick);
	UpdateMorph();
}

/*
* @brief �`�揈��
* @param[in] meshNo �`�惁�b�V���ԍ�(-1�ł��ׂĕ\��
*/
void Model::Draw(int meshNo)
{
	// �V�F�[�_�[�ݒ�
	m_pVS->Bind();
	m_pPS->Bind();

	// �e�N�X�`�������ݒ�
	bool isAutoTexture = (meshNo == -1);

	// �`�搔�ݒ�
	size_t drawNum = m_meshes.size();
	if (meshNo != -1)
		drawNum = meshNo + 1;
	else
		meshNo = 0;

	// �`��
	for (UINT i = meshNo; i < drawNum; ++i)
	{
		if (isAutoTexture) {
			m_pPS->SetTexture(0, m_materials[m_meshes[i].materialID].pTexture);
		}
		m_meshes[i].pMesh->Draw();
	}
}



/*
* @brief Assimp�Ńf�[�^�̓ǂݍ���
* @param[in] file �ǂݍ��ݐ�p�X
* @return aiScene�N���X�ւ̃|�C���^
*/
const void* Model::LoadAssimpScene(const char* file)
{
#ifdef _DEBUG
	m_errorStr = "";
#endif

	// assimp�̐ݒ�
	static Assimp::Importer importer;
	int flag = 0;
	flag |= aiProcess_Triangulate;
	flag |= aiProcess_FlipUVs;
	if (m_loadFlip == Flip::XFlip)  flag |= aiProcess_MakeLeftHanded;

	// assimp�œǂݍ���
	const aiScene* pScene = importer.ReadFile(file, flag);
#ifdef _DEBUG
	if (!pScene)
		m_errorStr += importer.GetErrorString();
#endif

	return pScene;
}

/*
* @brief �K�w���̍\�z
* @param[in] ptr aiScene�ւ̃|�C���^
*/
void Model::MakeNodes(const void* ptr)
{
	// �ċA������Assimp�̃m�[�h����ǂݎ��
	using FuncRecurciveMakeNodes = std::function<NodeIndex(aiNode*, NodeIndex, DirectX::XMMATRIX)>;
	FuncRecurciveMakeNodes func = [&func, this](aiNode* assimpNode, NodeIndex parent, DirectX::XMMATRIX mat)
	{
		// assimp���ŊK�w��񂪍ׂ�����������Ă���ꍇ�̏���
		std::string name = assimpNode->mName.data;
		if (name.find("$AssimpFbx") != std::string::npos)
		{
			// �����O�̃m�[�h�ɓ��B����܂ŁA�e�s����|�����킹�Ă���
			DirectX::XMMATRIX transform = GetMatrixFromAssimpMatrix(assimpNode->mTransformation);
			mat = transform * mat;
			return func(assimpNode->mChildren[0], parent, mat);
		}

		// Assimp�̃m�[�h�����i�[
		Node node;
		node.name	= name;
		node.parent	= parent;
		node.children.resize(assimpNode->mNumChildren);
		node.mat = mat;

		// �m�[�h�̈ꗗ�ɒǉ�
		m_nodes.push_back(node);
		NodeIndex nodeIndex = static_cast<NodeIndex>(m_nodes.size() - 1);

		// �q�v�f�̏���ǉ�
		for (UINT i = 0; i < assimpNode->mNumChildren; ++i)
		{
			m_nodes[nodeIndex].children[i] =
				func(assimpNode->mChildren[i], nodeIndex, DirectX::XMMatrixIdentity());
		}

		return nodeIndex;
	};

	// �m�[�h�쐬
	const aiScene* pScene = reinterpret_cast<const aiScene*>(ptr);
	func(pScene->mRootNode, NODE_NONE, DirectX::XMMatrixIdentity());

	// �A�j���[�V�����v�Z�̈�ɁA�m�[�h�����̏����f�[�^���쐬
	AnimeTransform init = {
		DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f),
		DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f),
		DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)
	};
	for (int i = 0; i < MAX_ANIMEPATTERN; ++i)
	{
		m_animeTransform[i].resize(m_nodes.size(), init);
	}
}

/*
* @brief ���_�Ƀ{�[���̃u�����h����ǉ�
* @param[in] ptr aiScene�ւ̃|�C���^
* @param[in] meshIndex ���_����ύX���郁�b�V��
*/
void Model::MakeVertexWeight(const void* ptr, int meshIndex)
{
	const aiScene* pScene = reinterpret_cast<const aiScene*>(ptr);
	aiMesh* assimpMesh = pScene->mMeshes[meshIndex];
	if (assimpMesh->HasBones())
		MakeVertexWeightHasBone(assimpMesh, m_meshes[meshIndex]);
	else
		MakeVertexWeightFromNode(ptr, assimpMesh, m_meshes[meshIndex]);
}

/*
* @brief �{�[�������Ƀu�����h�����擾
* @param[in] ptr aiMesh�ւ̃|�C���^
* @param[out] mesh ���_����ύX���郁�b�V��
*/
void Model::MakeVertexWeightHasBone(const void* ptr, Mesh& mesh)
{
	const aiMesh* assimpMesh = reinterpret_cast<const aiMesh*>(ptr);
	DirectX::XMMATRIX mFlip =
		DirectX::XMMatrixScaling(m_loadFlip == ZFlipUseAnime ? -1.0f : 1.0f, 1.0f, 1.0f);
	DirectX::XMMATRIX mScale =
		DirectX::XMMatrixScaling(1.f / m_loadScale, 1.f / m_loadScale, 1.f / m_loadScale);

	// �ǂݎ��p�̃E�F�C�g�f�[�^�쐬
	struct WeightPair
	{
		unsigned int idx;
		float weight;
	};
	std::vector<std::vector<WeightPair>> weights;
	weights.resize(mesh.vertices.size());


	// ���b�V���Ɋ��蓖�Ă��Ă���{�[���̈�m��
	mesh.bones.resize(assimpMesh->mNumBones);
	for (auto boneIt = mesh.bones.begin(); boneIt != mesh.bones.end(); ++boneIt)
	{
		UINT boneIdx = static_cast<UINT>(boneIt - mesh.bones.begin());
		aiBone* assimpBone = assimpMesh->mBones[boneIdx];

		// �\�z�ς݂̃m�[�h����Y���m�[�h�̃C���f�b�N�X���擾
		boneIt->nodeIndex = FindNode(assimpBone->mName.data);
		if (boneIt->nodeIndex == NODE_NONE)
		{
			continue;
		}

		// ���b�V���Ɋ��蓖�Ă��Ă���{�[�����A���_�ɖ߂��t�s���ݒ�
		boneIt->invOffset = GetMatrixFromAssimpMatrix(assimpBone->mOffsetMatrix);
		boneIt->invOffset.r[3].m128_f32[0] *= m_loadScale;
		boneIt->invOffset.r[3].m128_f32[1] *= m_loadScale;
		boneIt->invOffset.r[3].m128_f32[2] *= m_loadScale;
		boneIt->invOffset = mFlip * boneIt->invOffset * mScale;

		// �E�F�C�g�̐ݒ�
		for (UINT i = 0; i < assimpBone->mNumWeights; ++i)
		{
			aiVertexWeight& weight = assimpBone->mWeights[i];
			weights[weight.mVertexId].push_back({ boneIdx, weight.mWeight });
		}
	}

	// �擾���Ă������_�E�F�C�g�𒸓_�f�[�^�ɏ�������
	for (int i = 0; i < weights.size(); ++i)
	{
		// �v���O�������̊��蓖�Đ��𒴂���ꍇ�̐��K������
		if (weights[i].size() >= MAX_WEIGHT)
		{
			// �������������Ƀ\�[�g
			std::sort(weights[i].begin(), weights[i].end(),
				[](WeightPair& a, WeightPair& b) {
					return a.weight > b.weight;
				});
			// �E�F�C�g���ɍ��킹�Đ��K��
			float total = 0.0f;
			for (int j = 0; j < MAX_WEIGHT; ++j)
				total += weights[i][j].weight;
			for (int j = 0; j < MAX_WEIGHT; ++j)
				weights[i][j].weight /= total;
		}

		// ���K�������f�[�^�𒸓_�f�[�^�Ɋ��蓖��
		for (int j = 0; j < weights[i].size() && j < MAX_WEIGHT; ++j)
		{
			mesh.vertices[i].index[j] = weights[i][j].idx;
			mesh.vertices[i].weight[j] = weights[i][j].weight;
		}
	}
}

/*
* @brief �m�[�h�����Ƀu�����h�����擾
* @param[in] scene aiScene�ւ̃|�C���^
* @param[in] ptr aiMesh�ւ̃|�C���^
* @param[out] mesh ���_����ύX���郁�b�V��
* @detail �{�[�������蓖�Ă��ĂȂ����b�V���́A�e�m�[�h�̃{�[�������Ƃ��Čv�Z
*/
void Model::MakeVertexWeightFromNode(const void* scene, const void* ptr, Mesh& mesh)
{
	const aiScene* pScene = reinterpret_cast<const aiScene*>(scene);
	const aiMesh* assimpMesh = reinterpret_cast<const aiMesh*>(ptr);

	// �K�w���̃��b�V����T��
	NodeIndex nodeIndex = FindNode(assimpMesh->mName.data);
	if (nodeIndex == NODE_NONE) { return; }

	// ���b�V���łȂ��e�m�[�h���ċA�T��
	using FuncRecurciveFindNoMesh = std::function<int(int)>;
	FuncRecurciveFindNoMesh func = [&func, this, pScene](NodeIndex parent)
	{
		if (parent == NODE_NONE) { return NODE_NONE; }

		// ���ݒT�����̃m�[�h�������b�V���̈ꗗ�ƈ�v���邩�m�F
		std::string name = m_nodes[parent].name;
		for (UINT i = 0; i < pScene->mNumMeshes; ++i)
		{
			if (name == pScene->mMeshes[i]->mName.data)
			{
				return func(m_nodes[parent].parent);
			}
		}

		// ��v���Ȃ��m�[�h��ϊ����Ƃ��Ĉ���
		return parent;
	};

	// �{�[�����蓖�ď����쐬
	Bone bone = {};
	bone.nodeIndex = func(m_nodes[nodeIndex].parent);
	if (bone.nodeIndex != NODE_NONE) {
		// �m�[�h�ɕۑ�����Ă���s����t�s��Ƃ��Đݒ�
		bone.invOffset = DirectX::XMMatrixInverse(nullptr, m_nodes[bone.nodeIndex].mat);
		// �{�[���̏���ݒ�
		mesh.bones.resize(1);
		mesh.bones[0] = bone;

		// ���_���ׂĂ����蓖�Ă��{�[����100%�ˑ��Ƃ���
		for (auto vtxIt = mesh.vertices.begin(); vtxIt != mesh.vertices.end(); ++vtxIt)
			vtxIt->weight[0] = 1.0f;
	}
}



/*
* @brief assimp���̍s���XMMATRIX�^�ɕϊ�
* @param[in] M assimp�̍s��
* @return �ϊ���̍s��
*/
DirectX::XMMATRIX GetMatrixFromAssimpMatrix(aiMatrix4x4 M)
{
	return DirectX::XMMatrixSet(
		M.a1, M.b1, M.c1, M.d1,
		M.a2, M.b2, M.c2, M.d2,
		M.a3, M.b3, M.c3, M.d3,
		M.a4, M.b4, M.c4, M.d4
	);
}

/*
* @brief �f�t�H���g�̃V�F�[�_�[���쐬
* @param[out] vs ���_�V�F�[�_�[�i�[��
* @param[out] ps �s�N�Z���V�F�[�_�[�i�[��
*/
void MakeModelDefaultShader(VertexShader** vs, PixelShader** ps)
{
	const char* ModelVS = R"EOT(
struct VS_IN {
	float3 pos : POSITION0;
	float3 normal : NORMAL0;
	float2 uv : TEXCOORD0;
};
struct VS_OUT {
	float4 pos : SV_POSITION;
	float3 normal : NORMAL0;
	float2 uv : TEXCOORD0;
};
VS_OUT main(VS_IN vin) {
	VS_OUT vout;
	vout.pos = float4(vin.pos, 1.0f);
	vout.pos.z += 0.5f;
	vout.pos.y -= 0.8f;
	vout.normal = vin.normal;
	vout.uv = vin.uv;
	return vout;
})EOT";
	const char* ModelPS = R"EOT(
struct PS_IN {
	float4 pos : SV_POSITION;
	float3 normal : NORMAL0;
	float2 uv : TEXCOORD0;
};
Texture2D tex : register(t0);
SamplerState samp : register(s0);
float4 main(PS_IN pin) : SV_TARGET
{
	return tex.Sample(samp, pin.uv);
})EOT";
	*vs = new VertexShader();
	(*vs)->Compile(ModelVS);
	*ps = new PixelShader();
	(*ps)->Compile(ModelPS);
}

void Model::MakeMesh(const void* ptr)
{
	// ���O����
	aiVector3D zero3(0.0f, 0.0f, 0.0f);
	aiColor4D one4(1.0f, 1.0f, 1.0f, 1.0f);
	const aiScene* pScene = reinterpret_cast<const aiScene*>(ptr);
	float xFlip = m_loadFlip == Flip::XFlip ? -1.0f : 1.0f;
	float zFlip = (m_loadFlip == Flip::ZFlip || m_loadFlip == Flip::ZFlipUseAnime) ? -1.0f : 1.0f;
	int idx1 = (m_loadFlip == Flip::XFlip || m_loadFlip == Flip::ZFlip) ? 2 : 1;
	int idx2 = (m_loadFlip == Flip::XFlip || m_loadFlip == Flip::ZFlip) ? 1 : 2;

	// ���b�V���̍쐬
	m_meshes.resize(pScene->mNumMeshes);
	for (unsigned int i = 0; i < m_meshes.size(); ++i)
	{
		aiMesh* assimpMesh = pScene->mMeshes[i];
		Mesh& mesh = m_meshes[i];

		// �m�[�h�K�w���̒T��
		mesh.nodeIndex = FindNode(assimpMesh->mName.data);
		if (mesh.nodeIndex == NODE_NONE) { continue; }

		// ���_�������ݐ�̗̈��p��
		mesh.vertices.resize(assimpMesh->mNumVertices);

		// ���_�f�[�^�̏�������
		for (unsigned int j = 0; j < mesh.vertices.size(); ++j) {
			// ���f���f�[�^����l�̎擾
			aiVector3D pos = assimpMesh->mVertices[j];
			aiVector3D normal = assimpMesh->HasNormals() ? assimpMesh->mNormals[j] : zero3;
			aiVector3D uv = assimpMesh->HasTextureCoords(0) ?
				assimpMesh->mTextureCoords[0][j] : zero3;
			aiColor4D color = assimpMesh->HasVertexColors(0) ? assimpMesh->mColors[0][j] : one4;
			// �l��ݒ�
			mesh.vertices[j] = {
				DirectX::XMFLOAT3(pos.x * m_loadScale * xFlip, pos.y * m_loadScale, pos.z * m_loadScale * zFlip),
				DirectX::XMFLOAT3(normal.x, normal.y, normal.z),
				DirectX::XMFLOAT2(uv.x, uv.y),
				DirectX::XMFLOAT4(color.r, color.g, color.b, color.a)
			};
		}

		// �{�[������
		MakeVertexWeight(pScene, i);

		// �C���f�b�N�X�̏������ݐ�̗p��
		// mNumFaces�̓|���S���̐���\��(�P�|���S����3�C���f�b�N�X
		mesh.indices.resize(assimpMesh->mNumFaces * 3);

		// �C���f�b�N�X�̏�������
		for (unsigned int j = 0; j < assimpMesh->mNumFaces; ++j) {
			// ���f���f�[�^����l�̎擾
			aiFace face = assimpMesh->mFaces[j];

			// �l�̐ݒ�
			int idx = j * 3;
			mesh.indices[idx + 0] = face.mIndices[0];
			mesh.indices[idx + 1] = face.mIndices[idx1];
			mesh.indices[idx + 2] = face.mIndices[idx2];
		}

		// �}�e���A���̊��蓖��
		mesh.materialID = assimpMesh->mMaterialIndex;

		// ���b�V�������ɒ��_�o�b�t�@�쐬
		MeshBuffer::Description desc = {};
		desc.pVtx = mesh.vertices.data();
		desc.vtxSize = sizeof(Vertex);
		desc.vtxCount = mesh.vertices.size();
		desc.pIdx = mesh.indices.data();
		desc.idxSize = sizeof(unsigned long);
		desc.idxCount = mesh.indices.size();
		desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		mesh.pMesh = new MeshBuffer();
		mesh.pMesh->Create(desc);
	}
}

void Model::MakeMaterial(const void* ptr, std::string directory)
{
	// ���O����
	aiColor3D color(0.0f, 0.0f, 0.0f);
	const aiScene* pScene = reinterpret_cast<const aiScene*>(ptr);
	float shininess;

	// �}�e���A���̍쐬
	m_materials.resize(pScene->mNumMaterials);
	for (unsigned int i = 0; i < m_materials.size(); ++i)
	{
		aiMaterial* assimpMaterial = pScene->mMaterials[i];
		Material& material = m_materials[i];

		//--- �e��}�e���A���p�����[�^�[�̓ǂݎ��
		// �g�U���̓ǂݎ��
		if (assimpMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color) == AI_SUCCESS)
			material.diffuse = DirectX::XMFLOAT4(color.r, color.g, color.b, 1.0f);
		else
			material.diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		// �����̓ǂݎ��
		if (assimpMaterial->Get(AI_MATKEY_COLOR_AMBIENT, color) == AI_SUCCESS)
			material.ambient = DirectX::XMFLOAT4(color.r, color.g, color.b, 1.0f);
		else
			material.ambient = DirectX::XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
		// ���ˌ��̓ǂݎ��
		if (assimpMaterial->Get(AI_MATKEY_COLOR_SPECULAR, color) == AI_SUCCESS)
			material.specular = DirectX::XMFLOAT4(color.r, color.g, color.b, 0.0f);
		else
			material.specular = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
		// ���ˌ��̋�����ǂݎ��
		if (assimpMaterial->Get(AI_MATKEY_SHININESS, shininess) == AI_SUCCESS)
			material.specular.w = shininess;

		// �e�N�X�`���ǂݍ��ݏ���
		HRESULT hr;
		aiString path;

		// �e�N�X�`���̃p�X����ǂݍ���
		material.pTexture = nullptr;
		if (assimpMaterial->Get(AI_MATKEY_TEXTURE_DIFFUSE(0), path) != AI_SUCCESS) {
			continue;
		}

		// �e�N�X�`���̈�m��
		material.pTexture = new Texture;

		// ���̂܂ܓǂݍ���
		hr = material.pTexture->Create(path.C_Str());
		if (SUCCEEDED(hr)) { continue; }

		// �f�B���N�g���ƘA�����ĒT��
		hr = material.pTexture->Create((directory + path.C_Str()).c_str());
		if (SUCCEEDED(hr)) { continue; }

		// ���f���Ɠ����K�w��T��
		// �p�X����t�@�C�����̂ݎ擾
		std::string fullPath = path.C_Str();
		std::string baseDir = GetDirectory(fullPath.c_str());
		std::string fileName = fullPath.substr(baseDir.size());

		// �e�N�X�`���̓Ǎ�
		hr = material.pTexture->Create((directory + fileName).c_str());
		if (SUCCEEDED(hr)) { continue; }

		// �e�N�X�`����������Ȃ�����
		delete material.pTexture;
		material.pTexture = nullptr;
		SetErrorMessage("Not find texture. [" + fullPath + "]");
	}
}