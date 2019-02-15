#include "CampusGraph.h";
#include "CsvParser.h"
#include <iostream>
#include <queue>

//TODO: make shortcuts for acronyms
int main(void)
{
	//Example of how to parse a CSV file for graph building
	CsvStateMachine csm{ "distances.csv" };
	vector<vector<string>> data = csm.processFile();
	
	//Data is a vector of vectors. 
	//Data[0][0] will be the starting node.
	//Data[0][1] will be connected node
	//Data[0][2] will be the distance
	
	CampusGraph graph{};

	vector<string> connections(3); 
	int count = 0;

	for (auto i : data) {
		count = 0;
		for (auto x : i) {
			connections[count] = x;

			if (count < 2) {
				graph.addVertex(x);
				count++;
			}
		}
		graph.connectVertex(connections[0], connections[1], stoi(connections[2]));
	}

	/*
	graph.addVertex("a");
	graph.addVertex("b");
	graph.addVertex("c");
	graph.connectVertex("a", "b", 3, true);
	graph.connectVertex("a", "c", 15);
	graph.connectVertex("b", "c", 7, true);
	auto distances = graph.computeShortestPath("a");
	*/

	string start = "";
	string end = "";
	cout << "**HSU Transit Time Calculator**" << endl;
	cout << "Enter starting location: ";
	cin >> start;

	/*
	cout << "Enter end location: "; 
	cin >> end;
	*/

	unordered_map<string, int> distances{} = graph.computeShortestPath(start);

	cout << distances[start] ;

	
	

	return 0;
}