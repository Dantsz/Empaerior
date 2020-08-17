#include "pch.h"
#include "../include/input/eventhandler/eventhandler.h"




void Empaerior::Event_Listener::register_event(Empaerior::u_int type, EventCallback callback, Empaerior::s_inter call_times)
{
	_registeredCallbacks[type].push_back({ callback , call_times});
	
}

void Empaerior::Event_Listener::handleEvents(Empaerior::Event& cur_event)
{
	
	if (_registeredCallbacks.find(cur_event.event.type) == _registeredCallbacks.end()) return;

	for (int i = 0; i < _registeredCallbacks[cur_event.event.type].size(); i++)//iterate throught command and match thoose that fit
	{  

		_registeredCallbacks[cur_event.event.type][i].first(cur_event);
		if (_registeredCallbacks[cur_event.event.type][i].second == 1)
		{
			//delete
			_registeredCallbacks[cur_event.event.type].erase(_registeredCallbacks[cur_event.event.type].begin() + i);
		}
		else if (_registeredCallbacks[cur_event.event.type][i].second > 1)
		{
			--_registeredCallbacks[cur_event.event.type][i].second;
		}


	}

}

void Empaerior::event_handled(Empaerior::Event& event)
{
	event.is_handled = true;
}

Empaerior::boole Empaerior::is_event_handled(const Empaerior::Event& event)
{
	return event.is_handled;
}
