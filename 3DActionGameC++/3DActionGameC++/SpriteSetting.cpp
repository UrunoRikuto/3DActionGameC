#include "SpriteSetting.h"

CSpriteSetting::CSpriteSetting()
	: m_nAnimeFrame(0)
	, m_nAnimeNo(0)
	, m_fAnimeU(0.0f)
	, m_fAnimeV(0.0f)
{

}

CSpriteSetting::~CSpriteSetting()
{

}

void CSpriteSetting::Update(float InUV[][4], int InFrameTime, int InResetFrame, int InMaxFrame)
{
	if (m_nAnimeFrame >= InFrameTime)
	{
		m_nAnimeNo++;
		if (m_nAnimeNo >= InMaxFrame)
		{
			m_nAnimeNo = InResetFrame;
		}
		m_fAnimeU = InUV[m_nAnimeNo][2];
		m_fAnimeV = InUV[m_nAnimeNo][3];
		m_nAnimeFrame = 0;
	}
	else
	{
		m_nAnimeFrame++;
	}
}

void CSpriteSetting::Reset(float InUV[][4])
{
	m_nAnimeFrame = 0;
	m_nAnimeNo = 0;
	m_fAnimeU = InUV[0][2];
	m_fAnimeV = InUV[0][3];
}
