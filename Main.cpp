#include <iostream>

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include "Ant.hpp"
#include "Util.hpp"

class Application final : public olc::PixelGameEngine
{
public:
	bool OnUserCreate() override
	{
		sAppName = "Ants";

		for (unsigned i = 0; i < 100; i++)
		{
			Ant randomAnt;
			randomAnt.SetPosition(olc::vf2d(this->ScreenWidth() / 2.0f, this->ScreenHeight() / 2.0f));

			ants.push_back(randomAnt);
		}

		return true;
	}

	bool OnUserUpdate(const float dt) override
	{
		this->Clear(olc::BLACK);

		for (Ant &ant : ants)
		{
			ant.Update(dt);
			this->DrawAnt(ant);
		}

		return true;
	}

private:
	void DrawAnt(const Ant &ant)
	{
		this->FillCircle(ant.GetPosition(), 1.5f);
	}

private:
	std::vector<Ant> ants;
};

int main()
{
	Application app;
	if (app.Construct(1280, 720, 1, 1))
		app.Start();

	return 0;
}