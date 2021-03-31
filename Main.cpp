#include <memory>

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include "World.hpp"
#include "AntHome.hpp"
#include "FoodSource.hpp"
#include "Util.hpp"

class Application final : public olc::PixelGameEngine
{
public:
	bool OnUserCreate() override
	{
		sAppName = "Ants";

		world.Create(*this);

		AntHome *antHome = new AntHome(100);
		antHome->SetPosition(olc::vf2d(this->ScreenWidth() / 2.0f, this->ScreenHeight() / 2.0f));

		FoodSource *foodSource = new CircularFoodSource(100, 15.0f);
		foodSource->SetPosition(olc::vf2d(500.0f, 200.0f));

		world.Spawn(antHome);
		world.Spawn(foodSource);

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