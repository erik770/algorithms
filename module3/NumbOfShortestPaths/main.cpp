/*Задача 2. Количество различных путей (3 балла).
    0.2 сек, 10Mb
    Дан невзвешенный неориентированный граф.
    В графе может быть несколько кратчайших путей между какими-то вершинами.
    Найдите количество различных кратчайших путей между заданными вершинами.
    Требуемая сложность O(V+E) - пропорционально количеству вершин и рёбер.
    Формат ввода.
    v: кол-во вершин (макс. 50000),
    n: кол-во ребер (макс. 200000),
    n пар реберных вершин,
    пара вершин u, w для запроса.
    Формат вывода.
    Количество кратчайших путей от u к w.
  1
 /|\
0 | 3
 \|/
  2
in
4
5
0 1
0 2
1 2
1 3
2 3
0 3
out
2
 */
/* https://stackoverflow.com/questions/10226251/#10227808
  1   4   7   10
 / \ / \ / \ /  \
0   3   6   9    12
 \ / \ / \ / \  /
  2   5   8   11
in
13
16
0 1
0 2
1 3
2 3
3 4
3 5
4 6
5 6
6 7
6 8
7 9
8 9
9 10
9 11
10 12
11 12
0 12
out
16
 */

#include <iostream>

#include <set>
#include <vector>
#include <queue>

class ListGraph {
public:
    ListGraph(int vertices_count) {
        vertices.resize(vertices_count);
    }

    ~ListGraph() {

    }

    void AddEdge(int from, int to) {
        vertices[from].push_back(to);
        vertices[to].push_back(from);
    }

    int VerticesCount() const {
        return vertices.size();
    }

    std::vector<int> GetNextVertices(int vertex) const {
        return vertices[vertex];
    }

    std::vector<int> GetPrevVertices(int vertex) const {
        std::vector<int> result;

        for (const auto &parent: vertices) {
            for (const auto &child: parent) {
                if (child == vertex) {
                    result.push_back(child);
                    break;
                }
            }
        }

        return result;
    }

    int ShortestPathCounter(int from, int to) {
        std::vector<bool> visited(this->VerticesCount(), false);
        std::vector<int> shortest_path(this->VerticesCount(), 0);
        std::vector<int> short_path_counter(this->VerticesCount(), 0);


        std::queue<int> queue;
        queue.push(from);
        visited[from] = true;
        shortest_path[from] = 1;
        short_path_counter[from] = 1;

        while (!queue.empty()) {
            int currentVertex = queue.front();
            queue.pop();

            for (int nextVertex: this->GetNextVertices(currentVertex)) {
                if (!visited[nextVertex]) {
                    visited[nextVertex] = true;
                    queue.push(nextVertex);
                }

                if (shortest_path[currentVertex] + 1 < shortest_path[nextVertex] || shortest_path[nextVertex] == 0) {
                    shortest_path[nextVertex] = shortest_path[currentVertex] + 1;
                    short_path_counter[nextVertex] = short_path_counter[currentVertex];
                } else if (shortest_path[currentVertex] + 1 == shortest_path[nextVertex]) {
                    short_path_counter[nextVertex] += short_path_counter[currentVertex];
                }
            }
        }
        return short_path_counter[to];
    }

private:
    std::vector<std::vector<int>> vertices;
};


int main() {
    int v = 0;
    std::cin >> v;
    ListGraph graph(v);

    int n = 0;
    std::cin >> n;
    int from = 0, to = 0;
    for (int i = 0; i < n; ++i) {
        std::cin >> from >> to;
        graph.AddEdge(from, to);
    }
    std::cin >> from >> to;
    std::cout << graph.ShortestPathCounter(from, to) << std::endl;

    return 0;
}
