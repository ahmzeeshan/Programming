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
Node* findLCAInBinaryTree(Node* root, int val1, int val2) {

    // 1. An empty tree is trivially a BST
    if (!root)
        return nullptr;

    if (root->value == val1 || root->value == val2) {
        return root;
    }

    Node* left = findLCAInBinaryTree(root->lt, val1, val2);
    Node* right = findLCAInBinaryTree(root->rt, val1, val2);

    return left && right ? root : (left ? left : right);
}

int main(void) {
    Node* root1 = createTree({3, 6, 8, 2, 11, INT_MIN, 13, INT_MIN, INT_MIN, 9, 5, 7});
    std::cout << "Lowest common ancestor of nodes {2, 5} is " << findLCAInBinaryTree(root1, 2, 5)->value << std::endl;
    std::cout << "Lowest common ancestor of nodes {8, 11} is " << findLCAInBinaryTree(root1, 8, 11)->value << std::endl;
    std::cout << "Lowest common ancestor of nodes {8, 7} is " << findLCAInBinaryTree(root1, 8, 7)->value << std::endl;
    std::cout << "Lowest common ancestor of nodes {9, 5} is " << findLCAInBinaryTree(root1, 9, 5)->value << std::endl;

    return 0;
}
