#include <Empaerior.h>
#include <main.h>
#include <SDL_vulkan.h>
#include "Tools/Imgui/Emp_Imgui.h"
#include <vk_mem_alloc.h>

//#include "tools/emptmxlite/emptmxlite.h"
#include <thread>         

#include <SDL.h>
#include <SDL_render.h>
#include "core/mat.h"

//An example of what a application might look like
#include "rendering/vulkan_rendering/renderer.h"
#include <vulkan/vulkan.h>


//
//a user defined state
class APP_State1 : public Empaerior::State
{

public:

	APP_State1()
	{




	}



	~APP_State1()
	{
		ecs.Destroy();
	}

	void Update(const Empaerior::u_int dt) override
	{
		//DEBUG CODE, LETS YOU MOVE AROUND THE MAP




		//UPDATE 





	}

	void Render() override//renders the state
	{


	}
	void handleevents(Empaerior::Event& event) override
	{
		//HANDLE EVENTS
		event_system->handle_events(ecs, event);



	}



	std::shared_ptr<Empaerior::Event_System> event_system;

	float  i = 0;
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
		window.Init("Empaerior  3.0B -Vulkan Renderer", 960, 800);


		//CREATE A NEW STATE
		main_state = push_state(new APP_State1());
		
		vk.AttachWindow(window.window);
		Empaerior::FontLoading::initFontEngine();

		//make the state active

		Empaerior::Sprite testtette;
		activate_state(main_state);
		vk.run();
		ImGui_Emp::Init(window, vk);

		
		
		Empaerior::Font idk;
		vk.texture_atlas.create_texture_from_fontPath(idk, "assets/fonts/calibri.ttf", 64, vk.framebufferNeedsReconstruction);


		createSprite(vk.geometrybuffer, vk.texture_atlas, greenerboi, { 32 , 0,32,32 }, {0,0,100,100}, vk.texture_atlas.create_texture_from_file("textures/textur3e.png",vk.framebufferNeedsReconstruction));
		Empaerior::createTextSprite(vk.geometrybuffer, vk.texture_atlas, greenboi, { 0,0,32,32 }, {32,32}, idk, "ABCDEFGHi");
		//Empaerior::destroySprite(greenboi); 

		
	 //  auto txt = vk.texture_atlas.create_texture_from_file("textures/textur3e.png", vk.framebufferNeedsReconstruction);
		for (float i = 0; i < 1; i+=2)
		{
		
			for (float j = 0; j < 1; j+=2)
			{
				//createSprite(vk.geometrybuffer, vk.texture_atlas, greenerboi, { i * 32 , j * 32,32,32 }, {0,0,100,100}, vk.texture_atlas.create_texture_from_fontPath(idk, "assets/fonts/calibri.ttf",32,vk.framebufferNeedsReconstruction));
				
			}

		}

	

	}
	
	~Test_Aplication()
	{

	}

	//the main loop

	float i = 0;
	void run() override
	{


		//GAME LOOP

	//	destroySprite(greenboi);

		while (Empaerior::Application::is_running)
		{

			Empaerior::Timer timy;



			//poll what event is registered
			while (Empaerior::Application::PollEvent()) {

				//make it not handled yet
				Empaerior::Application::event.is_handled = false;
				//handle it
				handlevents(Empaerior::Application::event);


				if (Empaerior::Application::event.event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
					vk.framebufferNeedsReconstruction = true;

				}

				ImGuiEmpImpl::ProcessEvent(Empaerior::Application::event);

			}
			if (!Empaerior::Application::is_paused)
			{


				if (Empaerior::Input::Keyboard::is_key_pressed(SDL_SCANCODE_W))
				{
					vk.ubo.position.y -= 1;

					//	if(i< 0.4) i += 0.001;

						//setSpriteDepth(greenerboi, i);
						//std::cout << i << '\n';
				}
				else if (Empaerior::Input::Keyboard::is_key_pressed(SDL_SCANCODE_S))
				{
					vk.ubo.position.y += 1;
				
					//if (i > -0.4) i -= 0.001;
				//	setSpriteDepth(greenerboi, i);
				//	std::cout << i << '\n';
					
				}
				else if (Empaerior::Input::Keyboard::is_key_pressed(SDL_SCANCODE_A))
				{
					vk.ubo.position.x -= 1;

				}
				else if (Empaerior::Input::Keyboard::is_key_pressed(SDL_SCANCODE_D))
				{
					vk.ubo.position.x += 1;
				}
				else if (Empaerior::Input::Keyboard::is_key_pressed(SDL_SCANCODE_UP))
				{
					
				}
				else if (Empaerior::Input::Keyboard::is_key_pressed(SDL_SCANCODE_DOWN))
				{
					
				}

				if (vk.framebufferNeedsReconstruction)
				{
					vk.checkFrameBufferResize();
					ImGui_Emp::refreshImgui(window, vk);
					vk.framebufferNeedsReconstruction = false;
				}

				

			

			

				
				vk.ubo.position_mat = glm::translate(glm::mat4(1.0f), glm::vec3(vk.ubo.position.x * -1, vk.ubo.position.y * -1 , 0.0f));



				timy.start();



				ImGui_Emp::NewFrame(window, vk, camera);

				ImGui::ShowMetricsWindow();
				
			
				ImGui::ShowDemoWindow();
				ImGui::ShowAboutWindow();

				ImGui::Begin("Graphics");

				ImGui::Checkbox("Depth", &vk.GraphicsSettings.Depth);
				ImGui::Checkbox("Blending", &vk.GraphicsSettings.Blending);

				ImGui::Button("Apply", { 50, 25 });
				if (ImGui::IsItemClicked()) vk.framebufferNeedsReconstruction = true;
				ImGui::End();

				ImGui::Begin("Camera Settings");
				ImGui::InputFloat("Camera X", &vk.ubo.position.x, 10, 100, 2);
				ImGui::InputFloat("Camera Y", &vk.ubo.position.y, 10, 100, 2);
			

				

				ImGui::End();

				ImGui::Begin("Geometry Buffer Data");
				//TODO:
				if (ImGui::CollapsingHeader("Vertex Buffer")) {
					std::string bufferIndex("Current Buffer Index : " + std::to_string(vk.geometrybuffer.vertexBuffer.inUseBufferIndex));
					ImGui::Text(bufferIndex.c_str());

					std::string bufferAllocationSize("Buffer Allocation Size : " + std::to_string(vk.geometrybuffer.vertexBuffer.BufferSize[vk.geometrybuffer.vertexBuffer.inUseBufferIndex]));
					ImGui::Text(bufferAllocationSize.c_str());

					std::string bufferSize("Current Buffer Size : " + std::to_string(vk.geometrybuffer.vertexBuffer.used_size[vk.geometrybuffer.vertexBuffer.inUseBufferIndex]));
					ImGui::Text(bufferSize.c_str());

					std::string vertices("Current Vertice count : " + std::to_string(vk.geometrybuffer.vertexBuffer.used_size[vk.geometrybuffer.vertexBuffer.inUseBufferIndex] / sizeof(Vertex) )) ;
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

				


				vk.newFrame();

				ImGui_Emp::Render(window, vk, camera);
				//	vk.framebufferResized = true;
				vk.drawFrame();


				//std::cout <<"Frame time: " << timy.getTicks()<< ' '  << "FPS: " << 1000/ ( timy.getTicks<double,std::chrono::nanoseconds>()/ 1000000.0f) << '\n';
				timy.stop();
				vk.present();


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

	std::vector<Empaerior::Sprite> sprites;
	Empaerior::u_inter main_state;
	Empaerior::Sprite greenboi;
	Empaerior::Sprite greenerboi;
	Empaerior::Camera camera;
	VK_Renderer vk;
	int forTest = 0;
};

//CREATE A NEW APPLICATION
Empaerior::Application* Empaerior::Create_Application()
{
	return new Test_Aplication();
}