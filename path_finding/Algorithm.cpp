#include "Algorithm.h"


void alg::A_Star::Run(const gui::GridStartNode& StartNode, const gui::GridEndNode& EndNode,
	const float& ElapsedTime, std::vector<gui::Grid*>& Grid)
{
	std::cout << "A*\n";
}

void alg::Dijkstra::Run(const gui::GridStartNode& StartNode, const gui::GridEndNode& EndNode,
	const float& ElapsedTime, std::vector<gui::Grid*>& Grid)
{
	std::cout << "Dijkstra\n";
}

void alg::Wavefront::Run(const gui::GridStartNode& StartNode, const gui::GridEndNode& EndNode,
	const float& ElapsedTime, std::vector<gui::Grid*>& Grid)
{
	std::cout << "Wavefront\n";
}