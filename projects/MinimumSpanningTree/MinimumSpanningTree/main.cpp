#include "CityGraph.h";
#include "CsvParser.h"
#include <iostream>

int main(void)
{
	//Example of how to parse a CSV file for graph building
	
	string map, destination;

	cout << "***Route Planner***" << endl;
	cout << "Enter maps file: ";
	cin >> map;

	cout << endl << "Enter destinations file: ";
	cin >> destination;

	// Parse the map csv file
	CsvStateMachine csm{ map };
	vector<vector<string>> data = csm.processFile();
	// Parse the deliveries csv file
	CsvStateMachine deliveries_csm{ destination };
	vector<vector<string>> deliveries_data = deliveries_csm.processFile();

	CityGraph graph{};

	vector<string> connections(3);
	int count = 0;

	// creates the original graph
	for (auto i : data) {
		count = 0;
		for (auto x : i) {
			connections[count] = x;

			if (count < 2) {
				graph.addVertex(x);
				count++;
			}
		}
		graph.connectVertex(connections[0], connections[1], stoi(connections[2]), true);
	}

	// create reduced graph
	CityGraph reducedGraph;
	string new_source = "";
	reducedGraph = reducedGraph.createReducedGraph(graph, reducedGraph, deliveries_data, new_source);

	// creates new mst graph
	auto mst = reducedGraph.computeMinimumSpanningTree(new_source);

	// calculates the weight of the delivery path
	int weight = 0;
	for (auto nodes : mst) {
		weight += nodes.weight;
	}

	cout << "\nMinutes: " << weight << endl;

	// outputs path taken for the deliveries
	int count_4 = 0;
	for (auto nodes : mst) {
		if (count_4 == 0) {
			cout << nodes.sink->getKey() << "->" << nodes.source->getKey() << endl;
			count_4++;
		}
		else
		cout << nodes.source->getKey() << "->" << nodes.sink->getKey() << endl;
	}
	
	return 0;
}