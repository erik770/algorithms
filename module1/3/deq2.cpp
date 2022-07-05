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
#include <cstring>

#define STARTING_BUFF_CAPACITY 3
#define ARRAY_INCREASING_COEFF 2


class Deque {
public:
    Deque() : size(0), capacity(STARTING_BUFF_CAPACITY), head_index(0), tail_index(0) {
        buffer = new int[STARTING_BUFF_CAPACITY];
    }

    ~Deque() {
        delete[] buffer;
    }

    Deque(const Deque &) = delete;

    Deque &operator=(const Deque &) = delete;

    Deque(const Deque &&) = delete;

    Deque &operator=(const Deque &&) = delete;



//..........................................................................
    void push_front(const int val) {
       if(size == capacity){
           grow();
       }
       head_index = ((head_index - 1) + capacity) % capacity;

       buffer[head_index] = val;
       size++;
       return;
    }

    void push_back(const int val) {
        if(size == capacity){
            grow();
        }
        buffer[tail_index] = val;
        tail_index = (tail_index + 1) % capacity;

        size++;
        return;
    }

    int pop_front() {
        assert(!empty());

        int val = buffer[head_index];

        if (head_index == capacity - 1) {
            head_index = 0;
        } else {
            head_index++;
        }

        size--;
        return val;
    }

    int pop_back() {
        assert(!empty());

        if (tail_index == 0) {
            tail_index = capacity - 1;
        } else {
            tail_index--;
        }

        int val = buffer[tail_index];
        size--;
        return val;
    }

    const bool empty() const {
        return size == 0;
    }

private:
    void grow() {
        size_t new_capacity = ARRAY_INCREASING_COEFF * capacity;
        int *tmp_buffer = new int[new_capacity];

        memcpy(tmp_buffer, buffer + head_index, (capacity - head_index) * sizeof(int));

        if (head_index != 0) {
            memcpy(tmp_buffer + (capacity - head_index), buffer, tail_index * sizeof(int));
        }

        delete[] buffer;

        buffer = tmp_buffer;
        head_index = 0;
        tail_index = capacity;
        capacity = new_capacity;
    }

private:
    int *buffer;
    size_t size;
    size_t capacity;
    size_t head_index;
    size_t tail_index;
};

int main() {
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
