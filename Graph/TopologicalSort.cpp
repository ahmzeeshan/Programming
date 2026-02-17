#include <iostream>
#include <vector>
#include <list>

enum STATUS {
    WHITE = 0,
    BLACK = 1,
};

std::list<int>* createGraph(int noOfNodes) {
    std::list<int>* graph = new std::list<int> [noOfNodes];
    return graph;
}

void addEdge(std::list<int>* graph, int u, int v) {
    graph[u].push_back(v);
}

void performTopologicalSortImpl(const std::list<int>* &graph, const int u, std::vector<STATUS>& nodeStatus, std::string& topoSort) {
    // 1. Check if this node is already visited
    if (nodeStatus[u] == BLACK)
        return;

    // 2. Mark the node as visited
    nodeStatus[u] = BLACK;

    // 3. Traverse each edge from this node
    for (const int& v : graph[u]) {
        performTopologicalSortImpl(graph, v, nodeStatus, topoSort);
    }

    topoSort +=  " " + std::to_string(u);
}

std::string performTopologicalSort(const std::list<int>* graph, int noOfNodes) {
    if (noOfNodes == 0)
        return "";
    
    std::vector<STATUS> nodeStatus(noOfNodes, WHITE);
    std::string topoSort {};

    for (int u = 0; u < noOfNodes; u++) {
        performTopologicalSortImpl(graph, u, nodeStatus, topoSort);
    }

    std::reverse(topoSort.begin(), topoSort.end());
    return topoSort;
}

int main(void) {
    // 1. Create a graph from the given edges
    int noOfNodes {8};
    std::vector<std::vector<int>> edges {{0, 2}, {1, 2}, {1, 3}, {2, 4}, {3, 5}, {4, 5}, {4, 7}, {5, 6}};
    std::list<int>* graph = createGraph(noOfNodes);
    for (const auto& e : edges) {
        addEdge(graph, e[0], e[1]);
    }

    // 2. Call the function to perform a topological sort of the given graph
    std::cout << "Topological sort of the given graph: " << performTopologicalSort(graph, noOfNodes) << std::endl;

    return 0;
}