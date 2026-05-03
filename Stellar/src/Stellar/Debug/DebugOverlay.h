#ifndef STELLAR_DEBUG_OVERLAY_H
#define STELLAR_DEBUG_OVERLAY_H

#include "Stellar/Core/Common.h"
#include "Stellar/Core/GameState.h"
#include "Stellar/Debug/DebugTool.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui-SFML.h"

#ifdef STELLAR_DEBUG
#define REGISTER_DEBUG_TOOL(TYPE) \
    static struct TYPE##Registrar { \
        TYPE##Registrar() { \
            Stellar::DebugOverlay::RegisterTool<TYPE>(); \
        } \
    } TYPE##RegistrarInstance;
#else
#define REGISTER_DEBUG_TOOL(TYPE)
#endif

namespace Stellar {

	class DebugOverlay
	{
	public:
		void Load();
		void UpdateImGui(const std::shared_ptr<GameState>& _gameState, float _deltaTime);
	
		inline bool IsDebugEnabled() { return isDebugEnabled; }
		inline void ToggleDebug() { isDebugEnabled = !isDebugEnabled; }

		static DebugOverlay& Get();
		static void Shutdown();

		template<typename T>
		static void RegisterTool()
		{
			Get().tools.push_back(std::make_shared<T>());
		}

	private:
		void UpdateStats(const std::shared_ptr<GameState>& _gameState, float _deltaTime);
		void UpdateSettings(bool* _open);
		void UpdateGameState(const std::shared_ptr<GameState>& _gameState, float _deltaTime, bool* _open);
		void UpdateAbout(bool& _open);

	private:
		bool isDebugEnabled = false;
		std::vector<std::shared_ptr<DebugTool>> tools;
		inline static DebugOverlay* instance;
	};
}

#endif