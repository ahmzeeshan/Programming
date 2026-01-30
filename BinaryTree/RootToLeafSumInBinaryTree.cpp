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
bool rootToLeafSumInBinaryTreeImpl(Node* root, int sum, std::string& path) {
    // 1. Terminating condition if the node is null
    if (!root)
        return false;

    // 2. Update the sum
    sum -= root->value;

    // 3. If the sum is zero and this is a leaf node then return true and update the path else check the left and right subtree
    if (sum == 0 && isLeaf(root)) {
        path += std::to_string(root->value) + " ";
        return true;
    } else if (rootToLeafSumInBinaryTreeImpl(root->lt, sum, path) || rootToLeafSumInBinaryTreeImpl(root->rt, sum, path)) {
        path += std::to_string(root->value) + " ";
        return true;
    }

    return false;
}

/**
 * Checks if there exists a root to leaf path with the given sum. Returns the path if one exists else returns the empty string
 */
std::string rootToLeafSumInBinaryTree(Node* root, int sum) {
    if (!root)
        return "";

    std::string path {};
    rootToLeafSumInBinaryTreeImpl(root, sum, path);
    // TODO: Reverse the path before returning

    return path;
}

int main(void) {
    Node* root1 = createTree({10, 16, 5, INT_MIN, -3, 6, 11});
    std::cout << "The path with the root to leaf sum equal to 26 is : " << rootToLeafSumInBinaryTree(root1, 26) << std::endl;

    /* Node* root2 = createTree({INT_MIN});
    std::cout << "The total no. of nodes in this binary tree are: " << rootToLeafSumInBinaryTree(root2) << std::endl; */    

    return 0;
}
