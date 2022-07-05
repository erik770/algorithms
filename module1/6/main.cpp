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


// Описание для случая прохода от начала массива к концу:
// Выбирается опорный элемент как элемент по случайному индексу.
// Опорный элемент меняется с последним элементом массива.
// Во время работы Partition в начале массива содержатся элементы, не бо́льшие опорного.
// Затем располагаются элементы, строго бОльшие опорного.
// В конце массива лежат нерассмотренные элементы.
// Последним элементом лежит опорный.
// Итератор (индекс) i указывает на начало группы элементов, строго бо́льших опорного.
// Итератор j больше i, итератор j указывает на первый нерассмотренный элемент.
// Шаг алгоритма, пока j < a.len:
//     Рассматривается элемент, на который указывает j.
//     Если он больше опорного,
//         то сдвигаем j.
//     Если он не больше опорного,
//         то меняем a[i] и a[j] местами,
//         сдвигаем i и сдвигаем j.
// В конце работы алгоритма меняем опорный и элемент, на который указывает итератор i.

//  0123456789 <= опорного < 𝟬𝟭𝟮𝟯𝟰𝟱𝟲𝟳𝟴𝟵
//||2 8 7 1 3 5 6|4
// |2|8 7 1 3 5 6|4
//  2|𝟴|7 1 3 5 6|4
//  2|𝟴 𝟳|1 3 5 6|4
//  2 1|𝟳 𝟴|3 5 6|4
//  2 1 3|𝟴 𝟳|5 6|4
//  2 1 3|𝟴 𝟳 𝟱|6|4
//  2 1 3|𝟴 𝟳 𝟱 𝟲|4
//  2 1 3 4|𝟳 𝟱 𝟲 𝟴|

// Ввод
// 10 4
// 1 2 3 4 5 6 7 8 9 10
// Вывод
// 5

// Ввод
// 10 0
// 3 6 5 7 2 9 8 10 4 1
// Вывод
// 1

// Ввод
// 10 9
// 0 0 0 0 0 0 0 0 0 1
// Вывод
// 1

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
