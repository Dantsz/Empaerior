#pragma once
#include <chrono>
#include "../defines/defines.h"
namespace  Empaerior
{


	//Timer that doesn't depend on SDL, but is compatible with timer
	class Timer
	{
	public:
		using  time_type = std::chrono::time_point<std::chrono::steady_clock> ;
		
		//Start/Reset the timer
		void start()
		{
			mStarted = true;
			mStopped = false;
			stop_point = {};
			begin_point = std::chrono::steady_clock::now();
		}


		//Stops the timer
		void stop()
		{
			//Stop the timer
			mStarted = false;

			//Unpause the timer
			mStopped = true;

			stop_point = std::chrono::steady_clock::now();

		}
	
	
		EMP_FORCEINLINE Empaerior::boole is_Paused()
		{
			return mStopped;
		}
		EMP_FORCEINLINE Empaerior::boole is_Started()
		{
			return mStarted;
		}

		//Gets the timer's time		
		//If the templates are  not changed, it's compatible with Timer::get_ticks
		template <typename return_type = Empaerior::u_inter,typename cast_format = std::chrono::milliseconds>
		return_type getTicks()
		{
			if(mStopped)	return return_type(std::chrono::duration_cast<cast_format>(stop_point - begin_point).count());
			return return_type(std::chrono::duration_cast<cast_format>(std::chrono::steady_clock::now() - begin_point).count());
		}


		time_type begin_point = {};
		time_type stop_point = {};
	
		Empaerior::boole mStopped = false;
		Empaerior::boole mStarted = false;
	};


}