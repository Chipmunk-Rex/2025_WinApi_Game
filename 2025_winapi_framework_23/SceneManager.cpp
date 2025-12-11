#include "pch.h"
#include "SceneManager.h"
#include "DevScene.h"
#include "TestScene.h"
#include "Object.h"
#include "Collider.h"
#include "SceneSelectWindow.h"
#include "Core.h"
#include "UIScene.h"
#include "EnemyTestScene.h"
#include "StartScene.h"
#include "GameOverScene.h"
#include "EndingScene.h"
void SceneManager::Init()
{
	m_curScene = nullptr;

	// 씬 등록
	RegisterScene(L"TestScene", new TestScene());
	RegisterScene(L"DevScene", new DevScene());
	RegisterScene(L"UIScene", new UIScene());
	RegisterScene(L"EnemyTestScene", new EnemyTestScene());
	RegisterScene(L"StartScene", new StartScene());
	RegisterScene(L"GameOverScene", new GameOverScene());
	RegisterScene(L"EndingScene", new EndingScene());

	LoadScene(L"StartScene");
	// 첫 씬 지정
}

void SceneManager::Update()
{
	if (m_curScene == nullptr)
		return;
	m_curScene->Update();
	m_curScene->LateUpdate();
}

void SceneManager::FixedUpdate(float _fixedDT)
{
	if (m_curScene == nullptr)
		return;
	m_curScene->FixedUpdate(_fixedDT);
}

void SceneManager::Render(HDC _hdc)
{
	if (m_curScene == nullptr)
		return;
	m_curScene->Render(_hdc);
}

void SceneManager::RegisterScene(const wstring& _name, Scene* _scene)
{
	if (_name.empty() || _scene == nullptr)
		return;
	m_mapScenes.insert(m_mapScenes.end(), { _name, _scene });
}

void SceneManager::LoadScene(const wstring& _name)
{
	// 2번째 load 일시 change 역할
	if (m_curScene != nullptr)
	{
		m_curScene->Release();
		m_curScene = nullptr;
	}
	auto iter = m_mapScenes.find(_name);
	if (iter != m_mapScenes.end())
	{
		m_curScene = iter->second;
		m_curScene->Init();
	}
}

void SceneManager::ReleaseScenes()
{
	// 현재 씬 해제 로직은 각 씬 Release에서 수행됨
	for (auto& kv : m_mapScenes)
	{
		Scene* scn = kv.second;
		if (scn)
		{
			// 씬 내부 객체 정리
			scn->Release();
			delete scn;
		}
	}
	m_mapScenes.clear();
	m_curScene = nullptr;
}
