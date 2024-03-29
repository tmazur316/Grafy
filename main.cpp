#include <iostream>
#include <vector>

class Graph
{
  private:
    int size;
    std::vector<std::pair<int, int>> E;
    std::vector<int>* matrix;

    int DFS(bool* edge_table, int start, int visited)
    {
      if(edge_table[start])
        return visited;

      edge_table[start] = true;
      ++visited;

      for(auto i : matrix[start])
      {
        if(visited == size)
          break;
        visited = DFS(edge_table, i, visited);
      }

      return visited;
    }

    bool check_edge(std::pair<int, int> edge)
    {

      bool visited_edges[size];
      int visited = 0;

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

      visited = DFS(visited_edges, start, 2);
      return (visited != size);
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
    vec.emplace_back(std::make_pair(edge1, edge2));

  Graph g(size, vec);
  g.find_bridges();
  return 0;
}

