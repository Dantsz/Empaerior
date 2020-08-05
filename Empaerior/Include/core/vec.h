#pragma once
#include "defines/basic_defines.h"
#include "mat.h"
namespace Empaerior
{

	template<length_t length, typename type>
	struct vec
	{
		type elements[length] = { 0 };

		type& operator[](length_t index)
		{
			return elements[index];
		}

		type const& operator[](length_t index) const
		{
			return elements[index];
		}

			
	
	};

//vector-vector
#pragma region operators
	//hopefully loop unrolling kicks in here
	//IT SHOULD
	template<length_t length, typename type>
	void operator += (vec<length, type>& v1, const vec<length, type>& v2)
	{
		for (length_t i = 0; i < length; i++)
		{
			v1.elements[i] += v2.elements[i];
		};
	}
	template<length_t length, typename type>
	void operator += (vec<length, type>& v1, const type& scalar)
	{
		for (length_t i = 0; i < length; i++)
		{
			v1.elements[i] += scalar;
		};
	}

	template<length_t length, typename type>
	void operator -= (vec<length, type>& v1, const vec<length, type>& v2)
	{
		for (length_t i = 0; i < length; i++)
		{
			v1.elements[i] -= v2.elements[i];
		};
	}
	template<length_t length, typename type>
	void operator -= (vec<length, type>& v1, const type& scalar)
	{
		for (length_t i = 0; i < length; i++)
		{
			v1.elements[i] -= scalar;
		};
	}

	template<length_t length, typename type>
	void operator *= (vec<length, type>& v1, const vec<length, type>& v2)
	{
		for (length_t i = 0; i < length; i++)
		{
			v1.elements[i] *= v2.elements[i];
		};
	}
	template<length_t length, typename type>
	void operator *= (vec<length, type>& v1, const type& scalar)
	{
		for (length_t i = 0; i < length; i++)
		{
			v1.elements[i] *= scalar;
		};
	}

	template<length_t length, typename type>
	void operator /= (vec<length, type>& v1, const vec<length, type>& v2)
	{
		for (length_t i = 0; i < length; i++)
		{
			v1.elements[i] /= v2.elements[i];
		};
	}
	template<length_t length, typename type>
	void operator /= (vec<length, type>& v1, const type& scalar)
	{
		for (length_t i = 0; i < length; i++)
		{
			v1.elements[i] /= scalar;
		};
	}


	template<length_t length, typename type>
	vec<length, type> operator+(const vec<length, type>& v1, const vec<length, type>& v2)
	{
		vec<length, type> temp(v1);
		temp  += v2;;
		return  temp;
	}

	template<length_t length, typename type>
	vec<length, type> operator-(const vec<length, type>& v1, const vec<length, type>& v2)
	{
		vec<length, type> temp(v1);
		temp -= v2;;
		return  temp;
	}

	template<length_t length, typename type>
	vec<length, type> operator/(const vec<length, type>& v1, const vec<length, type>& v2)
	{
		vec<length, type> temp(v1);
		temp /= v2;;
		return  temp;
	}

	template<length_t length, typename type>
	const vec<length, type> operator*(const vec<length, type>& v1, const vec<length, type>& v2) 
	{
		vec<length, type> temp(v1);
		temp *= v2;;
		return  temp;
	}

	template<length_t length, typename type>
	bool operator==(const vec<length, type>& v1, const vec<length, type>& v2)
	{
		for (length_t i = 0; i < length; i++)
		{
			if (v1[i] != v2[i]) return false;
		}
		return true;
	}

	template<length_t length, typename type>
	bool operator!=(const vec<length, type>& v1, const vec<length, type>& v2)
	{
		for (length_t i = 0; i < length; i++)
		{
			if (v1[i] == v2[i]) return false;
		}
		return true;
	}
#pragma endregion
//vector-matrix
#pragma region operator m-v

	template<length_t length , typename type>
	vec<length,type> operator *(Empaerior::vec<length, type>& v, const Empaerior::mat<length, length, type>& mat)
	{
		vec<length, type> temp;
		type sum;
		for (length_t i = 0; i < length; i++)
		{
			sum = static_cast<type>(0);
			for (length_t j = 0; j < length; j++)
			{
				sum += mat[i][j] * v[j];
			}
			temp[i] = sum;

		}
		return temp;
	}

	template <length_t length, typename type>
	void operator *=(Empaerior::vec<length, type>& v,const Empaerior::mat<length,length,type>& mat)
	{
		
		v = v * mat;
		
	}

#pragma endregion


template <length_t length, typename type>
	type get_vector_length(Empaerior::vec<length,type>& v)
	{
		type temp = 0;
		for(length_t i  = 0 ; i < length ; i ++) temp += (v[i] * v[i]);
		
		return std::sqrt(temp);

	}

template <length_t length, typename type>
   void normalize_vector(Empaerior::vec<length,type>& v)
   {
	   type len = get_vector_length(v);
	   if(len != (type)0)
	   {
		   v/=len;
	   }
   }

template<length_t length , typename type>
	type dot_product(const Empaerior::vec<length,type>& v1, const Empaerior::vec<length,type>& v2)
	{
		type product = static_cast<type>(0);
		for(length_t i = 0 ; i < length ; i ++)
		{
			product += v1[i] * v2[i];
		}
		return product;
	
	}



}