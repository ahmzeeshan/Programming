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
 * Returns the height of a binary tree
 */
int heightOfBinaryTree(Node* root) {
    // 1. Terminating condition if the node is null
    if (!root)
        return 0;

    // 2. Return the maximum height from amongst the left & right subtree (+1 for the current node)
    return 1 + std::max(heightOfBinaryTree(root->lt), heightOfBinaryTree(root->rt));
}

int main(void) {
    Node* root1 = createTree({10, 5, 6, INT_MIN, INT_MIN, 8, 7, INT_MIN, INT_MIN, INT_MIN, 4});
    std::cout << "The total no. of nodes in this binary tree are: " << heightOfBinaryTree(root1) << std::endl;

    Node* root2 = createTree({INT_MIN});
    std::cout << "The total no. of nodes in this binary tree are: " << heightOfBinaryTree(root2) << std::endl;

    return 0;
}
