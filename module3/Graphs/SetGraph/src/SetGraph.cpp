#include "SetGraph.h"

SetGraph::SetGraph(int vertices_count) {
    vertices.resize(vertices_count);
}

SetGraph::SetGraph(const IGraph &graph) : vertices(graph.VerticesCount()) {
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        for (auto child: graph.GetNextVertices(i)) {
            vertices[i].insert(child);
        }
    }
}

SetGraph::~SetGraph() {

}

void SetGraph::AddEdge(int from, int to) {
    vertices[from].insert(to);
}

int SetGraph::VerticesCount() const {
    return vertices.size();
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const {
    std::vector<int> result;

    for (auto to: vertices[vertex]) {
        result.push_back(to);
    }
    return result;
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
    std::vector<int> result;

    for (const auto &parent: vertices) {
        for (auto child: parent) {
            if (child == vertex) {
                result.push_back(child);
            }
        }
    }
    return result;
}
