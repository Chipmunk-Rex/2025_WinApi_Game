#include "pch.h"
#include "SceneManager.h"
#include "DevScene.h"
#include "TestScene.h"
#include "Object.h"
#include "Collider.h"
#include "SceneSelectWindow.h"
#include "Core.h"
#include "UIScene.h"
void SceneManager::Init()
{
	m_curScene = nullptr;

	// �� ���
	RegisterScene(L"TestScene", std::make_shared<TestScene>());
	RegisterScene(L"DevScene", std::make_shared<DevScene>());
	RegisterScene(L"UIScene", std::make_shared<UIScene>());

	SceneSelectWindow sceneSelectWindow;
	sceneSelectWindow.Run(GET_SINGLE(Core)->GetHinstance(), SW_SHOWDEFAULT);
	// ù �� ����
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

void SceneManager::RegisterScene(const wstring& _name, std::shared_ptr<Scene> _scene)
{
	if (_name.empty() || _scene == nullptr)
		return;
	m_mapScenes.insert(m_mapScenes.end(), { _name, _scene });
}

void SceneManager::LoadScene(const wstring& _name)
{
	// 2��° load �Ͻ� change ����
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
