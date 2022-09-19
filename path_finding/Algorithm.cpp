#include "Algorithm.h"


alg::A_Star::A_Star()
{
}

void alg::A_Star::Run(const gui::GridStartNode& StartNode, const gui::GridEndNode& EndNode,
	const float& ElapsedTime, std::vector<gui::Grid*>& Grid, bool& VisualiseFlag)
{
	if (m_Flag)
	{
		m_Flag = false;
		for (auto& e : Grid)
		{
			std::cout << e->GetDistance() << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(3));
		}
		VisualiseFlag = false;
	}
}

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////


alg::Dijkstra::Dijkstra()
{
}

void alg::Dijkstra::Run(const gui::GridStartNode& StartNode, const gui::GridEndNode& EndNode,
	const float& ElapsedTime, std::vector<gui::Grid*>& Grid, bool& VisualiseFlag)
{
	if (m_Flag)
	{
		m_Flag = false;
		for (auto& e : Grid)
		{
			std::cout << e->GetDistance() << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(3));
		}
		VisualiseFlag = false;
	}

}

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////


alg::Wavefront::Wavefront()
{
}

void alg::Wavefront::Run(const gui::GridStartNode& StartNode, const gui::GridEndNode& EndNode,
	const float& ElapsedTime, std::vector<gui::Grid*>& Grid, bool& VisualiseFlag)
{
	if (m_Flag)
	{
		m_Flag = false;
		for (auto& e : Grid)
		{
			std::cout << e->GetDistance() << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(3));
		}
		VisualiseFlag = false;
	}
}


