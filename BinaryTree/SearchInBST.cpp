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
 * Returns the node with the given key, if present in BST
 */
Node* searchInBST(Node* root, int key) {
    if (!root)
        return nullptr;

    if (root->value == key)
        return root;

    if (root->value > key) {
        return searchInBST(root->lt, key);
    } else {
        return searchInBST(root->rt, key);
    }
}

int main(void) {
    Node* root1 = createTree({10, -5, 30, -10, 0, INT_MIN, 36, INT_MIN, INT_MIN, INT_MIN, 5});
    std::cout << "Searching for value: 0 -> " << (searchInBST(root1, 0) != nullptr ? "Found" : "Not Found") << std::endl;
    std::cout << "Searching for value: 36 -> " << (searchInBST(root1, 36) != nullptr ? "Found" : "Not Found") << std::endl;

    Node* root2 = createTree({10, INT_MIN, 15, INT_MIN, 16, INT_MIN, 18});
    std::cout << "Searching for value: 18 -> " << (searchInBST(root2, 18) != nullptr? "Found" : "Not Found") << std::endl;

    Node* root3 = createTree({10, -5, 25, -10, 5, INT_MIN, 36});
    std::cout << "Searching for value: 5 -> " << (searchInBST(root3, 5) != nullptr? "Found" : "Not Found") << std::endl;
    std::cout << "Searching for value: 22 -> " << (searchInBST(root3, 22) != nullptr? "Found" : "Not Found") << std::endl;

    return 0;
}
