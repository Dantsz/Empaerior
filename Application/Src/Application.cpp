#include <Empaerior.h>
#include <EmpaeriorEngine.h>
#include <SDL_vulkan.h>
#include "Tools/Imgui/Emp_Imgui.h"


//#include "tools/emptmxlite/emptmxlite.h"
#include <thread>         


#include <SDL.h>
#include <SDL_render.h>
#include "../include/core/mat.h"

//An example of what a application might look like
#include "rendering/vulkan_rendering/renderer.h"
#include <vulkan/vulkan.h>
#include "input/input.h"
#include <stb_image.h>
#include <rendering/vulkan_rendering/sprite.h>

inline Empaerior::Font idk;
inline std::string message = "gpdr";
inline Empaerior::Sprite lol;
//
//a user defined state
class APP_State1 : public Empaerior::State
{

public:

	APP_State1(VK_Renderer* renderer, Empaerior::u_inter originText)
	{
		ecs.Init();
		sprite_system = ecs.register_system<Empaerior::singleSpriteSystem>();
		sprite_system->Init(renderer);
		
		ecs.register_component<Empaerior::singleSprite_Component>();
		ecs.add_criteria_for_iteration<Empaerior::singleSpriteSystem, Empaerior::singleSprite_Component>();

		Empaerior::Sprite greenerboi;
	//	Empaerior::createSprite(renderer->geometrybuffer, renderer->texture_atlas, greenerboi, { 0,0,100,100 }, { 0,0,600,600 }, 1);

		morge.id = ecs.create_entity_ID();
		ecs.add_component<Empaerior::singleSprite_Component>(morge.id, {});
		sprite_system->createSprite(ecs, morge.id, { 0,100,960,320 }, {0,0,1,1}, 0);

		Empaerior::createTextSprite(renderer->geometrybuffer, renderer->texture_atlas, lol, {500,100,1000,1000}, {32,32}, idk, "gffgfgfgfgfg", { 255,255,255 });

	

		Empaerior::setTextSpriteMessage(lol, { 500,200,1000,1000 }, { 32,32 }, idk, "1234", { 255,255,255 });
		//Empaerior::destroySprite(borge[30]);	//Empaerior::setSpriteDimensions(borge[25], 0.0f, 0.0f);
	

	
	}



	~APP_State1()
	{
		ecs.Destroy();
	}

	void Update(const Empaerior::u_int dt) override
	{
	}

	void Render() override//renders the state
	{
	}
	void handleevents(Empaerior::Event& event) override
	{
		event_system->handle_events(ecs, event);
	}



	std::shared_ptr<Empaerior::Event_System> event_system;
	std::shared_ptr<Empaerior::singleSpriteSystem> sprite_system;
	int  i = 0;
private:

	int angle = 0;
	Empaerior::Entity morge;

};


//a user defined application
class Test_Aplication : public Empaerior::Application
{
public:
	Test_Aplication()
	{


		//CREATE A WINDOW
		window.Init("Empaerior  3.0B10 -Vulkan Renderer", 960, 540);/*?*/

		
		vk.Init(&Empaerior::Application::window);/*?*/
	

		ImGui_Emp::Init(window, vk);
		
		auto originText2 = vk.texture_atlas.create_texture_from_file("assets/textur2e.png");
		auto originText = vk.texture_atlas.create_texture_from_file("assets/textur3e.png");
		auto greenboiTxt = vk.texture_atlas.create_texture_from_file("assets/green_boi.png");
		vk.texture_atlas.create_texture_from_fontPath(idk, "assets/fonts/idk.ttf", 32);

		main_state = push_state(new APP_State1(&vk,originText));

		activate_state(main_state);

	}
	
	~Test_Aplication()
	{

	}

	//the main loop


	void run() override
	{


		//GAME LOOP
		while (Empaerior::Application::is_running)
		{

			Empaerior::Timer timy;

			//poll what event is registered
			while (Empaerior::Application::PollEvent()) {

				
				//handle it
				handlevents(Empaerior::Application::event);
				ImGuiEmpImpl::ProcessEvent(Empaerior::Application::event);
			}
			if (!Empaerior::Application::is_paused)
			{


				auto position = Empaerior::Input::Mouse::get_world_mouse_coords(vk.GraphicsSettings, vk.ubo);
				if (Empaerior::Input::Keyboard::is_key_pressed(SDL_SCANCODE_M))
				{

					Empaerior::createSprite(vk.geometrybuffer, vk.texture_atlas, greenboi, { position[0],position[1],10,10 }, { 0,0,vk.texture_atlas.image_dimensions[2][0],vk.texture_atlas.image_dimensions[2][1] }, 2);


				}
				else if (Empaerior::Input::Keyboard::is_key_pressed(SDL_SCANCODE_N))
				{
					vk.geometrybuffer.reset();
				}
				else if (Empaerior::Input::Keyboard::is_key_pressed(SDL_SCANCODE_O))
				{
					dump_data(vk.geometrybuffer);
				}	
				else if (Empaerior::Input::Keyboard::is_key_pressed(SDL_SCANCODE_E))
				{
					message += 'x';
			
					
					Empaerior::setTextSpriteMessage(lol, { 500,100,1000,1000 }, { 32,32 }, idk, message.c_str(), {255,255,255});
				}


				Update(0);



				timy.start();


				
				ImGui_Emp::NewFrame(window, vk);
				ShowImGuiWindows();
				
				vk.renderFrame([&](){ImGui_Emp::refreshImgui(window, vk);},[&](){ImGui_Emp::Render(window, vk);});/*?*/
				//dump_data(vk.geometrybuffer);
				timy.stop();
				
				//

			}






		}

		vkDeviceWaitIdle(vk.device);
		ImGui_Emp::Quit(vk);
		vk.cleanup();
	
	}


	void handlevents(Empaerior::Event& event) override
	{
		Empaerior::Application::window.window_listener.handleEvents(event);
		/*	if (active_states.size() == 0) return;
			for (Empaerior::u_inter i = active_states.size() - 1; active_states.size() > i; --i)
			{
				states[active_states[i]]->handleevents(event);
			}*/
	}
	void Update(const Empaerior::u_int dt)override
	{

		for (auto& index : active_states) states[index]->Update(dt);


	}


	void render() override
	{
		for (auto& index : active_states) states[index]->Render();

	}

	void ShowImGuiWindows()
	{
		ImGui::Begin("Graphics");
		if (ImGui::CollapsingHeader("Rasterization"))
		{
			ImGui::Checkbox("rasterizerDiscardEnable", &vk.GraphicsSettings.rasterizerDiscardEnable);
			ImGui::Checkbox("DepthClamp", &vk.GraphicsSettings.DepthClamp);
		}
		if (ImGui::CollapsingHeader("Depth Settings"))
		{
			ImGui::Checkbox("Depth", &vk.GraphicsSettings.Depth);
			ImGui::Checkbox("Stenciltest", &vk.GraphicsSettings.StencilTest);
			ImGui::Checkbox("DepthBoundtest", &vk.GraphicsSettings.DepthBoundTest);
			ImGui::InputFloat("MinDepth", &vk.GraphicsSettings.minDepth);
			ImGui::InputFloat("MaxDepth", &vk.GraphicsSettings.maxDepth);
		}
		if (ImGui::CollapsingHeader("Viewport"))
		{
			ImGui::InputFloat("ViewportX", &vk.GraphicsSettings.viewportX, 10, 100, 2);
			ImGui::InputFloat("ViewportY", &vk.GraphicsSettings.viewportY, 10, 100, 2);
			ImGui::InputFloat("ViewportW", &vk.GraphicsSettings.viewportW, 10, 100, 2);
			ImGui::InputFloat("ViewportH", &vk.GraphicsSettings.viewportH ,10, 100, 2);


		}
		
		ImGui::Checkbox("Blending", &vk.GraphicsSettings.Blending);
		

		ImGui::Button("Apply", { 50, 25 });
		if (ImGui::IsItemClicked()) vk.framebufferNeedsReconstruction = true;
	

		ImGui::Button("Reset", { 50,25 });
		if (ImGui::IsItemClicked()) { vk.GraphicsSettings = vk.InitialGraphicsSettings;  vk.framebufferNeedsReconstruction = true; }
		ImGui::End();

		ImGui::Begin("Camera Settings");
		ImGui::InputFloat("Camera X", &vk.ubo.position.x, 10, 100, 2);
		ImGui::InputFloat("Camera Y", &vk.ubo.position.y, 10, 100, 2);
		ImGui::InputFloat("ScaleX", &vk.ubo.scaleX, 0.1f, 100, 2);
		ImGui::InputFloat("ScaleY", &vk.ubo.scaleY, 0.1f, 100, 2);


		ImGui::End();

		ImGui::Begin("Geometry Buffer Data");

		if (ImGui::CollapsingHeader("Vertex Buffer")) {
			std::string bufferIndex("Current Buffer Index : " + std::to_string(vk.geometrybuffer.vertexBuffer.inUseBufferIndex));
			ImGui::Text(bufferIndex.c_str());

			std::string bufferAllocationSize("Buffer Allocation Size : " + std::to_string(vk.geometrybuffer.vertexBuffer.BufferSize[vk.geometrybuffer.vertexBuffer.inUseBufferIndex]));
			ImGui::Text(bufferAllocationSize.c_str());

			std::string bufferSize("Current Buffer Size : " + std::to_string(vk.geometrybuffer.vertexBuffer.used_size[vk.geometrybuffer.vertexBuffer.inUseBufferIndex]));
			ImGui::Text(bufferSize.c_str());

			std::string vertices("Current Vertice count : " + std::to_string(vk.geometrybuffer.vertexBuffer.used_size[vk.geometrybuffer.vertexBuffer.inUseBufferIndex] / sizeof(Vertex)));
			ImGui::Text(vertices.c_str());
		}
		if (ImGui::CollapsingHeader("Index Buffer")) {
			std::string bufferIndex("Current Buffer Index : " + std::to_string(vk.geometrybuffer.indexBuffer.inUseBufferIndex));
			ImGui::Text(bufferIndex.c_str());

			std::string bufferAllocation("Current Buffer Allocation : " + std::to_string(vk.geometrybuffer.indexBuffer.BufferSize[vk.geometrybuffer.indexBuffer.inUseBufferIndex]));
			ImGui::Text(bufferAllocation.c_str());

			std::string bufferSize("Current Buffer Size : " + std::to_string(vk.geometrybuffer.indexBuffer.used_size[vk.geometrybuffer.indexBuffer.inUseBufferIndex]));
			ImGui::Text(bufferSize.c_str());

			std::string vertices("Current Index count : " + std::to_string(vk.geometrybuffer.indexBuffer.used_size[vk.geometrybuffer.indexBuffer.inUseBufferIndex] / sizeof(uint32_t)));
			ImGui::Text(vertices.c_str());


		}
		ImGui::End();
		
		ImGui::ShowMetricsWindow();
	}

	std::vector<Empaerior::Sprite> sprites;
	Empaerior::u_inter main_state;
	Empaerior::Sprite greenboi;
	Empaerior::Sprite greenerboi;
	Empaerior::Sprite textboiii;

	VK_Renderer vk;
	float forTest = 0;
	float i  = 0, j = 0;

	std::string str = "1111111";
};

//CREATE A NEW APPLICATION
Empaerior::Application* Empaerior::Create_Application()
{
	return new Test_Aplication();
}