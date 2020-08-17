#include "pch.h"
#include "../include/application.h"






Empaerior::Application::Application()
{


}

void Empaerior::Application::Init()
{

	


}



void Empaerior::Application::Update(const Empaerior::u_int dt )
{
	for (Empaerior::s_inter i = active_states.size() - 1; i >= 0; i--)
	{
		states[active_states[i]]->Update(dt);
	}
}

void Empaerior::Application::handlevents(Empaerior::Event& event)
{
	Empaerior::Application::window.window_listener.handleEvents(event);

	for (Empaerior::u_inter i = active_states.size() - 1; active_states.size() > i; --i)
	{ 
		states[active_states[i]]->handleevents(event);
	}
}

void Empaerior::Application::render()
{
	for (Empaerior::s_inter i = active_states.size() - 1; i >= 0; i--)
	{
		states[active_states[i]]->Render();
	}
}

