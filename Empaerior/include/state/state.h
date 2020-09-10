#pragma once




//entity tests

#include "../include/core/ecs/ecs.h"
#include "../include/systems/systems.h"


#include "../include/core/defines/defines.h"
/*
	A state of the engine, which updates the layers contained in it's layers stack
*/

namespace Empaerior {
	class  State
	{
	public:
		State();
		virtual ~State() {

		};

		virtual void Update(const Empaerior::u_int dt) = 0;
		virtual void Render() = 0 ;//renders the state
		virtual void handleevents(Empaerior::Event& event) = 0;





		Empaerior::ECS ecs;
	protected:


	};
}