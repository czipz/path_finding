#pragma once

#include "Gui.h"

namespace alg
{
	class Algorithm
	{
	protected:

	public:

		virtual void Run(const gui::GridStartNode&, const gui::GridEndNode&,
			const float&, std::vector<gui::Grid*>&) = 0;
	};

	class A_Star : public Algorithm
	{
	private:

	public:

		void Run(const gui::GridStartNode&, const gui::GridEndNode&,
			const float&, std::vector<gui::Grid*>&);
	};

	class Dijkstra : public Algorithm
	{
	private:

	public:

		void Run(const gui::GridStartNode&, const gui::GridEndNode&,
			const float&, std::vector<gui::Grid*>&);
	};

	class Wavefront : public Algorithm
	{
	private:

	public:

		void Run(const gui::GridStartNode&, const gui::GridEndNode&,
			const float&, std::vector<gui::Grid*>&);
	};
}

