#include <iostream>
#include <queue>
#include <vector>

struct Node {
    int value = 0;
    Node* lt = nullptr;
    Node* rt = nullptr;
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

    head = new Node();
    head->value = nodeValues[index++];
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
                        node->lt = new Node();
                        node->lt->value = nodeValues[index];
                        nodes.push(node->lt);
                    }
                    index++;
                }

                if (index < noOfNodes) {
                    if (nodeValues[index] != INT_MIN) {
                        node->rt = new Node();
                        node->rt->value = nodeValues[index];
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
 * Given the root of a tree, prints pre-order traversal of a binary tree
 */
void performPreOrderTraversal(Node* head) {
    if (!head)
        return;

    std::cout << head->value << " ";
    performPreOrderTraversal(head->lt);
    performPreOrderTraversal(head->rt);
}

/**
 * Given the root of a tree, prints post-order traversal of a binary tree
 */
void performPostOrderTraversal(Node* head) {
    if (!head)
        return;

    performPostOrderTraversal(head->lt);
    performPostOrderTraversal(head->rt);
    std::cout << head->value << " ";
}

/**
 * Given the root of a tree, prints in-order traversal of a binary tree
 */
void performInorderTraversal(Node* head) {
    if (!head)
        return;

    performInorderTraversal(head->lt);
    std::cout << head->value << " ";
    performInorderTraversal(head->rt);
}

int main(void) {
    // Node* root = createTree({10, 15, 30, 3, 6, INT_MIN, 2, 5, INT_MIN, INT_MIN, INT_MIN, 9, 8});
    Node* root = createTree({10, 2, 5, 6, INT_MIN, 8, 3});

    std::cout << "Pre-Order Traversal: ";
    performPreOrderTraversal(root);
    std::cout << std::endl;
    std::cout << "Post-Order Traversal: ";
    performPostOrderTraversal(root);
    std::cout << std::endl;
    std::cout << "In-Order Traversal: ";
    performInorderTraversal(root);
    std::cout << std::endl;

    return 0;    
}
