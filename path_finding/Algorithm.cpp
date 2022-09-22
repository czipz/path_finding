#include "Algorithm.h"


alg::A_Star::A_Star()
{
}

void alg::A_Star::Run(const gui::GridStartNode& StartNode, const gui::GridEndNode& EndNode,
	std::vector<gui::Grid*>& Grid, bool& VisualiseFlag, bool& RestartFlag)
{
	if (m_Flag)
	{
		VisualiseFlag = true;
		RestartFlag = true;
		m_Flag = false;
		

		std::cout << "Start!\n";
		m_StartIndex = StartNode.GetIndex();
		m_DiscoveredNodesIndexes.push_back(m_StartIndex);

		int j = m_DiscoveredNodesIndexes.front();
		Grid[j]->ColorSearch();
		while (!m_DiscoveredNodesIndexes.empty())
		{
			if (j >= 0 && j < Grid.size())
			{
				if (Grid[j]->GetLocalDistance() + Heuristic(Grid, j, j - 1) < Grid[j - 1]->GetLocalDistance() && j - 1 != StartNode.GetIndex())
				{
					Grid[j - 1]->SetParentIndex(j);
					Grid[j - 1]->SetLocalDistance(Grid[j]->GetLocalDistance() + Heuristic(Grid, j, j - 1));
					Grid[j - 1]->SetGlobalDistance(Grid[j - 1]->GetLocalDistance() + Heuristic(Grid, j - 1, EndNode.GetIndex()));
					
					m_DiscoveredNodesIndexes.push_back(j - 1);
				}
				if (Grid[j]->GetLocalDistance() + Heuristic(Grid, j, j - 64) < Grid[j - 64]->GetLocalDistance() && j - 64 != StartNode.GetIndex())
				{
					Grid[j - 64]->SetParentIndex(j);
					Grid[j - 64]->SetLocalDistance(Grid[j]->GetLocalDistance() + Heuristic(Grid, j, j - 64));
					Grid[j - 64]->SetGlobalDistance(Grid[j - 64]->GetLocalDistance() + Heuristic(Grid, j - 64, EndNode.GetIndex()));
					
					m_DiscoveredNodesIndexes.push_back(j - 64);
				}
				if (Grid[j]->GetLocalDistance() + Heuristic(Grid, j, j + 1) < Grid[j + 1]->GetLocalDistance() && j + 1 != StartNode.GetIndex())
				{
					Grid[j + 1]->SetParentIndex(j);
					Grid[j + 1]->SetLocalDistance(Grid[j]->GetLocalDistance() + Heuristic(Grid, j, j + 1));
					Grid[j + 1]->SetGlobalDistance(Grid[j + 1]->GetLocalDistance() + Heuristic(Grid, j + 1, EndNode.GetIndex()));

					m_DiscoveredNodesIndexes.push_back(j + 1);
				}
				if (Grid[j]->GetLocalDistance() + Heuristic(Grid, j, j + 64) < Grid[j + 64]->GetLocalDistance() && j + 64 != StartNode.GetIndex())
				{
					Grid[j + 64]->SetParentIndex(j);
					Grid[j + 64]->SetLocalDistance(Grid[j]->GetLocalDistance() + Heuristic(Grid, j, j + 64));
					Grid[j + 64]->SetGlobalDistance(Grid[j + 64]->GetLocalDistance() + Heuristic(Grid, j + 64, EndNode.GetIndex()));

					m_DiscoveredNodesIndexes.push_back(j + 64);
				}
				m_DiscoveredNodesIndexes.pop_front();
				if (m_DiscoveredNodesIndexes.size() > 1)
				{
					m_DiscoveredNodesIndexes.sort([&](const auto& x1, const auto& x2)
						{
							return ((Grid[x1]->GetGlobalDistance() < Grid[x2]->GetGlobalDistance()));
						});
				}
				if (!m_DiscoveredNodesIndexes.empty())
				{
					j = m_DiscoveredNodesIndexes.front();
					Grid[j]->ColorSearch();
					if (j == EndNode.GetIndex())
						break;
				}
				else
				{
					std::cout << "No path!\n";
					m_NoPath = true;
				}

				//std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}
		}

		if (!m_NoPath)
		{
			int temp = EndNode.GetIndex();
			m_Path.push_back(temp);

			while (1)
			{
				temp = Grid[temp]->GetParentIndex();
				m_Path.push_back(temp);
				if (temp == StartNode.GetIndex())
					break;
			}

			for (auto it = m_Path.rbegin(); it != m_Path.rend(); it++)
			{
				Grid[*it]->ColorPath();
				std::this_thread::sleep_for(std::chrono::milliseconds(20));
			}
		}

		m_DiscoveredNodesIndexes.clear();
		m_Path.clear();
		m_NoPath = false;

		m_Flag = true;
		VisualiseFlag = false;
	}
}

int alg::A_Star::Heuristic(const std::vector<gui::Grid*>& Grid, const int& Index1, const int& Index2)
{
	int heuristic = sqrt(pow((Grid[Index1]->GetPosition().x - Grid[Index2]->GetPosition().x), 2) +
		pow((Grid[Index1]->GetPosition().y - Grid[Index2]->GetPosition().y), 2));
	return heuristic;
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

		VisualiseFlag = true;
		RestartFlag = true;
		m_Flag = false;

		std::cout << "Start!\n";

		int Cost = 1;
		m_StartIndex = StartNode.GetIndex();
		m_DiscoveredNodesIndexes.push_back(m_StartIndex);

		int j = m_DiscoveredNodesIndexes.front();
		Grid[j]->ColorSearch();
		while (!m_DiscoveredNodesIndexes.empty())
		{
			if (j >= 0 && j < Grid.size())
			{
				std::cout << "j - 1 = " << j - 1 << std::endl;
				std::cout << "StartNode.GetIndex() = " << StartNode.GetIndex() << std::endl;
				std::cout << "Grid[j]->GetLocalDistance() + Heuristic(Grid, j, j - 1) = " << Grid[j]->GetLocalDistance() + Heuristic(Grid, j, j - 1) << std::endl;
				std::cout << "Grid[j - 1]->GetLocalDistance() = " << Grid[j - 1]->GetLocalDistance() << std::endl;
				if (Grid[j]->GetLocalDistance() + Heuristic(Grid, j, j - 1) < Grid[j - 1]->GetLocalDistance() && j - 1 != StartNode.GetIndex() &&
					Grid[j - 1]->GetParentIndex() == -1)
				{
					Grid[j - 1]->SetParentIndex(j);
					Grid[j - 1]->SetLocalDistance(Grid[j]->GetLocalDistance() + Heuristic(Grid, j, j - 1));
					m_DiscoveredNodesIndexes.push_back(j - 1);
				}
				std::cout << "j - 64 = " << j - 64 << std::endl;
				std::cout << "StartNode.GetIndex() = " << StartNode.GetIndex() << std::endl;
				std::cout << "Grid[j]->GetLocalDistance() + Heuristic(Grid, j, j - 64) = " << Grid[j]->GetLocalDistance() + Heuristic(Grid, j, j - 64) << std::endl;
				std::cout << "Grid[j - 64]->GetLocalDistance() = " << Grid[j - 64]->GetLocalDistance() << std::endl;
				if (Grid[j]->GetLocalDistance() + Heuristic(Grid, j, j - 64) < Grid[j - 64]->GetLocalDistance() && j - 64 != StartNode.GetIndex() &&
					Grid[j - 64]->GetParentIndex() == -1)
				{
					Grid[j - 64]->SetParentIndex(j);
					Grid[j - 64]->SetLocalDistance(Grid[j]->GetLocalDistance() + Heuristic(Grid, j, j - 64));
					m_DiscoveredNodesIndexes.push_back(j - 64);
				}
				std::cout << "j + 1 = " << j + 1 << std::endl;
				std::cout << "StartNode.GetIndex() = " << StartNode.GetIndex() << std::endl;
				std::cout << "Grid[j]->GetLocalDistance() + Heuristic(Grid, j, j + 1) = " << Grid[j]->GetLocalDistance() + Heuristic(Grid, j, j + 1) << std::endl;
				std::cout << "Grid[j + 1]->GetLocalDistance() = " << Grid[j + 1]->GetLocalDistance() << std::endl;
				if (Grid[j]->GetLocalDistance() + Heuristic(Grid, j, j + 1) < Grid[j + 1]->GetLocalDistance() && j + 1 != StartNode.GetIndex() &&
					Grid[j + 1]->GetParentIndex() == -1)
				{
					Grid[j + 1]->SetParentIndex(j);
					Grid[j + 1]->SetLocalDistance(Grid[j]->GetLocalDistance() + Heuristic(Grid, j, j + 1));
					m_DiscoveredNodesIndexes.push_back(j + 1);
				}
				std::cout << "j + 64 = " << j +64 << std::endl;
				std::cout << "StartNode.GetIndex() = " << StartNode.GetIndex() << std::endl;
				std::cout << "Grid[j]->GetLocalDistance() + Heuristic(Grid, j, j + 64) = " << Grid[j]->GetLocalDistance() + Heuristic(Grid, j, j + 64) << std::endl;
				std::cout << "Grid[j + 64]->GetLocalDistance() = " << Grid[j + 64]->GetLocalDistance() << std::endl;
				if (Grid[j]->GetLocalDistance() + Heuristic(Grid, j, j + 64) < Grid[j + 64]->GetLocalDistance() && j + 64 != StartNode.GetIndex() &&
					Grid[j + 64]->GetParentIndex() == -1)
				{
					Grid[j + 64]->SetParentIndex(j);
					Grid[j + 64]->SetLocalDistance(Grid[j]->GetLocalDistance() + Heuristic(Grid, j, j + 64));
					m_DiscoveredNodesIndexes.push_back(j + 64);
				}
					m_DiscoveredNodesIndexes.pop_front();
					if (m_DiscoveredNodesIndexes.size() > 1)
					{
						m_DiscoveredNodesIndexes.sort([&](const auto& x1, const auto& x2)
							{
								return Grid[x1]->GetLocalDistance() < Grid[x2]->GetLocalDistance();
							});
					}
					if (!m_DiscoveredNodesIndexes.empty())
					{
						j = m_DiscoveredNodesIndexes.front();
						Grid[j]->ColorSearch();
						if (j == EndNode.GetIndex())
							break;
					}
					else
					{
						std::cout << "No Path!\n";
						m_NoPath = true;
					}
						
				//std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}
		}

		if (!m_NoPath)
		{
			int temp = EndNode.GetIndex();
			m_Path.push_back(temp);
			while (1)
			{
				temp = Grid[temp]->GetParentIndex();
				m_Path.push_back(temp);
				if (temp == StartNode.GetIndex())
					break;
			}

			for (auto it = m_Path.rbegin(); it != m_Path.rend(); it++)
			{
				Grid[*it]->ColorPath();
				std::this_thread::sleep_for(std::chrono::milliseconds(20));
			}
		}

		m_DiscoveredNodesIndexes.clear();
		m_Path.clear();
		m_NoPath = false;

		m_Flag = true;
		VisualiseFlag = false;
	}

}

int alg::Dijkstra::Heuristic(const std::vector<gui::Grid*>& Grid, const int& Index1, const int& Index2)
{
	int heuristic = sqrt(pow((Grid[Index1]->GetPosition().x - Grid[Index2]->GetPosition().x), 2) +
		pow((Grid[Index1]->GetPosition().y - Grid[Index2]->GetPosition().y), 2)) / 20;
	//std::cout << "heuristic = " << heuristic << std::endl;
	return heuristic;
}

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////


alg::Wavefront::Wavefront()
{
}

void alg::Wavefront::Run(const gui::GridStartNode& StartNode, const gui::GridEndNode& EndNode,
	std::vector<gui::Grid*>& Grid, bool& VisualiseFlag, bool& RestartFlag)
{

	if (m_Flag)
	{
		VisualiseFlag = true;
		RestartFlag = true;
		m_Flag = false;
		m_NoPath = false;

		m_StartIndex = StartNode.GetIndex();
		m_DiscoveredNodes = { m_StartIndex };

		Grid[m_StartIndex]->ColorSearch();
		m_DiscoveredNodeList.push_back(m_DiscoveredNodes);
		m_DiscoveredNodes.clear();
		int temp = 0;
		std::cout << "Searching for End Node...\n";
		for (std::set<int> i : m_DiscoveredNodeList)
		{
			if (!i.empty())
			{
				for (int j : i)
				{
					if (Grid[j - 1]->GetDistance() == 0)
					{
						m_DiscoveredNodes.emplace(j - 1);
						Grid[j - 1]->ColorSearch();
						Grid[j - 1]->SetDistance(Grid[j]->GetDistance() + 1);

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
			}
			else
				break;
		}
		std::cout << "Found End Node!\n";
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

			ListNeighbours.sort([](const auto& x1, const auto& x2)
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
				m_Path.push_back(FoundIndex);
			}
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

		std::cout << "Finished!\n";
		m_DiscoveredNodeList.clear();
		m_DiscoveredNodes.clear();
		m_Path.clear();
		
		m_Flag = true;
		VisualiseFlag = false;
	}
}



