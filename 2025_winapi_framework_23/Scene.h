#pragma once
#include "Object.h"
//class Object;
struct SpawnObject
{
	Object* obj;
	Layer type;
};

class Scene
{
public:
	Scene();
	virtual ~Scene();
public:
	virtual void Init() abstract;
	virtual void Update();
	virtual void LateUpdate();
	virtual void FixedUpdate(float _fixedDT);
	virtual void Render(HDC _hdc);
	virtual void Release();
public:
	const vector<Object*>& GetLayerObjects(Layer _type) const
	{
		return m_vecObj[(UINT)_type];
	}

	const vector<Object*>& GetLayerObjects(LayerMask layermask) const
	{
		static vector<Object*> result;
		result.clear();
		for (UINT i = 0; i < (UINT)Layer::END; ++i)
		{
			if (layermask & (1 << i))
			{
				const vector<Object*>& layerObjects = m_vecObj[i];
				result.insert(result.end(), layerObjects.begin(), layerObjects.end());
			}
		}
		return result;
	}

public:
	void AddObject(Object* _obj, Layer _type)
	{
		m_vecObj[(UINT)_type].push_back(_obj);
		_obj->SetLayer(_type);
	}
	template<typename T>
	T* Spawn(Layer _type, Vec2 _pos, Vec2 _size)
	{
		static_assert(std::is_base_of<Object,T>::value, "Object로부터 상속받아야 함");
		T* obj = new T;
		obj->SetPos(_pos);
		obj->SetSize(_size);
		AddObject(obj, _type);
		return obj;
	}
	template<typename T>
	T* Spawn(Layer _type)
	{
		static_assert(std::is_base_of<Object, T>::value, "Object로부터 상속받아야 함");
		T* obj = new T;
		AddObject(obj, _type);
		return obj;
	}
	void RequestDestroy(Object* obj); // 지연삭제
	void RequestSpawn(Object* obj, Layer _type); // 지연생성
	void FlushEvent();
private:
	void RemoveObject(Object* _obj);
private:
	vector<Object*> m_vecObj[(UINT)Layer::END];
	vector<Object*> m_killObject;
	vector<SpawnObject> m_spawnObject;
};

