#include "SDL_scancode.h"
#include "Tools/Imgui/Emp_Imgui.h"
#include <Empaerior.h>
#include <EmpaeriorEngine.h>
#include <SDL_vulkan.h>

//#include "tools/emptmxlite/emptmxlite.h"
#include <string>
#include <thread>

#include <SDL.h>
#include <SDL_render.h>

// An example of what a application might look like
#include "debugging/log.h"
#include "input/input.h"
#include "input/keyboard.h"
#include "input/mouse.h"
#include "rendering/vulkan_rendering/geometry_buffer.h"
#include "rendering/vulkan_rendering/renderer.h"
#include <rendering/vulkan_rendering/sprite.h>
#include <stb_image.h>
#include <vulkan/vulkan.h>

inline Empaerior::Font idk;
inline std::string message = "gpdr";
inline Empaerior::Sprite lol;

struct copyReductorComponent
{
    copyReductorComponent()
    {
        std::cout << "copy created\n";
    }
    ~copyReductorComponent()
    {
        std::cout << "copy destroyed\n";
    }
};

//
// a user defined state
class APP_State1 : public Empaerior::State
{

  public:
    APP_State1(VK_Renderer *renderer, Empaerior::Scene2D *m_scene, Empaerior::u_inter originText)
    {
        ecs.Init();
        ecs.register_system<Empaerior::singleSpriteSystem>(sprite_system);
        scene = m_scene;
        scene->init(*renderer);
        sprite_system.Init(ecs, renderer, scene);
        m_renderer = renderer;

        Empaerior::Sprite greenerboi{};
        Empaerior::createSprite(scene->geometrybuffer, renderer->texture_atlas, greenerboi, {0, 0, 99, 99},
                                {0, 0, 1, 1}, 0);
        Empaerior::setSpriteDepth(greenerboi, 0.9f);
        Empaerior::setSpriteAngle(greenerboi, 60.0f);

        Empaerior::Entity copier;
        copier.id = ecs.create_entity_ID();
        ecs.add_component<copyReductorComponent>(copier.id, {});
        ecs.add_component<Empaerior::singleSprite_Component>(copier.id, {});

        Empaerior::Sprite text{};
        Empaerior::createTextSprite((*renderer), *scene, text, {250, 250, 100, 100}, {32.f, 32.f}, idk,
                                    "ijgi gijfigji fgijfgij", {255, 255, 255});
    }
    ~APP_State1() override
    {
        ecs.Destroy();
        scene->cleanup();
    }
    void Update(const Empaerior::u_int dt) override
    {
        if (Empaerior::Input::Keyboard::is_key_pressed(SDL_SCANCODE_M))
        {

            auto position = Empaerior::Input::Mouse::get_world_mouse_coords(m_renderer->GraphicsSettings, scene->ubo);
            morge.push_back({});
            morge[morge.size() - 1].id = ecs.create_entity_ID();
            ecs.add_component<Empaerior::singleSprite_Component>(morge[morge.size() - 1].id, {});
            sprite_system.createSprite(ecs, morge[morge.size() - 1].id, {position[0], position[1], 100, 100},
                                       {0, 0, 1, 1}, 1);
            Empaerior::setSpriteDepth(
                ecs.get_component<Empaerior::singleSprite_Component>(morge[morge.size() - 1].id).sprites, 0.5f);
        }
        else if (Empaerior::Input::Keyboard::is_key_pressed(SDL_SCANCODE_Q))
        {
            if (morge.size() > 1)
            {
                sprite_system.destroySprite(&ecs, morge[morge.size() - 1].id);
                ecs.destroy_entity(morge[morge.size() - 1].id);
                morge.pop_back();
            }
        }
        else if (Empaerior::Input::Keyboard::is_key_pressed((SDL_SCANCODE_1)) && !morge.empty())
        {
            Empaerior::setSpriteTexture(
                ecs.get_component<Empaerior::singleSprite_Component>(morge[morge.size() - 1].id).sprites, 0);
            Empaerior::setSpriteDepth(
                ecs.get_component<Empaerior::singleSprite_Component>(morge[morge.size() - 1].id).sprites, .0f);
        }
    }
    void Render() override // renders the state
    {
    }

    void handleevents(Empaerior::Event &event) override
    {
        event_system.handle_events(ecs, event);
    }
    Empaerior::Event_System event_system;
    Empaerior::singleSpriteSystem sprite_system;
    int i = 0;

  private:
    int angle = 0;
    std::vector<Empaerior::Entity> morge;
    VK_Renderer *m_renderer;
    Empaerior::Scene2D *scene;
};

// a user defined application
class TestApplication : public Empaerior::Application
{
  public:
    TestApplication()
    {
        // CREATE A WINDOW
        window.Init("Empaerior  3.0C12 -Vulkan Renderer", 960, 540); /*?*/

        vk.Init(&window); /*?*/

        ImGui_Emp::Init(window, vk);

        auto originText2 = vk.texture_atlas.create_texture_from_file("assets/textur2e.png");
        auto originText = vk.texture_atlas.create_texture_from_file("assets/textur3e.png");
        auto greenboiTxt = vk.texture_atlas.create_texture_from_file("assets/green_boi.png");
        vk.texture_atlas.create_texture_from_fontPath(idk, "assets/fonts/idk.ttf", 32);

        main_state = push_state(new APP_State1(&vk, &scene, originText));

        activate_state(main_state);
    }

    ~TestApplication() override = default;

    // the main loop

    void run() override
    {

        // GAME LOOP
        while (Empaerior::Application::is_running)
        {

            Empaerior::Timer timy;

            // poll what event is registered
            while (Empaerior::Application::PollEvent())
            {
                // handle it
                handlevents(Empaerior::Application::event);
                ImGuiEmpImpl::ProcessEvent(Empaerior::Application::event);
            }
            if (!Empaerior::Application::is_paused)
            {
                Update(0);
                timy.start();
                if (Empaerior::Input::Keyboard::is_key_pressed(SDL_SCANCODE_E))
                {

                    Empaerior::Sprite sprt{};
                    Empaerior::createSprite(
                        vk, sprt,
                        {Empaerior::Input::Mouse::get_screen_mouse_coords(vk.GraphicsSettings).elements[0],
                         Empaerior::Input::Mouse::get_screen_mouse_coords(vk.GraphicsSettings).elements[1], 25, 25},
                        {0, 0, 1, 1}, 1);
                }
                Empaerior::Sprite text{};
                Empaerior::createTextSprite(vk, text, {250, 250, 100, 100}, {32.f, 32.f}, idk, "ijgi gijfigji fgijfgij",
                                            {255, 255, 255});
                if (Empaerior::Input::Keyboard::is_key_pressed(SDL_SCANCODE_E))
                {
                    // dump_data(vk.defaultScene.geometrybuffer);
                }

                timy.stop();

                ImGui_Emp::NewFrame(window, vk);

                timy.start();
                vk.renderFrame([&]() { ImGui_Emp::refreshImgui(window, vk); },
                               [&]() {
                                   ShowImGuiWindows();
                                   ImGui_Emp::Render(window, vk);
                               }); /*?*/
                vk.defaultScene.geometrybuffer.reset();
            }
        }
        vkDeviceWaitIdle(vk.device);
        ImGui_Emp::Quit(vk);
    }

    void handlevents(Empaerior::Event &event) override
    {
        window.window_listener.handleEvents(event);
        /*	if (active_states.size() == 0) return;
            for (Empaerior::u_inter i = active_states.size() - 1; active_states.size() > i; --i)
            {
                states[active_states[i]]->handleevents(event);
            }*/
    }
    void Update(const Empaerior::u_int dt) override
    {

        for (auto &index : active_states)
            states[index]->Update(dt);
    }

    void render() override
    {
        for (auto &index : active_states)
            states[index]->Render();
    }

    void ShowImGuiWindows()
    {
        static float defaultTextureColor[4] = {1.f, 0, 1.f, 1.f};
        ImGui::Begin("Graphics");
        if (ImGui::CollapsingHeader("Rasterization"))
        {
            ImGui::Checkbox("RasterizerDiscardEnable", &vk.GraphicsSettings.rasterizerDiscardEnable);
            ImGui::Checkbox("DepthClamp", &vk.GraphicsSettings.DepthClamp);
            ImGui::Checkbox("DepthBias", &vk.GraphicsSettings.DepthBias);
            ImGui::InputFloat("LineWidth", &vk.GraphicsSettings.lineWidth);
        }
        if (ImGui::CollapsingHeader("Multisampling"))
        {
            ImGui::Checkbox("SampleShadingEnable", &vk.GraphicsSettings.sampleShadingEnable);
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
            ImGui::InputFloat("ViewportH", &vk.GraphicsSettings.viewportH, 10, 100, 2);
            ImGui::InputInt2("ScissorOffset", vk.GraphicsSettings.scissorOffset.elements);
        }
        if (ImGui::CollapsingHeader("Blending"))
        {
            ImGui::Checkbox("Blending", &vk.GraphicsSettings.Blending);
            ImGui::Checkbox("LogicOpEnable", &vk.GraphicsSettings.LogicOPEnable);
            ImGui::InputFloat4("BlendConstants", vk.GraphicsSettings.blendConstants);
        }
        if (ImGui::CollapsingHeader("Textures"))
        {

            ImGui::SetColorEditOptions(ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Uint8 |
                                       ImGuiColorEditFlags_DisplayRGB);
            ImGui::ColorPicker3("Default Texture", defaultTextureColor);
        }
        ImGui::Button("Apply", {50, 25});
        if (ImGui::IsItemClicked())
        {
            for (size_t i = 0; i < 3; i++)
            {
                float rgb = defaultTextureColor[i] * 255;
                vk.GraphicsSettings.defaultTextureColor[i] = static_cast<Empaerior::byte>(rgb);
            }
            std::cout << '\n';
            vk.framebufferNeedsReconstruction = true;
            vk.texture_atlas.changeTextureAtIndex(0, vk.GraphicsSettings.defaultTextureColor.data(), 1, 1);
        }

        ImGui::Button("Reset", {50, 25});
        if (ImGui::IsItemClicked())
        {
            vk.GraphicsSettings = vk.InitialGraphicsSettings;
            vk.framebufferNeedsReconstruction = true;
            defaultTextureColor[0] = 1.f;
            defaultTextureColor[1] = 0;
            defaultTextureColor[2] = 1.f;
            defaultTextureColor[3] = 1.f;
        }
        ImGui::End();

        ImGui::Begin("Camera Settings");
        ImGui::InputFloat("Camera X", &vk.defaultScene.ubo.position.x, 10, 100, 2);
        ImGui::InputFloat("Camera Y", &vk.defaultScene.ubo.position.y, 10, 100, 2);
        ImGui::InputFloat("ScaleX", &vk.defaultScene.ubo.scaleX, 0.1f, 100, 2);
        ImGui::InputFloat("ScaleY", &vk.defaultScene.ubo.scaleY, 0.1f, 100, 2);

        ImGui::End();

        ImGui::Begin("Geometry Buffer Data");

        if (ImGui::CollapsingHeader("Vertex Buffer"))
        {
            std::string bufferIndex("Current Buffer Index : " +
                                    std::to_string(vk.defaultScene.geometrybuffer.vertexBuffer.get_in_use_index()));
            ImGui::Text(bufferIndex.c_str());

            std::string bufferAllocationSize(
                "Buffer Allocation Size : " +
                std::to_string(vk.defaultScene.geometrybuffer.vertexBuffer
                                   .BufferSize[vk.defaultScene.geometrybuffer.vertexBuffer.get_in_use_index()]));
            ImGui::Text(bufferAllocationSize.c_str());

            std::string bufferSize(
                "Current Buffer Size : " +
                std::to_string(vk.defaultScene.geometrybuffer.vertexBuffer
                                   .used_size[vk.defaultScene.geometrybuffer.vertexBuffer.get_in_use_index()]));
            ImGui::Text(bufferSize.c_str());

            std::string vertices(
                "Current Vertice count : " +
                std::to_string(vk.defaultScene.geometrybuffer.vertexBuffer
                                   .used_size[vk.defaultScene.geometrybuffer.vertexBuffer.get_in_use_index()] /
                               sizeof(Vertex)));
            ImGui::Text(vertices.c_str());
        }
        if (ImGui::CollapsingHeader("Index Buffer"))
        {
            std::string bufferIndex("Current Buffer Index : " +
                                    std::to_string(vk.defaultScene.geometrybuffer.indexBuffer.get_in_use_index()));
            ImGui::Text(bufferIndex.c_str());

            std::string bufferAllocation(
                "Current Buffer Allocation : " +
                std::to_string(vk.defaultScene.geometrybuffer.indexBuffer
                                   .BufferSize[vk.defaultScene.geometrybuffer.indexBuffer.get_in_use_index()]));
            ImGui::Text(bufferAllocation.c_str());

            std::string bufferSize(
                "Current Buffer Size : " +
                std::to_string(vk.defaultScene.geometrybuffer.indexBuffer
                                   .used_size[vk.defaultScene.geometrybuffer.indexBuffer.get_in_use_index()]));
            ImGui::Text(bufferSize.c_str());

            std::string vertices(
                "Current Index count : " +
                std::to_string(vk.defaultScene.geometrybuffer.indexBuffer
                                   .used_size[vk.defaultScene.geometrybuffer.indexBuffer.get_in_use_index()] /
                               sizeof(uint32_t)));
            ImGui::Text(vertices.c_str());
        }
        ImGui::End();

        ImGui::ShowMetricsWindow();
    }

    std::vector<Empaerior::Sprite> sprites;
    Empaerior::u_inter main_state;

    VK_Renderer vk;
    Empaerior::Scene2D scene;
    std::string str = "1111111";
};

// CREATE A NEW APPLICATION
Empaerior::Application *Empaerior::Create_Application()
{
    return new TestApplication();
}