#include "graph.h"

Graph::Graph(int node_number)
{
	_graph.resize(node_number);

	for (int i = 0; i < node_number; ++i)
	{
		std::vector<int> row;
		_graph[i] = row;
	}
}

void Graph::add_node(int node)
{
	std::vector<int> row;
	_graph.push_back(row);
}

void Graph::add_edge(int node1, int node2)
{
	_graph[node1].push_back(node2);
	_graph[node2].push_back(node1);
}

std::vector<int> Graph::nodes()
{
	std::vector<int> nodes;
	nodes.resize(_graph.size());
	for (int i = 0; i < _graph.size(); ++i)
	{
		nodes[i] = i;
	}

	return nodes;
}

const std::vector<int>::iterator Graph::edges_begin(int node)
{
	return _graph[node].begin();
}

const std::vector<int>::iterator Graph::edges_end(int node)
{
	return _graph[node].end();
}