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
		glm::mat4 scale_mat = glm::translate(glm::mat4(1.0f), {0,0,0});;
		glm::mat4 position_mat = glm::scale(glm::mat4(1.0f),glm::vec3(1.0f,1.0f,1.0f));
		glm::mat4 proj = glm::ortho(0.0f, 1.0f, 0.0f,1.0f, -1.0f, 1.0f);

		glm::vec3 position = {0,0,0};
		Empaerior::fl_point scaleX = 1.0f;
		Empaerior::fl_point scaleY = 1.0f;
	};

}
