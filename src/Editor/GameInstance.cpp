#include "Editor/Runtime.hpp"

#include "ObjectInterfacePerModule.h"
#include "IObject.h"
#include "Editor/GameInstance.hpp"
#include "Editor/SystemTable.h"
#include "ISimpleSerializer.h"
#include "IRuntimeObjectSystem.h"
#include "IObjectFactorySystem.h"

// #include "Editor/Layers/Layers.hpp"
#include "Editor/Layers/BaseLayer.hpp"


enum InterfaceIDEnumLuddite
{
        IID_IRCCPP_GAME_INSTANCE = IID_ENDInterfaceID, // IID_ENDInterfaceID from IObject.h InterfaceIDEnum

        IID_ENDInterfaceIDEnumLuddite
};

struct GameInstance : GameInstanceI, TInterface<IID_IRCCPP_GAME_INSTANCE, IObject>
{
        GameInstance()
        {
                PerModuleInterface::g_pSystemTable->pGameInstanceI = this;
                g_pSys->pRuntimeObjectSystem->GetObjectFactorySystem()->SetObjectConstructorHistorySize(10);
        }

        // void Serialize(ISimpleSerializer *pSerializer) override
        // {
        //         // SERIALIZE(show_demo_window);
        //         // SERIALIZE(compileStartTime);
        //         // SERIALIZE(compileEndTime);
        // }
        void Initialize() override
        {
                LD_LOG_INFO("Initialized");
                // std::cout << "please work" << std::endl;

                m_LayerStack.PushLayer(std::make_shared<BaseLayer>());
        }

        void OnUpdate(float delta_time) override
        {
                m_LayerStack.UpdateLayers(delta_time);
        }

        void OnRender(float lerp_alpha, Luddite::RenderTarget render_target) override
        {
                m_LayerStack.RenderLayers(lerp_alpha, render_target);
        }

        void OnImGuiRender(float lerp_alpha, Luddite::RenderTarget render_target) override
        {
                m_LayerStack.RenderLayersImGui(lerp_alpha, render_target);
        }

        Luddite::LayerStack m_LayerStack;
};

REGISTERSINGLETON(GameInstance, true);