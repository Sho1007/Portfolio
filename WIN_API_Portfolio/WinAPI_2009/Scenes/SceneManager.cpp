#include "Framework.h"
#include "SceneManager.h"

SceneManager::SceneManager()
	: curScene(nullptr)
{
}

SceneManager::~SceneManager()
{
	for (auto scene : scenes)
	{
		delete scene.second;
	}
	scenes.clear();
}

void SceneManager::Update()
{
	if (curScene == nullptr)
		return;
	curScene->Update();
}

void SceneManager::Render(HDC hdc)
{
	if (curScene == nullptr)
		return;
	curScene->Render(hdc);
}

Scene* SceneManager::Add(string key, Scene* scene)
{
	if (scenes.count(key) > 0)
		return scenes[key];

	scenes[key] = scene;
	return scenes[key];
}

void SceneManager::ChangeScene(string key)
{
	if (scenes.count(key) == 0)
		return;

	if (curScene == scenes[key])
		return;

	if (curScene != nullptr)
		curScene->End();

	curScene = scenes[key];
	curScene->Start();
}
