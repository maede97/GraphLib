#ifndef GL_FLOYD_WARSHALL_HPP
#define GL_FLOYD_WARSHALL_HPP

#include "../gl_base.hpp"

namespace gl {
namespace algorithm {

///////////////////////////////////////////////////////////
//    Class declaration
///////////////////////////////////////////////////////////

/** 
 * @class FloydWarshall
 * @brief Class computes that Shortest Paths for all pairs of nodes in the graph using the Floyd-Warshall algorithm.
 */
template <class Graph>
class FloydWarshall {
  using idx_t = typename Graph::idx_t;
  using val_t = typename Graph::val_t;
  using distance_matrix_t = std::vector<Distance<val_t>>;
  using idx_list_t = typename Graph::idx_list_t;

public:

  FloydWarshall();                                               ///< @brief Default constructor
  explicit FloydWarshall(const Graph& graph);                    ///< @brief Computation Constructor

  FloydWarshall(const FloydWarshall &) = default;                ///< Copy constructor
  FloydWarshall(FloydWarshall &&) noexcept = default;            ///< Move constructor
  FloydWarshall &operator=(const FloydWarshall &) = default;     ///< Copy assignment
  FloydWarshall &operator=(FloydWarshall &&) noexcept = default; ///< Move assignment
  ~FloydWarshall() = default;                                    ///< Default destructor

  /**
   * @brief Computation. This is where the shortest distances and the successors of each node pair gets computed.
   * @param graph Input graph on which the shortest paths will be computed.
   */
  void compute(const Graph& graph);
  /**
   * @brief Checks whether the input graph has negative cycles.
   * @return True for negative cycle / false for none.
   */
  bool hasNegativePath () const;
  /**
   * @brief Computes the shortest path length from 'src' to 'dest'.
   * @param src Starting point of shortest path.
   * @param dest End point of shortest path.
   * @return shortest path length / weight.
   */
  Distance<val_t> pathLength(const idx_t src, const idx_t dest) const;
  /**
   * @brief Computes the node sequence that represents the shortest path from 'src' to 'dest'.
   * @param src Starting point of shortest path.
   * @param dest End point of shortest path.
   * @return boolean stating existance of a path & shortest path in form of an ordered list of node indices.
   */
  std::pair<bool,idx_list_t> getPath(const idx_t src, const idx_t dest) const;
  /**
   * @brief Returns a graph that only contains the edges of the SPT (Shortest Path Tree) starting at 'src'.
   * @param[in] src source node of SPT graph.
   * @return SPT Graph.
   */
  Graph getSPT (const idx_t src) const;
  /**
   * @pre Connected graph
   * @brief Computes the closeness centrality of node 'id'
   * @param[in] id Node whose closeness centrality is to be computed
   * @return closeness centrality of 'id'.
   */
  double closenessCentrality (const idx_t id) const;
  /**
   * @brief Computes the harmonic centrality of node 'id'
   * @param[in] id Node whose harmonic centrality is to be computed
   * @return harmonic centrality of 'id'.
   */
  double harmonicCentrality (const idx_t id) const;


private:
  bool isInitialized_ = false;         ///< @brief Boolean storing initialization status
  std::pair<bool,idx_t> negativePath_; ///< @brief Boolean storing info on negative path in graph
  Graph graph_;                        ///< @brief Reference to graph
  distance_matrix_t dist_;             ///< @brief Shortest Path lengths
  idx_list_t next_;                    ///< @brief Shortest Path successors
};

///////////////////////////////////////////////////////////
//    Member function implementations
///////////////////////////////////////////////////////////

template <class Graph>
FloydWarshall<Graph>::FloydWarshall() : isInitialized_(false), negativePath_(std::make_pair<bool,idx_t>(false,0)) {}

template <class Graph>
FloydWarshall<Graph>::FloydWarshall(const Graph& graph) : isInitialized_(false), negativePath_(std::make_pair<bool,idx_t>(false,0)) 
{
  compute(graph);
}

template <class Graph>
void FloydWarshall<Graph>::compute(const Graph& graph)
{
  idx_t i, j, k;
  idx_t numNodes = graph.numNodes();
  val_t weight;
  distance_matrix_t dist (numNodes*numNodes);
  idx_list_t next (numNodes*numNodes,GL_INF(idx_t));
  // fill initial known edges
  for (int i = 0; i < graph.numNodes(); ++i)
  {
    for (int j = 0; j < graph.numNodes(); ++j)
    {
      if (!graph.hasEdge(i,j)) continue;
      weight = graph.getEdgeWeight(i,j);
      // check for negative weights in undirected graphs
      if (!graph.isDirected()) 
      {
        GL_ASSERT(weight >= 0,"FloydWarshall::compute | Graph is undirected and contains negative weights")
      }
      dist[i*numNodes+j].setDistance(weight);
      next[i*numNodes+j] = j;
    }
  }
  // set diagonals
  for (idx_t i = 0; i < numNodes; ++i)
  {
    dist[i*numNodes+i].setDistance(0);
    next[i*numNodes+i] = i;
  }
  // Actual Floyd-Warshall Algorithm
  for (k = 0; k < numNodes; ++k) {
    for (j = 0; j < numNodes; ++j) {
      for (i = 0; i < numNodes; ++i) {
        if (k == i || k == j) 
          continue;
        if (dist[i*numNodes+k] + dist[k*numNodes+j] < dist[i*numNodes+j])
        {
          dist[i*numNodes+j] = dist[i*numNodes+k] + dist[k*numNodes+j];
          next[i*numNodes+j] = next[i*numNodes+k];
        }
      }
    }
  }
  // Check for negative cycles
  for (idx_t i = 0; i < numNodes; ++i)
  {
    if (!dist[i*numNodes+i].isZero()) 
    {
      negativePath_ = {true,i};
    }
  }
  dist_ = dist;
  graph_ = graph;
  next_ = next;
  isInitialized_ = true;
}

template <class Graph>
bool FloydWarshall<Graph>::hasNegativePath () const {
  GL_ASSERT(isInitialized_,"FloydWarshall::hasNegativePath | FloydWarshall has not been initialized with a graph.")
  
  return negativePath_.first;
}

template <class Graph>
Distance<typename Graph::val_t> FloydWarshall<Graph>::pathLength (const idx_t src, const idx_t dest) const {
  GL_ASSERT(isInitialized_,"FloydWarshall::pathLength | FloydWarshall has not been initialized with a graph.")
  graph_.checkRange(src,dest);
  GL_ASSERT(!negativePath_.first,std::string("FloydWarshall::pathLength | The input graph has a negative cycle at node ")+std::to_string(negativePath_.second))
  
  return dist_[src*graph_.numNodes()+dest];
}

template <class Graph>
std::pair<bool,typename Graph::idx_list_t> FloydWarshall<Graph>::getPath (const idx_t src, const idx_t dest) const {
  GL_ASSERT(isInitialized_,"FloydWarshall::getPath | FloydWarshall has not been initialized with a graph.")
  graph_.checkRange(src,dest);
  GL_ASSERT(!negativePath_.first,std::string("FloydWarshall::getPath | The input graph has a negative cycle at node ")+std::to_string(negativePath_.second))

  // Check for path existance
  if (dist_[src*graph_.numNodes()+dest].isInfinite())
    return {false,{}};

  // backtracking
  typename Graph::idx_list_t out;
  out.push_back(src);
  idx_t u = src;
  while (u != dest) {
    u = next_[u*graph_.numNodes()+dest];
    out.push_back(u);
  }
  return {true,out};
}

template <class Graph>
Graph FloydWarshall<Graph>::getSPT (const idx_t src) const
{
  GL_ASSERT(isInitialized_,"FloydWarshall::getSPT | FloydWarshall has not been initialized with a graph.")
  graph_.checkRange(src);
  GL_ASSERT(!negativePath_.first,std::string("FloydWarshall::getSPT | The input graph has a negative cycle at node ")+std::to_string(negativePath_.second))

  Graph result(graph_.numNodes(),std::string(std::string("SPT of node ")+std::to_string(src)+std::string(" in ")+graph_.getGraphLabel()));
  for (idx_t i = 0; i < graph_.numNodes(); ++i)
  {
    auto path = getPath(src,i);
    if (path.first) {
      idx_t i = 0;
      for (idx_t j = i+1; j < path.second.size(); ++i, ++j)
      {
        if (!result.hasEdge(path.second[i],path.second[j])) 
        {
          result.setEdge(path.second[i],path.second[j],graph_.getEdgeWeight(path.second[i],path.second[j]));
        }
      }
    }
  }
  return result;
}

template <class Graph>
double FloydWarshall<Graph>::closenessCentrality (const idx_t id) const
{
  GL_ASSERT(isInitialized_,"FloydWarshall::closenessCentrality | FloydWarshall has not been initialized with a graph.")
  graph_.checkRange(id);
  GL_ASSERT(!negativePath_.first,std::string("FloydWarshall::closenessCentrality | The input graph has a negative cycle at node ")+std::to_string(negativePath_.second))

  double result = 0;
  Distance<typename Graph::val_t> distance;

  for (idx_t i = 0; i < graph_.numNodes(); ++i)
  {
    if (id == i) continue;
    distance = pathLength(i,id);
    if (distance.isInfinite()) 
      return 0;
    else
      result += distance.scalarDistance();
  }
  return static_cast<double>((graph_.numNodes()-1)/result);
}

template <class Graph>
double FloydWarshall<Graph>::harmonicCentrality (const idx_t id) const
{
  GL_ASSERT(isInitialized_,"FloydWarshall::closenessCentrality | FloydWarshall has not been initialized with a graph.")
  graph_.checkRange(id);
  GL_ASSERT(!negativePath_.first,std::string("FloydWarshall::closenessCentrality | The input graph has a negative cycle at node ")+std::to_string(negativePath_.second))

  double result = 0;
  Distance<typename Graph::val_t> distance;

  for (idx_t i = 0; i < graph_.numNodes(); ++i)
  {
    if (id == i) continue;
    distance = pathLength(i,id);
    if (distance.isInfinite()) 
      continue;
    else
      result += 1./distance.scalarDistance();
  }
  return static_cast<double>(result/(graph_.numNodes()-1));
}

} // namespace algorithm  
} // namespace gl

#endif // GL_FLOYD_WARSHALL_HPP