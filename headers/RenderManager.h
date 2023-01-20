#pragma once
#include <vector>
namespace Renderer
{

	class RenderObject
	{
	public:
		virtual void Draw() = 0;
		virtual void Update(double deltaTime) = 0;
	};

	class RendererManager
	{

	private:
		std::vector<RenderObject*> m_renderObjectList;

		bool Contains(std::vector<RenderObject*> list, RenderObject* obj);
		void RemoveObject(RenderObject* obj);

		std::vector<RenderObject*> m_objToDelete;

	public:
		RendererManager();
		~RendererManager();

		void ShouldRemove(RenderObject* obj);
		void AddObject(RenderObject* obj);
		void DrawObject();
		void UpdateObject(double deltaTime);

	};


}
