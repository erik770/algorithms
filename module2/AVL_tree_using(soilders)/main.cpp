//Требование для всех вариантов Задачи 4
//Решение должно поддерживать передачу функции сравнения снаружи.
//
//4_1. Солдаты. В одной военной части решили построить в одну шеренгу по росту. Т.к. часть была далеко не образцовая,
//то солдаты часто приходили не вовремя, а то их и вовсе приходилось выгонять из шеренги за плохо начищенные сапоги.
//Однако солдаты в процессе прихода и ухода должны были всегда быть выстроены по росту – сначала самые высокие, а в
//конце – самые низкие. За расстановку солдат отвечал прапорщик, который заметил интересную особенность – все солдаты
//в части разного роста. Ваша задача состоит в том, чтобы помочь прапорщику правильно расставлять солдат, а именно для
//каждого приходящего солдата указывать, перед каким солдатом в строе он должен становится.
//Требования: скорость выполнения команды - O(log n).
//Формат входных данных.
//Первая строка содержит число N – количество команд (1 ≤ N ≤ 30 000). В каждой следующей строке содержится описание
//команды: число 1 и X если солдат приходит в строй (X – рост солдата, натуральное число до 100 000 включительно) и
//число 2 и Y если солдата, стоящим в строе на месте Y надо удалить из строя. Солдаты в строе нумеруются с нуля.
//Формат выходных данных.
//На каждую команду 1 (добавление в строй) вы должны выводить число K – номер позиции, на которую должен встать этот
//солдат (все стоящие за ним двигаются назад).

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

    size_t insert(const Key &key) {  // тут я решил поменять интерфейс немного для решения задачи, теперь insert возвращает позицию солдата
        size_t position = 0;         // может и было бы правильней решение вынести в отдельную функцию, но я подумал
        root = insertInternal(key, root, position);  // что это еще доп код городить и сделал все в инсерте, думаю не критично
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

    int n = 0;
    int op = 0;
    int key = 0;


    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> op >> key;
        switch (op) {
            case 1 : {
                std::cout << tree.insert(key) << std::endl;
                break;
            }
            case 2 : {
                tree.erase(key);
                break;
            }
            default:
                break;
        }

    }
    return 0;
}

//7
//1 100
//1 120
//1 70
//1 40
//1 80
//1 75
//2 4