#include "Model.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

/*
* @brief ���[�t�f�[�^�̒ǉ�
* @param[in] file �ǂݍ��ݐ�p�X
* @param[out] out �ǂݎ�����f�[�^�Ɋ��蓖�Ă�ꂽ�C���f�b�N�X(�����ǂݍ��މ\�������邽��
* @return �ǂݎ�茋��
*/
bool Model::AddMorph(const char* file, Indices* out)
{
	// Assimp���œǂݍ��݂����s
	const aiScene* pScene = static_cast<const aiScene*>(LoadAssimpScene(file));
	if (!pScene)
	{
#if MODEL_FORCE_ERROR
		ShowErrorMessage(file, false);
#endif
		return false;
	}

	// ���b�V���`�F�b�N
	if (IsError(!pScene->HasMeshes(), "no meshes."))
	{
#if MODEL_FORCE_ERROR
		ShowErrorMessage(file, true);
#endif
		return false;
	}

	// ���b�V�����ƂɊ��蓖�Ă��Ă��郂�[�t�^�[�Q�b�g���쐬
	for (unsigned int i = 0; i < pScene->mNumMeshes; ++i)
	{
		MakeMorphMesh(pScene->mMeshes[i], i, out);
	}

#if MODEL_FORCE_ERROR
	ShowErrorMessage(file, true);
#endif
	return true;
}

/*
* @brief ���[�t�̍����������w��
* @param[in] no �u�����h������ύX���郂�[�t�̃f�[�^
*/
void Model::SetMorphWeight(MorphNo no, float weight)
{
	if (no < m_morphes.size())
		m_morphes[no].weight = weight;
}

/*
* @brief ���[�t�A�j���[�V�����̓ǂݍ���
* @param[in] file �ǂݍ��ݐ�p�X
* @return �A�j���[�V�����ԍ�
*/
Model::AnimeNo Model::AddMorphAnime(const char* file)
{
	// Assimp���œǂݍ��݂����s
	const aiScene* pScene = static_cast<const aiScene*>(LoadAssimpScene(file));
	if (!pScene)
	{
#if MODEL_FORCE_ERROR
		ShowErrorMessage(file, false);
#endif
		return ANIME_NONE;
	}

	// �A�j���[�V�����f�[�^�̃`�F�b�N
	if (IsError(!pScene->HasAnimations(), "no morph anime."))
	{
#if MODEL_FORCE_ERROR
		ShowErrorMessage(file, true);
#endif
		return ANIME_NONE;
	}

	// ���[�t�A�j���[�V�����̃`�F�b�N
	aiAnimation* assimpAnime = pScene->mAnimations[0];
	if (IsError(assimpAnime->mNumMorphMeshChannels <= 0, "no morph anime."))
	{
#if MODEL_FORCE_ERROR
		ShowErrorMessage(file, true);
#endif
		return ANIME_NONE;
	}

	// �A�j���[�V�����Ώۂ̃��b�V�����ǂݍ��܂�Ă��邩�m�F
	aiMeshMorphAnim* assimpMorphAnime = assimpAnime->mMorphMeshChannels[0];
	std::string meshName = assimpMorphAnime->mName.data;
	meshName = meshName.substr(0, meshName.size() - 2); // assimp�̃A�j���[�V��������(����) "*0"���܂܂��̂ō폜
	NodeIndex mesh = FindNode(meshName.c_str());
	if (IsError(mesh == NODE_NONE, "no match morph target mesh."))
	{
#if MODEL_FORCE_ERROR
		ShowErrorMessage(file, false);
#endif
		return ANIME_NONE;
	}

	// �Y���̃��b�V���Ɋ��蓖�Ă��Ă��郂�[�t�f�[�^�̖��̂��擾
	using Names = std::vector<std::string>;
	Names morphNames;
	for (unsigned int i = 0; i < pScene->mNumMeshes; ++i) {
		
		// ���[�t�^�[�Q�b�g�̖��̂ƃ��b�V���̖��̂��m�F
		aiMesh* assimpMesh = pScene->mMeshes[i];
		if (meshName != assimpMesh->mName.data) { continue; }

		// ���b�V�����Ɋ��蓖�Ă��Ă��郂�[�t�̖��̂��擾
		for (unsigned int j = 0; j < assimpMesh->mNumAnimMeshes; ++j) {
			morphNames.push_back(assimpMesh->mAnimMeshes[j]->mName.data);
		}
		break;
	}

	// ���蓖�Ă��Ȃ��������̂��Ȃ����m�F
	if (IsError(morphNames.empty(), "no names."))
	{
#if MODEL_FORCE_ERROR
		ShowErrorMessage(file, false);
#endif
		return ANIME_NONE;
	}

	// �m���ɃA�j���[�V�����f�[�^�����肻���Ȃ̂ŁA�f�[�^���쐬
	m_morphAnimes.push_back({});
	MorphAnimation& anime = m_morphAnimes.back();

	// �A�j���[�V�����Ώۂ̃��[�t�̖��̂���A���ɓǂݍ��܂�Ă��郂�[�t�f�[�^�̃C���f�b�N�X�ɕϊ�
	Names::iterator it = morphNames.begin();
	while (it != morphNames.end()) {

		// ���[�t�f�[�^�̈ꗗ���疼�O�ƈ�v����f�[�^��T��
		auto morphIt = std::find_if(m_morphes.begin(), m_morphes.end(),
			[&it](MorphMesh& mesh) {
				return (*it) == mesh.name;
			});

		// �C���f�b�N�X�֕ϊ�
		if (morphIt != m_morphes.end()) {
			anime.morphs.push_back(static_cast<unsigned int>(morphIt - m_morphes.begin()));
		}
		else
			anime.morphs.push_back(-1);
		++it;
	}

	// �A�j���[�V�����f�[�^�̓ǂݎ��
	MakeMorphTimeline(anime, assimpAnime);
	// �^�C�����C���̍ŏI�f�[�^���A�j���[�V�����̍Đ����ԂƂ��Ċi�[
	anime.info.totalTime = anime.timelines.back().time;

#if MODEL_FORCE_ERROR
	ShowErrorMessage(file, true);
#endif
	return static_cast<AnimeNo>(m_morphAnimes.size() - 1);
}

/*
* @brief ���[�t�A�j���[�V�����̍Đ�
* @param[in] no �Đ�����A�j���[�V����
* @param[in] loop ���[�v�Đ��t���O
* @param[in] speed �Đ����x
*/
void Model::PlayMorph(AnimeNo no, bool loop, float speed)
{
	if (no < m_morphAnimes.size()) {
		m_morphPlayNo = no;
		m_morphAnimes[no].info.isLoop = loop;
		m_morphAnimes[no].info.speed = speed;
		m_morphAnimes[no].info.nowTime = 0.0f;
	}
}



/*
* @brief ���[�t�̃��b�V���f�[�^�쐬
* @param[in] ptr ���b�V���f�[�^
* @param[in] meshIndex ���[�t�Ή������郁�b�V���̃C���f�b�N�X
* @param[out] out ���[�t�𕡐��ǂݍ��񂾏ꍇ�̓ǂݎ��C���f�b�N�X���
*/
void Model::MakeMorphMesh(const void* ptr, int meshIndex, Indices* out)
{
	const aiMesh* asmpMesh = static_cast<const aiMesh*>(ptr);

	// ���[�t���܂܂�郁�b�V�����`�F�b�N
	unsigned int animeMeshNum = asmpMesh->mNumAnimMeshes;
	if (animeMeshNum <= 0)
	{
		std::string msg;
		msg += "no morph. [";
		msg += asmpMesh->mName.data;
		msg += "]";
		SetErrorMessage(msg.c_str());
		return;
	}

	// �������݉\�ȃ��b�V���ɕύX
	MeshBuffer* mesh = m_meshes[meshIndex].pMesh;
	MeshBuffer::Description desc = mesh->GetDesc();
	if (!desc.isWrite) {
		desc.pVtx = m_meshes[meshIndex].vertices.data();
		desc.pIdx = m_meshes[meshIndex].indices.data();
		desc.isWrite = true;
		mesh->Create(desc);
	}

	// ���[�t�^�[�Q�b�g�̃��b�V���𐶐�
	for (unsigned int i = 0; i < animeMeshNum; ++i)
	{
		const aiAnimMesh* animeMesh = asmpMesh->mAnimMeshes[i];

		// ���_������v���Ă��邩�m�F
		unsigned int vtxNum = animeMesh->mNumVertices;
		if (vtxNum != m_meshes[meshIndex].vertices.size())
		{
			std::string msg;
			msg += "no match morph vtxNum. [";
			msg += animeMesh->mName.data;
			msg += "]";
			SetErrorMessage(msg.c_str());
			continue;
		}

		// ���łɓ����̃��[�t���쐬����Ă��Ȃ�������
		auto it = std::find_if(m_morphes.begin(), m_morphes.end(),
			[&animeMesh](MorphMesh& mesh) {
				return mesh.name == animeMesh->mName.data;
			});
		if (it != m_morphes.end()) {
			continue;
		}

		// ���[�t�̏����쐬
		m_morphes.push_back({});
		Model::MorphMesh& morph = m_morphes.back();
		morph.name		= animeMesh->mName.data;
		morph.meshNo	= meshIndex;
		morph.weight	= animeMesh->mWeight;
		MakeMorphVertices(morph.vertices, animeMesh);

		// �����������[�t�̃C���f�b�N�X���쐬
		if (out) {
			out->push_back(static_cast<unsigned long>(m_morphes.size() - 1));
		}
	}
}

/*
* @brief ���[�t�̒��_�f�[�^�쐬
* @param[out] out ���_�f�[�^�i�[��
* @param[in] ptr ���b�V�����
*/
void Model::MakeMorphVertices(MorphVertices& out, const void* ptr)
{
	const aiAnimMesh* animeMesh = static_cast<const aiAnimMesh*>(ptr);
	unsigned int vtxNum = animeMesh->mNumVertices;

	out.resize(vtxNum);
	for(unsigned int i = 0; i < vtxNum; ++ i)
	{
		// ���W
		if (animeMesh->HasPositions()) {
			aiVector3D& vec = animeMesh->mVertices[i];
			out[i].pos = { vec.x * m_loadScale, vec.y * m_loadScale, vec.z * m_loadScale };
		}
		// �@��
		if (animeMesh->HasNormals()) {
			aiVector3D& vec = animeMesh->mNormals[i];
			out[i].normal = { vec.x, vec.y, vec.z };
		}
		// UV���W
		if (animeMesh->HasTextureCoords(0)) {
			aiVector3D& vec = animeMesh->mTextureCoords[0][i];
			out[i].uv = { vec.x, vec.y };
		}
	}
}

/*
* @brief �^�C�����C���f�[�^�̍쐬
* @param[out] anime �^�C�����C���f�[�^�i�[��
* @param[in] ptr ���[�t�̃A�j���[�V�����f�[�^
*/
void Model::MakeMorphTimeline(MorphAnimation& anime, const void* ptr)
{
	const aiAnimation* assimpAnime = static_cast<const aiAnimation*>(ptr);
	const aiMeshMorphAnim* assimpMorphAnime = assimpAnime->mMorphMeshChannels[0];
	float fbxToGameFrame = static_cast<float>(assimpAnime->mTicksPerSecond);
	
	// �L�[���ɉ����ă^�C�����C���쐬
	anime.timelines.resize(assimpMorphAnime->mNumKeys);
	for (unsigned int i = 0; i < assimpMorphAnime->mNumKeys; ++i)
	{
		aiMeshMorphKey* assimpKey = &assimpMorphAnime->mKeys[i];
		MorphTimeline& timeline = anime.timelines[i];

		// �^�C�����C���̃L�[���Ԃ�ݒ�
		timeline.time = static_cast<float>(assimpKey->mTime) / fbxToGameFrame;
		// ���O�v�Z�ς݂̊��蓖�ă��[�t���ɉ����ă^�C�����C���̃f�[�^���g��
		timeline.weights.resize(anime.morphs.size());

		// �����L�[���^�C�����C���Ɋ��蓖��
		int index = 0;
		for (int j = 0; j < timeline.weights.size(); ++j) {
			// ���蓖�čς݂̃��[�t�ɑ΂���L�[�����݂��邩����
			if (assimpKey->mValues[index] == j) {
				timeline.weights[assimpKey->mValues[index]] = static_cast<float>(assimpKey->mWeights[index]);
				++index;
			}
			else
			{
				// ��̏����ŕ�ԃf�[�^�i�[��Ƃ��āA-1��ݒ�
				timeline.weights[j] = -1.0f;
			}
		}
	}

	// �L�[���Ȃ������f�[�^�ɑ΂��ĕ�ԏ��������s
	for (int i = 0; i < anime.morphs.size(); ++i)
	{
		int index = 0;
		float value = anime.timelines[index].weights[i];

		// -1�ȊO�̃L�[���o�Ă���܂ŒT��
		while (value < 0.0f) {
			value = anime.timelines[index].weights[i];
			++index;
			if (index >= anime.timelines.size() && value < 0.0f) {
				value = 0.0f; // �Ō�܂�-1�̒l���i�[����Ă����ꍇ
				break;
			}
		}

		// �X�^�[�g�n�_�܂Ŗ߂��āA�T���ʒu�܂œ����f�[�^���i�[
		for (int j = index - 1; j >= 0; --j) {
			anime.timelines[j].weights[i] = value;
		}

		// �^�C�����C���̏I�[�܂�-1�̌��ɕ�ԃf�[�^���i�[
		while (index < anime.timelines.size() - 1) {
			// �T���ʒu�̍X�V
			int start = index;

			// -1�ȊO�̃L�[�܂ŒT��
			do {
				++index;
				// �I�[�ɓ��B����܂�-1�����Ȃ��ꍇ�A�X�^�[�g�n�_�̒l���i�[
				if (index >= anime.timelines.size()) {
					--index;
					value = anime.timelines[start].weights[i];
					break;
				}
				value = anime.timelines[index].weights[i];
			} while (value < 0.0f);

			// �J�n�n�_����T���ʒu�܂ŕ�ԃf�[�^���i�[
			AnimeTime startTime	= anime.timelines[start].time;
			AnimeTime timeLen	= anime.timelines[index].time - startTime;
			float startValue	= anime.timelines[start].weights[i];
			float endValue		= value;
			for (int j = start + 1; j <= index; ++j) {
				// ���݂̃L�[�ʒu�ɉ�������Ԃ̒l���v�Z
				float rate = (anime.timelines[j].time - startTime) / timeLen;
				anime.timelines[j].weights[i] = endValue * rate + startValue * (1.0f - rate);
			}
		}
	}
}

/*
* @brief ���[�t�̍������ʂ̍X�V
*/
void Model::UpdateMorph()
{
	// �X�V�\�ȃ��b�V����T��
	for(auto meshIt = m_meshes.begin(); meshIt != m_meshes.end(); ++ meshIt)
	{
		// �������ݕs�̃��b�V���Ɋւ��Ă͏������s��Ȃ�
		if (!meshIt->pMesh->GetDesc().isWrite) { continue; }

		// �Y���̔ԍ��̃��b�V���Ɉ�v���郂�[�t�^�[�Q�b�g��T��
		std::vector<int> morphIdx;
		int meshNo = static_cast<int>(meshIt - m_meshes.begin());
		auto morphIt = m_morphes.begin();
		float totalWeight = 0.0f;
		while (morphIt != m_morphes.end()) {
			if (morphIt->meshNo == meshNo) {
				if (morphIt->weight > FLT_EPSILON) {
					// ���b�V���ɂ�����ő�E�F�C�g�̌v�Z
					totalWeight += morphIt->weight;
					// �X�V���K�v�ȃ��[�t�̏���ۑ�
					morphIdx.push_back(static_cast<NodeIndex>(morphIt - m_morphes.begin()));
				}
			}
			++morphIt;
		}

		// �u�����h�O�̃f�[�^�����O�R�s�[
		Vertices vtx;
		vtx.resize(meshIt->vertices.size());
		for (unsigned int i = 0; i < meshIt->vertices.size(); ++i) {
			vtx[i] = meshIt->vertices[i];
			// ���[�t�̃u�����h�Ώۂ̃f�[�^����������
			vtx[i].pos = {};
			vtx[i].normal = {};
			vtx[i].uv = {};
		}


		// �u�����h�̊�����1.0�ɖ����Ȃ��ꍇ�A�c��̊������f�t�H���g�̒��_�Ƃ̃u�����h�ƌ��Ȃ�
		if (totalWeight < 1.0f)
		{
			float weight = 1.0f - totalWeight;
			auto vtxIt = meshIt->vertices.begin();
			while (vtxIt != meshIt->vertices.end()) {
				AddMorphVtxWeight(
					&vtx[vtxIt - meshIt->vertices.begin()],
					{ vtxIt->pos, vtxIt->normal, vtxIt->uv }, weight);
				++vtxIt;
			}
			totalWeight = 1.0f;
		}

		// ���[�t�^�[�Q�b�g�Ɋ�Â��ău�����h�̊������w��
		auto idxIt = morphIdx.begin();
		while (idxIt != morphIdx.end())
		{
			auto morph = m_morphes[*idxIt];
			auto vtxIt = morph.vertices.begin();
			while (vtxIt != morph.vertices.end()) {
				AddMorphVtxWeight(
					&vtx[vtxIt - morph.vertices.begin()],
					*vtxIt, morph.weight / totalWeight);
				++vtxIt;
			}
			++idxIt;
		}

		// ���[�t�̍������ʂ���������
		meshIt->pMesh->Write(vtx.data());
	}
}

/*
* @brief ���[�t�A�j���[�V�����̍X�V
* @param[in] tick �X�V����
*/
void Model::StepMorph(float tick)
{
	// �A�j���[�V�����`�F�b�N
	if (m_morphPlayNo == ANIME_NONE) { return; }

	// �A�j���[�V�����Đ����Ԃ̍X�V
	MorphAnimation& anime = m_morphAnimes[m_morphPlayNo];
	anime.info.nowTime += tick * anime.info.speed;
	CheckAnimePlayLoop(anime.info);

	// ���݂̎�������e���[�t�̃u�����h�������v�Z
	float totalWeight = 0.0f;
	if (anime.info.nowTime <= anime.timelines[0].time)
	{
		// �ŏ��̃L�[���O�̎��Ԃ́A�擪�̒l�Ōv�Z
		SetMorphWeight(m_morphPlayNo, anime.timelines[0].weights[0]);
		totalWeight += anime.timelines[0].weights[0];
	}
	else if (anime.info.nowTime >= anime.timelines.back().time)
	{
		// �ŏI�̃L�[����̎��Ԃ́A�ŏI�̒l�Ōv�Z
		SetMorphWeight(m_morphPlayNo, anime.timelines.back().weights[0]);
		totalWeight = anime.timelines.back().weights[0];
	}
	else
	{
		// �^�C�����C�����̒l�́A�O��̃L�[�̕�ԂŌv�Z
		for (int i = 1; i < anime.timelines.size(); ++i)
		{
			if (anime.info.nowTime > anime.timelines[i].time) { continue; }

			// ��Ԃ̊������v�Z
			auto start	= anime.timelines[i - 1];
			auto end	= anime.timelines[i];
			float rate = (anime.info.nowTime - start.time) / (end.time - start.time);

			// �������[�t�̃u�����h�����v�Z
			for (int j = 0; j < anime.morphs.size(); ++j) {
				float weight = end.weights[j] * rate + start.weights[j] * (1.0f - rate);
				SetMorphWeight(anime.morphs[j], weight);
				totalWeight += weight;
			}
			break;
		}
	}

	// �A�j���[�V�����ΏۈȊO�̃��[�t�̃u�����h��ύX
	float weight = 1.0f - std::min(1.0f, totalWeight);
	for (int i = 0; i < m_morphes.size(); ++i) {
		bool isAnime = false;
		for (int j = 0; j < anime.morphs.size(); ++j) {
			if (i == anime.morphs[j]) {
				isAnime = true;
				break;
			}
		}

		if (!isAnime) {
			SetMorphWeight(i, m_morphes[i].weight * weight);
		}
	}
}

/*
* @brief ���[�t�������̒��_�f�[�^�̌v�Z
* @param[out] out ������f�[�^
* @param[in] in �������f�[�^
* @param[in] weight ���f�[�^�̍�������
*/
void Model::AddMorphVtxWeight(Vertex* out, MorphVertex in, float weight)
{
	out->pos.x += in.pos.x * weight;
	out->pos.y += in.pos.y * weight;
	out->pos.z += in.pos.z * weight;
	out->normal.x += in.normal.x * weight;
	out->normal.y += in.normal.y * weight;
	out->normal.z += in.normal.z * weight;
	out->uv.x += in.uv.x * weight;
	out->uv.y += in.uv.y * weight;
}

