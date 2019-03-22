#include "../../src/structures/ListGraph.hpp"

int main(int argc, char const *argv[])
{
  using graph_t = gl::LGraph<int>;

  graph_t g (3);
  g.setEdge(2,1,8); // initial set
  g.setEdge(1,0);   // set as simple undirected
  g.setEdge(2,0,5);
  g.numNodes();
  std::cout << "numNodes: " << g.numNodes() << std::endl
            << g << std::endl;
  g.updateEdge(1,0,5); // update via updateEdge
  g.setEdge(1,0,4); // update via setEdge
  auto neighbours_of_2 = g.getNeighbours(2);
  std::cout << "Neighbours of 2: ";
  for (auto x : neighbours_of_2) {
    std::cout << "(" << x.first << "," << x.second << ") ";
  }
  std::cout << std::endl;
  std::cout << "Degree of 2: " << g.getDegree(2) << std::endl;
  g.delEdge(2,0);   // remove edge
  // g.setEdge(5,2,1);  // test out of range check
  std::cout << g << std::endl;

  return 0;
}