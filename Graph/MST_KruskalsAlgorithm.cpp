#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <vector>


struct NODE {
    char data;
    int rank;
    NODE* parent;
};

NODE* makeSet(char data) {
    NODE* n = new NODE();
    n->data = data;
    n->rank = 0;
    n->parent = n;

    return n;
}

NODE* findSet(NODE* n) {
    if (n->parent == n)
        return n;

    n->parent = findSet(n->parent);
    return n->parent;
}

bool mergeSet(NODE* v1, NODE* v2) {
    NODE* p1 = findSet(v1);
    NODE* p2 = findSet(v2);

    if (p1 == p2)
        return false;

    if (p1->rank >= p2->rank) {
        p1->rank += (p1->rank == p2->rank);
        p2->rank = 0;
        p2->parent = p1;
    } else {
        p1->rank = 0;
        p1->parent = p2;
    }

    return true;
}

int main(void)
{
    int noOfNodes = 6;
    std::vector<std::vector<int> > edges = { {'A', 'B', 3}, {'A', 'D', 1}, {'B', 'C', 1}, {'B', 'D', 3}, {'C', 'D', 1}, {'C', 'E', 5}, {'C', 'F', 4}, {'D', 'E', 6}, {'E', 'F', 2} };
    std::sort(edges.begin(), edges.end(), [](const std::vector<int>& e1, const std::vector<int>& e2) {
        return e1[2] < e2[2];
    });

    std::unordered_map<char, NODE*> vertexNodeMap;
    for (int i = 0; i < noOfNodes; i++) {
        vertexNodeMap['A' + i] = makeSet('A' + i);
    }

    std::cout << "Minimum spanning tree for the given graph is: " << std::endl;
    for (const auto& e : edges) {
        if (mergeSet(vertexNodeMap[e[0]], vertexNodeMap[e[1]])) {
            std::cout << "\t{ " << e[0] << ", " << e[1] << " } : " << e[2] << std::endl;
        }
    }

    return 0;
}