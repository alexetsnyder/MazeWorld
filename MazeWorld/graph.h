#pragma once
#include <vector>

class Graph
{
	public:
		Graph(int node_number = 0);

		void add_node(int node);
		void add_edge(int node1, int node2);

		std::vector<int> nodes();
		const std::vector<int>::iterator edges_begin(int node);
		const std::vector<int>::iterator edges_end(int node);
			
	private:
		std::vector<std::vector<int> > _graph;
};