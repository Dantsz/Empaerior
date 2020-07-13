#pragma once
#include <glm/glm.hpp>
namespace Empaerior
{

	struct Camera2D
	{
		Camera2D()
		{
			position_mat = glm::translate(glm::mat4(1.0f), position);
		}

		glm::mat4 scale;
		glm::mat4 position_mat;
		glm::mat4 proj;

		glm::vec3 position = {0,0,0};

	};

}