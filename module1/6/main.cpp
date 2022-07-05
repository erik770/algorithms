//Дано множество целых чисел из [0..10^9] размера n.
//Используя алгоритм поиска k-ой порядковой статистики, требуется найти следующие параметры множества:
//10%  перцентиль
//медиана
//90%  перцентиль
//
//Требования: к дополнительной памяти: O(n).
//Среднее время работы: O(n)
//Должна быть отдельно выделенная функция partition.
//Рекурсия запрещена.
//Решение должно поддерживать передачу функции сравнения снаружи.
//
//6_3. Реализуйте стратегию выбора опорного элемента “случайный элемент”.
//Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.

#include <iostream>
#include <cmath>

template<class T>
struct DefaultComparator {
    bool operator()(const T&l, const T &r) const {
        return l < r;
    }
};

template<class T, class Comparator = DefaultComparator<T>>
size_t partition(T *arr, size_t left, size_t right, Comparator comp = Comparator()) {
    if (left == right - 1) {
        return left;
    }
    size_t pivot_idx = rand() % (right - 1 - left) + left;

    T pivot = arr[pivot_idx];

    size_t i = left;
    size_t j = left;

    std::swap(arr[pivot_idx], arr[right - 1]);
    while (true) {
        for (; comp(arr[i], pivot) ; ++j, ++i);
        for (; !comp(arr[j], pivot) && (j < right - 1); j++);
        if (j == right - 1) {
            break;
        }
        std::swap(arr[j], arr[i]);
    }
    std::swap(arr[right - 1], arr[i]);
    return i;
}

template<class T>
void kth_element(T *arr, size_t size, size_t k) {
    size_t left =  0;
    size_t right = size;

    while (true) {
        int middle = partition(arr, left, right);
        if (middle == k) {
            return;
        } else if (middle < k) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
}


int main() {
    int n = 0;
    std::cin >> n;

    int *arr = new int[n];
    for (size_t i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    auto ten_per = size_t(std::round(n * 0.1));
    kth_element(arr, n, ten_per);
    std::cout << arr[ten_per] << std::endl;

    auto mid_per = size_t(std::round(n * 0.5));
    kth_element(arr, n, mid_per);
    std::cout << arr[mid_per] << std::endl;


    auto nine_per = size_t(std::round(n * 0.9));
    if (n < 6) {   // не придумал ничего лучше, чтобы 90% не вылезало за массив при маленьких n
        nine_per = n - 1;
    }
    kth_element(arr, n, nine_per);
    std::cout << arr[nine_per] << std::endl;

    delete[] arr;

    return 0;
}
