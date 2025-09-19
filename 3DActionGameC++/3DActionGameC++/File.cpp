/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
* file：File.cpp
*
* 概要：ファイル処理を管理するファイル
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/

#include "File.h"
#include <iostream>
#include <fstream>
#include "Main.h"


/// <summary>
/// JSONファイルを読み込む関数
/// </summary>
/// <param name="In_FilePath">ファイルパス</param>
/// <returns>読み込んだデータ</returns>
nlohmann::json LoadJson(const std::string& In_FilePath)
{
	// ファイルを開く
	std::ifstream file(In_FilePath);

	// ファイルが開けなかった場合のエラーメッセージ
	if (!file.is_open())
	{
		MessageBoxA(nullptr, "ファイルを開くことができませんでした ", "Error", MB_OK | MB_ICONERROR);
		return nlohmann::json();
	}

	// JSONデータを読み込む
	nlohmann::json jsonData;
	file >> jsonData;

	// ファイルを閉じる
	file.close();

	// 読み込んだJSONデータを返す
	return jsonData;
}
