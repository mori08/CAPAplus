#include<Siv3D.hpp>

#include"ControllPanel.h"

#include"Home.h"

#include"Calendar.h"

#include"Editor.h"

#include"Search.h"

#include"BackGround.h"

#include"CardListManager.h"

#include"Define.h"

#include"StringInputer.h"



using namespace My;


void Main()
{
	Data::Note::accessBook().readAllText();

	WaitKey();

	asseter(L"Assets/");

	const String FONT_NAME = L"メイリオ";

	FontAsset::Register(L"10", 10, FONT_NAME);

	FontAsset::Register(L"15", 15, FONT_NAME);

	FontAsset::Register(L"20", 20, FONT_NAME);

	FontAsset::Register(L"25", 25, FONT_NAME);

	
	MyApp scene_manager;

	scene_manager.add<Scene::Home>(L"Home");
	scene_manager.add<Scene::Calendar>(L"Calendar");
	scene_manager.add<Scene::Editor>(L"Editor");
	scene_manager.add<Scene::Search>(L"Search");

	while (System::Update())
	{
		UI::BackGound::Instatnce().updateAndDraw();

		UI::ControlPanel::Instance().update();

		UI::ControlPanel::Instance().draw();

		scene_manager.updateAndDraw();

#ifdef _DEBUG

		FontAsset(L"10")(Profiler::FPS(), L"fps").draw(Point(600, 0));

#endif // _DEBUG
	}
	
	Data::Note::accessBook().writeAllText();
}



void My::asseter(String direname)
{
	// 指定されたディレクトリのファイルパスを配列に
	Array<FilePath> contents = FileSystem::DirectoryContents(direname);


	for (const auto& content : contents)
	{

		String filename = FileSystem::FileName(content);


		// 指定されたパスがディレクトリであるとき
		if (FileSystem::IsDirectory(content))
		{
			asseter(direname + filename + L"/"); // 関数を再び呼ぶ
		}


		// 指定されたパスがファイルであるとき
		else if (FileSystem::IsFile(content))
		{

			// 拡張子がpngのとき
			if (FileSystem::Extension(content) == L"png")
			{
				TextureAsset::Register(FileSystem::BaseName(content), direname + filename);
			}

			// 拡張子がmp3のとき
			else if (FileSystem::Extension(content) == L"mp3")
			{
				SoundAsset::Register(FileSystem::BaseName(content), direname + filename);
			}

		}
	}
}
