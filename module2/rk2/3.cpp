// сделал на основе свое домашки по хеш таблице надеюсь, не запрещено :)))

#include <iostream>
#include <vector>
#include <string>

#define  INCREASING_COEFF 2
#define DEFAULT_INIT_CAPACITY 8
#define HASH_PRIME_NUMBER 73
#define REHASH_COEF 0.75

enum STATES {
    EMPTY = 0, FULL, DELETED
};

struct Node {
    std::string product_name;
    int color;
    int size;

    bool operator==(const Node& rhs) const{
        if(this->product_name == rhs.product_name &&
           this->color == rhs.color &&
           this->size == rhs.size){
            return true;
        }
        return false;
    }
};


size_t str_hash(const std::string &data) {
    size_t hash = 0;
    for (size_t i = 0; data[i] != '\0'; i++) {
        hash += (HASH_PRIME_NUMBER * hash + data[i]);
    }
    return hash;
}

template<class T>
struct Hasher {
    size_t operator()(const T &key) const {
        return rand();
    }
};

template<>
struct Hasher<Node> {
    size_t operator()(const Node &key) const {
        return str_hash(key.product_name);
    }
};

template<class T>
struct DefaulEqual {
    bool operator()(const T &l, const T &r) const {
        return l == r;
    }
};


template<class Key, class Equal = DefaulEqual<Key>, class Hash = Hasher<Key>>
class HashSet {
public:
    struct Elem {
        Elem() : state(EMPTY) {};

        ~Elem() {};

        void set_elem(const Key &key) {
            this->key = key;
            state = FULL;
        }

        Key key;
        int state;
    };


    HashSet(size_t initial_capacity = DEFAULT_INIT_CAPACITY,
            Hash hash = Hash(),
            Equal equal = Equal()) : buckets(initial_capacity, Elem()), capacity(initial_capacity), items_count(0) {};

    ~HashSet() {};

    HashSet(const HashSet &) = delete;

    HashSet &operator=(const HashSet &) = delete;

    bool add(const Key &key) {
        if ((float) items_count / capacity >= REHASH_COEF) {
            grow();
        }

        size_t hash_idx = hash(key) % capacity;
        size_t i = 0;
        int first_deleted_idx = -1;
        while (buckets[hash_idx].state != EMPTY && i < capacity) {
            if (buckets[hash_idx].key == key && buckets[hash_idx].state != DELETED) {
                return false;
            }
            if (buckets[hash_idx].state == DELETED && first_deleted_idx == -1) {
                first_deleted_idx = hash_idx;
            }
            i++;
            hash_idx = quadr_next(hash_idx, i);
        }

        if (first_deleted_idx == -1) {
            buckets[hash_idx].set_elem(key);
        } else {
            buckets[first_deleted_idx].set_elem(key);
        }
        items_count++;
        return true;
    }

    bool has(const Key &key) const {
        size_t hash_idx = hash(key) % capacity;
        size_t i = 0;
        while (buckets[hash_idx].state != EMPTY && i < capacity) {
            if (equal(buckets[hash_idx].key, key) && buckets[hash_idx].state == FULL) {
                return true;
            }
            i++;
            hash_idx = quadr_next(hash_idx, i);
        }
        return false;
    }

    bool del(const Key &key) {
        size_t hash_idx = hash(key) % capacity;
        size_t i = 0;
        while (buckets[hash_idx].state != EMPTY && i < capacity) {
            if (equal(buckets[hash_idx].key, key) && buckets[hash_idx].state == FULL) {
                buckets[hash_idx].state = DELETED;
                items_count--;
                return true;
            }
            i++;
            hash_idx = quadr_next(hash_idx, i);
        }
        return false;
    }


private:
    void grow() {
        capacity = buckets.size() * INCREASING_COEFF;
        std::vector<Elem> new_buckets(capacity, Elem());
        for (size_t i = 0; i < buckets.size(); i++) {
            if (buckets[i].state == FULL) {
                size_t hash_idx = hash(buckets[i].key) % capacity;
                size_t j = 0;
                while (new_buckets[hash_idx].state != EMPTY && j < capacity) {
                    j++;
                    hash_idx = quadr_next(hash_idx, j);
                }
                new_buckets[hash_idx].set_elem(buckets[i].key);
            }
        }
        buckets = new_buckets;
    };

    size_t quadr_next(size_t hash, size_t i) const {
        return (hash + (i * (i + 1)) / 2) % capacity;
    }

    std::vector<Elem> buckets;

    Hash hash;
    Equal equal;

    size_t capacity;
    size_t items_count;
};




int main() {
    HashSet<Node> set;

    Node key;

    char operation = '\0';
    std::string str;
    int color;
    int size;
    while (std::cin >> operation >> str >> color >> size) {
        bool res = false;
        key.product_name = str;
        key.color = color;
        key.size = size;
        switch (operation) {
            case '+':
                res = set.add(key);
                break;
            case '?':
                res = set.has(key);
                break;
            case '-':
                res = set.del(key);
                break;
            default:
                break;
        }
        if (res) {
            std::cout << "OK" << std::endl;
        } else {
            std::cout << "FAIL" << std::endl;
        }
    }
    return 0;
}
