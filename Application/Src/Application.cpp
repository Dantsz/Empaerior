#include <Empaerior.h>
#include <main.h>
#include <SDL_vulkan.h>
#include "Tools/Imgui/Emp_Imgui.h"
#include <vk_mem_alloc.h>

//#include "tools/emptmxlite/emptmxlite.h"
#include <thread>         

#include <SDL.h>
#include <SDL_render.h>
#include "../include/core/mat.h"

//An example of what a application might look like
#include "rendering/vulkan_rendering/renderer.h"
#include <vulkan/vulkan.h>
#include "input/input.h"


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
		window.Init("Empaerior  3.0B8 -Vulkan Renderer", 960, 540);


		//CREATE A NEW STATE
		main_state = push_state(new APP_State1());
		
		vk.AttachWindow(window.window);
		Empaerior::FontLoading::initFontEngine();

		//make the state active

		Empaerior::Sprite testtette;
		activate_state(main_state);
		vk.run();
		ImGui_Emp::Init(window, vk);

		
		
	
		auto originText2 = vk.texture_atlas.create_texture_from_file("assets/textur2e.png", vk.framebufferNeedsReconstruction);
		auto originText = vk.texture_atlas.create_texture_from_file("assets/textur3e.png", vk.framebufferNeedsReconstruction);
		auto greenboiTxt = vk.texture_atlas.create_texture_from_file("assets/green_boi.png",vk.framebufferNeedsReconstruction);
	

		
	 //  auto txt = vk.texture_atlas.create_texture_from_file("textures/textur3e.png", vk.framebufferNeedsReconstruction);
	/*	for (float i = 0; i < 100; i+=1){
		
			for (float j = 0; j < 100; j+=1)
			{
				int text = int(i + j) % 3;
				createSprite(vk.geometrybuffer, vk.texture_atlas, greenerboi, { (i-15) * 32 ,   (j-15) * 32,32,32 }, { 0,0,vk.texture_atlas.image_dimensions[text].elements[0],vk.texture_atlas.image_dimensions[text].elements[1] }, text);
				setSpriteDepth(greenerboi,0.1);
			}

		}*/
		
		vk.texture_atlas.create_texture_from_fontPath(idk, "assets/fonts/idk.ttf", 64, vk.framebufferNeedsReconstruction);

	

	//	Empaerior::setTextSpriteDepth(greenboi, 1.0f);
		//Empaerior::createSprite(vk.geometrybuffer, vk.texture_atlas, greenerboi, { 32,32,32,32 }, { 0,0,vk.texture_atlas.image_dimensions[originText][0],vk.texture_atlas.image_dimensions[originText][1] }, originText);
		//Empaerior::setSpriteDepth(greenerboi, 0.5f);
		

		Empaerior::createSprite(vk.geometrybuffer, vk.texture_atlas, greenerboi, { 16,32,32,32 }, { 0,0,vk.texture_atlas.image_dimensions[originText][0],vk.texture_atlas.image_dimensions[originText][1] }, originText2);
	//	Empaerior::setSpriteDepth(greenerboi,0.9f);

		//Empaerior::createTextSprite(vk.geometrybuffer, vk.texture_atlas, greenboi, { 0,0,480,3000 }, { 32,32 }, idk, "ABCDEFGHIJKL", {1.0f,1.0f,1.0f});
	//	Empaerior::setTextSpriteDepth(greenboi, 0.0f);

	}
	
	~Test_Aplication()
	{

	}

	//the main loop


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


			
				
				if (vk.framebufferNeedsReconstruction)
				{
					vk.checkFrameBufferResize();
					ImGui_Emp::refreshImgui(window, vk);
					vk.framebufferNeedsReconstruction = false;
				}



				auto position = Empaerior::Input::Mouse::get_world_mouse_coords(vk.GraphicsSettings, vk.ubo);
				//std::cout << position[0]	 << ' ' << position[1] << '\n';
				
				
				vk.ubo.position_mat = glm::translate(glm::mat4(1.0f), glm::vec3(vk.ubo.position.x * -1, vk.ubo.position.y * -1 , 1.0f));
				



				//Empaerior::setSpriteAngle(greenerboi, forTest);
				//forTest += 1;

				
				//


				if (Empaerior::Input::Keyboard::is_key_pressed(SDL_SCANCODE_M))
				{

					Empaerior::createSprite(vk.geometrybuffer, vk.texture_atlas, greenboi, { position[0],position[1],10,10 }, { 0,0,vk.texture_atlas.image_dimensions[2][0],vk.texture_atlas.image_dimensions[2][1] }, 2);


				}





				timy.start();

				//dump_data(vk.geometrybuffer);

				ImGui_Emp::NewFrame(window, vk, camera);
				ShowImGuiWindows();
		
			
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
	Empaerior::Camera camera;
	VK_Renderer vk;
	float forTest = 0;
	float i  = 0, j = 0;
	Empaerior::Font idk;
	std::string str = "1111111";
};

//CREATE A NEW APPLICATION
Empaerior::Application* Empaerior::Create_Application()
{
	return new Test_Aplication();
}