#include <iostream>
#include <vector>
#include <set>
#define min(a, b) (a) >= (b)? (b) : (a)
typedef std::vector<std::vector<int>> Graph;

void dfs(const Graph &graph, int node, bool *visited, std::vector<int> &result)
{
	result.push_back(node);
	visited[node] = true;
	for (auto &sub:graph[node])
	{
		if (!visited[sub])
		{
			dfs(graph, sub, visited, result);
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
	dfs(graph, 1, visited, result);

	int size = result.size() / k;
	int left = result.size() % k;

	int total = result.size();
	int index = 0;
	for (int i = 0; i < k; i++)
	{
		int count = size;
		if (left > 0)
		{
			count++;
			left--;
		}
		std::cout<<count<<" ";
		for (int i = 0; i < count; i++)
		{
			std::cout<<result[index++]<<" ";
		}
		std::cout<<std::endl;
	}

	return 0;
}