/*������������������������������������������������������������������������������������������������������������������������������
*
* file�FFile.cpp
*
* �T�v�F�t�@�C���������Ǘ�����t�@�C��
*
������������������������������������������������������������������������������������������������������������������������������*/

#include "File.h"
#include <iostream>
#include <fstream>
#include "Main.h"


/// <summary>
/// JSON�t�@�C����ǂݍ��ފ֐�
/// </summary>
/// <param name="In_FilePath">�t�@�C���p�X</param>
/// <returns>�ǂݍ��񂾃f�[�^</returns>
nlohmann::json LoadJson(const std::string& In_FilePath)
{
	// �t�@�C�����J��
	std::ifstream file(In_FilePath);

	// �t�@�C�����J���Ȃ������ꍇ�̃G���[���b�Z�[�W
	if (!file.is_open())
	{
		MessageBoxA(nullptr, "�t�@�C�����J�����Ƃ��ł��܂���ł��� ", "Error", MB_OK | MB_ICONERROR);
		return nlohmann::json();
	}

	// JSON�f�[�^��ǂݍ���
	nlohmann::json jsonData;
	file >> jsonData;

	// �t�@�C�������
	file.close();

	// �ǂݍ���JSON�f�[�^��Ԃ�
	return jsonData;
}
