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
 * Checks if two trees with roots root1 & root2 are equal
 */
bool sameBinaryTree(Node* root1, Node* root2) {
    // 1. If both nodes are null, then the tree rooted at this node is equal trivially
    if (!root1 && !root2)
        return true;

    // 2. If root1 or root2 are null, then the tree rooted at this node are not equal
    if (!root1 || !root2)
        return false;

    // 3. Else check the given node and the left & right subtree
    return (root1->value == root2->value)
        && (sameBinaryTree(root1->lt, root2->lt))
        && (sameBinaryTree(root1->rt, root2->rt)); 
}

int main(void) {
    Node* root11 = createTree({10, 12, 13, INT_MIN, INT_MIN, 15, 14, INT_MIN, 16});
    Node* root12 = createTree({10, 12, 13, INT_MIN, INT_MIN, 15, 14, INT_MIN, 16});
    std::cout << "The tree with roots root11 & root12 are " << (sameBinaryTree(root11, root12) ? "equal." : "not equal.") << std::endl;

    Node* root21 = createTree({11, 15, 18, INT_MIN, INT_MIN, 21});
    Node* root22 = createTree({11, 15, 18});
    std::cout << "The tree with roots root21 & root22 are " << (sameBinaryTree(root21, root22) ? "equal." : "not equal.") << std::endl;

    Node* root31 = createTree({11, 12, 15});
    Node* root32 = createTree({11, 12, 16});
    std::cout << "The tree with roots root31 & root32 are " << (sameBinaryTree(root31, root32) ? "equal." : "not equal.") << std::endl;

    return 0;
}
