#pragma once


#include "../entity.h"
#include <memory>


template< typename T >
typename std::vector<T>::iterator
EMP_FORCEINLINE insert_sorted(std::vector<T>& vec, T const& item)
{
	return vec.insert
	(
		std::upper_bound(vec.begin(), vec.end(), item),
		item
	);
}

namespace Empaerior {
	//Thanks to 
	//"A system is any functionality that iterates upon a list of entities with a certain signature of components."
	//
	class ECS;     // forward declaration

	class System
	{
	public:

		virtual ~System()
		{

		}

		virtual void OnEntityRemovedfromSystem(Empaerior::ECS* ecs,const Empaerior::u_inter& entity_id)
		{

		}
		//the id of the entities the system works on

		std::vector<Empaerior::u_inter> entities_id;
	};

	



	class SystemManager
	{
	public:
		template <typename T>
		std::shared_ptr<T>  register_system()
		{
			const char* system_type = typeid(T).name();
			try
			{
				//if the system is already present //  throw
				if (typetosystem.find(system_type) != typetosystem.end())
				{

					throw E_runtime_exception("Unable to register system: system is already registered.", __FILE__, __LINE__, __FUNCTION__);

				}
				std::shared_ptr<T> system = std::make_shared<T>();
				typetosystem.insert({ system_type,system });

				return system;

			}
			catch (E_runtime_exception & e)
			{
				e.print_message();
				return nullptr;
			}
			



		}

		template<typename T>
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
		template <typename T>
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
		void OnEntityDestroy(const Empaerior::u_inter& entity_id)
		{
			for (auto const& it : typetosystem)
			{
				it.second->entities_id.erase(std::remove(it.second->entities_id.begin(), it.second->entities_id.end(), entity_id), it.second->entities_id.end());
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

		//compare the signature//return 1  if ther are equal
		static bool compare_signatures(const Empaerior::vector<bool>& signature1, const Empaerior::vector<bool>& signature2)
		{
			if (signature1.size() != signature2.size()) return false;
			for (int i = 0; i < signature1.size(); i++)
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


			//if a signature has a system but the tntity does not 
			//return false
			for (int i = 0; i < system_s.size(); i++)
			{
				if (system_s[i] && !entity_s[i]) return false;
			}
			return true;
		}

		//get the signature of a system based on type
		Empaerior::hash_map<const char*, Empaerior::vector<bool>> typetosignature;
		//get the system based on type
		Empaerior::hash_map<const char*, std::shared_ptr<System>> typetosystem;

	};




}
