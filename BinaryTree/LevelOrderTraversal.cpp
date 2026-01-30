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
 * Checks if the binary tree rooted at root is BST
 */
void performLevelOrderTraversal(Node* root) {
    // 1. An empty tree is trivially a BST
    if (!root)
        return;

    // 2. Declare state variables and initialize them
    std::queue<Node*> Q {};
    Q.push(root);

    while (!Q.empty()) {
        int noOfNodes = Q.size();
        while (noOfNodes--) {
            Node* node = Q.front();
            Q.pop();
            std::cout << node->value << " ";

            if (node->lt) {
                Q.push(node->lt);
            }
            if (node->rt) {
                Q.push(node->rt);
            }
        }
        std::cout << std::endl;
    }
    return;
}

int main(void) {
    Node* root1 = createTree({10, 9, -10, 11, INT_MIN, 16, 21, INT_MIN, 15, 18, INT_MIN, INT_MIN, 19});
    std::cout << "Level order traversal of tree is: " << std::endl;
    performLevelOrderTraversal(root1);

    Node* root2 = createTree({10, 21, 19, INT_MIN, 15, -6, 0, 18, INT_MIN, INT_MIN, 17, INT_MIN, 12});
    std::cout << "Level order traversal of tree is: " << std::endl;
    performLevelOrderTraversal(root2);

    return 0;
}
