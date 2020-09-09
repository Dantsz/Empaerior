#pragma once
#include "../include/core/defines/defines.h"





#include "../include/state/state.h"

#include "../include/rendering/window.h"


#include "../include/input/eventhandler/eventhandler.h"
#include "../include/core/exceptions/exceptions.h"
#include "../include/debugging/log.h"

namespace  Empaerior{




//this is the base application class
//all others applications should inherit from this class
class Application
{
public:
	Application();

	virtual ~Application() {};

	void Init();


	//the running function
	virtual void run() = 0;


	virtual void handlevents(Empaerior::Event& event);
    virtual void Update(const Empaerior::u_int dt);
	
	//polls event , uses the class event
	static bool PollEvent()
	{
		return SDL_PollEvent(&event.event);
	}

#pragma region	STATE EDITING
	//Returns the index of the state in the vector
	//can be accesed through the vector
	static Empaerior::u_inter push_state(Empaerior::State* n_state)
	{

		try
		{

			//check if the state is null
			if(n_state == nullptr) throw E_runtime_exception("Tried to add a null state to the application", __FILE__, __LINE__, __FUNCTION__);
			
			//check if the state is already in the application
			Empaerior::vector<Empaerior::State*>::iterator itr = std::find(states.begin(), states.end(), n_state);
			if (itr != states.cend()) throw E_runtime_exception("State is already present in the application", __FILE__, __LINE__, __FUNCTION__);
		
			
			//check if there's any free index
			if (freed_indexes.empty())
			{
				states.emplace_back(n_state);
				return states.size() - 1;
			}
			else
			{
				
				Empaerior::u_inter index = freed_indexes[freed_indexes.size()-1];
				states[index] = n_state;
				//remove the index from the freed queue
				freed_indexes.pop_back();
				return index;
			}

			
		}
		catch (E_runtime_exception & e)
		{
			e.print_message();
			return -1;
		}

	}

	//puts the state present at the index in the states vector in the active stack


	static void activate_state(const Empaerior::u_inter index)
	{
		try
		{
	        
			//check if the index is valid
			//because the index is signed, check if it's negative
			if (index >= states.size()) throw E_runtime_exception("Invalid Index ", __FILE__, __LINE__,__FUNCTION__);

			Empaerior::vector<Empaerior::u_inter>::iterator itr = std::find(active_states.begin(), active_states.end(), index);

			if (itr != active_states.cend()) throw E_runtime_exception("State at the provided index is already active ", __FILE__, __LINE__, __FUNCTION__);


			//ENGINE_INFO("ACTIVATED STATE: " + std::to_string(index));
			active_states.emplace_back(index);
		}
		catch (E_runtime_exception & e)
		{
			e.print_message();
			return;
		}
	}

	//remove state from active stack
	//index - the  positiob of the state in the main state vector , not the active stack
	static void pause_state(const Empaerior::u_inter index)
	{


		
		try {
			//check validity and search for the index in the active states
			if (index >= states.size() || index < 0) throw E_runtime_exception("Invalid Index ", __FILE__, __LINE__, __FUNCTION__);
			
			//check if the state is active by searching  for the index
			Empaerior::vector<Empaerior::u_inter>::iterator itr = std::find(active_states.begin(), active_states.end(), index);

			if (itr == active_states.cend()) throw E_runtime_exception("State at the provided index is not active ", __FILE__, __LINE__, __FUNCTION__);

		
			
			//put it in to be paused 
			to_be_paused.emplace_back(std::distance(active_states.begin(), itr));

		}
		catch (E_runtime_exception& e)
		{
			e.print_message();
			return;

		}


		

	}

	//deletes state at index
	//To be implemented later

	static void delete_state(const Empaerior::u_inter index)
	{
		
		try {
			//if it active remove it in order to make sure it's not active when it's deleted
			if (index >= states.size() || index < 0) throw E_runtime_exception("Invalid Index ", __FILE__, __LINE__, __FUNCTION__);
			Empaerior::vector<Empaerior::u_inter>::iterator itr = std::find(active_states.begin(), active_states.end(), index);
			//put it in to be pause
			if (itr != active_states.cend()) 	to_be_paused.emplace_back(std::distance(active_states.begin(), itr));
			//put it to_be_deleted
			to_be_deleted.emplace_back(index);
		


		}
		catch (E_runtime_exception & e)
		{
			e.print_message();
			return;

		}
	
	}
	
	//Clear things up after an cycle
	static void refresh()
	{
		if (!to_be_paused.empty())
		{
			//removed paused states


			for (Empaerior::u_inter i = to_be_paused.size() - 1; to_be_paused.size() > i; --i)
			{
				//erase from active
				active_states.erase(active_states.begin() + i);
				//remove the paused

			}
			to_be_paused.clear();
		}

		if (to_be_deleted.empty()) return;


		for (Empaerior::u_inter i = to_be_deleted.size() - 1; to_be_deleted.size() > i; --i)
		{
			//delete 


			//delete the state
			delete states[to_be_deleted[i]];
			states[to_be_deleted[i]] = nullptr;

			//add it the freed queue
			freed_indexes.emplace_back(to_be_deleted[i]);
			ENGINE_INFO("DELETED STATE" + std::to_string(to_be_deleted[i]));

		}

		to_be_deleted.clear();


	}
#pragma endregion

#pragma region ACTIVE STATE MANIPULATION
	
	//check to see if the state is active
	//returns the index in active_states if true or -1 if it's inactive or doesn't exist
	static EMP_FORCEINLINE Empaerior::u_inter is_active(const Empaerior::u_inter index)
	{
		try
		{
			if (index >= states.size() || index < 0) throw E_runtime_exception("Invalid Index ", __FILE__, __LINE__, __FUNCTION__);
			Empaerior::vector<Empaerior::u_inter>::iterator itr = std::find(active_states.begin(), active_states.end(), index);
			if (itr == active_states.cend())
			{
				return -1;
			}
			return Empaerior::u_inter(std::distance(active_states.begin(), itr));
		}
		catch (E_runtime_exception& e)
		{
			e.print_message();
			return -1;
		}
	}

	//moves the state in the front by n 
	static void move_up_by(const Empaerior::u_inter index,const Empaerior::u_inter& n)
	{
		try {
			//if the state is not active
			Empaerior::u_inter in_active_index = is_active(index);

			if (in_active_index == -1) throw E_runtime_exception("State is not active", __FILE__, __LINE__, __FUNCTION__);
			//if the state is already on the top
			if (active_states[active_states.size() - 1] == index)
			{
				ENGINE_WARN("State " + std::to_string(index) + " is already on top");
				return;
			}
			
			if (n >= active_states.size())
			{
				ENGINE_WARN("There are less than " + std::to_string(n) + " states, moving the state to the top instead");

			}
	
	
			//swap the element with the n-th element
			for (Empaerior::u_inter i = 0; i < n ; i++)
			{
				active_states[in_active_index + i] = active_states[in_active_index + i + 1];
			}
			active_states[in_active_index + n] = index;


			
		}
		catch (E_runtime_exception & e)
		{
			e.print_message();
			return;
		}


	}
	//moves the state below by n states
	static void move_below_by(const Empaerior::u_inter index,const Empaerior::u_inter& n)
	{
		try
		{
			//if the state is not active
			Empaerior::u_inter in_active_index = is_active(index);

			if (in_active_index == -1) throw E_runtime_exception("State is not active", __FILE__, __LINE__, __FUNCTION__);

			//if the state is already at the bottom
			if (active_states[0] == index)
			{
				ENGINE_WARN("State " + std::to_string(index) + " is already on the bottom");
				return;
			}

			if (n >= active_states.size())
			{
				ENGINE_WARN("There are less than " + std::to_string(n) + " states, moving the state to the bottom instead");

			}

			//Swap elements
			for (Empaerior::u_inter i = 2; i <( n <  (active_states.size() - 1) ? n + 2 : active_states.size() + 1);  i++)
			{
				Empaerior::u_inter aux = active_states[in_active_index - i + 2];
				active_states[in_active_index - i + 2] = active_states[in_active_index - i + 1];
				active_states[in_active_index - i + 1] = aux;


			}
		


		
		}
		catch (E_runtime_exception & e)
		{
			e.print_message();
			return;
		}

	}
	//moves the state to the top
	static void move_top(const Empaerior::u_inter index)
	{
		try
		{
			Empaerior::s_inter in_active_index = is_active(index);
			if (in_active_index == -1) throw E_runtime_exception("State is not active", __FILE__, __LINE__, __FUNCTION__);
			move_up_by(index, active_states.size() - 1 - in_active_index);
		}
		catch (E_runtime_exception & e)
		{
			e.print_message();
			return;
		}

	}
	//moves the state to the buttom
	static void move_bottom(const Empaerior::u_inter index)
	{
		try
		{
			Empaerior::s_inter in_active_index = is_active(index);
			if (in_active_index == -1) throw E_runtime_exception("State is not active", __FILE__, __LINE__, __FUNCTION__);
			move_below_by(index, in_active_index);
		}
		catch (E_runtime_exception & e)
		{
			e.print_message();
			return;
		}
	}
#pragma endregion

	virtual void render();



private:



public:


	//the index of the states that will be updated
	//
	static Empaerior::vector<Empaerior::u_inter> active_states;

	static Empaerior::vector<Empaerior::State*> states;
	
	static Empaerior::Window window;

	static Empaerior::u_int dt;
	
	static Empaerior::boole is_paused;
	static Empaerior::boole is_running;

	static Empaerior::Event event;





private:


	//this is used by make_pause
	//it puts the index if the states which it want paused in this vector and it is removed from active_states when refresh is called
	static Empaerior::vector<Empaerior::u_inter> to_be_paused;
	//the same ,but for state-deleteion
	static Empaerior::vector<Empaerior::u_inter> to_be_deleted;
	//indexes freed to be replaces by new states
	static Empaerior::vector<Empaerior::u_inter> freed_indexes;

};
	//defined in the application *Thanks to cherno* , 
	//it is intended to create a derived class from Application
	Application* Create_Application();



}