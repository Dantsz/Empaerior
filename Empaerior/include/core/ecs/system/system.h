#pragma once


#include "../entity.h"
#include <algorithm>
#include <memory>
#include <concepts>


namespace Empaerior {


	//Thanks to 
	//"A system is any functionality that iterates upon a list of entities with a certain signature of components."
	//
	class ECS;     // forward declaration

    class EntitySystemList
    {
    public:
        void OnEntityRemovedfromSystem(Empaerior::ECS* ecs,const Empaerior::u_inter& entity_id)
        {

        }
        //the id of the entities the system works on
        std::vector<Empaerior::u_inter> entities_id;
    };

	//concept for a valid system
	//must have a vector of size_ts or Empaerior::u_inter
	template <typename systemt>
	concept systemT = requires(systemt sys ){
        std::same_as<decltype(sys.entityList),std::shared_ptr<Empaerior::EntitySystemList>>;
		{sys.entityList->entities_id[0]};
		{sys.entityList->entities_id.size()};
	};

	class SystemManager
	{
	public:
		//creates a system of type T and puts it in the map
		template <systemT T>
		bool  register_system(T& system)
		{
			const char* system_type = typeid(T).name();
			try
			{
				//if the system is already present //  throw
				if (typetosystem.find(system_type) != typetosystem.end())
				{
					throw E_runtime_exception("Unable to register system: system is already registered.", __FILE__, __LINE__, __FUNCTION__);
				}
				std::shared_ptr<EntitySystemList> systemEVec = std::make_shared<EntitySystemList>();
				typetosystem.insert({ system_type,systemEVec });
				set_signature<T>(Empaerior::vector<bool>{});
				system.entityList = systemEVec;
				return true; 
			}
			catch (E_runtime_exception & e)
			{
				e.print_message();
				return false;
			}
		}
		//sets the signature of the system with type T
		template<systemT T>
		void set_signature(const Empaerior::vector<bool>& signature)
		{
			const char* system_type = typeid(T).name();	
			try
			{
				//if the system is not found  //throw
				if (typetosystem.find(system_type) == typetosystem.end())
				{
					throw E_runtime_exception("Unable to set the signature: system does not exist.", __FILE__, __LINE__, __FUNCTION__);
				}
				
				typetosignature[system_type] = signature;


			}
			catch (E_runtime_exception & e)
			{
				e.print_message();
			}
		}

		//gets signature of a system
		template <systemT T>
		Empaerior::vector<bool> get_system_signature()
		{

			const char* system_type = typeid(T).name();
			try
			{
				//if the system is not found  //throw
				if (typetosystem.find(system_type) == typetosystem.end())
				{
					throw E_runtime_exception("Unable to fetch the signature: system does not exist.", __FILE__, __LINE__, __FUNCTION__);
				}

				return typetosignature[system_type];


			}
			catch (E_runtime_exception & e)
			{
				//returns an empty signature
				e.print_message();
				return {};
			}


		}


		//erase entity from all systems
		void OnEntityDestroy(Empaerior::ECS* ecs,const Empaerior::u_inter& entity_id)
		{
			for (auto const& it : typetosystem)
			{
				it.second->entities_id.erase(std::remove(it.second->entities_id.begin(), it.second->entities_id.end(), entity_id), it.second->entities_id.end());
				it.second->OnEntityRemovedfromSystem(ecs,entity_id);
			}

		}

		// Notify each system that an entity's signature changed
		void OnEntitySignatureChange(Empaerior::ECS* ecs,const Empaerior::u_inter& entity_id, Empaerior::vector<bool>& signature)
		{
			for (auto const& it : typetosystem)
			{
				auto const& type = it.first;
				auto const& system = it.second;
				auto const& systemSignature = typetosignature[type];
				if (compare_entity_to_system(signature,systemSignature))
				{
					//TODO : MAKE A METHOD TO SYSTEM , method needs to be virtual /Onewntitierase/insert
					insert_sorted(system->entities_id, entity_id);
				}
				else
				{
					system->entities_id.erase(std::remove(system->entities_id.begin(), system->entities_id.end(), entity_id), system->entities_id.end());
					system->OnEntityRemovedfromSystem(ecs, entity_id);
				}

			}

		}


		//compare the signature//return 1  if they are equal
		static bool compare_signatures(const Empaerior::vector<bool>& signature1, const Empaerior::vector<bool>& signature2)
		{
			if (signature1.size() != signature2.size()) return false;
			for (size_t i = 0; i < signature1.size(); i++)
			{
				//if a signature  is missing somewhere
				if (signature1[i] != signature2[i]) return false;
			}
			return true;
		}
		//compares the signature of an entity to a specific system and if they are compatible , aka the entity has all the components the system needs return true
		static bool compare_entity_to_system(const Empaerior::vector<bool>& entity_s , const Empaerior::vector<bool> system_s)
		{
			
			///if the system signature doesn't match the entity
			if (system_s.size() > entity_s.size()) return false;
			//if a signature has a system but the etity does not 
			//return false
			for (size_t i = 0; i < system_s.size(); i++)
			{
				if (system_s[i] && !entity_s[i]) return false;
			}
			return true;
		}

		//get the signature of a system based on type
		Empaerior::hash_map<const char*, Empaerior::vector<bool>> typetosignature;
		//get the system based on type
		Empaerior::hash_map<const char*, std::shared_ptr<EntitySystemList>> typetosystem;

	};




}
