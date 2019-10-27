#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

namespace mini
{
	class Transform final
	{
		glm::ivec3 mPosition;
	public:
		const glm::ivec3& GetPosition() const { return mPosition; }
		void SetPosition(int x, int y, int z);
	};
}
