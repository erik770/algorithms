//Дан невзвешенный неориентированный граф. В графе может быть несколько кратчайших путей между какими-то вершинами.
// Найдите количество различных кратчайших путей между заданными вершинами.
//Требования: сложность O(V+E).
//Формат ввода.
//v: кол-во вершин (макс. 50000),
//n: кол-во ребер (макс. 200000),
//n пар реберных вершин,
//пара вершин u, w для запроса.
//Формат вывода.
//Количество кратчайших путей от u к w.
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
