#pragma once


#include "defcs.h"
#include "FrameFormat.h"

namespace manager
{
	class FrameManager
	{
	private:
		//------------------------------ Constructors
		FrameManager() {};
		~FrameManager() {};

	public:
		//------------------------------ Singleton Pattern
		FrameManager(const FrameManager &) = delete;
		const FrameManager &operator=(const FrameManager &) = delete;
		static FrameManager* getInstance();

		//------------------------------ Primary Functions
		void init();
		void listener();
	};
}