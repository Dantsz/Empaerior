#include <Empaerior.h>
#include <EmpaeriorEngine.h>
#include <SDL_vulkan.h>
#include "SDL_scancode.h"
#include "Tools/Imgui/Emp_Imgui.h"


//#include "tools/emptmxlite/emptmxlite.h"
#include <thread>         


#include <SDL.h>
#include <SDL_render.h>


//An example of what a application might look like
#include "rendering/vulkan_rendering/renderer.h"
#include <vulkan/vulkan.h>
#include "input/input.h"
#include <stb_image.h>
#include <rendering/vulkan_rendering/sprite.h>

inline Empaerior::Font idk;
inline std::string message = "gpdr";
inline Empaerior::Sprite lol;

struct copyReductorComponent
{
    copyReductorComponent()
    {
        std::cout<<"copy created\n";
    }

};


//
//a user defined state
class APP_State1 : public Empaerior::State
{

public:

	APP_State1(VK_Renderer* renderer, Empaerior::u_inter originText)
	{
		ecs.Init();
		ecs.register_system<Empaerior::singleSpriteSystem>(sprite_system);
		sprite_system.Init(ecs,renderer);
		m_renderer = renderer;
		

		Empaerior::Sprite greenerboi;
		Empaerior::createSprite(renderer->geometrybuffer, renderer->texture_atlas, greenerboi, { 0,0,99,99 }, { 0,0,1,1 }, 0);
        Empaerior::setSpriteDepth(greenerboi,0.9f);
		Empaerior::Entity copier;
        copier.id = ecs.create_entity_ID();
		ecs.add_component<copyReductorComponent>(copier.id,{});
		ecs.add_component<Empaerior::singleSprite_Component>(copier.id,{});
		sprite_system.createSprite(ecs,copier.id,{0,0,100,100},"assets/2209.png");
		Empaerior::setSpriteDepth(ecs.get_component<Empaerior::singleSprite_Component>(copier.id).sprites,0.0f);

	}
	~APP_State1()
	{
		ecs.Destroy();
	}
	void Update(const Empaerior::u_int dt) override
	{
		if (Empaerior::Input::Keyboard::is_key_pressed(SDL_SCANCODE_M))
			{
					
				auto position = Empaerior::Input::Mouse::get_world_mouse_coords(m_renderer->GraphicsSettings, m_renderer->ubo);
				morge.push_back({});
				morge[morge.size() - 1].id = ecs.create_entity_ID();
				ecs.add_component<Empaerior::singleSprite_Component>(morge[morge.size() - 1].id, {});
				sprite_system.createSprite(ecs, morge[morge.size() - 1].id, { position[0],position[1],100,100 }, {0,0,1,1}, 1);
				Empaerior::setSpriteDepth(ecs.get_component<Empaerior::singleSprite_Component>(morge[morge.size() -1].id).sprites,0.5f);
			}
		else if(Empaerior::Input::Keyboard::is_key_pressed(SDL_SCANCODE_Q))
		{
			if(morge.size() > 1)
			{
			 sprite_system.destroySprite(&ecs, morge[morge.size() -1].id);
			 ecs.destroy_entity(morge[morge.size() - 1].id);
			 morge.pop_back();
			
			}
		} else if(Empaerior::Input::Keyboard::is_key_pressed((SDL_SCANCODE_1)) && !morge.empty())
        {
		    Empaerior::setSpriteTexture(ecs.get_component<Empaerior::singleSprite_Component>(morge[morge.size() -1 ].id).sprites,0);
		    Empaerior::setSpriteDepth(ecs.get_component<Empaerior::singleSprite_Component>(morge[morge.size() -1 ].id).sprites,.0f);
        }

	}
	void Render() override//renders the state
	{
	}

	void handleevents(Empaerior::Event& event) override
	{
		event_system.handle_events(ecs, event);
	}
    Empaerior::Event_System event_system;
	Empaerior::singleSpriteSystem sprite_system;
	int  i = 0;
private:

	int angle = 0;
	std::vector<Empaerior::Entity> morge;
	VK_Renderer* m_renderer;
};


//a user defined application
class TestApplication : public Empaerior::Application
{
public:
    TestApplication()
	{


		//CREATE A WINDOW
		window.Init("Empaerior  3.0C11 -Vulkan Renderer", 960, 540);/*?*/

		
		vk.Init(&window);/*?*/
	

		ImGui_Emp::Init(window, vk);
		
		auto originText2 = vk.texture_atlas.create_texture_from_file("assets/textur2e.png");
		auto originText = vk.texture_atlas.create_texture_from_file("assets/textur3e.png");
		auto greenboiTxt = vk.texture_atlas.create_texture_from_file("assets/green_boi.png");
		vk.texture_atlas.create_texture_from_fontPath(idk, "assets/fonts/idk.ttf", 32);

		main_state = push_state(new APP_State1(&vk,originText));

		activate_state(main_state);

	}
	
	~TestApplication() override = default;


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
		    	if (Empaerior::Input::Keyboard::is_key_pressed(SDL_SCANCODE_N))
		   		{
					vk.geometrybuffer.reset();
				}
				else if (Empaerior::Input::Keyboard::is_key_pressed(SDL_SCANCODE_O))
				{
					dump_data(vk.geometrybuffer);
				}	
				else if (Empaerior::Input::Keyboard::is_key_pressed(SDL_SCANCODE_E))
				{
					std::array<Empaerior::byte,4> pixel = {255,255,255,255};
					vk.texture_atlas.changeTextureAtIndex(0,pixel.data(), 1,1);
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
		window.window_listener.handleEvents(event);
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
			ImGui::Checkbox("RasterizerDiscardEnable", &vk.GraphicsSettings.rasterizerDiscardEnable);
			ImGui::Checkbox("DepthClamp", &vk.GraphicsSettings.DepthClamp);
			ImGui::Checkbox("DepthBias",&vk.GraphicsSettings.DepthBias);
			ImGui::InputFloat("LineWidth",&vk.GraphicsSettings.lineWidth);
		}
		if(ImGui::CollapsingHeader("Multisampling"))
        {
		    ImGui::Checkbox("SampleShadingEnable",&vk.GraphicsSettings.sampleShadingEnable);
        }
		if (ImGui::CollapsingHeader("Depth Settings"))
		{
			ImGui::Checkbox("Depth", &vk.GraphicsSettings.Depth);
			ImGui::Checkbox("StencilTest", &vk.GraphicsSettings.StencilTest);
			ImGui::Checkbox("DepthBoundTest", &vk.GraphicsSettings.DepthBoundTest);
			ImGui::InputFloat("MinDepth", &vk.GraphicsSettings.minDepth);
			ImGui::InputFloat("MaxDepth", &vk.GraphicsSettings.maxDepth);
		}
		if (ImGui::CollapsingHeader("Viewport"))
		{
			ImGui::InputFloat("ViewportX", &vk.GraphicsSettings.viewportX, 10, 100, 2);
			ImGui::InputFloat("ViewportY", &vk.GraphicsSettings.viewportY, 10, 100, 2);
			ImGui::InputFloat("ViewportW", &vk.GraphicsSettings.viewportW, 10, 100, 2);
			ImGui::InputFloat("ViewportH", &vk.GraphicsSettings.viewportH ,10, 100, 2);
            ImGui::InputInt2("ScissorOffset", vk.GraphicsSettings.scissorOffset.elements);
		}
		if(ImGui::CollapsingHeader("Blending"))
        {
            ImGui::Checkbox("Blending", &vk.GraphicsSettings.Blending);
            ImGui::Checkbox("LogicOpEnable",&vk.GraphicsSettings.LogicOPEnable);
            ImGui::InputFloat4("BlendConstants",vk.GraphicsSettings.blendConstants);
        }

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

	VK_Renderer vk;
	std::string str = "1111111";
};

//CREATE A NEW APPLICATION
Empaerior::Application* Empaerior::Create_Application()
{
	return new TestApplication();
}