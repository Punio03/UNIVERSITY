//
// Created by Jakub Malczak on 31/10/2023.
//
#include <iostream>
#include <unordered_map>
#include <forward_list>
#include <queue>
#include <set>
using namespace std;

using Edge = pair<string,double>;
using AdjList = unordered_map<string,forward_list<Edge>>;

struct compare {
    bool operator()(const pair<Edge,string>& a, const pair<Edge,string>& b) {
        return a.first.second > b.first.second;
    }
};

class Graph {
    AdjList adj_list;
public:
    [[nodiscard]] AdjList get_adj_list() const { return adj_list; }

    void add_vertex(const string& id) {
        if (!id.empty() && adj_list.find(id) == adj_list.end()) {
            adj_list[id] = forward_list<Edge>();
        }
    }

    void add_edge(const string& from, const string& to, double weight) {
        if (!from.empty() && !to.empty()) {
            adj_list[from].emplace_front(to,weight);
            adj_list[to].emplace_front(from,weight);
        }
    }

    void remove_vertex(const string& id) {
        adj_list.erase(id);
        for (auto& [_,edges] : adj_list) {
            edges.remove_if([&id](const Edge& e) {
                return id == e.first;
            });
        }
    }

    void remove_edge(const string& from, const string& to) {
        adj_list[from].remove_if([&to](const Edge& e) {
            return to == e.first;
        });

        adj_list[to].remove_if([&from](const Edge& e) {
            return from == e.first;
        });
    }

    void change_edge_weight(const string& from, const string& to, double new_weight) {
        for (auto& [id,weight] : adj_list[from]) {
            if (to == id) {
                weight = new_weight;
                break;
            }
        }

        for (auto& [id,weight] : adj_list[to]) {
            if (from == id) {
                weight = new_weight;
                break;
            }
        }
    }

    Graph primMST(const string& start) {
        priority_queue<pair<Edge,string>,vector<pair<Edge,string>>,compare> pq;
        set<string> visited;
        Graph mst;

        mst.add_vertex(start);
        visited.insert(start);
        for (Edge& e : adj_list[start]) {
            pq.emplace(e,start);
        }

        while (!pq.empty()) {
            auto [edge,from] = pq.top();
            auto [to,weight] = edge;
            pq.pop();

            if (visited.find(to) == visited.end()) {
                visited.insert(to);
                mst.add_vertex(to);
                mst.add_edge(from,to,weight);

                for (const auto& next_edge : adj_list[to]) {
                    if (visited.find(next_edge.first) == visited.end()) {
                        pq.emplace(next_edge,to);
                    }
                }
            }
        }

        return mst;
    }

    friend ostream& operator<<(ostream& os, const Graph& g) {
        for (const auto& [key,edges] : g.get_adj_list()) {
            os << key << ": ";
            for (const auto& [to,weight] : edges) {
                os << "(" << to << ", " << weight << ") ";
            }
            os << "\n";
        }
        return os;
    }
};

int main() {
    Graph g;
    g.add_vertex("A");
    g.add_vertex("B");
    g.add_vertex("C");
    g.add_vertex("D");
    g.add_vertex("E");

    g.add_edge("A", "B", 4);
    g.add_edge("A", "C", 1);
    g.add_edge("B", "C", 2);
    g.add_edge("B", "D", 5);
    g.add_edge("C", "D", 8);
    g.add_edge("C", "E", 10);
    g.add_edge("D", "E", 2);

    cout << "Oryginalny graf:\n" << g << endl;

    Graph mst = g.primMST("A");
    cout << "Minimalne drzewo rozpinające (MST):\n" << mst << endl;
}

