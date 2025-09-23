/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
* file：Easing.h
*
* 概要：イージング関数を管理するファイル
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/

#pragma once
#include "StructMath.h"
#include <cmath>

/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
/*＝　　　EaseOutQuart　　　＝*/
/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/

/// <summary>
/// EaseOutQuartのイージング関数
/// </summary>
/// <param name="t">経過時間</param>
/// <returns>計算結果</returns>
inline  float easeOutQuart(float t)
{
    return 1 - pow(1 - t, 4);
}
/// <summary>
/// EaseOutQuartの移動関数
/// </summary>
/// <param name="t">経過時間</param>
/// <param name="start">初期位置</param>
/// <param name="end">最終位置</param>
/// <returns>計算結果</returns>
inline XMFLOAT2 easeMoveOutQuart(float t, XMFLOAT2 start, XMFLOAT2 end) 
{
    float easedT = easeOutQuart(t);
    return 
    {
        start.x + (end.x - start.x) * easedT,
        start.y + (end.y - start.y) * easedT
    };
}




/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
/*＝　　　EaseOutBack　　　 ＝*/
/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/

/// <summary>
/// EaseOutBackのイージング関数
/// </summary>
/// <param name="t">経過時間</param>
/// <param name="overshoot">過剰量</param>
/// <returns>計算結果</returns>
inline float easeOutBack(float t, float overshoot = 1.70158f) 
{
    return 1 + (--t) * t * ((overshoot + 1) * t + overshoot);
}

/// <summary>
/// EaseOutBackの移動関数
/// </summary>
/// <param name="t">経過時間</param>
/// <param name="start">開始位置</param>
/// <param name="end">最終位置</param>
/// <param name="overshoot">過剰量</param>
/// <returns>計算結果</returns>
inline XMFLOAT2 easeMoveOutBack(float t, XMFLOAT2 start, XMFLOAT2 end, float overshoot = 1.70158f)
{
    float easedT = easeOutBack(t, overshoot);
    return 
    {
        start.x + (end.x - start.x) * easedT,
        start.y + (end.y - start.y) * easedT
    };
}




/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
/*＝　　　EaseOutQuint　　　＝*/
/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/

/// <summary>
/// EaseOutQuintのイージング関数
/// </summary>
/// <param name="t">現在時間</param>
/// <returns>計算結果</returns>
inline float easeOutQuint(float t) 
{
    return 1 - pow(1 - t, 5);
}

/// <summary>
/// EaseOutQuintの移動関数
/// </summary>
/// <param name="t">現在時間</param>
/// <param name="start">開始位置</param>
/// <param name="end">最終位置</param>
/// <returns>計算結果</returns>
inline XMFLOAT2 easeMoveOutQuint(float t, XMFLOAT2 start, XMFLOAT2 end)
{
	float easedT = easeOutQuint(t);
	return
	{
		start.x + (end.x - start.x) * easedT,
		start.y + (end.y - start.y) * easedT
	};
}
