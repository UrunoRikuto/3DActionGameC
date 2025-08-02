#include "Model.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

/*
* @brief �A�j���[�V�����f�[�^�̒ǉ��ǂݍ���
* @param[in] file �ǂݍ��ݐ�p�X
* @return �A�j���[�V�����ԍ�
*/
Model::AnimeNo Model::AddAnimation(const char* file)
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

	// �A�j���[�V�����`�F�b�N
	if (IsError(!pScene->HasAnimations(), "no animation."))
	{
#if MODEL_FORCE_ERROR
		ShowErrorMessage(file, false);
#endif
		return ANIME_NONE;
	}

	// �A�j���[�V�����f�[�^�m��
	aiAnimation* assimpAnime = pScene->mAnimations[0];
	m_animes.push_back(Animation());
	Animation& anime = m_animes.back();

	// �A�j���[�V�����ݒ�
	using XMVectorKey = std::pair<float, DirectX::XMVECTOR>;
	using XMVectorKeys = std::map<float, DirectX::XMVECTOR>;
	float fbxToGameFrame = static_cast<float>(assimpAnime->mTicksPerSecond);
	anime.info.totalTime = static_cast<float>(assimpAnime->mDuration) / fbxToGameFrame;
	anime.info.speed = 1.0f;

	anime.channels.resize(assimpAnime->mNumChannels);
	AnimeChannels::iterator channelIt = anime.channels.begin();
	for(auto channelIt = anime.channels.begin(); channelIt != anime.channels.end(); ++channelIt)
	{
		// �Ή�����`�����l��(�{�[��)��T��
		uint32_t channelIdx = static_cast<uint32_t>(channelIt - anime.channels.begin());
		aiNodeAnim* assimpChannel = assimpAnime->mChannels[channelIdx];
		channelIt->node = FindNode(assimpChannel->mNodeName.data);
		if (channelIt->node == NODE_NONE) { continue; }

		// �e�L�[�̒l��z��ɃR�s�[
		XMVectorKeys keys[3];
		AnimeTimeline& timeline = channelIt->timeline;
		// �ʒu
		for (UINT i = 0; i < assimpChannel->mNumPositionKeys; ++i)
		{
			aiVectorKey& key = assimpChannel->mPositionKeys[i];
			keys[0].insert(XMVectorKey(static_cast<float>(key.mTime) / fbxToGameFrame,
				DirectX::XMVectorSet(key.mValue.x, key.mValue.y, key.mValue.z, 0.0f)
			));
		}
		// ��]
		for (UINT i = 0; i < assimpChannel->mNumRotationKeys; ++i)
		{
			aiQuatKey& key = assimpChannel->mRotationKeys[i];
			keys[1].insert(XMVectorKey(static_cast<float>(key.mTime) / fbxToGameFrame,
				DirectX::XMVectorSet(key.mValue.x, key.mValue.y, key.mValue.z, key.mValue.w)));
		}
		// �g�k
		for (UINT i = 0; i < assimpChannel->mNumScalingKeys; ++i)
		{
			aiVectorKey& key = assimpChannel->mScalingKeys[i];
			keys[2].insert(XMVectorKey(static_cast<float>(key.mTime) / fbxToGameFrame,
				DirectX::XMVectorSet(key.mValue.x, key.mValue.y, key.mValue.z, 0.0f)));
		}

		// �e�^�C�����C���̐擪�̎Q�Ƃ�ݒ�
		XMVectorKeys::iterator it[] = { keys[0].begin(), keys[1].begin(), keys[2].begin() };
		for (int i = 0; i < 3; ++i)
		{
			// �L�[��������Ȃ��ꍇ�́A�Q�ƏI��
			if (keys[i].size() == 1)
				++it[i];
		}

		// �e�v�f���Ƃ̃^�C�����C���ł͂Ȃ��A���ׂĂ̕ϊ����܂߂��^�C�����C���̍쐬
		while (it[0] != keys[0].end() && it[1] != keys[1].end() && it[2] != keys[2].end())
		{
			// ����̎Q�ƈʒu�ň�ԏ��������Ԃ��擾
			float time = anime.info.totalTime;
			for (int i = 0; i < 3; ++i)
			{
				if (it[i] != keys[i].end())
				{
					time = std::min(it[i]->first, time);
				}
			}

			// ���ԂɊ�Â��ĕ�Ԓl���v�Z
			DirectX::XMVECTOR result[3];
			for (int i = 0; i < 3; ++i)
			{
				// �擪�̃L�[��菬�������Ԃł���΁A�擪�̒l��ݒ�
				if (time < keys[i].begin()->first)
				{
					result[i] = keys[i].begin()->second;
				}
				// �ŏI�L�[���傫�����Ԃł���΁A�ŏI�̒l��ݒ�
				else if (keys[i].rbegin()->first <= time)
				{
					result[i] = keys[i].rbegin()->second;
					it[i] = keys[i].end();
				}
				// �L�[���m�ɋ��܂ꂽ���Ԃł���΁A��Ԓl���v�Z
				else
				{
					// �Q�Ƃ��Ă��鎞�ԂƓ����ł���΁A���̎Q�ƂփL�[��i�߂�
					if (it[i]->first <= time)
					{
						++it[i];
					}

					// ��Ԓl�̌v�Z
					XMVectorKeys::iterator prev = it[i];
					--prev;
					float rate = (time - prev->first) / (it[i]->first - prev->first);
					result[i] = DirectX::XMVectorLerp(prev->second, it[i]->second, rate);
				}
			}

			// �w�莞�ԂɊ�Â����L�[��ǉ�
			AnimeTransform transform;
			DirectX::XMStoreFloat3(&transform.translate, result[0]);
			DirectX::XMStoreFloat4(&transform.quaternion, result[1]);
			DirectX::XMStoreFloat3(&transform.scale, result[2]);
			timeline.insert(AnimeKey(time, transform));
		}
	}

	// �A�j���ԍ���Ԃ�
	return static_cast<AnimeNo>(m_animes.size() - 1);
}

/*
* @brief �A�j���[�V�����Đ�
* @param[in] no �Đ�����A�j���[�V�����ԍ�
* @param[in] loop ���[�v�Đ��t���O
* @param[in] speed �Đ����x
*/
void Model::PlayAnime(AnimeNo no, bool loop, float speed)
{
	// �Đ��`�F�b�N
	if (!CheckAnimeNo(no)) { return; }
	if (m_playNo == no) { return; }

	// �����A�j���[�V�������`�F�b�N
	if (no != PARAMETRIC_ANIME)
	{
		// �ʏ�̏�����
		InitAnime(no);
		m_animes[no].info.isLoop	= loop;
		m_animes[no].info.speed		= speed;
	}
	else
	{
		// �����A�j���[�V�����̌��ɂȂ��Ă���A�j���[�V������������
		InitAnime(m_parametric[0]);
		InitAnime(m_parametric[1]);
		m_animes[m_parametric[0]].info.isLoop = loop;
		m_animes[m_parametric[1]].info.isLoop = loop;
		SetParametricBlend(0.0f);
	}

	// �Đ��A�j���[�V�����̐ݒ�
	m_playNo = no;
}

/*
* @brief �u�����h�Đ�
* @param[in] no �A�j���[�V�����ԍ�
* @param[in] blendTime �u�����h�Ɋ|���鎞��
* @param[in] loop ���[�v�t���O
* @param[in] speed �Đ����x
*/
void Model::PlayBlend(AnimeNo no, AnimeTime blendTime, bool loop, float speed)
{
	// �Đ��`�F�b�N
	if (!CheckAnimeNo(no)) { return; }

	// �����A�j���[�V�������`�F�b�N
	if (no != PARAMETRIC_ANIME)
	{
		InitAnime(no);
		m_animes[no].info.isLoop = loop;
		m_animes[no].info.speed = speed;
	}
	else
	{
		// �����A�j���[�V�����̌��ɂȂ��Ă���A�j���[�V������������
		InitAnime(m_parametric[0]);
		InitAnime(m_parametric[1]);
		m_animes[m_parametric[0]].info.isLoop = loop;
		m_animes[m_parametric[1]].info.isLoop = loop;
		SetParametricBlend(0.0f);
	}

	// �u�����h�̐ݒ�
	m_blendTime = 0.0f;
	m_blendTotalTime = blendTime;
	m_blendNo = no;
}

/*
* @brief �������A�j���[�V�����̐ݒ�
* @param[in] no1 �������A�j��1
* @param[in] no2 �������A�j��2
*/
void Model::SetParametric(AnimeNo no1, AnimeNo no2)
{
	// �A�j���[�V�����`�F�b�N
	if (!CheckAnimeNo(no1)) { return; }
	if (!CheckAnimeNo(no2)) { return; }

	// �����ݒ�
	m_parametric[0] = no1;
	m_parametric[1] = no2;
	SetParametricBlend(0.0f);
}

/*
* @brief �A�j���[�V�����̍��������ݒ�
* @param[in] blendRate ��������
*/
void Model::SetParametricBlend(float blendRate)
{
	// �������A�j�����ݒ肳��Ă��邩�m�F
	if (m_parametric[0] == ANIME_NONE || m_parametric[1] == ANIME_NONE) return;

	// ���������ݒ�
	m_parametricBlend = blendRate;

	// �����Ɋ�Â��ăA�j���[�V�����̍Đ����x��ݒ�
	Animation& anime1 = m_animes[m_parametric[0]];
	Animation& anime2 = m_animes[m_parametric[1]];
	float blendTotalTime =
		anime1.info.totalTime * (1.0f - m_parametricBlend) +
		anime2.info.totalTime * m_parametricBlend;
	anime1.info.speed = anime1.info.totalTime / blendTotalTime;
	anime2.info.speed = anime2.info.totalTime / blendTotalTime;
}

/*
* @brief �A�j���[�V�����̍Đ����Ԃ�ύX
* @param[in] no �ύX����A�j��
* @param[in] time �V�����Đ�����
*/
void Model::SetAnimeTime(AnimeNo no, AnimeTime time)
{
	// �A�j���[�V�����`�F�b�N
	if (!CheckAnimeNo(no)) { return; }
	if (no == PARAMETRIC_ANIME) { return; }

	// �Đ����ԕύX
	Animation& anime = m_animes[no];
	anime.info.nowTime = time;
	CheckAnimePlayLoop(anime.info);
}



/*
* @brief �A�j���[�V�����̍X�V
* @param[in] tick �X�V����
*/
void Model::StepAnime(float tick)
{
	// �A�j���[�V�����̍Đ��m�F
	if (m_playNo == ANIME_NONE) { return; }

	//--- �A�j���[�V�����s��̍X�V
	// �p�����g���b�N
	if (m_playNo == PARAMETRIC_ANIME || m_blendNo == PARAMETRIC_ANIME)
	{
		CalcAnime(PARAMETRIC0, m_parametric[0]);
		CalcAnime(PARAMETRIC1, m_parametric[1]);
	}
	// ���C���A�j��
	if (m_playNo != ANIME_NONE && m_playNo != PARAMETRIC_ANIME)
	{
		CalcAnime(MAIN, m_playNo);
	}
	// �u�����h�A�j��
	if (m_blendNo != ANIME_NONE && m_blendNo != PARAMETRIC_ANIME)
	{
		CalcAnime(BLEND, m_blendNo);
	}

	// �A�j���[�V�����s��Ɋ�Â��č��s����X�V
	CalcBones(0, DirectX::XMMatrixScaling(m_loadScale, m_loadScale, m_loadScale));

	//--- �A�j���[�V�����̎��ԍX�V
	// ���C���A�j��
	UpdateAnime(m_playNo, tick);
	// �u�����h�A�j��
	if (m_blendNo != ANIME_NONE)
	{
		UpdateAnime(m_blendNo, tick);
		m_blendTime += tick;
		if (m_blendTime <= m_blendTime)
		{
			// �u�����h�A�j���̎����I��
			m_blendTime = 0.0f;
			m_blendTotalTime = 0.0f;
			m_playNo = m_blendNo;
			m_blendNo = ANIME_NONE;
		}
	}
	// �p�����g���b�N
	if (m_playNo == PARAMETRIC_ANIME || m_blendNo == PARAMETRIC_ANIME)
	{
		UpdateAnime(m_parametric[0], tick);
		UpdateAnime(m_parametric[1], tick);
	}
}

/*
* @brief �A�j���[�V�������̏�����
* @param[in] no �A�j���[�V�����ԍ�
*/
void Model::InitAnime(AnimeNo no)
{
	// �A�j���̐ݒ�Ȃ��A�p�����g���b�N�Őݒ肳��Ă���Ȃ珉�������Ȃ�
	if (no == ANIME_NONE || no == PARAMETRIC_ANIME) { return; }

	Animation& anime	= m_animes[no];
	anime.info.nowTime	= 0.0f;
	anime.info.speed	= 1.0f;
	anime.info.isLoop	= false;
}

/*
* @brief �A�j���[�V�����̍X�V
* @param[in] no �A�j���[�V�����ԍ�
* @param[in] tick �X�V����
*/
void Model::UpdateAnime(AnimeNo no, float tick)
{
	// �A�j���[�V�����`�F�b�N
	if (!CheckAnimeNo(no)) { return; }
	if (no == PARAMETRIC_ANIME) { return; }

	// �A�j���[�V�������Ԃ̍X�V
	Animation& anime = m_animes[no];
	SetAnimeTime(no, anime.info.nowTime + anime.info.speed * tick);
}

/*
* @brief ���Ԃɉ����ăA�j���[�V�����̃^�C�����C���̒l���v�Z
* @param[in] kind �X�V����A�j���[�V�����̎��
* @param[in] no �A�j���[�V�����ԍ�
*/
void Model::CalcAnime(AnimePattern kind, AnimeNo no)
{
	// �A�j���[�V�����`�F�b�N
	if (!CheckAnimeNo(no)) { return; }
	if (no == PARAMETRIC_ANIME) { return; }

	Animation& anime = m_animes[no];
	AnimeChannels::iterator channelIt = anime.channels.begin();
	for(auto channelIt = anime.channels.begin(); channelIt != anime.channels.end(); ++channelIt)
	{
		// �A�j���[�V�����ŕύX����{�[�����Ȃ���΃X�L�b�v
		if (channelIt->node == NODE_NONE) { continue; }

		// �^�C�����C���̐ݒ肪�Ȃ���΃X�L�b�v
		AnimeTimeline& timeline = channelIt->timeline;
		if (timeline.empty()) { continue; }

		// �{�[���̎p�����^�C�����C���ɉ����čX�V
		AnimeTransform& transform = m_animeTransform[kind][channelIt->node];
		if (timeline.size() <= 1)
		{
			// �L�[��������Ȃ��̂Œl�����̂܂܎g�p
			transform = channelIt->timeline[0];
		}
		else
		{
			AnimeTimeline::iterator startIt = timeline.begin();
			if (anime.info.nowTime <= startIt->first)
			{
				// �擪�L�[�����O�̎��ԂȂ�A�擪�̒l���g�p
				transform = startIt->second;
			}
			else if (timeline.rbegin()->first <= anime.info.nowTime)
			{
				// �ŏI�L�[������̎��ԂȂ�A�Ō�̒l���g�p
				transform = timeline.rbegin()->second;
			}
			else
			{
				// �w�肳�ꂽ���Ԃ�����2�̃L�[����A��Ԃ��ꂽ�l���v�Z
				AnimeTimeline::iterator nextIt = timeline.upper_bound(anime.info.nowTime);
				startIt = nextIt;
				--startIt;
				float rate = (anime.info.nowTime - startIt->first) / (nextIt->first - startIt->first);
				LerpTransform(&transform, startIt->second, nextIt->second, rate);
			}
		}
	}
}

/*
* @brief �A�j���[�V�����Đ����@�ʂɌv�Z����Ă���s�������
* @param[in] index �v�Z�Ώۂ̃m�[�h
* @param[in] parennt �e�̎p���s��
*/
void Model::CalcBones(NodeIndex index, const DirectX::XMMATRIX parent)
{
	AnimeTransform transform; // �������ʂ̊i�[��

	// �p�����g���b�N�̍���
	if (m_playNo == PARAMETRIC_ANIME || m_blendNo == PARAMETRIC_ANIME)
	{
		LerpTransform(&transform,
			m_animeTransform[PARAMETRIC0][index],
			m_animeTransform[PARAMETRIC1][index],
			m_parametricBlend);

		// �̂��̃u�����h�Ƃ̍����̂��߂ɁA�p�����g���b�N�̌��ʂ��Đ��E�u�����h�̂����ꂩ�Ɋi�[
		if (m_playNo == PARAMETRIC_ANIME) { m_animeTransform[MAIN][index] = transform; }
		if (m_blendNo == PARAMETRIC_ANIME) { m_animeTransform[BLEND][index] = transform; }
	}

	// �u�����h�A�j���̍���
	if (m_blendNo != ANIME_NONE)
	{
		LerpTransform(&transform,
			m_animeTransform[MAIN][index],
			m_animeTransform[BLEND][index],
			m_blendTime / m_blendTotalTime);
	}
	else
	{
		// �����̕K�v���Ȃ������̂ŁA���C���̏������̂܂܊i�[
		transform = m_animeTransform[MAIN][index];
	}

	// �Y���m�[�h�̎p���s����v�Z
	Node& node = m_nodes[index];
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslationFromVector(DirectX::XMLoadFloat3(&transform.translate));
	DirectX::XMMATRIX R = DirectX::XMMatrixRotationQuaternion(DirectX::XMLoadFloat4(&transform.quaternion));
	DirectX::XMMATRIX S = DirectX::XMMatrixScalingFromVector(DirectX::XMLoadFloat3(&transform.scale));
	node.mat = (S * R * T) * parent;

	// �q�v�f�̎p�����X�V
	Children::iterator it = node.children.begin();
	while (it != node.children.end())
	{
		CalcBones(*it, node.mat);
		++it;
	}
}

/*
* @brief �A�j���[�V�����̕��
* @param[out] pOut ���ʂ̊i�[��
* @param[in] a ��Ԍ�1
* @param[in] b ��Ԍ�2
* @param[in] rate ��Ԋ���
*/
void Model::LerpTransform(AnimeTransform* pOut, const AnimeTransform& a, const AnimeTransform& b, float rate)
{
	// ��Ԍ��̏����x�N�g���Ɋi�[
	DirectX::XMVECTOR vec[][2] = {
		{ DirectX::XMLoadFloat3(&a.translate),	DirectX::XMLoadFloat3(&b.translate) },
		{ DirectX::XMLoadFloat4(&a.quaternion),	DirectX::XMLoadFloat4(&b.quaternion) },
		{ DirectX::XMLoadFloat3(&a.scale),		DirectX::XMLoadFloat3(&b.scale) },
	};

	// ���(��Quaternion�����͋��ʕ�Ԃ��K�v�H
	for (int i = 0; i < 3; ++i)
		vec[i][0] = DirectX::XMVectorLerp(vec[i][0], vec[i][1], rate);

	// �v�Z���ʂ̊i�[
	DirectX::XMStoreFloat3(&pOut->translate, vec[0][0]);
	DirectX::XMStoreFloat4(&pOut->quaternion, vec[1][0]);
	DirectX::XMStoreFloat3(&pOut->scale, vec[2][0]);
}