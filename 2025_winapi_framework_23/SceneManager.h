#pragma once
//class Scene;
#include "Scene.h"
class SceneManager
{
	DECLARE_SINGLE(SceneManager);
public:
	void Init();
	void Update(); // LateUpdate;
	void FixedUpdate(float _fixedDT);
	void Render(HDC _hdc);
public:
	void RequestDestroy(Object* obj)
	{
		if (obj == nullptr || obj->GetIsDead())
			return;

		if (m_curScene)
			m_curScene->RequestDestroy(obj);
	}
public:
	void RegisterScene(const wstring& _name, Scene* _scene);
	void LoadScene(const wstring& _name);
	void ReleaseScenes();
public:
	Scene* GetCurScene() const
	{
		return m_curScene;
	}
	const std::unordered_map<wstring, Scene*>& GetAllScenes() const
	{
		return m_mapScenes;
	}
private:
	Scene* m_curScene;
	std::unordered_map<wstring, Scene*> m_mapScenes;
};
