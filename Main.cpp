#include <memory>

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include "World.hpp"
#include "Util.hpp"

template<typename T>
using Ptr = std::unique_ptr<T>;

class Application final : public olc::PixelGameEngine
{
public:
	bool OnUserCreate() override
	{
		sAppName = "Ants";

		world.Create(*this, 1000);

		return true;
	}

	bool OnUserUpdate(const float dt) override
	{
		this->Clear(olc::BLACK);

		world.Update(dt);
		world.Render(*this);

		return true;
	}

private:
	World world;
};

int main()
{
	Application app;
	if (app.Construct(1280, 720, 1, 1))
		app.Start();

	return 0;
}