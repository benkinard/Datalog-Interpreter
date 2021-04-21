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
    void dfs(int rule);
    void dfsSCC(int rule);
    void dfsForest();
    void dfsForestSCC(std::stack<int> dfsOrder);
    void Print() const;
    void ReversePostorder();
private:
    std::map<int, std::set<int> > edges;
    std::map<int, bool> visited;
    std::stack<int> postorder;
    std::vector<std::set<int> > sccs;
    std::set<int> tempSCC;
};

#endif