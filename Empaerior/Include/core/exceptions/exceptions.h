#pragma once
#include "../defines/defines.h"
#include <exception>
#include <stdexcept>
#include <string>

#include <iostream>

#ifdef EMP_USE_LOGS
	#include "../include/debugging/log.h"
#endif // EMP_USE_LOGS


class E_runtime_exception : public std::exception
{
public:
	
	


	E_runtime_exception(const Empaerior::string& what, const Empaerior::string& file, const  Empaerior::u_inter& line, const  Empaerior::string& func)
	{
		message = "Exception: " + what + " in " + file +  " function :" + func + " at line " + std::to_string(line) + '\n';
	}
	
	void print_message()
	{
	#ifdef EMP_USE_LOGS
		ENGINE_ERROR(message);
	#endif
	}

	const char* what() const noexcept override 
	{
		return message.c_str();
	}

private:
	Empaerior::string message = "";//message
	



};