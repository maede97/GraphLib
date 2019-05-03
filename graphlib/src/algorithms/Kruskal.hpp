#ifndef GL_KRUSKAL_HPP
#define GL_KRUSKAL_HPP

#include "../structures/DisjointSets.hpp"

namespace gl::algorithm {

///////////////////////////////////////////////////////////
//    Class declaration
///////////////////////////////////////////////////////////

/** A Minimum Spanning Tree (MST) is a subgraph of a given graph that covers all nodes, but with minimal edge weight cost.
 * @class Kruskal
 * @brief Class that computes a Minimum Spanning Tree using Kruskal's algorithm. 
 */

template <class Graph>
class Kruskal {
  using Edge = typename Graph::Edge;
  using idx_t = typename Graph::idx_t;
  using val_t = typename Graph::val_t;
  using visit_list_t = typename Graph::visit_list_t;

public: 
  /**
   * @brief Constructor. This is where the MST is computed based on a * greedy heuristic that only adds the cheapest edges.
   * @param graph Input graph on which the Minimum Spanning Tree will * be computed.
   */
  explicit Kruskal(const Graph&);

  Kruskal() = delete;
  Kruskal(const Kruskal &) = default;                ///< @brief Copy constructor
  Kruskal(Kruskal &&) noexcept = default;            ///< @brief Move constructor
  Kruskal &operator=(const Kruskal &) = default;     ///< @brief Copy assignment
  Kruskal &operator=(Kruskal &&) noexcept = default; ///< @brief Move assignment
  ~Kruskal() = default;                              ///< @brief Destructor

  /**
   * @brief Provides a Selector Object to color the edges in the MST.
   * @param[in] color New color for the MST edges.
   * @return Selector Object: std::pair<bool,gl::Color>
   */
  std::function<std::pair<bool,gl::Color>(const idx_t src, const idx_t dest)> EdgeSelector(const gl::Color& color = gl::Color("red")) const;
  /**
   * @brief Provides a Selector Object to color the nodes in the MST.
   * @param[in] color New color for the MST nodes.
   * @return Selector Object: std::pair<bool,gl::Color>
   */
  std::function<std::pair<bool,gl::Color>(const idx_t node)> NodeSelector(const gl::Color& color = gl::Color("red")) const;
  /**
   * @brief Computes the cost of the MST (sum of all edge weights in the MST).
   * @return MST cost.
   */
  val_t getCost() const;
  /**
   * @brief Returns a graph that only contains the edges of the MST
   * @return MST Graph.
   */
  Graph getMST() const;

private:
  Graph result_;       ///< @brief MST graph
  val_t cost_;         ///< @brief MST cost (sum of all edge weights)
};

///////////////////////////////////////////////////////////
//    Member function implementations
///////////////////////////////////////////////////////////

template <class Graph>
Kruskal<Graph>::Kruskal(const Graph& graph)
{
  GL_ASSERT(!graph.isDirected(),(std::string("Kruskal: '")+graph.getGraphLabel()+std::string("' is not undirected.\n")))
  std::vector<Edge> edges;
  Graph result(graph.numNodes(),std::string(std::string("MST of ")+graph.getGraphLabel()));
  val_t cost {0};
  DisjointSets disjointSets(graph.numNodes());

  // get vector of all edges in the graph
  for (auto it = graph.edge_cbegin(); it != graph.edge_cend(); ++it) 
  {
    edges.push_back(*it);
  }
  // sort edges by increasing weight
  std::sort(edges.begin(),edges.end(),[](const Edge& lhs, const Edge& rhs)
  {
    return lhs.weight() < rhs.weight();
  });
  
  // construct MST
  for(auto edge : edges) 
  {
    idx_t one = edge.source();
    idx_t two = edge.dest();
    
    idx_t setOne = disjointSets.find(one);
    idx_t setTwo = disjointSets.find(two);

    if (setOne != setTwo)
    {
      result.setEdge(edge);
      cost += edge.weight();
      disjointSets.merge(one,two);
    }
  }

  result_ = result;
  cost_ = cost;
}

template <class Graph>
std::function<std::pair<bool,gl::Color>(const typename Graph::idx_t src, const typename Graph::idx_t dest)> Kruskal<Graph>::EdgeSelector (const gl::Color& color) const 
{
  return [&color, this](const idx_t src, const idx_t dest) -> std::pair<bool,gl::Color> {
    if (result_.hasEdge(src,dest)) 
      return {true,color};
    else
      return {false,gl::Color()};
  };
}

template <class Graph>
std::function<std::pair<bool,gl::Color>(const typename Graph::idx_t node)> Kruskal<Graph>::NodeSelector (const gl::Color& color) const 
{
  return [&color, this](const idx_t node) -> std::pair<bool,gl::Color> {
    if (0 <= node && node < result_.numNodes())
      return {true,color};
    else return {false,gl::Color()};
  };
}

template <class Graph>
typename Kruskal<Graph>::val_t Kruskal<Graph>::getCost () const 
{
  return cost_;
}

template <class Graph>
Graph Kruskal<Graph>::getMST () const 
{
  auto result = result_;
  return result;
}

} // namespace gl::algorithm 

#endif // GL_Kruskal_HPP