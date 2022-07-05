#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(int vertices_count) : vertices_count(vertices_count),
                                               matrix(vertices_count * vertices_count, false) {

}

MatrixGraph::MatrixGraph(const IGraph &graph) : vertices_count(graph.VerticesCount()),
                                                matrix(vertices_count * vertices_count, false) {
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        for (auto j: graph.GetNextVertices(i)) {
            matrix[i * vertices_count + j] = true;
        }
    }
}

MatrixGraph::~MatrixGraph() {

}

void MatrixGraph::AddEdge(int from, int to) {
    matrix[from * vertices_count + to] = true;
}

int MatrixGraph::VerticesCount() const {
    return vertices_count;
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
    std::vector<int> result;

    for (int j = 0; j < vertices_count; ++j) {
        if (matrix[vertex * vertices_count + j]) {
            result.push_back(j);
        }
    }
    return result;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
    std::vector<int> result;

    for (int i = 0; i < vertices_count; ++i) {
        if (matrix[i * vertices_count + vertex]) {
            result.push_back(i);
        }
    }
    return result;
}
