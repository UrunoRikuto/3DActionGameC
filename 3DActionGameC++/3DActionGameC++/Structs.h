#pragma once
#include <DirectXMath.h>

/*
* @brief ステータスレベル情報
* @param 生命力：Vitality
* @param 筋　力：Muscle
* @param 精神力：Mental
* @param 持久力：Endurance
* @param 技　量：Skill
*/
struct StatusParameterLevel
{
	int Vitality;	// 生命力
	int Muscle;		// 筋  力
	int Mental;		// 精神力
	int Endurance;	// 持久力
	int Skill;		// 技  量
};