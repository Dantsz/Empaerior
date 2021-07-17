#pragma once
#include "core/defines/basic_defines.h"
#include <vector>

namespace Empaerior
{

	//a vector that doesn't immediately delete an element when deletion is called
	//it's not advised to iterate upon and serves as just a container of data 
	//iteration is done throught the returned indexes of push_back
	//this class main pupose is to be a vector without iterator invalidation upon erasion
	template <typename T, typename indexing_type = size_t, class Allocator = std::allocator<T>>
	class unsafe_vector
	{
	public:
		//TODO :
		//should be renamed
		//it doesn't always push_back
		[[nodiscard]] indexing_type push_back(const T& object)
		{
			if (freed_indexes.empty())
			{
				objects.push_back(object);
				return objects.size() - 1;
			}
			else
			{

				indexing_type index = freed_indexes.back();
				freed_indexes.pop_back();
				objects[index].~T();
				objects[index] = object;
				return index;

			}
		}

		template<typename ...Args>
		[[nodiscard]] indexing_type emplace_back(Args&& ...args)
		{
			if (freed_indexes.empty())
			{
				objects.emplace_back(std::forward<Args>(args)...);
				return objects.size() - 1;

			}
			else
			{
				indexing_type index = freed_indexes.back();
				freed_indexes.pop_back();
				objects[index].~T();
				objects[index] = { args... };
				return index;
			}
		}
		

		void remove(indexing_type index)
		{

			freed_indexes.push_back(index);

		}


		T& operator[](indexing_type index)
		{
			return objects[index];
		}


		//get the number of used items
		//objects that are not removed 
		EMP_FORCEINLINE indexing_type size()
		{
			return objects.size() - freed_indexes.size();
		}

		//get the number of items that can be stored before an vector push_back is called
		EMP_FORCEINLINE indexing_type free_size()
		{
			return freed_indexes.size();
		}

		std::vector<T, Allocator> objects;
		std::vector<indexing_type> freed_indexes;

	};

	//finds the largest value lower than item and puts it before it, item must not be present in the vector
	template< typename T >
	EMP_FORCEINLINE typename Empaerior::vector<T>::iterator insert_sorted(Empaerior::vector<T>& vec, T const& item)
	{
		if(std::binary_search(vec.begin(),vec.end(),item) == true) return vec.end();
		auto upperBound = std::upper_bound(vec.begin(), vec.end(), item);
		return vec.insert
		(
			upperBound,
			item
		);
	}

}
