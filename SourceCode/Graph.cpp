#include "Graph.h"

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
    }
}

void Graph::Reverse(std::map<int, std::set<int> > dependency) {
    for (std::map<int, std::set<int> >::iterator itrOut; itrOut != dependency.end(); itrOut++) {
        std::set<int> neighbors;
        for (std::map<int, std::set<int> >::iterator itrIn; itrIn != dependency.end(); itrIn++) {
            for (int i : itrIn->second) {
                if (itrOut->first == i) {
                    neighbors.insert(itrIn->first);
                }
            }
        }
        edges.insert(std::pair<int, std::set<int> > (itrOut->first, neighbors));
        neighbors.clear();
    }
}