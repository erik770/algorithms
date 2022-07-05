//Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией.
//Хранимые строки непустые и состоят из строчных латинских букв.
//Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
//Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае,
// когда коэффициент заполнения таблицы достигает 3/4.
//Структура данных должна поддерживать операции добавления строки в множество,
// удаления строки из множества и проверки принадлежности данной строки множеству.

//1_1. Для разрешения коллизий используйте квадратичное пробирование. i-ая проба
//g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.

/*Формат ввода
 * Каждая строка входных данных задает одну операцию над множеством.
 * Запись операции состоит из типа операции и следующей за ним через пробел строки, над которой проводится операция.
 * Тип операции – один из трех символов:
 *     + означает добавление данной строки в множество;
 *     - означает удаление строки из множества;
 *     ? означает проверку принадлежности данной строки множеству.
 * При добавлении элемента в множество НЕ ГАРАНТИРУЕТСЯ, что он отсутствует в этом множестве.
 * При удалении элемента из множества НЕ ГАРАНТИРУЕТСЯ, что он присутствует в этом множестве.
 *
 * Формат вывода
 * Программа должна вывести для каждой операции одну из двух строк OK или FAIL, в зависимости от того,
 * встречается ли данное слово в нашем множестве.
 * Пример
 * Ввод
+ hello
+ bye
? bye
+ bye
- bye
? bye
? hello
 * Вывод
OK
OK
OK
FAIL
OK
FAIL
OK
*/


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
        return key;
    }
};

template<>
struct Hasher<std::string> {
    size_t operator()(const std::string &key) const {
        return str_hash(key);
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

    // алгоритм добавления
    // если надо - увеличиваем размер
    // заводим последовательность для поиска
    // и проходим по индексам, которые возвращает последовательность
    // если мы обратились, и валидный указатель и строки совпадают
    //     то возвращаем false
    // если мы обратились и удалено
    //     запоминаем это место
    //     идём дальше
    // если мы обратились и там пусто
    //     если было удалённое значение
    //         то записываем в него
    //     иначе записываем в найденное пустое
    // если вышли за пределы возвращаем false
    //     (такого быть не должно)
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

    // алгоритм:
    // получаем последовательность, по которой идём
    // если натыкаемся на не равную строку, идём вперёд
    //                 на удалённое значение идём вперёд
    //                 на конец, возвращаем  false
    //                 на равную строку, возвращаем true
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

    // получаем последовательность значений
    // ищем для каждого, пока не встретим пустое значение
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
    HashSet<std::string> set;

    std::string key;
    char operation = '\0';
    while (std::cin >> operation >> key) {
        bool res = false;
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
