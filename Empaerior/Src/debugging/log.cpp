#include "pch.h"

#ifdef EMP_USE_LOGS

	#include "../include/debugging/log.h"
	#include <spdlog/sinks/stdout_color_sinks.h>
	
 	std::shared_ptr<spdlog::logger> Empaerior::Log::Logger::engine_logger;
	std::shared_ptr<spdlog::logger>	Empaerior::Log::Logger::application_logger;

	void Empaerior::Log::Init()
	{
		spdlog::set_pattern("%^[%T]%n:%v%$");
		Empaerior::Log::Logger::engine_logger = spdlog::stdout_color_mt("ENGINE");
		Empaerior::Log::Logger::engine_logger->set_level(spdlog::level::trace);

		Empaerior::Log::Logger::application_logger = spdlog::stdout_color_mt("APPLICATION");
		Empaerior::Log::Logger::application_logger->set_level(spdlog::level::trace);
	
	}


#endif

