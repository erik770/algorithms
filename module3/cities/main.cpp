// https://habr.com/post/119158/
// https://neerc.ifmo.ru/wiki/index.php?title=Эвристики_для_поиска_кратчайших_путей
// https://neerc.ifmo.ru/wiki/index.php?title=Алгоритм_Дейкстры
/*
Города
1 секунда, 20Mb
Требуется отыскать самый выгодный маршрут между городами.
Из города может выходить дорога, которая возвращается в этот же город.(Граф с петлями).
Все указанные дороги двусторонние.(Граф неориентированный.)
Между любыми двумя городами может быть больше одной дороги.(Кратные рёбра.)
Требуемое время работы O((N + M)log N), где
    N – количество городов, N ≤ 10000,
    M – известных дорог между ними, M ≤ 250000.
Длина каждой дороги ≤ 10000.
Формат ввода
Первая строка содержит число N – количество городов.
Вторая строка содержит число M - количество дорог.
Каждая следующая строка содержит описание дороги (откуда, куда, время в пути).
Последняя строка содержит маршрут (откуда и куда нужно доехать).
Формат вывода
Вывести длину самого выгодного маршрута.
in
6
9
0 3 1
0 4 2
1 2 7
1 3 2
1 4 3
1 5 3
2 5 3
3 4 4
3 5 6
0 2
out
9
in
5
6
0 1 3
0 2 2
0 3 1
1 4 3
2 4 2
3 4 1
0 4
out
2
*/

#include <iostream>

#include <set>
#include <vector>
#include <limits>

class ListGraph {
public:
    ListGraph(int vertices_count) {
        vertices.resize(vertices_count);
    }

    ~ListGraph() {

    }

    void AddEdge(int from, int to, int weight) {
        vertices[from].emplace_back(weight, to);
        vertices[to].emplace_back(weight, from);
    }

    int VerticesCount() const {
        return vertices.size();
    }

    std::vector<std::pair<int, int>> GetNextVertices(int vertex) const {
        return vertices[vertex];
    }

    std::vector<std::pair<int, int>> GetPrevVertices(int vertex) const {
        std::vector<std::pair<int, int>> result;

        for (const auto &parent: vertices) {
            for (const auto &child: parent) {
                if (child.second == vertex) {
                    result.push_back(child);
                    break;
                }
            }
        }

        return result;
    }

    int ShortestPath(int from, int to) {
        std::vector<int> shortest_path(this->VerticesCount(), std::numeric_limits<int>::max());
        std::vector<int> prev_vert_int_path(this->VerticesCount(), 0);


        std::set<int> queue;
        queue.insert(from);
        shortest_path[from] = 0;

        while (!queue.empty()) {
            int currentVertex = *queue.begin();
            queue.erase(queue.begin());

            for (std::pair<int, int> nextVertex: this->GetNextVertices(currentVertex)) {

                if (shortest_path[currentVertex] + nextVertex.first < shortest_path[nextVertex.second]) {
                    queue.erase(nextVertex.second);
                    shortest_path[nextVertex.second] = shortest_path[currentVertex] + nextVertex.first;
                    queue.insert(nextVertex.second);
                }
            }
        }
        return shortest_path[to];
    }

private:
    std::vector<std::vector<std::pair<int,int>>> vertices;
};


int main() {
    int v = 0;
    std::cin >> v;
    ListGraph graph(v);

    int n = 0;
    std::cin >> n;
    int from = 0, to = 0, weight = 0;
    for (int i = 0; i < n; ++i) {
        std::cin >> from >> to >> weight;
        graph.AddEdge(from, to, weight);
    }
    std::cin >> from >> to;
    std::cout << graph.ShortestPath(from, to) << std::endl;

    return 0;
}
