#pragma once

//Log usage

#if defined(EMPAERIOR_DEBUG) || defined(EMPAERIOR_RELEASE)

#define EMP_USE_LOGS

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



#ifdef EMP_USE_LOGS

#include <spdlog/spdlog.h>

namespace Empaerior
{

	namespace Log
	{

		void Init();

		struct Logger
		{
			static 	std::shared_ptr<spdlog::logger> engine_logger;
			static  std::shared_ptr<spdlog::logger> application_logger;
		};
 
	
	}

}
#endif


//LOGIGING MACROS
#ifdef EMP_USE_LOGS



#define ENGINE_TRACE(...) 	Empaerior::Log::Logger::engine_logger->trace(__VA_ARGS__)
#define ENGINE_INFO(...) 	Empaerior::Log::Logger::engine_logger->info(__VA_ARGS__)
#define ENGINE_WARN(...) 	Empaerior::Log::Logger::engine_logger->warn(__VA_ARGS__)
#define ENGINE_ERROR(...) 	Empaerior::Log::Logger::engine_logger->error(__VA_ARGS__)
#define ENGINE_CRITICAL(...) 	Empaerior::Log::Logger::engine_logger->critical(__VA_ARGS__)

#define APP_TRACE(...) Empaerior::Log::Logger::application_logger->trace(__VA_ARGS__)
#define APP_INFO(...) Empaerior::Log::Logger::application_logger->info(__VA_ARGS__)
#define APP_WARN(...) Empaerior::Log::Logger::application_logger->warn(__VA_ARGS__)
#define APP_ERROR(...) Empaerior::Log::Logger::application_logger->error(__VA_ARGS__)
#define APP_CRITICAL(...) Empaerior::Log::Logger::application_logger->critical(__VA_ARGS__)



#endif // EMP_USE_LOGS