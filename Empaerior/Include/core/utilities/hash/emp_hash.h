#pragma once
#include "sha256.h"
#include "../../defines/defines.h"
#include <string>
namespace Empaerior
{
    namespace Hash
    {


        EMP_FORCEINLINE std::string sha256_data(void* data, size_t size)
        {
            SHA256 sha256;
            return  sha256(data, size);
        }

    }
	
}
