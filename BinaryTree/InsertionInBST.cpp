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
 * Prints the given tree
 */
void printTree(Node* head) {
    std::cout << "Level order traversal of tree is:" << std::endl;
    std::queue<Node*> levelQueue;
    levelQueue.push(head);

    while (levelQueue.size()) {
        std::cout << "\t";
        int noOfNodes = levelQueue.size();
        while (noOfNodes--) {
            Node* node = levelQueue.front();
            levelQueue.pop();
            if (node == nullptr) {
                std::cout << INT_MIN << " ";
            } else {
                std::cout << node->value << " ";
                levelQueue.push(node->lt);
                levelQueue.push(node->rt);
            }
        }
        std::cout << std::endl;
    }
}

/**
 * Returns the node with the given key, if present in BST
 */
void InsertInBST(Node** root, int key) {
    Node* newNode = new Node(key);
    if (*root == nullptr) {
        *root = newNode;
        return;
    }

    Node *prevHead = nullptr, *head = *root;
    while (head) {
        prevHead = head;
        if (head->value >= key) {
            head = head->lt;
        } else {
            head = head->rt;
        }
    }

    if (prevHead->value >= key) {
        prevHead->lt = newNode;
    } else {
        prevHead->rt = newNode;
    }
}

int main(void) {
    Node* root1 = createTree({10, -5, 16, -8, 7, INT_MIN, 18});
    InsertInBST(&root1, 6);
    printTree(root1);
    InsertInBST(&root1, 17);
    printTree(root1);

    Node* root2 = createTree({10, INT_MIN, 15, INT_MIN, 16, INT_MIN, 18});
    InsertInBST(&root2, 19);
    printTree(root2);

    Node* root3 = nullptr;
    InsertInBST(&root3, 101);
    printTree(root3);

    return 0;
}
