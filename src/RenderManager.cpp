#include "RenderManager.h"
#include <algorithm>

namespace Renderer
{
	
	RendererManager::RendererManager()
	{
	}

	RendererManager::~RendererManager()
	{
	}

	bool RendererManager::Contains(std::vector<RenderObject*> list, RenderObject* obj)
	{

		if (std::find(list.begin(), list.end(), obj) != list.end()) return true;

		return false;
	}

	void RendererManager::AddObject(RenderObject* obj)
	{
		if (Contains(m_renderObjectList, obj)) return; 

		m_renderObjectList.push_back(obj);
	}
	
	void RendererManager::RemoveObject(RenderObject* obj)
	{
		if (!Contains(m_renderObjectList, obj)) return;

		m_renderObjectList.push_back(obj);
	}

	void RendererManager::DrawObject()
	{
		for (std::vector<RenderObject*>::iterator i = m_renderObjectList.begin() ; i != m_renderObjectList.end(); i++)
		{
			(*i)->Draw();
		}
	}
}