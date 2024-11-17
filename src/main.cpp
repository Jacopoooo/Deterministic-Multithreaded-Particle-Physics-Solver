#include "simulation.hpp"

int main()
{
	constexpr size_t particlesNum = 100;
	constexpr size_t screenWidth = 1200;
	constexpr size_t screenHeight = 800;
	Simulation s(particlesNum, screenWidth, screenHeight);

	s.run();

	return 0;
}