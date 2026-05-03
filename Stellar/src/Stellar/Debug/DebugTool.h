#ifndef STELLAR_DEBUG_TOOL_H
#define STELLAR_DEBUG_TOOL_H

#include "Stellar/Core/Common.h"

namespace Stellar
{
	class DebugTool
	{
	public:
		DebugTool(std::string _name)
			: name(_name) {}

		virtual void UpdateImGui(float _deltaTime) {}

		inline const std::string& GetName() { return name; }

	private:
		std::string name;
		bool isEnabled = false;
		friend class DebugOverlay;
	};
}

#endif