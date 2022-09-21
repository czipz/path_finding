#include "Algorithm.h"


alg::A_Star::A_Star()
{
}

void alg::A_Star::Run(const gui::GridStartNode& StartNode, const gui::GridEndNode& EndNode,
	std::vector<gui::Grid*>& Grid, bool& VisualiseFlag, bool& RestartFlag)
{
	if (m_Flag)
	{
		m_Flag = false;
		for (auto& e : Grid)
		{
			std::cout << e->GetDistance() << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
		VisualiseFlag = false;
		m_Flag = true;
	}
}

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////


alg::Dijkstra::Dijkstra()
{
}

void alg::Dijkstra::Run(const gui::GridStartNode& StartNode, const gui::GridEndNode& EndNode,
	std::vector<gui::Grid*>& Grid, bool& VisualiseFlag, bool& RestartFlag)
{
	if (m_Flag)
	{
		m_Flag = false;
		for (auto& e : Grid)
		{
			std::cout << e->GetDistance() << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
		VisualiseFlag = false;
		m_Flag = true;
	}
}

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////


alg::Wavefront::Wavefront()
{
}

void alg::Wavefront::Run(const gui::GridStartNode& StartNode, const gui::GridEndNode& EndNode,
	std::vector<gui::Grid*>& Grid, bool& VisualiseFlag, bool& RestartFlag)
{
	// - problem jest jak nie ma drogi
	// - bugi po restarcie i poruszaniu Startem i Endem

	if (m_Flag)
	{
		VisualiseFlag = true;
		RestartFlag = true;
		m_Flag = false;
		m_NoPath = false;

		m_StartIndex = StartNode.GetIndex();
		m_FoundIndex = m_StartIndex;
		m_DiscoveredNodes = { m_StartIndex };

		Grid[m_StartIndex]->ColorSearch();
		m_DiscoveredNodeList.push_back(m_DiscoveredNodes);
		m_DiscoveredNodes.clear();
		int temp = 0;
		for (std::set<int> i : m_DiscoveredNodeList)
		{
			if (!i.empty())
			{
				for (int j : i) // iteruje po kazdym indeksie z Setu
				{
					if (Grid[j - 1]->GetDistance() == 0)
					{
						m_DiscoveredNodes.emplace(j - 1);
						Grid[j - 1]->ColorSearch();
						Grid[j - 1]->SetDistance(Grid[j]->GetDistance() + 1);
						std::cout << Grid[j - 1]->GetDistance() << std::endl;

						if (j - 1 == EndNode.GetIndex())
						{
							temp = j - 1;
							break;
						}
					}
					if (Grid[j + 1]->GetDistance() == 0)
					{
						m_DiscoveredNodes.emplace(j + 1);
						Grid[j + 1]->SetDistance(Grid[j]->GetDistance() + 1);
						Grid[j + 1]->ColorSearch();

						if (j + 1 == EndNode.GetIndex())
						{
							temp = j + 1;
							break;
						}
					}
					if (Grid[j + 64]->GetDistance() == 0)
					{
						m_DiscoveredNodes.emplace(j + 64);
						Grid[j + 64]->SetDistance(Grid[j]->GetDistance() + 1);
						Grid[j + 64]->ColorSearch();

						if (j + 64 == EndNode.GetIndex())
						{
							temp = j + 64;
							break;
						}
					}
					if (Grid[j - 64]->GetDistance() == 0)
					{
						m_DiscoveredNodes.emplace(j - 64);
						Grid[j - 64]->ColorSearch();
						Grid[j - 64]->SetDistance(Grid[j]->GetDistance() + 1);

						if (j - 64 == EndNode.GetIndex())
						{
							temp = j - 64;
							break;
						}
					}
					std::this_thread::sleep_for(std::chrono::nanoseconds(1000));
				}
				if (temp == EndNode.GetIndex())
					break;
				m_DiscoveredNodeList.push_back(m_DiscoveredNodes);
				m_DiscoveredNodes.clear();
				//std::cout << "Halo\n";
				//std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}
			else
				break;
		}
		std::cout << "razdwa\n";
		int FoundIndex = EndNode.GetIndex();

		while (FoundIndex != StartNode.GetIndex() && !m_NoPath)
		{
			std::list<std::tuple<int, int>> ListNeighbours;
			if (Grid[FoundIndex + 1]->GetDistance() > 0)
				ListNeighbours.push_back({ FoundIndex + 1, Grid[FoundIndex + 1]->GetDistance() });
			if (Grid[FoundIndex - 1]->GetDistance() > 0)
				ListNeighbours.push_back({ FoundIndex - 1, Grid[FoundIndex - 1]->GetDistance() });
			if (Grid[FoundIndex - 64]->GetDistance() > 0)
				ListNeighbours.push_back({ FoundIndex - 64, Grid[FoundIndex - 64]->GetDistance() });
			if (Grid[FoundIndex + 64]->GetDistance() > 0)
				ListNeighbours.push_back({ FoundIndex + 64, Grid[FoundIndex + 64]->GetDistance() });

			ListNeighbours.sort([&](const auto& x1, const auto& x2)
				{
					int d1 = std::get<1>(x1);
					int d2 = std::get<1>(x2);
					return d1 < d2;
				});
			if (ListNeighbours.empty())
				m_NoPath = true;
			else
			{
				FoundIndex = std::get<0>(ListNeighbours.front());
				std::cout << "Distance=" << std::get<1>(ListNeighbours.front()) << std::endl;
				std::cout << "FoundIndex=" << FoundIndex << std::endl;
				m_Path.push_back(FoundIndex);
			}
			//std::this_thread::sleep_for(std::chrono::nanoseconds(10000));
		}

		if (!m_NoPath)
		{
			for (auto it = m_Path.rbegin(); it != m_Path.rend(); it++)
			{
				Grid[*it]->ColorPath();
				std::this_thread::sleep_for(std::chrono::milliseconds(20));
			}
			Grid[EndNode.GetIndex()]->ColorPath();
		}

		std::cout << "Koniec\n";
		m_DiscoveredNodeList.clear();
		m_DiscoveredNodes.clear();
		m_Path.clear();
		
		m_Flag = true;
		VisualiseFlag = false;
	}

}



