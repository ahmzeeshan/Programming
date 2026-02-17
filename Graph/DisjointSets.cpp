/**
 * Program to perform three operations on disjoint sets:
 *      - makeSet
 *      - findSet
 *      - mergeSet
 * 
 * This algorithm uses union-by-rank & path compression
 */

#include <iostream>
#include <vector>
#include <unordered_map>

/**
 * Structure to maintain information about each set
 */
struct NODE {
    int data;
    unsigned int rank;
    NODE* parent;
};

/**
 * Prints the current node status
 */
void printNodeStatus(const std::unordered_map<int, NODE*>& vertexNodeMap) {
    for (const auto& e : vertexNodeMap) {
        NODE* n = e.second;
        std::cout << "\t{ data, rank, NODE* } : { " << n->data << ", " << n->rank << ", " << n->parent << " }" << std::endl;
    }
}

/**
 * Creates and returns a NODE* represnting a set for each element passed to it
 */
NODE* makeSet(int data) {
    NODE* n = new NODE();
    n->data = data;
    n->rank = 0;
    n->parent = n;

    return n;
}

/**
 * Finds the parent node for the give vertex - performing path compression in the process
 */
NODE* findParent(NODE* n) {
    if (n->parent == n)
        return n;

    n->parent = findParent(n->parent);
    return n->parent;
}

/**
 * Merges two nodes together
 */
void mergeSet(NODE* v1, NODE* v2) {
    if (v1 == nullptr || v2 == nullptr)
        return;

    NODE* p1 = findParent(v1);
    NODE* p2 = findParent(v2);

    if (p1 != p2) {
        if (p1->rank >= p2->rank) {
            p1->rank = p1->rank == p2->rank ? p1->rank + 1 : p1->rank;
            p2->rank = 0;
            p2->parent = p1;
        } else {
            p1->rank = 0;
            p1->parent = p2;
        }
    }
}

int main(void) {
    // Describe the graph
    int noOfNodes = 7;
    std::vector<std::vector<int>> edges = { {1, 2}, {2, 3}, {4, 5}, {6, 7}, {5, 6}, {3, 7}};

    // Make set for each node
    std::unordered_map<int, NODE*> vertexNodeMap;
    for (int i = 1; i < noOfNodes + 1; i++) {
        vertexNodeMap[i] = makeSet(i);
    }

    // Print the node status before processing
    std::cout << "Status pre merge: " << std::endl;
    printNodeStatus(vertexNodeMap);


    // Merge nodes that have an edge between them
    for (const auto& e : edges) {
        NODE* v1 = vertexNodeMap[e[0]];
        NODE* v2 = vertexNodeMap[e[1]];
        mergeSet(v1, v2);
    }

    // Print the details post merge operation
    std::cout << "Status post merge: " << std::endl;
    printNodeStatus(vertexNodeMap);

    return 0;
}


