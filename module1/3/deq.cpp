//Во всех задачах из следующего списка следует написать структуру данных, обрабатывающую команды push* и pop*.
//Формат входных данных.
//В первой строке количество команд n. n ≤ 1000000.
//Каждая команда задаётся как 2 целых числа: a b.
//a = 1 - push front
//a = 2 - pop front
//a = 3 - push back
//a = 4 - pop back
//Команды добавления элемента 1 и 3 заданы с неотрицательным параметром b.
//Для дека используются все четыре команды.
//Если дана команда pop*, то число b - ожидаемое значение.
// Если команда pop вызвана для пустой структуры данных, то ожидается “-1”.
//Формат выходных данных.
//Требуется напечатать YES - если все ожидаемые значения совпали.
//Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.
//
// 3_2. Реализовать дек с динамическим зацикленным буфером.
//Требования: Дек должен быть реализован в виде класса.


#include <iostream>
#include <cassert>

#define STARTING_BUFF_CAPACITY 3
#define ARRAY_INCREASING_COEFF 2
#define ARRAY_DECREASING_COEFF 2

typedef struct Node {
    Node() : next(nullptr), previous(nullptr), value(0) {}

    explicit Node(int value) : next(nullptr), previous(nullptr), value(value) {}

    Node(const Node &node) = default;

    Node &operator=(const Node &node) = default;

    Node(const Node &&) = delete;

    Node &operator=(const Node &&) = delete;

    ~Node() = default;

//..........................................................................
    Node *next;
    Node *previous;
    int value;
} Node;


class Deque {
public:
    Deque() : size(0), capacity(STARTING_BUFF_CAPACITY), head_index(0), tail_index(0) {
        buffer = new int *[STARTING_BUFF_CAPACITY];
    }

    Deque(const Deque &) = delete;

    Deque &operator=(const Deque &) = delete;

    Deque(const Deque &&) = delete;

    Deque &operator=(const Deque &&) = delete;

    ~Deque() {
        while (!empty()) {
            delete buffer[head_index % capacity];
            head_index++;
            size--;
        }
        delete[] buffer;
    }

//..........................................................................
    void push_front(int val) {
        int *element = new int(val);
        if (size == capacity) {
            grow();
        }
        if (empty()) {
            head_index = capacity - 1;
            buffer[head_index] = element;
            size++;
            tail_index = head_index;
            return;
        }

        if (head_index > 0) {
            head_index--;
            buffer[head_index] = element;
        } else {
            head_index = capacity - 1;
            buffer[head_index] = element;
        }

        size++;
        return;
    }

    void push_back(int val) {
        int *element = new int(val);
        if (size == capacity) {
            grow();
        }
        if (empty()) {
            tail_index = 0;
            buffer[tail_index] = element;
            size++;
            head_index = tail_index;
            return;
        }

        if (tail_index < capacity - 1) {
            tail_index++;
            buffer[tail_index] = element;
        } else {
            tail_index = 0;
            buffer[tail_index] = element;
        }
        size++;
        return;
    }

    int pop_front() {
        assert(!empty());

        int val = *buffer[head_index];
        delete buffer[head_index];
        if (head_index == capacity - 1) {
            head_index = 0;
        } else {
            head_index++;
        }
        size--;
        if (size <= capacity/2 && capacity!= 1) {
            shrink();
        }
        return val;
    }

    int pop_back() {
        assert(!empty());

        int val = *buffer[tail_index];
        delete buffer[tail_index];
        if (tail_index == 0) {
            tail_index = capacity - 1;
        } else {
            tail_index--;
        }
        size--;
        if (size <= capacity/2) {
            shrink();
        }
        return val;
    }

    bool empty() {
        return size == 0;
    }

private:
    void grow() {
        size_t new_capacity =0;
        if (capacity == 0 || capacity == 1) {
            new_capacity = STARTING_BUFF_CAPACITY;
        } else {
            new_capacity = ARRAY_INCREASING_COEFF * capacity;
        }
        int **buffer = new int *[new_capacity];
        if (size > 0) {
            size_t target = 0;

            if (head_index <= tail_index) {
                for (size_t i = head_index; i <= tail_index; i++) {
                    buffer[target] = buffer[i];
                    target++;
                }
            } else {
                for (size_t i = head_index; i < capacity; i++) {
                    buffer[target] = buffer[i];
                    target++;
                }
                for (size_t i = 0; i <= tail_index; i++) {
                    buffer[target] = buffer[i];
                    target++;
                }
            }
            head_index = 0;
            tail_index = target - 1;
        } else {
            head_index = 0;
            tail_index = 0;
        }
        capacity = new_capacity;
        delete[] buffer;
        buffer = buffer;
    }

    void shrink() {
        size_t new_capacity = capacity / ARRAY_DECREASING_COEFF;
        int **buffer = new int *[new_capacity];
        if (size > 0) {
            size_t target = 0;

            if (head_index <= tail_index) {
                for (size_t i = head_index; i <= tail_index; i++) {
                    buffer[target] = buffer[i];
                    target++;
                }
            } else {
                for (size_t i = head_index; i < capacity; i++) {
                    buffer[target] = buffer[i];
                    target++;
                }
                for (size_t i = 0; i <= tail_index; i++) {
                    buffer[target] = buffer[i];
                    target++;
                }
            }
            head_index = 0;
            tail_index = target - 1;
        } else {
            head_index = 0;
            tail_index = 0;
        }
        capacity = new_capacity;
        delete[] buffer;
        buffer = buffer;
    }

private:
    int **buffer;
    size_t size;
    size_t capacity;
    size_t head_index;
    size_t tail_index;
};
//void test2() {
//    Deque deq;
//    deq.push_back(1);
//    deq.push_back(2);
//    deq.push_back(3);
//    assert(deq.pop_front() == 1);
//    assert(deq.pop_front() == 2);
//    assert(deq.pop_front() == 3);
//    deq.push_back(1);
//    assert(deq.pop_front() == 1);
//    deq.push_back(1);
//    deq.push_back(2);
//    deq.push_back(3);
//    assert(deq.pop_back() == 3);
//    assert(deq.pop_back() == 2);
//    assert(deq.pop_back() == 1);
//}
//void test() {
//    Deque deq;
////    assert(deq.empty());
//
//    deq.push_back(1);
//    deq.push_back(2);
//    deq.push_back(3);
//    deq.push_back(4);
//    deq.push_back(5);
//    deq.push_back(6);
//    deq.push_back(7);
//    deq.push_back(8);
//    deq.push_back(9);
//    deq.push_back(10);
//    deq.push_front(1);
//    deq.push_front(2);
//    deq.push_front(3);
//    deq.push_front(4);
//    deq.push_front(5);
//    deq.push_front(6);
//    deq.push_front(7);
//    deq.push_front(8);
//    deq.push_front(9);
//    deq.push_front(10);
//    assert(deq.pop_back() == 10);
//    assert(deq.pop_back() == 9);
//    assert(deq.pop_back() == 8);
//    assert(deq.pop_back() == 7);
//    assert(deq.pop_back() == 6);
//    assert(deq.pop_back() == 5);
//    assert(deq.pop_back() == 4);
//    assert(deq.pop_back() == 3);
//    assert(deq.pop_back() == 2);
//    assert(deq.pop_back() == 1);
//    deq.push_front(20);
//    deq.push_front(30);
//    deq.push_front(40);
//    assert(deq.pop_front() == 40);
//    assert(deq.pop_front() == 30);
//
//    assert(deq.pop_back() == 1);
//    assert(deq.pop_back() == 2);
//    assert(deq.pop_back() == 3);
//    assert(deq.pop_back() == 4);
//    assert(deq.pop_back() == 5);
//    assert(deq.pop_back() == 6);
//    assert(deq.pop_back() == 7);
//    assert(deq.pop_back() == 8);
//    assert(deq.pop_back() == 9);
//    assert(deq.pop_back() == 10);
//}



void test2() {
    Deque deq;
    deq.push_back(1);
    deq.push_back(2);
    deq.push_back(3);
    assert(deq.pop_front() == 1);
    assert(deq.pop_front() == 2);
    assert(deq.pop_front() == 3);
    deq.push_back(1);
    assert(deq.pop_front() == 1);
    deq.push_back(1);
    deq.push_back(2);
    deq.push_back(3);
    assert(deq.pop_back() == 3);
    assert(deq.pop_back() == 2);
    assert(deq.pop_back() == 1);
}

void test() {
    Deque deq;

    deq.push_back(1);
    deq.push_back(2);
    deq.push_back(3);
    deq.push_back(4);
    deq.push_back(5);
    deq.push_back(6);
    deq.push_back(7);
    deq.push_back(8);
    deq.push_back(9);
    deq.push_back(10);
    assert(deq.pop_back() == 10);
    assert(deq.pop_back() == 9);
    assert(deq.pop_back() == 8);
    assert(deq.pop_back() == 7);
    assert(deq.pop_back() == 6);
    assert(deq.pop_back() == 5);
    assert(deq.pop_back() == 4);
    assert(deq.pop_back() == 3);
    assert(deq.pop_back() == 2);
    assert(deq.pop_back() == 1);
    deq.push_front(20);
    deq.push_front(30);
    deq.push_front(40);
    assert(deq.pop_front() == 40);
    assert(deq.pop_front() == 30);

}

//    void shrink() {
//        size_t new_capacity = capacity / ARRAY_DECREASING_COEFF;
//        Node **buffer = new Node *[new_capacity];
//        if (size > 0) {
//            size_t target = 0;
//
//            if (head_index <= tail_index) {
//                for (size_t i = head_index; i <= tail_index; i++) {
//                    buffer[target] = buffer[i];
//                    target++;
//                }
//            } else {
//                for (size_t i = head_index; i < capacity; i++) {
//                    buffer[target] = buffer[i];
//                    target++;
//                }
//                for (size_t i = 0; i <= tail_index; i++) {
//                    buffer[target] = buffer[i];
//                    target++;
//                }
//            }
//            head_index = 0;
//            tail_index = target - 1;
//        } else {
//            head_index = 0;
//            tail_index = 0;
//        }
//        capacity = new_capacity;
//        delete[] buffer;
//        buffer = buffer;
//    }

int main() {
//    test();
//    test2();
    int n = 0;
    Deque deque;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        int command = 0;
        int value = 0;
        int result = 0;
        std::cin >> command >> value;

        switch (command) {
            case 1:
                deque.push_front(value);
                break;
            case 2:
                if (deque.empty()) {
                    result = -1;
                } else {
                    result = deque.pop_front();
                }
                if (value != result) {
                    std::cout << "NO" << std::endl;
                    return 0;
                }
                break;
            case 3:
                deque.push_back(value);
                break;
            case 4:
                if (deque.empty()) {
                    result = -1;
                } else {
                    result = deque.pop_back();
                }
                if (value != result) {
                    std::cout << "NO" << std::endl;
                    return 0;
                }
                break;
            default:
                std::cout << "NO" << std::endl;
                return 0;

        }
    }
    std::cout << "YES" << std::endl;
    return 0;
}
