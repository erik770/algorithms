// тут я опять из домашки своей)))

#include <iostream>

template<class T>
struct DefaultComparator {
    int operator()(const T &left, const T &right) const {
        if (left < right) {
            return -1;
        } else if (left > right) {
            return 1;
        }
        return 0;

    }
};


template<class Key, class Comparator = DefaultComparator<Key>>
class AVLTree {
    struct Node {
        Node(const Key &key) : key(key), left(nullptr), right(nullptr), num_of_el(1), height(1) {}


        Key key;
        Node *left;
        Node *right;
        size_t num_of_el;
        int8_t height;
    };

public:
    AVLTree(Comparator comp = Comparator()) : root(nullptr), comp(comp) {}

    AVLTree(const AVLTree& other) = delete;
    AVLTree& operator=(const AVLTree& other) = delete;
    AVLTree(AVLTree&& other) = delete;
    AVLTree& operator=(AVLTree&& other) = delete;


    ~AVLTree() {
        destrInternal(root);
    }

    size_t insert(const Key &key) {
        size_t position = 0;
        root = insertInternal(key, root, position);
        return position;
    }


    bool has(const Key &key) const {
        return hasInternal(key, root);
    }

    void erase(size_t position) {
        root = eraseInternal(position + 1, root);
    }

private:
    Node *root;
    Comparator comp;

private:
    bool hasInternal(const Key &key, Node *node) const {
        if (!node) {
            return false;
        }

        int cmp_res = comp(key, node->key);
        if (cmp_res == 0) {
            return true;
        }
        if (cmp_res == -1) {
            return hasInternal(key, node->left);
        } else {
            return hasInternal(key, node->right);
        }

    }

    Node *insertInternal(const Key &key, Node *node, size_t &position) {
        if (!node) {
            return new Node(key);
        }

        if (comp(key, node->key) == -1) {
            position += get_num_of_el(node->right) + 1;
            node->left = insertInternal(key, node->left, position);
        } else {
            node->right = insertInternal(key, node->right, position);
        }
        return balance(node);
    }

    Node *eraseInternal(size_t position, Node *node) {
        if (!node || position > get_num_of_el(node)) {
            return nullptr;
        }

        if (comp(position, get_num_of_el(node->right) + 1) == -1) {
            node->right = eraseInternal(position, node->right);
        } else if (comp(position, get_num_of_el(node->right) + 1) == 1) {
            node->left = eraseInternal(position - get_num_of_el(node->right) - 1, node->left);

        } else {
            Node *left = node->left;
            Node *right = node->right;
            delete node;

            if (!right) {
                return left;
            }

            Node *min = findMin(right);
            min->right = removeMin(right);
            min->left = left;


            return balance(min);
        }
        return balance(node);
    }

    void destrInternal(Node* node){
        if(node){
            destrInternal(node->left);
            destrInternal(node->right);
            delete node;
        }
    }

    Node *findMin(Node *node) {
        while (node->left) {
            node = node->left;
        }

        return node;
    }

    Node *removeMin(Node *node) {
        if (!node->left) {
            return node->right;
        }
        node->left = removeMin(node->left);
        return balance(node);
    }

    Node *balance(Node *node) {
        fix_height_and_num_of_el(node);

        switch (bfactor(node)) {
            case 2: {
                if (bfactor(node->right) < 0) {
                    node->right = rotate_right(node->right);
                }
                return rotate_left(node);
            }
            case -2: {
                if (bfactor(node->left) < 0) {
                    node->left = rotate_left(node->left);
                }
                return rotate_right(node);
            }
            default:
                return node;
        }
    }

    Node *rotate_left(Node *node) {
        Node *tmp = node->right;
        node->right = tmp->left;
        tmp->left = node;
        fix_height_and_num_of_el(node);
        fix_height_and_num_of_el(tmp);
        return tmp;
    }

    Node *rotate_right(Node *node) {
        Node *tmp = node->left;
        node->left = tmp->right;
        tmp->right = node;
        fix_height_and_num_of_el(node);
        fix_height_and_num_of_el(tmp);
        return tmp;
    }

    int8_t get_height(Node *node) {
        if (node) {
            return node->height;
        } else {
            return 0;
        }
    }

    size_t get_num_of_el(Node *node) {
        if (node) {
            return node->num_of_el;
        } else {
            return 0;
        }
    }

    void fix_height_and_num_of_el(Node *node) {
        if (!node) {
            return;
        }
        node->height = std::max(get_height(node->right), get_height(node->left)) + 1;
        node->num_of_el = get_num_of_el(node->right) + get_num_of_el(node->left) + 1;
    };

    int8_t bfactor(Node *node) {
        return get_height(node->right) - get_height(node->left);
    }
};

int main() {
    AVLTree<int> tree;

    std::string operation;
    int key;
    while (std::cin >> operation >> key) {
        if(operation == "insert") {
            tree.insert(key);
        }
        if(operation == "exists") {
            if(tree.has(key)){
                std::cout << "true";
            } else {
                std::cout << "false";
            }
        }
        if(operation == "delete") {
            tree.erase(key);
        }
        if(operation == "next") {

        }
        if(operation == "prev") {

        }

    }
    return 0;
}
