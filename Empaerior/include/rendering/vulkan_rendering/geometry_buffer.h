#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <vulkan/vulkan.h>

#include <vector>
#include <array>
#include "misc_functions.h"
#include "../include/core/unsafe_vector.h"

#include <iostream>
#include "vertex.h"
//the number of buffers in action
//should ideally be 2
static constexpr size_t buffering  = 2;




/*
 Buffers for GPU memory
*/
struct DynamicBuffer
{
	
	Empaerior::unsafe_vector<size_t> index;


	VkBuffer inUseBuffer;
	VkDevice device;



	std::vector<VkBuffer> Buffers;

	std::vector<VmaAllocation> BuffersAllocations;

	std::vector<VkDeviceSize> BufferSize;
	std::vector<size_t> used_size;
	std::vector<void*> BuffersData;
	VkBufferUsageFlagBits usage;
	VmaAllocator* m_allocator;
	size_t inUseBufferIndex = 0;
	bool updateBuffer = false;


	//set initial size and creates the initial buffers
	void Init(size_t initialSize)
	{
		for (size_t i = 0; i < buffering; i++)
		{
			VmaAllocationCreateInfo bufferAllocInfo{};
			bufferAllocInfo.usage = VMA_MEMORY_USAGE_CPU_TO_GPU;
			Empaerior::VKfunctions::allocateBuffer(*m_allocator, BufferSize[inUseBufferIndex] + initialSize, usage, &Buffers[i], &BuffersAllocations[i], &bufferAllocInfo);
			vmaMapMemory(*m_allocator, BuffersAllocations[i], &BuffersData[i]);

			BufferSize[i] = initialSize;
			used_size[i] = 0;
		}
		inUseBuffer = Buffers[0];
		inUseBufferIndex = 0;
	}


	void ExpandBuffer(size_t size)
	{

		vkDeviceWaitIdle(device);
		size_t dataIndex = (inUseBufferIndex + 1) % buffering;//where the new buffer needs to go
		size_t srcdataIndex = dataIndex;// from where to take the data
		if(!updateBuffer)
		{
			srcdataIndex = inUseBufferIndex;
			updateBuffer = true;
		}
		//if the buffer hasn't been updated before , it doesn't have any new data that the old buffer doesn't have
		//so a third buffer is not needed
		//
		VmaAllocationCreateInfo bufferAllocateInfo{};
		bufferAllocateInfo.usage = VMA_MEMORY_USAGE_CPU_TO_GPU;
		bufferAllocateInfo.requiredFlags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

	
		
		VkBuffer stagingBuffer{};
		VmaAllocation stagingBufferAllocation{};
		void* stagingBufferData = nullptr;

		Empaerior::VKfunctions::allocateBuffer(*m_allocator, BufferSize[srcdataIndex] + size, usage, &stagingBuffer, &stagingBufferAllocation, &bufferAllocateInfo);
		vmaMapMemory(*m_allocator, stagingBufferAllocation, &stagingBufferData);
		memcpy(stagingBufferData, BuffersData[srcdataIndex], BufferSize[srcdataIndex]);
			
		vmaUnmapMemory(*m_allocator, BuffersAllocations[srcdataIndex]);
		vmaDestroyBuffer(*m_allocator, Buffers[srcdataIndex], BuffersAllocations[srcdataIndex]);
			

		Buffers[dataIndex] = stagingBuffer;
		BuffersAllocations[dataIndex] = stagingBufferAllocation;
		
		BuffersData[dataIndex] = stagingBufferData;

		BufferSize[dataIndex] = BufferSize[dataIndex] + size;
		
			
	}

	size_t get_in_use_index() const
	{
		if(updateBuffer) 
		{
			 return  (inUseBufferIndex + 1) % buffering;
		}
		return inUseBufferIndex;
	}

	[[nodiscard]]size_t allocate(size_t size)
	{
		//create a new pointer
		size_t place = index.emplace_back(used_size[get_in_use_index()]);
			
		//check if there's space available
		if (size >= BufferSize[get_in_use_index()] - used_size[get_in_use_index()]) // create new space
		{
			//expand the buffer while the new allocation is bigger
			while (BufferSize[get_in_use_index()] - used_size[get_in_use_index()]  < size)
			{
				//ENGINE_WARN("Expanding buffer");
				ExpandBuffer(BufferSize[get_in_use_index()]);
			}
		}
		//mark the meory as used
		used_size[get_in_use_index()] += size;
	

		return place;
	}


	//removes the data segment entierly,
	//COSTLY OPERATION
	void deallocate(size_t allocationIndex, size_t size)
	{
		//std::cout << "Deallocating " << size << " bytes\n";
		/*
		How this works

			0123456789
		    deallocate called with index 3 , size 2
			0123456789 ==> 0125678989 ==> 01256789**
			fix the index allocations
			DONE
		
		*/
		
		used_size[get_in_use_index()] -= size;
		
		unsigned char* data = (unsigned char*) BuffersData[get_in_use_index()];

		
		//overwrite deleted data to fill the hole
		for (size_t i = index[allocationIndex] ; i < used_size[get_in_use_index()] ; i++)
		{
			data[i] = data[i + size];
		}
		
		//adjust the allocations
		for (auto& objectIndex : index.objects)
		{
			if (objectIndex >= index[allocationIndex])
			{
				objectIndex -= size;
			}
		}

		
		//remove from index
		
		index.remove(allocationIndex);
		

	}

	void updateInUseBuffers()
	{
		if (updateBuffer)
		{
			//ENGINE_WARN("updated buffer");
			size_t new_bufferindex = (inUseBufferIndex + 1) % buffering;
		
			inUseBuffer = Buffers[new_bufferindex];
			inUseBufferIndex = new_bufferindex;
			updateBuffer = false;
		}
	}
	//invalidates all allocations
	void resetBuffer()
	{
		//clear direct allocations
		index.objects.clear();
		index.freed_indexes.clear();
		//"delete" the data
		for (size_t i = 0; i < buffering; i++)
		{
			used_size[i] = 0;
		}
	
		//go to the first buff
		//inUseBufferIndex = 0;
		//inUseBuffer = Buffers[0];
	}
};


struct geometryBuffer
{
	
	void attachrenderer(VmaAllocator* allocator, VkDevice device,Empaerior::u_inter swapChainImages)
	{
		m_allocator = allocator;
		images = swapChainImages;

		vertexBuffer.Buffers.resize(buffering);
		vertexBuffer.BuffersAllocations.resize(buffering);
		vertexBuffer.BufferSize.resize(buffering);
		vertexBuffer.BuffersData.resize(buffering);
		vertexBuffer.used_size.resize(buffering);
		vertexBuffer.m_allocator = m_allocator;
		vertexBuffer.usage = VkBufferUsageFlagBits(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT);
		vertexBuffer.Init(initialVertexSize);
		vertexBuffer.device = device;


		indexBuffer.Buffers.resize(buffering);
		indexBuffer.BuffersAllocations.resize(buffering);
		indexBuffer.BufferSize.resize(buffering);
		indexBuffer.BuffersData.resize(buffering);
		indexBuffer.used_size.resize(buffering);
		indexBuffer.m_allocator = m_allocator;
		indexBuffer.usage = VkBufferUsageFlagBits(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT);
		indexBuffer.Init(initialIndexSize);
		indexBuffer.device = device;
	}

	void cleanup()
	{
		cleanupVertexBuffer();
		cleanupIndexBuffer();
	
	}



	


	void cleanupVertexBuffer()
	{
		for (size_t i = 0; i < buffering; i++)
		{
			vmaUnmapMemory(*m_allocator, vertexBuffer.BuffersAllocations[i]);
			vmaDestroyBuffer(*m_allocator, vertexBuffer.Buffers[i], vertexBuffer.BuffersAllocations[i]);
		}
	}
	void cleanupIndexBuffer()
	{
		for (size_t i = 0; i < buffering; i++)
		{
			vmaUnmapMemory(*m_allocator, indexBuffer.BuffersAllocations[i]);
			vmaDestroyBuffer(*m_allocator, indexBuffer.Buffers[i], indexBuffer.BuffersAllocations[i]);
		}
	}
	



	void updateInUseBuffers()
	{
		
		indexBuffer.updateInUseBuffers();
		vertexBuffer.updateInUseBuffers();
		
	}

	//reset the buffer to the original state
	void reset()
	{
		indexBuffer.resetBuffer();
		vertexBuffer.resetBuffer();
		
	}


	DynamicBuffer vertexBuffer;
	DynamicBuffer indexBuffer;

	VmaAllocator* m_allocator;

	Empaerior::u_inter images;
	const size_t initialVertexSize = 4ULL * sizeof(Vertex);
	const size_t initialIndexSize = 6ULL * sizeof(uint32_t);
};



EMP_FORCEINLINE void dump_IndexData(geometryBuffer& geometrybuffer)
{
	uint32_t* index_data = static_cast<uint32_t*>(geometrybuffer.indexBuffer.BuffersData[geometrybuffer.indexBuffer.get_in_use_index()]);
	std::cout << "======Index=====\n";
	std::cout << geometrybuffer.indexBuffer.used_size[geometrybuffer.indexBuffer.get_in_use_index()] / sizeof(uint32_t) << " will be drawn\n";
	for (size_t i = 0; i < (geometrybuffer.indexBuffer.used_size[geometrybuffer.indexBuffer.get_in_use_index()] / sizeof(uint32_t)); i++)
	{
		std::cout << index_data[i] << ' ';
		if (i % 6 == 5) std::cout << '\n';
	}
	std::cout << "====================\n";
}
EMP_FORCEINLINE void dump_VertexData(geometryBuffer& buffer)
{
	Vertex* vertex_data = static_cast<Vertex*>(buffer.vertexBuffer.BuffersData[buffer.indexBuffer.get_in_use_index()]);
	std::cout << "==========Vertex=========\n";
	for (size_t i = 0; i < buffer.vertexBuffer.used_size[buffer.indexBuffer.get_in_use_index()] / sizeof(Vertex); i++)
	{
		if (i % 4 == 0) std::cout << i << ":\n";
		std::cout << vertex_data[i].pos.x << ' ' << vertex_data[i].pos.y << ' ' << vertex_data[i].pos.z << ' ' << vertex_data[i].texCoord.x << ' ' << vertex_data[i].texCoord.y <<' ' <<vertex_data[i].tex_id <<  '\n';

	}
}
EMP_FORCEINLINE void dump_data(geometryBuffer& buffer)
{

	dump_IndexData(buffer);
	dump_VertexData(buffer);

	
}


