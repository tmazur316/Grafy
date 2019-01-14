#include <iostream>
#include <vector>

class Graph
{
  private:
    int size;
    std::vector<std::pair<int, int>> E;
    std::vector<int>* matrix;

    void DFS(bool* edge_table, int start)
    {
      if(edge_table[start])
        return;
      edge_table[start] = true;

      for(auto i : matrix[start])
        DFS(edge_table, i);
    }

    bool check_edge(std::pair<int, int> edge)
    {

      bool visited_edges[size];

      for (auto i = 0; i < size; ++i)
        visited_edges[i] = false;

      visited_edges[edge.first] = true;
      visited_edges[edge.second] = true;

      int start = 0;
      for (int i = 0; i < size; ++i)
      {
        if (!visited_edges[i])
          break;
        ++start;
      }

      DFS(visited_edges, start);

      for (int i = 0; i < size; ++i)
        if(!visited_edges[i])
          return true;

      return false;
    }

  public:
    explicit Graph(int number): size(number)
    {
      matrix = new std::vector<int>[number];
    }

    Graph(int number, std::vector<std::pair<int, int>> vec): Graph(number)
    {
      for(auto i : vec)
        E.push_back(i);

      for(auto i : E)
      {
        matrix[i.first].push_back(i.second);
        matrix[i.second].push_back(i.first);
      }
    }

    ~Graph()
    {
      delete [] matrix;
    }

    void find_bridges()
    {
      for(auto i : E)
        if(check_edge(i))
          std::cout<<i.first<<' '<<i.second<<std::endl;
    }
};

int main()
{
  int size;
  int edge1;
  int edge2;
  std::vector<std::pair<int, int>> vec;

  std::cin>>size;

  while(std::cin>>edge1 && std::cin>>edge2)
    vec.push_back(std::make_pair(edge1, edge2));

  Graph g(size, vec);
  g.find_bridges();
}

