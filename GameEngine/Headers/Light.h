#pragma once



namespace light
{
	class Light
	{
	public:
		//------------------------------ Primary Functions
		virtual void sendUniformDataToShader() = 0;
		virtual void update() = 0;
		virtual void draw() = 0;
		virtual void computeModelMatrix() = 0;
	};
}