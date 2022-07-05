//4.1 Слияние массивов.
//Напишите программу, которая использует кучу для слияния K отсортированных массивов суммарной длиной N.
//Требования: время работы O(N * logK). Ограничение на размер кучи O(K)..
//Формат входных данных: Сначала вводится количество массивов K. Затем по очереди размер каждого массива и элементы массива. Каждый массив упорядочен по возрастанию.
//Формат выходных данных: Итоговый отсортированный массив.

#include <iostream>
#include <cstring>

#define STARTING_BUFF_CAPACITY 3
#define ARRAY_INCREASING_COEFF 2

template<class T>
struct DefaultComparator {
    bool operator()(const T &l, const T &r) {
        return l < r;
    }
};

typedef struct arr_represent {
    bool operator<(const arr_represent &r) const {
        return this->arr[this->idx_max] < r.arr[r.idx_max];
    }

    int *arr;
    size_t idx_max;
    size_t arr_size;
} arr_represent;


template<class T, class Comparator = DefaultComparator<T>>
class Heap {
public:
    explicit Heap(Comparator comp = Comparator()) {
        size = 0;
        capacity = STARTING_BUFF_CAPACITY;
        buffer = new T[STARTING_BUFF_CAPACITY];
    };

    Heap(const T *arr, size_t size_arg, Comparator comp = Comparator()) : size(size_arg), capacity(2 * size_arg) {
        buffer = new T[capacity];
        for (size_t i = 0; i < size_arg; ++i) {
            buffer[i] = arr[i];    // тут можно поспорить, но я подумал что будет неправильно
        }                          // портить массив который нам дают на вход

        heapify();
    };

    ~Heap() {
        delete[] buffer;
    };


    void pop();

    void push(const T &val);

    const T &top() const;


    Heap(const Heap &) = delete;

    Heap(Heap &&) = delete;

    Heap &operator=(const Heap &) = delete;

    Heap &operator=(Heap &&) = delete;

    bool empty() const;

    size_t get_size() const;


private:
    void heapify();

    void sift_up(size_t idx);

    void sift_down(size_t idx);

    void resize();

    Comparator comp;

    T *buffer;
    size_t size;
    size_t capacity;
};

template<class T, class Comparator>
size_t Heap<T, Comparator>::get_size() const {
    return size;
}

template<class T, class Comparator>
bool Heap<T, Comparator>::empty() const {
    return size == 0;
}

template<class T, class Comparator>
void Heap<T, Comparator>::sift_up(size_t idx) {
    while (idx > 0) {
        size_t parent = 0;
        if (idx > 1) {
            parent = (idx - 1) / 2;
        }

        if (comp(buffer[parent], buffer[idx])) {
            return;
        }
        std::swap(buffer[idx], buffer[parent]);
        idx = parent;
    }
}

template<class T, class Comparator>
void Heap<T, Comparator>::sift_down(size_t idx) {
    if (empty())
        return;

    while (2 * idx + 1 <= size - 1) {
        size_t idx_min = idx;
        if (comp(buffer[2 * idx + 1], buffer[idx_min])) {
            idx_min = 2 * idx + 1;
        }
        if (((2 * idx) + 2 <= size - 1) && comp(buffer[(2 * idx) + 2], buffer[idx_min])) {
            idx_min = (2 * idx) + 2;
        }
        if (idx == idx_min) {
            break;
        }
        std::swap(buffer[idx], buffer[idx_min]);
        idx = idx_min;
    }
}

template<class T, class Comparator>
void Heap<T, Comparator>::push(const T &val) {
    if (size == capacity) {
        resize();
    }
    buffer[size] = val;
    size++;
    sift_up(size - 1);
}

template<class T, class Comparator>
const T &Heap<T, Comparator>::top() const {
    return buffer[0];
}

template<class T, class Comparator>
void Heap<T, Comparator>::pop() {
    if (size) {
        buffer[0] = buffer[size - 1];
        size--;
        sift_down(0);
    }
}

template<class T, class Comparator>
void Heap<T, Comparator>::heapify() {
    size_t start_idx = ((size - 1) - 1) / 2;
    if (start_idx >= 0 && size > 1) {
        for (size_t i = start_idx; i > 0; i--) {
            sift_down(i);
        }
        sift_down(0);
    }
}

template<class T, class Comparator>
void Heap<T, Comparator>::resize() {
    capacity *= ARRAY_INCREASING_COEFF;
    T *newData = new T[capacity];
    std::copy(buffer, buffer + size - 1, newData);
    delete[] buffer;
    buffer = newData;
}


//..........................................................................

auto heap_merge_sort(Heap<arr_represent> *heap, size_t size_of_array) {
    auto output_array = new int[size_of_array];
    for (size_t i = 0; i < size_of_array; ++i) {
        arr_represent tmp = heap->top();
        heap->pop();

        output_array[i] = tmp.arr[tmp.idx_max];

        tmp.idx_max++;
        if (tmp.idx_max < tmp.arr_size) {
            heap->push(tmp);
        } else {
            delete[] tmp.arr;
        }
    }
    return output_array;
}

int main() {

    size_t numb_of_arrays = 0;
    std::cin >> numb_of_arrays;
    size_t total_amount_of_elem = 0;

    if (numb_of_arrays == 0) {
        return 0;
    }
    if (numb_of_arrays == 1) {
        std::cin >> total_amount_of_elem;
        for (size_t i = 0; i < total_amount_of_elem; i++) {
            int tmp = 0;
            std::cin >> tmp;
            std::cout << tmp << ' ';
        }
        return 0;
    }

    auto *array_of_arrays = new arr_represent[numb_of_arrays];
    for (size_t k = 0; k < numb_of_arrays; ++k) {
        size_t amount_of_elem_in_arr = 0;
        std::cin >> amount_of_elem_in_arr;
        if (amount_of_elem_in_arr == 0) {
            continue;
        }
        total_amount_of_elem += amount_of_elem_in_arr;
        auto *array = new arr_represent;
        array->arr = new int[amount_of_elem_in_arr];
        for (size_t j = 0; j < amount_of_elem_in_arr; j++) {
            std::cin >> array->arr[j];
        }
        array->idx_max = 0;
        array->arr_size = amount_of_elem_in_arr;
        array_of_arrays[k] = *array;
        delete array;
    }
    Heap heap(array_of_arrays, numb_of_arrays);


    auto result_sorted_arr = heap_merge_sort(&heap, total_amount_of_elem);
    for (size_t i = 0; i < total_amount_of_elem; i++) {
        std::cout << result_sorted_arr[i] << ' ';
    }

    delete[] result_sorted_arr;

    delete[] array_of_arrays;

    return 0;
}