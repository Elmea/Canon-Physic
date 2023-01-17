#pragma once
#include <vector>
namespace Renderer
{

	class RenderObject
	{
	public:
		virtual void Draw() = 0;
		virtual void Update() = 0;
	};

	class RendererManager
	{

	private:
		std::vector<RenderObject*> m_renderObjectList;

		bool Contains(std::vector<RenderObject*> list, RenderObject* obj);

	public:
		RendererManager();
		~RendererManager();

		void AddObject(RenderObject* obj);
		void RemoveObject(RenderObject* obj);
		void DrawObject();
		void UpdateObject();

	};


}
