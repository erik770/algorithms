#pragma once

#include "IGraph.h"

class ArcGraph: public IGraph {
public:
    ArcGraph(int vertices_count);
    ArcGraph(const IGraph& graph);
    ~ArcGraph();

    void AddEdge(int from, int to) override;
    int VerticesCount() const override;
    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    int vertices_count;
    std::vector<std::pair<int, int>> edges;
};