#include "Algorithm.h"

alg::Algorithm::Algorithm()
{

}

alg::Algorithm::~Algorithm()
{
}

alg::A_Star::A_Star()
{

}

alg::A_Star::~A_Star()
{

}

void alg::A_Star::Run(const gui::GridStartNode& StartNode, const gui::GridEndNode& EndNode,
	const float& ElapsedTime, std::vector<gui::Grid*>& Grid)
{
	std::cout << "A*\n";
}

alg::Dijkstra::Dijkstra()
{

}

alg::Dijkstra::~Dijkstra()
{

}

void alg::Dijkstra::Run(const gui::GridStartNode& StartNode, const gui::GridEndNode& EndNode,
	const float& ElapsedTime, std::vector<gui::Grid*>& Grid)
{
	std::cout << "Dijkstra\n";
}