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
 * Checks whether a given node is a leaf node
 */
bool isLeaf(Node* node) {
    return !node->lt && !node->rt;
}

/**
 * Returns the height of a binary tree
 */
bool checkIfBinaryTreeIsBSTImpl(Node* root, int leftLimit, int rightLimit) {
    // 1. Terminating condition if the node is null
    if (!root)
        return true;

    // 2. Check to see if the node's value is within the min & max range
    return (root->value >= leftLimit && root->value <= rightLimit)
        && checkIfBinaryTreeIsBSTImpl(root->lt, leftLimit, root->value)
        && checkIfBinaryTreeIsBSTImpl(root->rt, root->value, rightLimit);
}

/**
 * Checks if the binary tree rooted at root is BST
 */
bool checkIfBinaryTreeIsBST(Node* root) {
    // 1. An empty tree is trivially a BST
    if (!root)
        return true;

    // 2. Check and return whether the tree is BST
    return checkIfBinaryTreeIsBSTImpl(root, INT_MIN, INT_MAX);
}

int main(void) {
    Node* root1 = createTree({10, 0, 25, -1, 21, 16, 32});
    std::cout << "The given binary tree is " << (checkIfBinaryTreeIsBST(root1) ? "" : "not ") << "a BST." << std::endl;

    Node* root2 = createTree({10, -10, 19, -20, 0, 17});
    std::cout << "The given binary tree is " << (checkIfBinaryTreeIsBST(root2) ? "" : "not ") << "a BST." << std::endl;

    Node* root3 = createTree({10, 10, 19, -5, INT_MIN, 17, 21});
    std::cout << "The given binary tree is " << (checkIfBinaryTreeIsBST(root3) ? "" : "not ") << "a BST." << std::endl;

    return 0;
}
