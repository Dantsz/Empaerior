#include "pch.h"

Empaerior::Application::Application() = default;
void Empaerior::Application::Init()
{

	


}

void Empaerior::Application::Update(Empaerior::u_int dt )
{
	for (Empaerior::u_inter i = active_states.size() - 1; i >= 0; i--)
	{
		states[active_states[i]]->Update(dt);
	}
}

void Empaerior::Application::handlevents(Empaerior::Event& curEvent)
{
	Empaerior::Application::window.window_listener.handleEvents(curEvent);

	for (Empaerior::u_inter i = active_states.size() - 1; active_states.size() > i; --i)
	{ 
		states[active_states[i]]->handleevents(curEvent);
	}
}

void Empaerior::Application::render()
{
	for (Empaerior::u_inter i = active_states.size() - 1; i >= 0; i--)
	{
		states[active_states[i]]->Render();
	}
}

