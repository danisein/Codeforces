#include <iostream>
#include <vector>
#include <set>
struct Node
{
	int color;
	std::vector<int> link_nodes;
};

void print(Node *nodes, int size)
{
	for (int i = 1; i <= size; i++)
	{
		std::cout<<i<<std::endl;
		std::cout<<"\t"<<"color:"<<nodes[i].color;
		std::cout<<"\t"<<"link_nodes:";
		for (int node :nodes[i].link_nodes)
		{
			std::cout<<node<<" ";
		}
		std::cout<<std::endl;
	}
}
bool check_same_color(Node *node, int root, int parent)
{
	Node &root_node = node[root];
	for (auto child:root_node.link_nodes)
	{
		if (child == parent)
			continue;
		Node &child_node = node[child];
		if (child_node.color != root_node.color)
			return false;
		if (!check_same_color(node, child, root))
			return false;
	}
	return true;
}

bool checksubtree(Node *node, int root, int color_size)
{
	Node &root_node = node[root];
	if (root_node.link_nodes.size() < color_size - 1)
		return false;
	bool pass = true;
	for (auto child:root_node.link_nodes)
	{
		if (!check_same_color(node, child, root))
		{
			pass = false;
			break;
		}
	}
	return pass;
}

bool find_diff_color(Node *node, int root, int parent, std::pair<int, int> &diff)
{
	Node &root_node = node[root];
	for (auto child:root_node.link_nodes)
	{
		if (child == parent)
			continue;
		Node &child_node = node[child];
		if (child_node.color != root_node.color)
		{
			diff.first = root;
			diff.second = child;
			return true;
		}
		if (find_diff_color(node, child, root, diff))
			return true;
	}

	diff.first = 0;
	diff.second = 0;
	return false;
}
int main()
{
	int n;
	std::cin>>n;
	Node *nodes = new Node[n+1];
	std::set<int> color_set;
	for (int i = 0; i < n - 1; i++)
	{
		int left = 0;
		int right = 0;
		std::cin>>left>>right;
		nodes[left].link_nodes.push_back(right);
		nodes[right].link_nodes.push_back(left);
	}
	for (int i = 1; i <= n; i++)
	{
	 	int color = 0;
	 	std::cin>>color;
	 	color_set.insert(color);
	 	nodes[i].color = color;
	}
	// print(nodes, n);
	int root = 0;
	std::pair<int, int> diff;
	int color_size = color_set.size();
	if (find_diff_color(nodes, 1, 0, diff))
	{
		if (checksubtree(nodes, diff.first, color_size))
			root = diff.first;
		else if (checksubtree(nodes, diff.second, color_size))
			root = diff.second;
		if (root == 0)
			std::cout<<"NO"<<std::endl;
		else
		{
			std::cout<<"YES"<<std::endl;
			std::cout<<root<<std::endl;
		}
	}
	else
	{
		std::cout<<"YES"<<std::endl;
		std::cout<<"1"<<std::endl;
	}
	delete []nodes;
	return 0;
}