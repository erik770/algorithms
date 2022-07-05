#include "ListGraph.h"

ListGraph::ListGraph(int vertices_count) {
    vertices.resize(vertices_count);
}

ListGraph::ListGraph(const IGraph &graph): vertices(graph.VerticesCount()) {
    for (int i = 0; i < graph.VerticesCount() ; ++i) {
        vertices[i] = graph.GetNextVertices(i);
    }
}

ListGraph::~ListGraph() {

}

void ListGraph::AddEdge(int from, int to) {
    vertices[from].push_back(to);
}

int ListGraph::VerticesCount() const {
    return vertices.size();
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const {
    return vertices[vertex];
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
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
