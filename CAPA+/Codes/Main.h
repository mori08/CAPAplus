#pragma once


#include<Siv3D.hpp>

#include<HamFramework.hpp>

#include"Data\Day\Day.h"



struct GameData
{
	My::Data::Day day;
};

using MyApp = SceneManager<String, GameData>;



namespace My
{

	/// <summary>
	/// �摜�E�����A�Z�b�g�Ǘ����܂��B
	/// </summary>
	/// <param name="direname"> �Ǘ��������f�B���N�g�� </param>
	void asseter(String direname);

}