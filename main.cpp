#include <iostream>
#include <list>
#include <utility>
#include <vector>
#include <algorithm>



class Graph
{
  private:
    int size;
    std::vector<std::pair<int, int>> E;
    std::list<int>* matrix;

    void DFS(bool* edge_table, int start)
    {
      if(edge_table[start])
        return;
      edge_table[start] = true;

      for(auto i: matrix[start])
        DFS(edge_table, i);
    }

    bool check_bridge(std::pair<int, int> edge)
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
      matrix = new std::list<int>[number];
    }

    Graph(int number, std::initializer_list<std::pair<int, int>> list): Graph(number)
    {
      for(auto i : list)
        E.push_back(i);

      for(auto i : E)
      {
        matrix[i.first].push_back(i.second);
        matrix[i.second].push_back(i.first);
      }

      /*for(auto iter : E)
        std::cout<<iter.first<<" "<<iter.second <<std::endl;

      for(auto i = 0; i < number; ++i)
      {
        for(auto j: matrix[i])
        {
          std::cout<<j<<' ';
        }
        std::cout<<std::endl;
      }*/
    }

    ~Graph()
    {
      delete [] matrix;
    }

    void find_bridges()
    {
      for(auto i : E)
        if(check_bridge(i))
          std::cout<<i.first<<' '<<i.second<<std::endl;
    }
};


int main()
{
  //Graph g(4,  {{0, 1}, {1, 2}, {3, 2}, {0, 3}, {2, 0}});
  Graph g(0,  {});
  g.find_bridges();
}

