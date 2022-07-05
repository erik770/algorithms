#include <iostream>
#include <stack>
#include <vector>
#include <queue>

template<class T>
struct DefaultComparator {
    bool operator()(const T &left, const T &right) const {
        return left < right;
    }
};

template<class T>
struct DefaulEqual {
    bool operator()(const T &l, const T &r) const {
        return l == r;
    }
};


template<class Key, class Comparator = DefaultComparator<Key>, class Equal = DefaulEqual<Key>>
class BinarySearchTree {
    struct Node {
        Key key;

        Node *left;
        Node *right;

        Node() : key(0), left(nullptr), right(nullptr) {}

        Node(const Key &key) : key(key), left(nullptr), right(nullptr) {}
    };

public:
    BinarySearchTree(Comparator comp = Comparator(), Equal equal = Equal()) : root(nullptr), comp(comp), equal(equal) {}

    ~BinarySearchTree() {
        if(!root){
            return;
        }

        std::queue<Node*> delete_q;
        delete_q.push(root);

        while(!delete_q.empty()){
            Node* current_node = delete_q.front();
            delete_q.pop();

            if(current_node->left){
                delete_q.push(current_node->left);
            }
            if(current_node->right){
                delete_q.push(current_node->right);
            }
            delete current_node;
        }
    }

    void Add(const Key &key) {
        Node **current_node = &root;
        while (*current_node != nullptr) {
            if (comp(key, (*current_node)->key)) {
                current_node = &(*current_node)->left;
            } else {
                current_node = &(*current_node)->right;
            }
        }
        *current_node = new Node(key);
    }

    bool Has(const Key &key) {
        Node* current_node = root;

        while (current_node != nullptr && !equal(current_node->key, key)){
            if (comp(key, current_node->key)) {
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

    void Delete(const Key &key) {
        if(equal(root->key, key)){
            delete root;
            root = nullptr;
        }

        Node** current_node = &root;
        while (*current_node != nullptr) {
            if (comp(key, (*current_node)->key)) {  // если элемент меньше то налево
                current_node = &(*current_node)->left;
            } else {
                if(equal((*current_node)->key, key)){  // иначе либо нашли
                    break;
                }
                current_node = &(*current_node)->right;  // либо направо
            }
        }

        if(!*current_node){  //если не нашли элемент такой
            return;
        }

        Node* new_node = nullptr;
        if((*current_node)->left && (*current_node)->right){  // если есть обе ветки
            Node** min_from_right = &(*current_node)->right;
            while ((*min_from_right)->left) {           // ищем имнимальный элемент справа, чтобы им заменить удаляемый
                min_from_right = &(*min_from_right)->left;
            }
            new_node = *min_from_right;

            *min_from_right = (*min_from_right)->right;  // на место минимума справа цепляем его правую ветку(если есть)
            new_node->right = (*current_node)->right;  //подцепляем старые указатели к новой ноде
            new_node->left = (*current_node)->left;
            delete *current_node;
            *current_node = new_node;
            return;
        }

        if((*current_node)->left){
            new_node = (*current_node)->left;
        } else{
            new_node = (*current_node)->right;
        }
        delete *current_node;
        *current_node = new_node;
   }


    std::vector<Key> make_vect_in_order() {
        std::stack<Node *> stack;
        std::vector<Key> vector;

        Node *current_node = root;
        while (current_node != nullptr || !stack.empty()) {
            while (current_node != nullptr) {
                stack.push((current_node));
                current_node = (current_node)->left;
            }

            auto top_node = stack.top();
            stack.pop();

            vector.push_back(top_node->key);
            if ((top_node)->right) {
                current_node = (top_node)->right;

            }
        }
        return vector;
    };

private:
    Node *root;
    Comparator comp;
    Equal equal;

};



int main() {
    BinarySearchTree<int> bst;

    size_t n = 0;
    int curr = 0;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> curr;
        bst.Add(curr);
    }
    std::vector<int> result_vect = bst.make_vect_in_order();
    for (int i = 0; i < n; ++i) {
        std::cout << result_vect[i] << " ";
    }

//    проверка метода Has, работает :)
//    for(int j = 0; j < 13; j++) {
//        if (bst.Has(j)) {
//            std::cout << std::endl << "has";
//        } else {
//            std::cout << std::endl << "has not";
//        }
//    }

//    проверка метода Delete, работает :)
//    for(int j = 5; j < 9; j++) {
//        bst.Delete(j);
//    }
//    std::vector<int> result_vect_after_delete = bst.make_in_order_vect();
//    for (int i = 0; i < n - 4; ++i) {
//        std::cout << result_vect_after_delete[i] << " ";
//    }
    return 0;
}
