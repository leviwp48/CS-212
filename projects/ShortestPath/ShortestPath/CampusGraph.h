#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include "StringGraphNode.h"
#include <unordered_map>
#include <string>
#include <queue>
using namespace std;

// Creating a class PairComparer. 
// Has a constructor that takes in the pair of a StringGraphNode pointer and an int as "first" , and again as "second"
// It will return true or false for the comparison of first's int > second's int
class PairComparer
{
public:
   bool operator()(pair<StringGraphNode*, int> first, pair<StringGraphNode*, int> second)
   {
      return first.second > second.second;
   }
};

// Class CampusGraph
// Has a private variable _graph that is the hashmap of <string, StringGraphNode*>
// Has public function addVertex by key or by Node

class CampusGraph
{
private:
	unordered_map<string, StringGraphNode*> _graph;

public:
	vector<string> visited;

	void addVertex(const string& key)
	{
		if (_graph[key] == NULL) {
			_graph[key] = new StringGraphNode(key);
		}
	}

	void addVertex(StringGraphNode* node)
	{
		_graph[node->getKey()] = node;
	}

	void connectVertex(
		const string& source,
		const string& sink,
		const int& weight,
		bool is_bidirectional = false)
	{
		_graph[source]->addEdge(_graph[sink], weight);
		if (is_bidirectional == true)
		{
			connectVertex(sink, source, weight, false);
		}
	}

	/*
	void setVisited(const string& s)
	{
		visited.push(s);
	}
	*/
	string getVisited()
	{
		
	}

	bool isVisitedEmpty() {
		bool isEmpty = visited.empty();
		return isEmpty;
	}

	//TODO: Need to implement a hash map to 

	unordered_map<string, int> computeShortestPath(const string& start, const string& destination)
	{
		//return value
		unordered_map<string, int> distances{};
		//counts distance from start

		visited.clear();
		int edgeCount = 0;
		//make sure we received a valid starting point
		if (_graph.find(start) != _graph.end())
		{
			//define PQ
			priority_queue < pair<StringGraphNode*, int>,
				vector<pair<StringGraphNode*, int>>,
				PairComparer> to_visit{};

			//prime PQ with starting location
			to_visit.push(make_pair(_graph[start], 0));

			while (to_visit.empty() == false)
			{

				auto top = to_visit.top();
				string key = top.first->getKey();
				

				int weight = top.second;
				to_visit.pop();
				
				//edgeCount--;

				//if (edgeCount == 0) {

				//}
				
				//have we seen top before?
				//This is cool. distances.find(key) will look through itself for the first occurence of 
				//itself. if it's the last one to be saved, we are good. 
				//checks if the current root is in the distances map.
				//
				if (distances.find(key) == distances.end() && distances.find(destination) == distances.end())
				{
		
					//mark as visited
					//marks the current root as visited so we don't look at it as a root again
					distances[key] = weight;
					visited.push_back(key);

					//push all unknown outoing edges into PQ
					//push all of the current roots edges into the PQ
					for (auto edge : top.first->getEdges())
					{

						//node is one of the edges we are currently looking through
						//If we are at the root A then we would be looking at it's edges for B and C
						StringGraphNode* node = dynamic_cast<StringGraphNode*>(edge.first);
						//edgeCount++;
						//looks if the edge is in the distances map. someties it may be and we may need to update for the 
						//shorter path. 
						if (key == start && node->getKey() == destination) {
							visited.clear();
							visited.push_back(start);
							visited.push_back(destination);
							distances[node->getKey()] = edge.second;
							break;
						}
						else if (distances.find(node->getKey()) == distances.end())
						{
							to_visit.push(make_pair(node, weight + edge.second));
						}
						//so if the edge is in the map then we need to see if our current weight is shorter than whats in the map
						else if (distances[node->getKey()] + edge.second < distances[key])
						{
							distances[key] = distances[node->getKey()] + edge.second;
							to_visit.push(make_pair(node, distances[key]));
						}
						
						/*
						if (distances.count(node->getKey()) > 0) {
							if (distances[node->getKey()] > edge.second) {
								distances[node->getKey] = edge.second;
							}
							
						}
						*/
						
					}
				}
			}
		}
		return distances;
	}
};

#endif // !GRAPH_H
