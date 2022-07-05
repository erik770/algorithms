Дан базовый интерфейс для представления ориентированного графа:
```
struct IGraph {
    virtual ~IGraph() {}
    
    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;
    
    virtual int VerticesCount() const = 0;
    
    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
}; 
```

Необходимо написать несколько реализаций интерфейса:
##### - [ListGraph](ListGraph/src/ListGraph.cpp), хранящий граф в виде массива списков смежности,
##### - [MatrixGraph](MatrixGraph/src/MatrixGraph.cpp), хранящий граф в виде матрицы смежности,
##### - [SetGraph](SetGraph/src/SetGraph.cpp), хранящий граф в виде массива хэш-таблиц/сбалансированных деревьев поиска,
##### - [ArcGraph](ArcGraph/src/ArcGraph.cpp), хранящий граф в виде одного массива пар {from, to}.

Также необходимо реализовать конструктор, принимающий const IGraph&. Такой конструктор должен скопировать переданный граф в создаваемый объект.
Для каждого класса создавайте отдельные h и cpp файлы.
Число вершин графа задается в конструкторе каждой реализации.