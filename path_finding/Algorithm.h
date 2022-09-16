#pragma once

#include "Gui.h"

namespace alg
{
	class Algorithm
	{
	protected:

	public:
		Algorithm();
		virtual ~Algorithm();

		virtual void Run(const gui::GridStartNode&, const gui::GridEndNode&,
			const float&, std::vector<gui::Grid*>&) = 0;
	};

	class A_Star : public Algorithm
	{
	private:

	public:
		A_Star();
		~A_Star();

		void Run(const gui::GridStartNode&, const gui::GridEndNode&,
			const float&, std::vector<gui::Grid*>&);
	};

	class Dijkstra : public Algorithm
	{
	private:

	public:
		Dijkstra();
		~Dijkstra();

		void Run(const gui::GridStartNode&, const gui::GridEndNode&,
			const float&, std::vector<gui::Grid*>&);
	};
}

