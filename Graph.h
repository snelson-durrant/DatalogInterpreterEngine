#ifndef GRAPH_H
#define GRAPH_H
#include "DatalogProgram.h"
#include "Rule.h"
#include <map>
#include <set>

class Graph
{

public:
    std::vector<bool> visit_list;
    std::map<int, std::set<int>> adj_list;
    std::map<int, std::set<int>> rev_list;
    std::vector<int> postorder;
    std::vector<int> order;
    std::vector<std::vector<int>> scc;
    Graph() = default;

    std::vector<std::vector<int>> get_scc() {
        dfs_back_forest();
        dfs_forward_forest();
        return scc;
    }

    void add_nodes(DatalogProgram* data) {
        std::cout << "Dependency Graph" << std::endl;
        for (unsigned int i = 0; i < data->get_rules().size(); i++) {
            std::set<int> edges;
            std::cout << "R" << i << ":";
            bool first = true;
            for (unsigned int p = 0; p < data->get_rules()[i]->bodyPredicates.size(); p++) {
                for (unsigned int j = 0; j < data->get_rules().size(); j++) {
                    if (data->get_rules()[j]->headPredicate->get_id() == data->get_rules()[i]->bodyPredicates[p]->get_id()) {
                        if (!first) {
                            std::cout << ",";
                        }
                        first = false;
                        std::cout << "R" << j;

                        // deals with the reverse tree
                        auto it = rev_list.find(j);
                        if (it != rev_list.end()) {
                            it->second.insert(i);
                        } else {
                            std::set<int> rev_edges;
                            rev_edges.insert(i);
                            rev_list.insert({j, rev_edges});
                        }

                        edges.insert(j);
                    }
                }
            }
            adj_list.insert({i, edges});
            visit_list.push_back(false);
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    void dfs(int node, std::map<int,std::set<int>> list) {
        visit_list[node] = true;
        auto it = list.find(node);
        if (it != list.end()) {
            for (auto n : it->second) {
                // access elements
                if(!visit_list[n]) {
                    dfs(n, list);
                }
            }
        }
        postorder.push_back(node);
    };

    void dfs_back_forest() {
        for (unsigned int i = 0; i < visit_list.size(); i++) {
            if (!visit_list[i]) {
                dfs(i, rev_list);
            }
        }
    }

    void dfs_forward_forest() {
        order = postorder;
        visit_list.clear();
        for (unsigned int i = 0; i < postorder.size(); i++) {
            visit_list.push_back(false);
        }
        postorder.clear();
        for (unsigned int i = order.size() - 1; i > 0; i--) {
            if (!visit_list[i]) {
                dfs(order[i], adj_list);
                scc.push_back(postorder);
                postorder.clear();
            }
        }
    }

};

#endif // GRAPH_H