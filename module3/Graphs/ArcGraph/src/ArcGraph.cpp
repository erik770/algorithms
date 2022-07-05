#include "ArcGraph.h"

ArcGraph::ArcGraph(int vertices_count) : vertices_count(vertices_count) {
}

ArcGraph::ArcGraph(const IGraph &graph) : vertices_count(graph.VerticesCount()) {
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        for (auto child: graph.GetNextVertices(i)) {
            edges.emplace_back(i, child);
        }
    }

}

ArcGraph::~ArcGraph() {

}

void ArcGraph::AddEdge(int from, int to) {
    edges.emplace_back(from, to);
}

int ArcGraph::VerticesCount() const {
    return vertices_count;
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
    std::vector<int> result;

    for (auto edge: edges) {
        if (edge.first == vertex) {
            result.push_back(edge.second);
        }
    }
    return result;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
    std::vector<int> result;

    for (auto edge: edges) {
        if (edge.second == vertex) {
            result.push_back(edge.first);
        }
    }
    return result;
}
