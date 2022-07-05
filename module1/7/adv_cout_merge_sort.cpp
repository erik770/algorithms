//Требование для всех вариантов Задачи 5
//Во всех задачах данного раздела необходимо реализовать и использовать сортировку слиянием в виде шаблонной функции.
//Решение должно поддерживать передачу функции сравнения снаружи.
//Общее время работы алгоритма O(n log n).
//5_1. Реклама.
//В супермаркете решили оптимизировать показ рекламы. Известно расписание прихода и ухода покупателей
//(два целых числа). Каждому покупателю необходимо показать минимум 2 рекламы.  Рекламу можно транслировать
//только в целочисленные моменты времени. Покупатель может видеть рекламу от момента прихода до момента
//ухода из магазина.
//В каждый момент времени может показываться только одна реклама. Считается, что реклама показывается мгновенно.
//Если реклама показывается в момент ухода или прихода, то считается, что посетитель успел её посмотреть.
//Требуется определить минимальное число показов рекламы.

#include <iostream>

template<class T>
struct DefaultComparator {
    bool operator()(const T &l, const T &r) {
        return l < r;
    }
};

typedef struct visit {
    bool operator<(const visit &r) const {
        if (this->time.second == r.time.second) {
            return this->time.first > r.time.first;
        }
        return this->time.second < r.time.second;
    }

    std::pair<int, int> time;
} visit;

template<class T, class Comparator = DefaultComparator<T>>
void merge_arr(T *first_arr, size_t first_len,
               T *second_arr, size_t second_len,
               T *result_arr, Comparator comp = Comparator()) {

    size_t iterator1 = 0, iterator2 = 0, iterator_result = 0;

    while (iterator1 < first_len && iterator2 < second_len) {
        if (comp(first_arr[iterator1], second_arr[iterator2])) {
            result_arr[iterator_result++] = first_arr[iterator1++];
        } else {
            result_arr[iterator_result++] = second_arr[iterator2++];
        }
    }

    while (iterator1 < first_len) {
        result_arr[iterator_result++] = first_arr[iterator1++];
    }
    while (iterator2 < second_len) {
        result_arr[iterator_result++] = second_arr[iterator2++];
    }
}

template<class T, class Comparator = DefaultComparator<T>>
void merge_sort(T *arr, size_t arr_size, Comparator comp = Comparator()) {
    if (arr_size <= 1) {
        return;
    }
    size_t first_len = arr_size / 2;
    size_t second_len = arr_size - first_len;

    merge_sort(arr, first_len);
    merge_sort(arr + first_len, second_len);

    T *buffer = new T[arr_size];
    merge_arr(arr, first_len, arr + first_len, second_len, buffer, comp);
    std::copy(buffer, buffer + arr_size, arr);

    delete[] buffer;
}


int count_adv(visit *arr, size_t arr_size) {
    if (arr_size == 0) {
        return 0;
    }
    merge_sort(arr, arr_size);

    int counter = 2;

    int leave_time = arr[0].time.second;
    int pre_leave_time = leave_time - 1;

    size_t iterator = 1;

    while (iterator < arr_size) {
        if (arr[iterator].time.first > leave_time) {
            leave_time = arr[iterator].time.second;
            pre_leave_time = leave_time - 1;
            counter += 2;
            iterator++;
            continue;
        }

        if (arr[iterator].time.first == leave_time ||
            ((arr[iterator].time.first > pre_leave_time) && (arr[iterator].time.second > leave_time))) {
            pre_leave_time = leave_time;
            leave_time = arr[iterator].time.second;
            counter++;
            iterator++;
            continue;
        }
        iterator++;
    }

    return counter;
}

int main() {
    int n = 0;
    std::cin >> n;
    auto *arr = new visit[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i].time.first;
        std::cin >> arr[i].time.second;
    }

    std::cout << count_adv(arr, n);
    delete[] arr;
    return 0;
}
