#pragma once
#include "point2.h"
#include "utilities/math.h"

namespace Empaerior
{
#pragma region Rect
	//A simple Rectangl without roation
	template <typename T>
	struct S_Rect
	{
		T x, y;
		T w, h;

		S_Rect<T>& operator = (const S_Rect<T>& rect)
		{
			x = rect.x;
			y = rect.y;
			w = rect.w;
			h = rect.h;
			return *this;
		}


	};

	//Rectangle with rotation
	template <typename T, typename rotation_type>
	struct T_Rect
	{
		S_Rect<T> dimensions;
		rotation_type angle; // the angle of rotation

		T_Rect<T, rotation_type>& operator =(const T_Rect<T, rotation_type>& rect)
		{
			dimensions = rect.dimensions;
			angle = rect.angle;
			return *this;
		}

		T_Rect<T, rotation_type>& operator=(const S_Rect<T>& t_rect)
		{
			dimensions = t_rect;
			return *this;
		}


	};

	
	enum Rect_Corners
	{
		top_left = 0,
		bottom_left = 1,
		top_right = 2,
		bottom_right = 3

	};

	namespace Rect_Funct
	{


		//Functions to get the corner
		//top_left
		//bottom_left
		//top_right
		//bottom_right
		template <typename T, typename rotation_type>
		Empaerior::Point2<T> get_rect_corner(const T_Rect<T, rotation_type>& rect, const Rect_Corners& corner_flag) //fishy
		{
			T o_x = rect.dimensions.x + rect.dimensions.w / 2;
			T o_y = rect.dimensions.y + rect.dimensions.h / 2;

			Empaerior::Point2<T> corner;

			//rotating the point clockwise
			corner.x = o_x + (rect.dimensions.x + static_cast<Empaerior::boole>(corner_flag & 2) * rect.dimensions.w - o_x) * Empaerior::Math::cosd(rect.angle) - (rect.dimensions.y + static_cast<Empaerior::boole>(corner_flag & 1) * rect.dimensions.h - o_y) * Empaerior::Math::sind(rect.angle);
			corner.y = o_y + (rect.dimensions.y + static_cast<Empaerior::boole>(corner_flag & 1) * rect.dimensions.h - o_y) * Empaerior::Math::cosd(rect.angle) + (rect.dimensions.x + static_cast<Empaerior::boole>(corner_flag & 2) * rect.dimensions.w - o_x) * Empaerior::Math::sind(rect.angle);

			return corner;
		}

		template <typename T, typename rotation_type>
		T get_rect_area(const T_Rect<T, rotation_type>& rect)
		{
			return rect.dimensions.w * rect.dimensions.h;
		}


	}

#pragma  endregion

	template <typename T>
	std::ostream& operator<<(std::ostream& out, S_Rect<T>& rect)
	{
		return out << rect.x << ' ' << rect.y << ' ' << rect.w << ' ' << rect.h;
	}

	template <typename T, typename rotation_type>
	std::ostream& operator<<(std::ostream& out, T_Rect<T, rotation_type>& rect)
	{
		return out << rect.dimensions << ' ' << rect.angle;
	}


	template <typename T>
	std::istream& operator>>(std::istream& in, S_Rect<T>& rect)
	{
		in >> rect.x >> rect.y >> rect.w >> rect.h;
		return in;
	}

	template <typename T, typename rotation_type>
	std::istream& operator>>(std::istream& in, T_Rect<T, rotation_type>& rect)
	{
		in >> rect.dimensions >> rect.angle;
		return in;
	}
}