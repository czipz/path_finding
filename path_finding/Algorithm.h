#pragma once

#include <thread>
#include <chrono>
#include "Gui.h"

namespace alg
{
	class Algorithm
	{
	protected:
		bool m_Flag = true;

	public:
		Algorithm() = default;
		virtual void Run(const gui::GridStartNode&, const gui::GridEndNode&,
			const float&, std::vector<gui::Grid*>&, bool&) = 0;

	};

	class A_Star : public Algorithm
	{
	private:

	public:
		A_Star();
		void Run(const gui::GridStartNode&, const gui::GridEndNode&,
			const float&, std::vector<gui::Grid*>&, bool&);
	};

	class Dijkstra : public Algorithm
	{
	private:

	public:
		Dijkstra();
		void Run(const gui::GridStartNode&, const gui::GridEndNode&,
			const float&, std::vector<gui::Grid*>&, bool&);
	};

	class Wavefront : public Algorithm
	{
	private:
		int m_FoundIndex;
		int m_StartIndex;
		std::set<int> m_DiscoveredNodes;
		std::list<std::set<int>> m_DiscoveredNodeList;
		std::list<int> m_Path;
		bool m_NoPath = false;

	public:
		Wavefront();
		void Run(const gui::GridStartNode&, const gui::GridEndNode&,
			const float&, std::vector<gui::Grid*>&, bool&);
	};
}

