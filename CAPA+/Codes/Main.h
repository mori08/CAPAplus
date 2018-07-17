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
	/// 画像・音をアセット管理します。
	/// </summary>
	/// <param name="direname"> 管理したいディレクトリ </param>
	void asseter(String direname);

}