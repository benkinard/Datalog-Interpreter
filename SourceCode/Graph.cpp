#include "Graph.h"
#include <iostream>

Graph::Graph() {}

void Graph::Build(std::vector<Rule*> rules) {
    // Loop through Rules
    for (unsigned int i = 0; i < rules.size(); i++) {
        // Create set to store the rules that are "adjacent" to the current rule
        std::set<int> adjacent;
        // Loop through Rules to check if body predicates contain head predicates
        for (unsigned int j = 0; j < rules.size(); j++) {
            // Loop through the body predicates of the current (ith) rule
            for (unsigned int k = 0; k < rules.at(i)->predicates.size(); k++) {
                if (rules.at(i)->predicates.at(k)->id == rules.at(j)->headPredicate->id) {
                    adjacent.insert(j);
                }
            }
        }
        edges.insert(std::pair<int, std::set<int> > (i, adjacent));
        adjacent.clear();
        visited.insert(std::pair<int, bool> (i, false));
    }
}

void Graph::Reverse(std::map<int, std::set<int> > dependency) {
    for (std::map<int, std::set<int> >::iterator itrOut = dependency.begin(); itrOut != dependency.end(); itrOut++) {
        std::set<int> neighbors;
        for (std::map<int, std::set<int> >::iterator itrIn = dependency.begin(); itrIn != dependency.end(); itrIn++) {
            if (!(itrIn->second.empty())) {
                for (int i : itrIn->second) {
                    if (itrOut->first == i) {
                        neighbors.insert(itrIn->first);
                    }
                }
            }
        }
        edges.insert(std::pair<int, std::set<int> > (itrOut->first, neighbors));
        neighbors.clear();
        visited.insert(std::pair<int, bool> (itrOut->first, false));
    }
}

void Graph::dfs(int rule) {
    // Mark this rule as being visited
    std::map<int, bool>::iterator vst;
    vst = visited.find(rule);
    vst->second = true;

    // Loop through adjacent rules
    std::map<int, std::set<int> >::iterator edg;
    edg = edges.find(rule);
    if (!(edg->second.empty())) {
        for (int i : edg->second) {
            vst = visited.find(i);
            // If this edge has not been visited then run DFS on it
            if (vst->second == false) {
                dfs(i);
            }
        }
    }
    postorder.push(rule);
}

void Graph::dfsSCC(int rule) {
    // Mark this rule as being visited
    visited.at(rule) = true;
    
    // Loop through the adjacent rules
    if (!(edges.at(rule).empty())) {
        for (int i : edges.at(rule)) {
            // If this edge has not been visited then run DFS on it
            if (!visited.at(i)) {
                dfsSCC(i);
            }
        }
    }
    tempSCC.insert(rule);
}

void Graph::dfsForest() {
    for (auto map : edges) {
        if (visited.at(map.first) == false) {
            dfs(map.first);
        }
    }
}

void Graph::dfsForestSCC(std::stack<int> dfsOrder) {
    postorder = dfsOrder;
    while (!postorder.empty()) {
        if (visited.at(postorder.top()) == false) {
            dfsSCC(postorder.top());
            sccs.push_back(tempSCC);
            tempSCC.clear();
        }
        postorder.pop();
    }
}

void Graph::Print() const {
    for (auto map : edges) {
        std::cout << "R" << map.first << ":";
        if (!(map.second.empty())) {
            for (int i : map.second) {
                std::cout << " R" << i;
            }
        }
        std::cout << std::endl;
    }
}

void Graph::ReversePostorder() {
    while (!postorder.empty()) {
        std::cout << "R" << postorder.top() << " ";
        postorder.pop();
    }
}