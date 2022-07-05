#include <iostream>
#include "ListGraph.h"
#include "MatrixGraph.h"
#include "SetGraph.h"
#include "ArcGraph.h"

void BFS(const IGraph &graph, int vertex, std::vector<bool> &visited, const std::function<void(int)> &func) {
    std::queue<int> queue;
    queue.push(vertex);
    visited[vertex] = true;

    while (!queue.empty()) {
        int currentVertex = queue.front();
        queue.pop();

        func(currentVertex);

        for (int nextVertex: graph.GetNextVertices(currentVertex)) {
            if (!visited[nextVertex]) {
                visited[nextVertex] = true;
                queue.push(nextVertex);
            }
        }
    }
}

void mainBFS(const IGraph &graph, const std::function<void(int)> &func) {
    std::vector<bool> visited(graph.VerticesCount(), false);
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        if (!visited[i]) {
            BFS(graph, i, visited, func);
        }
    }

}

void DFS(const IGraph &graph, int vertex, std::vector<bool> &visited, const std::function<void(int)> &func) {
    visited[vertex] = true;
    func(vertex);

    for (int nextVertex: graph.GetNextVertices(vertex)) {
        if (!visited[vertex]) {
            DFS(graph, nextVertex, visited, func);
        }
    }
}

void mainDFS(const IGraph &graph, const std::function<void(int)> &func) {
    std::vector<bool> visited(graph.VerticesCount(), false);

    for (int i = 0; i < graph.VerticesCount(); ++i) {
        if (!visited[i]) {
            DFS(graph, i, visited, func);
        }
    }
}


int main() {
    ListGraph listGraph(8);
    listGraph.AddEdge(0, 1);
    listGraph.AddEdge(0, 5);
    listGraph.AddEdge(1, 2);
    listGraph.AddEdge(1, 3);
    listGraph.AddEdge(1, 5);
    listGraph.AddEdge(1, 6);
    listGraph.AddEdge(3, 2);
    listGraph.AddEdge(3, 4);
    listGraph.AddEdge(3, 6);
    listGraph.AddEdge(5, 4);
    listGraph.AddEdge(5, 6);
    listGraph.AddEdge(6, 4);

    MatrixGraph matrixGraph(listGraph);
    SetGraph setGraph(matrixGraph);
    ArcGraph arcGraph(listGraph);

    std::cout << std::endl << "BFS" << std::endl << "-----------------";
    std::cout << std::endl << "List Graph:" << std::endl;
    mainBFS(listGraph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl << "Matrix Graph:" << std::endl;
    mainBFS(matrixGraph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl << "Set Graph:" << std::endl;
    mainBFS(setGraph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl << "Arc Graph:" << std::endl;
    mainBFS(arcGraph, [](int vertex) { std::cout << vertex << " "; });


    std::cout << std::endl << std::endl << "DFS" << std::endl << "-----------------";
    std::cout << std::endl << "List Graph:" << std::endl;
    mainDFS(listGraph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl << "Matrix Graph:" << std::endl;
    mainDFS(matrixGraph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl << "Set Graph:" << std::endl;
    mainDFS(setGraph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl << "Arc Graph:" << std::endl;
    mainDFS(arcGraph, [](int vertex) { std::cout << vertex << " "; });

    return 0;
}
