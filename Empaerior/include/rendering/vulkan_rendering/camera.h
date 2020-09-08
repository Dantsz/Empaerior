#pragma once
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../../core/defines/defines.h"
namespace Empaerior
{

	struct Camera2D
	{
		Camera2D()
		{
			position_mat = glm::translate(glm::mat4(1.0f), position);
			
		}

		glm::mat4 scale_mat;
		glm::mat4 position_mat;
		glm::mat4 proj;

		glm::vec3 position = {0,0,0};
		Empaerior::fl_point scaleX = 1.0f;
		Empaerior::fl_point scaleY = 1.0f;
	};

}