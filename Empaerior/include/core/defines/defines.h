#pragma once


#include "basic_defines.h"
#include "struct_defines.h"




//Platform detection
#ifdef _WIN32
	#ifdef _WIN64//if 64 bit 
	//add 64 flag
		#define EMPAERIOR_64BIT
	#else // if 32 bit
		#define EMPAERIOR_32BIT
		#pragma warning  "x86 is not a actively tested"	//x86 flag
	
#endif // _WIN64

#elif __APPLE__
	#error "No Apple platforms are supported"
#elif __linux__
	#define EMPAERIOR_64BIT
#else
	#error "platform not supported yet"

#endif 





//Log usage

#if defined(EMPAERIOR_DEBUG) || defined(EMPAERIOR_RELEASE)

#define EMP_USE_LOGS
#define EMP_USE_DATA_DUMPS
#else

#define ENGINE_TRACE(...) 	
#define ENGINE_INFO(...) 
#define ENGINE_WARN(...) 	
#define ENGINE_ERROR(...) 
#define ENGINE_CRITICAL(...) 	

#define APP_TRACE(...) 
#define APP_INFO(...) 
#define APP_WARN(...) 
#define APP_ERROR(...)
#define APP_CRITICAL(...) 


#endif

