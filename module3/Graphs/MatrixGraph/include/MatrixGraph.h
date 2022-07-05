#pragma once
#include "IGraph.h"
#include <memory>
#include <array>

class MatrixGraph: public IGraph {
public:
    MatrixGraph(int vertices_count);
    MatrixGraph(const IGraph& graph);
    ~MatrixGraph();

    void AddEdge(int from, int to) override;
    int VerticesCount() const override;
    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    int vertices_count;
    std::vector<bool> matrix;
};