#pragma once

#include "../defines/basic_defines.h"
#include <numbers>


namespace Empaerior
{
	namespace Math {

		//dergrees to radians
		EMP_FORCEINLINE Empaerior::fl_point d2r(Empaerior::fl_point d)
		{
			return (d / 180.0f) * Empaerior::fl_point(std::numbers::pi);
		}

		//sin & cos in degress
		EMP_FORCEINLINE Empaerior::fl_point sind(Empaerior::fl_point x)
		{

			return std::sin(d2r(x));
		}


		EMP_FORCEINLINE Empaerior::fl_point cosd(Empaerior::fl_point x)
		{
			return std::cos(d2r(x));
		}

		EMP_FORCEINLINE Empaerior::fl_point tand(Empaerior::fl_point x)
		{
			return std::tan(d2r(x));
		}



	}

}
