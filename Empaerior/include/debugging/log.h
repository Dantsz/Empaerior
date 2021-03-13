#pragma once
#include "../core/defines/defines.h"
#include <iostream>

namespace Empaerior
{
    template<typename T>
    void log(const T& message)
    {
        std::cout<<message << '\n';
    }
}