#include "../../src/structures/MatrixGraph.hpp"
#include "../../src/algorithms/TransitiveClosure.hpp"

int main(int argc, char const *argv[])
{
  using graph = gl::MGraph<int>;
  graph g(8);
  g.readFile("../test/algorithms/testGraph.txt"); // assumes funning from build folder
  std::cout << g << std::endl;
  graph::idx_list_t tc;
  for(graph::idx_t i = 0; i < g.numNodes(); i++)
  {
    tc = g.transitiveClosure(i);
    std::cout << "Transitive Closure of " << i << ": ";
    for (auto v : tc) {
      std::cout << v << " ";
    }
    std::cout << std::endl;
  }
  return 0;
}