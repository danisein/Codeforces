#include <iostream>
#include <vector>
#include <string>
#include <map>
typedef std::pair<std::string, std::string> TeamHometownPair;
typedef std::vector<TeamHometownPair> Inputs;
typedef std::map<std::string, int> Results;
typedef std::map<std::string, int> FirstOptions;
bool GetClubNames(const Inputs &inputs, int index, int count, FirstOptions &unchosenFirsts, FirstOptions &chosenFirsts,Results &results)
{
	if (index >= count)
	{
		
		return true;
	}

	auto &value =  inputs[index];
	std::string first_opt = value.first.substr(0,3);
	std::string second_opt = value.first.substr(0,2) + value.second.substr(0,1);

	auto find_result = results.find(first_opt);
	bool first_opt_exist_in_result = results.end() != find_result;
	if (!first_opt_exist_in_result && (unchosenFirsts.find(first_opt) == unchosenFirsts.end()))
	{
		results[first_opt] = index;
		chosenFirsts[first_opt] = index;
		if (GetClubNames(inputs, index + 1, count, unchosenFirsts, chosenFirsts,results))
			return true;
		chosenFirsts.erase(chosenFirsts.find(first_opt));
		results.erase(results.find(first_opt));
	}
	find_result = results.find(second_opt);
	if ((find_result == results.end()) && chosenFirsts.find(first_opt) == chosenFirsts.end())
	{
		unchosenFirsts[first_opt] = index;
		results[second_opt] = index;
		if (GetClubNames(inputs, index + 1, count, unchosenFirsts, chosenFirsts, results))
		{
			return true;
		}

		unchosenFirsts.erase(unchosenFirsts.find(first_opt));
		results.erase(results.find(second_opt));
	}
	return false;

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

	if (GetClubNames(inputs, 0, size, unchosenFirsts, chosenFirsts,results))
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