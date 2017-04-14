#include <iostream>
#include <vector>
#include <set>

typedef std::vector<std::vector<int>> Graph;

void dsf(const Graph &graph, int node, bool *visited, std::vector<int> &result)
{
	result.push_back(node);
	visited[node] = true;
	for (auto &sub:graph[node])
	{
		if (!visited[sub])
		{
			dsf(graph, sub, visited, result);
			result.push_back(node);
		}
	}
}

int main()
{
	int n,m,k;
	std::cin>>n>>m>>k;
	Graph graph(n + 1);
	for (int i = 0; i < m; i++)
	{
		int left, right;
		std::cin>>left>>right;
		graph[left].push_back(right);
		graph[right].push_back(left);
	}


	bool *visited = new bool[n + 1];
	for (int i = 0; i < n + 1; i++)
		visited[i] = false;

	std::vector<int> result;
	dsf(graph, 1, visited, result);

	int size = result.size() / k;
	int left = result.size() % k;
	if (left > 0)
		size++;

	int total = result.size();
	int index = 0;
	if (result.size() != (2 * n - 1))
		std::cout<<result.size();
	for (int i = 0; i < k; i++)
	{
		int count = size;
		if (i == (k - 1))
			count = total - size * (k - 1);
		std::cout<<count<<" ";
		for (int i = 0; i < count; i++)
		{
			std::cout<<result[index++]<<" ";
		}
		std::cout<<std::endl;
	}

	return 0;
}