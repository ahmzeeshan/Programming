#include <iostream>
#include <queue>
#include <vector>

struct Node {
    int value = 0;
    Node* lt = nullptr;
    Node* rt = nullptr;

    Node(int v) : value(v){
    }
};

/**
 * Prints the status of the transient tree creation queue
 */
void printNode(std::queue<Node*> Q) {
    std::cout << "The current queue status is : ";
    while (!Q.empty()) {
        Node* node = Q.front();
        Q.pop();
        std::cout << node->value << " ";
    }
    std::cout << std::endl;
}

/**
 * Given a vector containing elements of a tree, creates, and returns the tree root
 */
Node* createTree(std::vector<int> nodeValues) {
    if (nodeValues.empty() || nodeValues[0] == INT_MIN)
        return nullptr;

    int index = 0, noOfNodes = nodeValues.size();
    Node* head = nullptr;

    head = new Node(nodeValues[index++]);
    std::queue<Node*> nodes;
    nodes.push(head);

    while (nodes.size()) {
        int levelNodeCount = nodes.size();
        while (levelNodeCount--) {
            Node* node = nodes.front();
            nodes.pop();
            if (node->value != INT_MIN) {
                if (index < noOfNodes) {
                    if (nodeValues[index] != INT_MIN) {
                        node->lt = new Node(nodeValues[index]);
                        nodes.push(node->lt);
                    }
                    index++;
                }

                if (index < noOfNodes) {
                    if (nodeValues[index] != INT_MIN) {
                        node->rt = new Node(nodeValues[index]);
                        nodes.push(node->rt);
                    }
                    index++;
                } 
            }
        }
        // printNode(nodes);
    }
    
    return head;
}

/**
 * Finds the lowest common ancestor in a given binary search tree
 */
Node* findLCAInBSTImpl(Node* root, int min, int max) {
    // 1. An empty tree is trivially a BST
    if (!root)
        return nullptr;

    if (root->value >= min && root->value <= max) {
        return root;
    } else if (root->value < min) {
        return findLCAInBSTImpl(root->rt, min, max);
    } else {
        return findLCAInBSTImpl(root->lt, min, max);
    }

    return nullptr;
}

int findLCAInBST(Node* root, int val1, int val2) {
    // 1. If the tree is empty then return null
    if (!root)
        return -1;

    // 2. Declare state variables
    Node* ancestor = findLCAInBSTImpl(root, std::min(val1, val2), std::max(val1, val2));
    return ancestor == nullptr ? -1 : ancestor->value;
}

int main(void) {
    Node* root1 = createTree({10, -10, 30, INT_MIN, 8, 25, 60, 6, 9, INT_MIN, 28, INT_MIN, 78});
    std::cout << "Lowest common ancestor of nodes {28, 78} is " << findLCAInBST(root1, 28, 78) << std::endl;
    std::cout << "Lowest common ancestor of nodes {6, 30} is " << findLCAInBST(root1, 6, 30) << std::endl;
    std::cout << "Lowest common ancestor of nodes {30, 78} is " << findLCAInBST(root1, 30, 78) << std::endl;
    std::cout << "Lowest common ancestor of nodes {6, 9} is " << findLCAInBST(root1, 6, 9) << std::endl;

    return 0;
}
