#pragma once
#include <memory>

#include "entity.h"
#include "components/componentmanager.h"
#include "system/system.h"

/*The ECS is heaviley isnpired by AUSTIN MORLAN's implementation , but it has a bit more functionality and ease of use. It's a bit more 'loose'.
  It's minimal and doesn't have very specific function so it may be interchangeable with other ECS.
*/


namespace Empaerior
{
	class ECS
	{
	public:
		void Init()
		{
			component_manager = std::make_unique<Empaerior::ComponentManager>();
			entity_manager = std::make_unique<Empaerior::EnityManager>();
			system_manager = std::make_unique<Empaerior::SystemManager>();

		}
		void Destroy()
		{
			component_manager.reset();
			entity_manager.reset();
			system_manager.reset();
		}



		//assigns a new id for an entity
		Empaerior::u_inter create_entity_ID()
		{
			return entity_manager->add_Entity();
		}
		//destroy entity
		void destroy_entity(const Empaerior::u_inter& id)
		{
			entity_manager->delete_entity(id);
			component_manager->OnEntityDestroyed(id);
			system_manager->OnEntityDestroy(id);
			

		}
		//get entity signature
		Empaerior::vector<bool> get_entity_signature(const Empaerior::u_inter& entity_id)
		{
			return entity_manager->get_signature(entity_id);
		}




		template<typename T>
		void register_component()
		{
			component_manager->register_component<T>();
		}

		template <typename T, typename secondT , typename ...OtherT>
		void register_component()
		{
			component_manager->register_component<T>();
			register_component<secondT, OtherT...>();
		}
	


		template<typename T>
		void add_component(const Empaerior::u_inter& entity_id, T component)
		{
			
			//add the component
			component_manager->add_component<T>(entity_id, component);


			//modify the signature to match the new addition
			Empaerior::vector<bool> e_signature = entity_manager->get_signature(entity_id);
			Empaerior::u_inter component_type = component_manager->get_component_id<T>();
			//while the vector of signature doesn't have elements until the current component add 0 to the signature
			while (e_signature.size() <= component_type)
			{
				e_signature.emplace_back(0);
			}
			//add the new signature
			e_signature[component_type] = 1;
			entity_manager->set_signature(entity_id, e_signature);
			system_manager->OnEntitySignatureChange(this, entity_id, e_signature);
		}
		template<typename T, typename ...Other>
		void add_component(const Empaerior::u_inter& entity_id, T component,const Other&... other)
		{
		
			//add the component
			component_manager->add_component<T>(entity_id, component);


			//modify the signature to match the new addition
			Empaerior::vector<bool> e_signature = entity_manager->get_signature(entity_id);
			Empaerior::u_inter component_type = component_manager->get_component_id<T>();
			//while the vector of signature doesn't have elements until the current component add 0 to the signature
			while (e_signature.size() <= component_type)
			{
				e_signature.emplace_back(0);
			}
			//add the new signature
			e_signature[component_type] = 1;
			entity_manager->set_signature(entity_id, e_signature);
			system_manager->OnEntitySignatureChange(this,entity_id, e_signature);
			add_component<Other...>(entity_id, other ...);
		}

		template < typename T>
		void remove_component(const Empaerior::Entity& entity_id)
		{
		
			Empaerior::vector<bool>& e_signature = entity_manager->get_signature(entity_id.id);
			Empaerior::u_inter component_type = component_manager->get_component_id<T>();
			e_signature[component_type] = 0;
			system_manager->OnEntitySignatureChange(this, entity_id.id, e_signature);
			component_manager->remove_component<T>(entity_id);
			
		}
		//weird workaround 
		template < typename T, typename secondT, typename ... Other>
		void remove_component(const Empaerior::Entity& entity_id)
		{
			
			Empaerior::vector<bool>& e_signature = entity_manager->get_signature(entity_id.id);
			Empaerior::u_inter component_type = component_manager->get_component_id<T>();
			e_signature[component_type] = 0;
			system_manager->OnEntitySignatureChange(this, entity_id.id, e_signature);
			component_manager->remove_component<T>(entity_id);
			
		
			remove_component<secondT, Other...>(entity_id);
		}
		


		template <typename T>
		Empaerior::boole has_components(const Empaerior::u_inter& entity_id)
		{
			return component_manager->get_container<T>()->has_component(entity_id);
		}
		template <typename T , typename secondT , typename ...Other>
		Empaerior::boole has_components(const Empaerior::u_inter& entity_id)
		{
			if (!component_manager->get_container<T>()->has_component(entity_id)) return 0;
			return has_components<secondT, Other...>(entity_id);
		}
		



		template <typename T>
		T& get_component(const Empaerior::u_inter& entity_id)
		{
			return component_manager->get_component<T>(entity_id);
		}

		template <typename T>
		Empaerior::u_inter get_component_id()
		{
			return component_manager->get_component_id<T>();
		}


		template <typename T>
		std::shared_ptr<T> register_system()
		{
			return system_manager->register_system<T>();
		}

		//sets the signature of T
		template <typename T>
		void set_system_signature(Empaerior::vector<bool>& signature)
		{
			system_manager->set_signature<T>(signature);
		}

		//gets the signature of T
		template <typename T>
		Empaerior::vector<bool> get_system_signature()
		{
			return system_manager->get_system_signature<T>();
		}

		//add the components to the system <sys> as a criteria for iteration , if the entity doen't have the systems specified , it will not iterate ovr them 
		template< typename sys>
		void add_criteria_for_iteration()
		{
			

		}
		template <typename sys , typename comp , typename ...comps >
		void add_criteria_for_iteration()
		{
			//get the current signature of sys
			Empaerior::vector<bool> signature = get_system_signature<sys>();

			//get the id of the component
			Empaerior::u_inter component_id = get_component_id<comp>();
			//modify the signature to fit the new component
			while (signature.size() <= component_id)
			{
				signature.emplace_back(0);
			}
			//mark the component as being a part of the system
			signature[component_id] = 1;
			//set the new signature
			set_system_signature<sys>(signature);




			add_criteria_for_iteration<sys, comps...>();

		}


		//sets the whole criteria instead of adding to it
		template <typename sys>
		void set_criteria_for_iteration()
		{

		}

		template<typename sys, typename comp, typename ...comps>
		void set_criteria_for_iteration()
		{
			//get the current signature of sys
			Empaerior::vector<bool> signature = get_system_signature<sys>();
			
			//reset criteria 
		
			for(auto i = 0 ; i < signature.size() ; i++)
			{
				signature[i] = 0;
			}


			//get the id of the component
			Empaerior::u_inter component_id = get_component_id<comp>();
			//modify the signature to fit the new component
			while (signature.size() <= component_id)
			{
				signature.emplace_back(0);
			}
			//mark the component as being a part of the system
			signature[component_id] = 1;
			//set the new signature
			set_system_signature<sys>(signature);
		}
		

		//gets maximum number of components of a certain type created
		//for example if 2 components have been created and 1 deleted
		//calling get_maximum_component_count will return 2
		//only used for debbuging
		template <typename comp, typename return_type = size_t>
		return_type get_maximum_component_count()
		{
			return component_manager->get_container<comp>()->components.size();
		}

	
		std::unique_ptr<Empaerior::ComponentManager> component_manager;
		std::unique_ptr<Empaerior::EnityManager> entity_manager;
		std::unique_ptr<Empaerior::SystemManager> system_manager;
	};

}