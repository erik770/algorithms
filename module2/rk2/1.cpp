#include <iostream>
#include <stack>


class BinarySearchTree {
    struct Node {
        int key;

        Node *left;
        Node *right;

        Node() : key(0), left(nullptr), right(nullptr) {}

        Node(const int &key) : key(key), left(nullptr), right(nullptr) {}
    };

public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree() {destrInternal(root);}  //  размер не сказано, и про рекурсию тоже, решил для ускорения времени так сделать

    void Add(const int &key) {
        Node **current_node = &root;
        while (*current_node != nullptr) {
            if (key < (*current_node)->key) {
                current_node = &(*current_node)->left;
            } else {
                current_node = &(*current_node)->right;
            }
        }
        *current_node = new Node(key);
    }

    bool Has(const int &key) {
        Node* current_node = root;

        while (current_node != nullptr && current_node->key == key){
            if (key < current_node->key) {
                current_node = current_node->left;
            } else {
                current_node = current_node->right;
            }
        }
        if(!current_node){ // если вышли из while по nullptr то нет элемента
            return false;
        }
        return true;
    }

    void destrInternal(Node* node){
        if(node){
            destrInternal(node->left);
            destrInternal(node->right);
            delete node;
        }
    }

    int checkIfAllSame(){
        std::stack<Node *> stack;

        Node *current_node = root;
        int pivot = root->key;
        while (current_node != nullptr || !stack.empty()){
            while (current_node != nullptr) {
                stack.push((current_node));
                current_node = (current_node)->left;
            }

            auto top_node = stack.top();
            stack.pop();

            if(top_node->key != pivot){
                return 0;
            }
            if ((top_node)->right) {
                current_node = (top_node)->right;

            }
        }
        return 1;
    }

    int shortestPath(){
        return shortestPathInternal(root);
    }

    int shortestPathInternal(Node* node){
        int counter = 0;

        if(node == nullptr){
            return 0;
        }
        int left_part = shortestPathInternal(node->left);
        int right_part = shortestPathInternal(node->right);

        if(left_part == 0){
            return 1 + right_part;
        }
        if(right_part == 0){
            return 1 + left_part;
        }

        return (1 + std::min(right_part, left_part));
    }

private:
    Node* root;
};


int main() {
    int n = 0;
    BinarySearchTree tree;

    while(std::cin >> n){
        tree.Add(n);
    };

    std::cout << tree.shortestPath();


    return 0;
}
