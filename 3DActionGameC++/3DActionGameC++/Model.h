/*
* @date 2024.12.27 morphing�ǉ�
* @date 2025.01.04 morphing�A�j���[�V�������݂Ŏb��Ŋ���
* @date 2025.01.06 �t���[�Y�̃G���[���b�Z�[�W�\��
* @date 2025.01.09 ���t�@�N�^�����O
* @brief 
* @ �����A�j���[�V�����Ƃ�(���̂����ǋL
* 
*/
#ifndef __MODEL_H__
#define __MODEL_H__

#include <DirectXMath.h>
#include <vector>
#include "Shader.h"
#include "MeshBuffer.h"
#include <functional>

#ifdef _DEBUG
#define MODEL_FORCE_ERROR (1) // �G���[���b�Z�[�W�����\��
#else
#define MODEL_FORCE_ERROR (0)
#endif

class Model
{
public:
	// ���f�����]�ݒ�
	enum Flip
	{
		None,			// DirectX����(���]����
		XFlip,			// Maya����
		ZFlip,			// DirectX����(Maya����180��]�������
		ZFlipUseAnime,	// DirecX����(�A�j���[�V����������ꍇ�@������`�F�b�N�s�\��
	};

private:
	// �A�j���[�V�����Đ����@
	enum AnimePattern
	{
		MAIN,			// �ʏ�Đ�
		BLEND,			// �u�����h�Đ�
		PARAMETRIC0,	// ����A
		PARAMETRIC1,	// ����B
		MAX_ANIMEPATTERN
	};

public:
	// �^��`
	using NodeIndex	= int;	// �{�[��(�K�w)�ԍ�
	using MorphNo	= int;	// ���[�t�f�[�^�ԍ�
	using AnimeNo	= int;	// �A�j���[�V�����ԍ�

	// �萔��`
	static const NodeIndex	NODE_NONE			= -1;	// �Y���m�[�h�Ȃ�
	static const MorphNo	MORPH_NONE			= -1;	// �Y�����[�t�Ȃ�
	static const AnimeNo	ANIME_NONE			= -1;	// �Y���A�j���[�V�����Ȃ�
	static const AnimeNo	PARAMETRIC_ANIME	= -2;	// �����A�j���[�V����

private:
	// �����^��`
	using AnimeTime = float;
	using Children	= std::vector<NodeIndex>;	// �m�[�h�K�w���

	// �����萔��`
	static const UINT	MAX_BONE	= 200;	// �P���b�V���̍ő�{�[����(������ύX����ꍇ.hlsl���̒�`���ύX����
	static const UINT	MAX_WEIGHT	= 4;	// �P���_�Ɋ��蓖�Ă���ő�{�[����

	// �K�w���
	struct Node
	{
		std::string			name;		// �K�w��
		NodeIndex			parent;		// �e�{�[��
		Children			children;	// �q�{�[��
		DirectX::XMMATRIX	mat;		// �A�j���[�V�����p�ϊ��s��
	};
	using Nodes = std::vector<Node>;

	// �A�j���[�V�����Đ����
	struct AnimePlayInfo
	{
		AnimeTime		nowTime;	// ���݂̍Đ�����
		AnimeTime		totalTime;	// �ő�Đ�����
		float			speed;		// �Đ����x
		bool			isLoop;		// ���[�v�w��
	};

	//===== �A�j���[�V���� =====
	// �A�j���[�V�����̕ϊ����
	struct AnimeTransform
	{
		DirectX::XMFLOAT3	translate;
		DirectX::XMFLOAT4	quaternion;
		DirectX::XMFLOAT3	scale;
	};
	using AnimeKey			= std::pair<AnimeTime, AnimeTransform>;
	using AnimeTimeline		= std::map<AnimeTime, AnimeTransform>;
	using AnimeTransforms	= std::vector<AnimeTransform>;

	// �A�j���[�V�����ƃm�[�h�̊֘A�t�����
	struct AnimeChannel
	{
		NodeIndex		node;		// �Ή�����m�[�h
		AnimeTimeline	timeline;	// �m�[�h�ɕt������A�j���[�V�������
	};
	using AnimeChannels = std::vector<AnimeChannel>;

	// �A�j���[�V�������
	struct Animation
	{
		AnimePlayInfo	info;		// �Đ����
		AnimeChannels	channels;	// �ϊ����
	};
	using Animations = std::vector<Animation>;

	//===== �u�����h�V�F�C�v =====
	// ���[�t�B���O�p���_
	struct MorphVertex
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 normal;
		DirectX::XMFLOAT2 uv;
	};
	using MorphVertices = std::vector<MorphVertex>;

	// ���[�t�B���O�p���b�V��
	struct MorphMesh
	{
		std::string		name;		// ���[�t�f�[�^��
		int				meshNo;		// �Ή����郁�b�V��
		float			weight;		// �u�����h����
		MorphVertices	vertices;	// �ό`���_���
	};
	using MorphMeshes = std::vector<MorphMesh>;

	// ���[�t�B���O�A�j���[�V�������̃u�����h���
	using MorphAnimeWeights = std::vector<float>;	// �A�j���[�V�������̃u�����h����
	struct MorphTimeline
	{
		AnimeTime			time;		// �A�j���[�V�������s����
		MorphAnimeWeights	weights;	// ���[�t�^�[�Q�b�g���Ƃ̃u�����h����
	};
	using MorphTimelines	= std::vector<MorphTimeline>;

	// ���[�t�B���O�̃A�j���[�V�������
	using MorphAnimeTargets = std::vector<unsigned int>;
	struct MorphAnimation
	{
		AnimePlayInfo		info;		// �Đ����
		MorphAnimeTargets	morphs;		// �Đ����ɕύX���郂�[�t�^�[�Q�b�g
		MorphTimelines		timelines;	// �A�j���[�V�������
	};
	using MorphAnimations = std::vector<MorphAnimation>;

public:
	// ���_���
	struct Vertex
	{
		DirectX::XMFLOAT3	pos;
		DirectX::XMFLOAT3	normal;
		DirectX::XMFLOAT2	uv;
		DirectX::XMFLOAT4	color;
		float				weight[MAX_WEIGHT];
		unsigned int		index[MAX_WEIGHT];
	};
	using Vertices	= std::vector<Vertex>;
	using Indices	= std::vector<unsigned long>;

	// �{�[�����
	struct Bone
	{
		NodeIndex			nodeIndex;	// �ό`���͊K�w���Ɋi�[
		DirectX::XMMATRIX	invOffset;	// �t�s��
	};
	using Bones = std::vector<Bone>;

	// ���b�V��
	struct Mesh
	{
		NodeIndex		nodeIndex;	// �K�w�Ƃ̕R�Â�
		Vertices		vertices;	// ���_���
		Indices			indices;	// �C���f�b�N�X���
		unsigned int	materialID;	// �g�p����}�e���A��
		Bones			bones;		// ���b�V���ɕR�Â���Ă���{�[��
		MeshBuffer*		pMesh;		// �`��f�[�^
	};
	using Meshes = std::vector<Mesh>;

	// �}�e���A�����
	struct Material
	{
		DirectX::XMFLOAT4	diffuse;	// �g�U��(���C���J���[
		DirectX::XMFLOAT4	ambient;	// ����(�A�̕����̃J���[
		DirectX::XMFLOAT4	specular;	// ���ʔ��ˌ�(�������镔���̃J���[
		Texture*			pTexture;	// �e�N�X�`��
	};
	using Materials = std::vector<Material>;


public:
	Model();
	~Model();

	//========================================
	//     ��{����
	//========================================
	/*
	* @brief ���Z�b�g
	*/
	void Reset();

	/*
	* @brief ���_�V�F�[�_�[�̐ݒ�
	* @param[in] vs ���_�V�F�[�_�[
	*/
	void SetVertexShader(Shader* vs);

	/*
	* @brief �s�N�Z���V�F�[�_�[�̐ݒ�
	* @param[in] ps �s�N�Z���V�F�[�_�[
	*/
	void SetPixelShader(Shader* ps);

	/*
	* @brief ���f���f�[�^�̓ǂݍ���
	* @param[in] file �ǂݍ��ݐ�p�X
	* @param[in] scale �g�嗦
	* @param[in] flip ���]�ݒ�
	* @return �ǂݍ��݌���
	*/
	bool Load(const char* file, float scale = 1.0f, Flip flip = Flip::None);

	/*
	* @brief �X�V����
	* @param[in] tick �o�ߎ���(�b)
	*/
	void Step(float tick);

	/*
	* @brief �`�揈��
	* @param[in] meshNo �`�惁�b�V���ԍ�(-1�ł��ׂĕ\��
	*/
	void Draw(int meshNo = -1);


	//========================================
	//     �`�F�b�N����
	//========================================
	/*
	* @brief �ǂݍ��ݏ������s��̃G���[���b�Z�[�W�擾
	* @return �G���[���b�Z�[�W
	*/
	static std::string GetError();

	/*
	* @brief �{�[���̃f�o�b�O�\��
	* @param[in] world ���[���h�s��
	*/
	void DrawBone(DirectX::XMMATRIX world = DirectX::XMMatrixIdentity());

	//========================================
	//     �A�j���[�V����
	//========================================
	/*
	* @brief �A�j���[�V�����f�[�^�̒ǉ��ǂݍ���
	* @param[in] file �ǂݍ��ݐ�p�X
	* @return �A�j���[�V�����ԍ�
	*/
	AnimeNo AddAnimation(const char* file);

	/*
	* @brief �A�j���[�V�����̍Đ�
	* @param[in] no �Đ�����A�j���[�V�����ԍ�
	* @param[in] loop ���[�v�Đ��t���O
	* @param[in] speed �Đ����x
	*/
	void PlayAnime(AnimeNo no, bool loop, float speed = 1.0f);

	/*
	* @brief �u�����h�Đ�
	* @param[in] no �A�j���[�V�����ԍ�
	* @param[in] blendTime �u�����h�Ɋ|���鎞��
	* @param[in] loop ���[�v�t���O
	* @param[in] speed �Đ����x
	*/
	void PlayBlend(AnimeNo no, AnimeTime blendTime, bool loop, float speed = 1.0f);

	/*
	* @brief �A�j���[�V�����̍����Đ�
	* @param[in] no1 �������P
	* @param[in] no2 �������Q
	*/
	void SetParametric(AnimeNo no1, AnimeNo no2);

	/*
	* @brief �����������w��
	* @param[in] blendRate 0�`1�̊Ԃ�no1��no2�̃A�j��������(0��no1,1��no2)
	*/
	void SetParametricBlend(float blendRate);

	/*
	* @brief �A�j���[�V�����̌��݂̍Đ����Ԃ�ύX
	* @param[in] no �ύX�Ώۂ̃A�j���[�V�����ԍ�
	* @param[in] time �ύX��̎���
	*/
	void SetAnimeTime(AnimeNo no, AnimeTime time);



	//========================================
	//     �u�����h�V�F�C�v
	//========================================
	/*
	* @brief ���[�t�f�[�^�̒ǉ�
	* @param[in] file �ǂݍ��ݐ�p�X
	* @param[out] out �ǂݎ�����f�[�^�Ɋ��蓖�Ă�ꂽ�C���f�b�N�X(�����ǂݍ��މ\�������邽��
	* @return �ǂݎ�茋��
	*/
	bool AddMorph(const char* file, Indices* out = nullptr);

	/*
	* @brief ���[�t�̍����������w��
	* @param[in] no ������ύX���郂�[�t
	* @param[in] weight ��������
	*/
	void SetMorphWeight(MorphNo no, float weight);

	/*
	* @brief ���[�t�A�j���[�V�����̒ǉ��ǂݍ���
	* @param[in] file �ǂݍ��ݐ�p�X
	* @return �A�j���[�V�����ԍ�
	*/
	AnimeNo AddMorphAnime(const char* file);

	/*
	* @brief ���[�t�A�j���[�V�����̍Đ�
	* @param[in] no �Đ�����A�j���[�V����
	* @param[in] loop ���[�v�Đ��t���O
	* @param[in] speed �Đ����x
	*/
	void PlayMorph(AnimeNo no, bool loop, float speed = 1.0f);


	//========================================
	//     ���擾
	//========================================
	/*
	* @brief ���b�V�������擾
	* @return ���b�V����
	*/
	unsigned int GetMeshNum();

	/*
	* @brief ���b�V�������擾
	* @param[in] index �擾���郁�b�V���ԍ�
	* @return ���b�V�����
	*/
	const Mesh* GetMesh(unsigned int index);

	/*
	* @brief �}�e���A�������擾
	* @return �}�e���A����
	*/
	unsigned int GetMaterialNum();

	/*
	* @brief �}�e���A�������擾
	* @param[in] index �擾����}�e���A���ԍ�
	* @return �}�e���A�����
	*/
	const Material* GetMaterial(unsigned int index);

	/*
	* @brief �A�j���[�V������̕ϊ��s��擾
	* @param[in] index �{�[���ԍ�
	* @return �Y���{�[���̕ϊ��s��
	*/
	DirectX::XMMATRIX GetBoneMatrix(NodeIndex index);
	
	/*
	* @brief �A�j���[�V�����Đ�����
	* @param[in] no �A�j���[�V�����ԍ�
	* @return �Đ���
	*/
	bool IsAnimePlay(AnimeNo no);

	/*
	* @brief �Đ����̃A�j���ԍ��擾
	* @return �A�j���[�V�����ԍ�
	*/
	AnimeNo GetAnimePlayNo();

	/*
	* @brief �Đ����̃u�����h�ԍ��擾
	* @return �A�j���[�V�����ԍ�
	*/
	AnimeNo GetAnimeBlendNo();

	/*
	* @brief �A�j���[�V�������擾
	* @return �A�j���[�V�������
	*/
	const AnimePlayInfo* GetPlayAnimeInfo();

private:
	//========================================
	//     ��{����
	//========================================
	// assimp�Ńf�[�^��ǂݍ���
	const void* LoadAssimpScene(const char* file);
	// �K�w���̍\�z
	void MakeNodes(const void* ptr);
	// ���b�V���̍쐬
	void MakeMesh(const void* ptr);
	// �}�e���A���̍쐬
	void MakeMaterial(const void* ptr, std::string directory);
	// ���_�u�����h�̍쐬
	void MakeVertexWeight(const void* ptr, int meshIndex);
	// �{�[������̒��_�u�����h�쐬
	void MakeVertexWeightHasBone(const void* ptr, Mesh& mesh);
	// �e�q�֌W�����Ƃɒ��_�u�����h�쐬
	void MakeVertexWeightFromNode(const void* scene, const void* ptr, Mesh& mesh);

	//========================================
	//     �`�F�b�N����
	//========================================
	// �A�j���[�V�����̃��[�v�`�F�b�N
	void CheckAnimePlayLoop(AnimePlayInfo& info);
	// �G���[�`�F�b�N
	bool IsError(bool condition, std::string message);
	// �G���[���b�Z�[�W�̐ݒ�
	void SetErrorMessage(std::string message);
	// �G���[���b�Z�[�W�̕\��
	void ShowErrorMessage(const char* caption, bool isWarning);
	// �m�[�h�T��
	NodeIndex FindNode(const char* name);
	// �t���[�Y�ς݃��b�V���̃`�F�b�N
	bool CheckMeshFreeze(const void* ptr);
	// �A�j���[�V�����ԍ��̃`�F�b�N
	bool CheckAnimeNo(AnimeNo no);


	//========================================
	//     �A�j���[�V����
	//========================================
	// �A�j���[�V�����̍X�V
	void StepAnime(float tick);
	// �A�j���[�V�����̏�����
	void InitAnime(AnimeNo no);
	// �A�j���[�V�����̍Đ����̍X�V
	void UpdateAnime(AnimeNo no, float tick);
	// �A�j���[�V�����̎p���s����v�Z
	void CalcAnime(AnimePattern kind, AnimeNo no);
	// �Đ����@�ʂ̍s�񌋉ʂ̍���
	void CalcBones(NodeIndex index, const DirectX::XMMATRIX parent);
	// �s�񌋉ʓ��m�̕��
	void LerpTransform(AnimeTransform* pOut, const AnimeTransform& a, const AnimeTransform& b, float rate);

	//========================================
	//     �u�����h�V�F�C�v
	//========================================
	// ���[�t�̃��b�V���f�[�^�쐬
	void MakeMorphMesh(const void* ptr, int meshIndex, Indices* out);
	// ���[�t�̃��b�V���Ɋ��蓖�Ă��钸�_�f�[�^�̍쐬
	void MakeMorphVertices(MorphVertices& out, const void* ptr);
	// ���[�t�A�j���[�V�����̃^�C�����C���쐬
	void MakeMorphTimeline(MorphAnimation& anime, const void* ptr);
	// ���[�t�̍X�V
	void UpdateMorph();
	// ���[�t�A�j���[�V�����̍X�V
	void StepMorph(float tick);
	// ���[�t�������̒��_�v�Z
	void AddMorphVtxWeight(Vertex* out, MorphVertex in, float weight);

	//========================================
	//     ���擾
	//========================================
	// �f�B���N�g���̎擾
	std::string GetDirectory(const char* file);

private:
	static VertexShader*	m_pDefVS;		// �f�t�H���g���_�V�F�[�_�[
	static PixelShader*		m_pDefPS;		// �f�t�H���g�s�N�Z���V�F�[�_�[
	static unsigned int		m_shaderRef;	// �V�F�[�_�[�Q�Ɛ�
#ifdef _DEBUG
	static std::string m_errorStr;	
#endif

private:
	float			m_loadScale;	// �ǂݍ��ݎ��̊g�嗦
	Flip			m_loadFlip;		// �ǂݍ��ݎ��̔��]�ݒ�
	VertexShader*	m_pVS;			// �ݒ蒆�̒��_�V�F�[�_
	PixelShader*	m_pPS;			// �ݒ蒆�̃s�N�Z���V�F�[�_
	Nodes			m_nodes;		// �K�w���
	Meshes			m_meshes;		// ���b�V���z��
	Materials		m_materials;	// �}�e���A���z��
	
	AnimeTransforms	m_animeTransform[MAX_ANIMEPATTERN];	// �A�j���[�V�����Đ����@�ʕό`���
	Animations		m_animes;			// �A�j���z��
	AnimeNo			m_playNo;			// ���ݍĐ����̃A�j���ԍ�
	AnimeNo			m_blendNo;			// �u�����h�Đ����s���A�j���ԍ�
	AnimeNo			m_parametric[2];	// �����Đ����s���A�j���ԍ�
	AnimeTime		m_blendTime;		// ���݂̑J�ڌo�ߎ���
	AnimeTime		m_blendTotalTime;	// �A�j���J�ڂɂ����鍇�v����
	float			m_parametricBlend;	// �p�����g���b�N�̍Đ�����

	MorphMeshes		m_morphes;		// ���[�t�z��
	MorphAnimations m_morphAnimes;	// ���[�t�A�j���z��
	AnimeNo			m_morphPlayNo;	// �Đ����̃��[�t�A�j���[�V����
};


#endif // __MODEL_H__