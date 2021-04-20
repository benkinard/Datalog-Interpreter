#ifndef GRAPH_H
#define GRAPH_H
#include <stack>
#include <map>
#include <set>
#include <vector>
#include "Rule.h"

class Graph {
    friend class Interpreter;
public:
    Graph();
    void Build(std::vector<Rule*> rules);
    void Reverse(std::map<int, std::set<int> > dependency);
    std::stack<int> dfs();
    // Tree dfs();
    std::stack<int> dfsForest();
    // Forest dfsForest();
private:
    std::map<int, std::set<int> > edges;
    std::map<int, bool> visited;
    std::stack postorder;
}

#endif