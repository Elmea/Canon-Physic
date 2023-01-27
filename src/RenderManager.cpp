#include "RenderManager.h"
#include "Projectile.h"
#include <algorithm>
#include <iostream>
namespace Renderer
{
	
	RendererManager::RendererManager()
	{
	}

	RendererManager::~RendererManager()
	{
		for (std::vector<RenderObject*>::iterator i = m_renderObjectList.begin(); i != m_renderObjectList.end(); ++i)
		{
			delete((*i));
		}

		m_renderObjectList.clear();
	}

	bool RendererManager::Contains(std::vector<RenderObject*> list, RenderObject* obj)
	{

		if (std::find(list.begin(), list.end(), obj) != list.end()) return true;

		return false;
	}

	void RendererManager::ShouldRemove(RenderObject* obj)
	{
		if (!Contains(m_renderObjectList, obj)) return;

		m_objToDelete.push_back(obj);
	}

	void RendererManager::AddObject(RenderObject* obj)
	{
		if (Contains(m_renderObjectList, obj)) return; 

		m_renderObjectList.push_back(obj);
	}
	
	void RendererManager::RemoveObject(RenderObject* obj)
	{
		m_renderObjectList.erase(std::remove(m_renderObjectList.begin(), m_renderObjectList.end(), obj), m_renderObjectList.end());
		delete obj;
		m_renderObjectList.shrink_to_fit();
	}

	void RendererManager::DrawObject()
	{
		for (std::vector<RenderObject*>::iterator i = m_renderObjectList.begin() ; i != m_renderObjectList.end(); ++i)
		{
			(*i)->Draw();
		}
	}

	void RendererManager::UpdateObject(double deltaTime)
	{
		for (std::vector<RenderObject*>::iterator i = m_renderObjectList.begin(); i != m_renderObjectList.end(); i++)
		{
			(*i)->Update(deltaTime);
		}


		for (auto obj : m_objToDelete)
		{
			RemoveObject(obj);
		}
		m_objToDelete.clear();

	}
	
}