#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
typedef std::pair<std::string, std::string> TeamHometownPair;
typedef std::vector<TeamHometownPair> Inputs;
typedef std::map<std::string, int> Results;
typedef std::map<std::string, int> FirstOptions;
typedef std::map<std::string, std::set<int>> GroupItems;
std::string GetFirstOption(const TeamHometownPair &pair)
{
	return pair.first.substr(0, 3);
}

std::string GetSecondOption(const TeamHometownPair &pair)
{
	return pair.first.substr(0, 2) + pair.second.substr(0, 1);
}
bool GetClubNames(const Inputs &raw, Results &results)
{
	int size = raw.size();
	GroupItems items;
	for (int i = 0; i < size; i++)
	{
		std::string first_opt = GetFirstOption(raw[i]);
		auto itr = items.find(first_opt);
		if (itr != items.end())
			itr->second.insert(i);
		else
		{
			items[first_opt] = std::set<int>({i});
		}
	}
	auto itr = items.begin();
	std::set<int> alone_items;
	for (; itr != items.end(); ++itr)
	{
		auto &index_set = itr->second;

		auto index_itr = index_set.begin();
		if (index_set.size() <= 1)
		{
			alone_items.insert(*index_itr);
			continue;
		}
		for (; index_itr != index_set.end(); ++index_itr)
		{
			std::string second_opt = GetSecondOption(raw[*index_itr]);
			if (results.find(second_opt) != results.end())
				return false;
			results[second_opt] = *index_itr;
		}
	}//end for

	while (!alone_items.empty())
	{
		auto copy = alone_items;
		alone_items.clear();
		auto copy_itr = copy.begin();

		for (; copy_itr != copy.end(); ++copy_itr)
		{
			int index = *copy_itr;
			std::string first_opt = GetFirstOption(raw[index]);
			if (results.find(first_opt) == results.end())
			{
				alone_items.insert(index);
			}
			else
			{
				std::string second_opt = GetSecondOption(raw[index]);
				if (results.find(second_opt) != results.end())
					return false;
				results[second_opt] = index;
			}
		}//end for

		if (alone_items.size() == copy.size())
			break;
	}//end while
	auto alone_itr = alone_items.begin();
	for (; alone_itr != alone_items.end(); ++alone_itr)
	{
		std::string first_opt = GetFirstOption(raw[*alone_itr]);
		results[first_opt] = *alone_itr;
	}
	return true;
}
int main()
{
	Inputs inputs;
	Results results;
	FirstOptions unchosenFirsts;
	FirstOptions chosenFirsts;
	int size = 0;
	std::cin>>size;
	char team[25];
	char hometown[25];
	for (int i = 0; i < size; i++)
	{
		std::cin>>team;
		std::cin>>hometown;
		inputs.push_back(std::make_pair(std::string(team), std::string(hometown)));
	}


	if (GetClubNames(inputs, results))
	{
		std::cout<<"YES"<<std::endl;
		std::vector<std::string> sorted_result(size);
		auto itr = results.begin();
		for (; itr != results.end(); ++itr)
		{
			sorted_result[itr->second] = itr->first;
		}
		for (int i = 0; i < size; i++)
			std::cout<<sorted_result[i]<<std::endl;
	}
	else
	{
		std::cout<<"NO"<<std::endl;
	}


	return 0;
}