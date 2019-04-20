#ifndef GL_BFS_HPP
#define GL_BFS_HPP

#include <limits>

#include "../structures/Graph.hpp"

namespace gl {
namespace algorithm {

///////////////////////////////////////////////////////////
//    Class declaration
///////////////////////////////////////////////////////////

/**
 * @class BFS
 * @brief Class that provides Graph traversal using the BFS scheme.
 */

template <class SCALAR, class STORAGE, class DIRECTION>
class BFS {
  using Graph = gl::Graph<SCALAR,STORAGE,DIRECTION>;
  using idx_t = typename Graph::idx_t;                   ///< @brief Type of indices
  using ordered_list_t = typename Graph::ordered_list_t; ///< @brief Ordered node ID list.
  using visit_list_t = typename Graph::visit_list_t;     ///< @brief Boolean list that stored previously visited nodes.
  using BFS_queue_t = std::deque<idx_t>;                 ///< @brief Data structure for BFS searches.
  using distance_list_t = std::vector<idx_t>;            ///< @brief Stores BFS distances of each node.
  using idx_list_t = typename Graph::idx_list_t;         ///< @brief Unordered node ID list.

public: 
  /**
   * @brief Constructor. This is where the BFS tree gets computed.
   * @param[in] graph Graph that will be traversed
   * @param[in] src Source node. Starting point of the Breadth First Search.
   */
  BFS(const Graph&, const idx_t);
  BFS() = delete;
  BFS(BFS &&) = default;
  BFS(const BFS &) = default;
  BFS &operator=(BFS &&) = default;
  BFS &operator=(const BFS &) = default;
  ~BFS();

  /**
   * @brief Computes the BFS node traversal order from the source.
   * @return ordered BFS traversal order
   */
  ordered_list_t getTraversalOrder () const;
  /**
   * @brief Computes the BFS node traversal order from the source.
   * @param[in] distance Maximum distance to source of the nodes that are to be found.
   * @return ordered BFS traversal order up to given distance from source
   */
  ordered_list_t getTraversalOrderMaxDistance (const idx_t& distance) const;

  /**
   * @brief Computes all nodes that are at the exact distance given from the source.
   * @param[in] distance Exact distance to source of the nodes that are to be found.
   * @return list of nodes at exact given distance from source.
   */
  idx_list_t getNodesExactDistance (const idx_t& distance) const;
  /**
   * @brief Computes all nodes that are at within a maximum distance given from the source.
   * @param[in] distance Maximum distance to source of the nodes that are to be found.
   * @return list of nodes within given distance from source.
   */
  idx_list_t getNodesMaxDistance (const idx_t& distance) const;

private:
  Graph const& graph_; ///< @brief Reference to graph
  idx_t src_; ///< @brief Source node
  ordered_list_t final_; ///< @brief BFS Traversal order
  distance_list_t distances_; ///< @brief List containing distances from source
};

///////////////////////////////////////////////////////////
//    Member function implementations
///////////////////////////////////////////////////////////

template <class SCALAR, class STORAGE, class DIRECTION>
BFS<SCALAR,STORAGE,DIRECTION>::~BFS() {}

template <class SCALAR, class STORAGE, class DIRECTION>
BFS<SCALAR,STORAGE,DIRECTION>::BFS(const Graph& graph, const idx_t src) : graph_(graph), src_(src) {
  idx_t INF = std::numeric_limits<idx_t>::max();

  BFS_queue_t queue;      // nodes to check the neighbours of
  ordered_list_t out;     // result node lists
  idx_list_t tempList;    // temporary node lists
  visit_list_t visited(graph.numNodes(),false);  // list of visited nodes
  distance_list_t distances(graph.numNodes(),INF);
  auto v = src;

  // traversal
  queue.push_back(v);
  visited[v] = true;
  distances[v] = 0;
  while(!queue.empty()) {
    v = queue.front();
    queue.pop_front();
    out.push_back(v);
    tempList = graph.getUnvisitedNeighbours(v,visited);
    for (auto elem : tempList) {
      visited[elem] = true;
      distances[elem] = distances[v] + 1;
      queue.push_back(elem);
    }
  }
  final_ = out;
  distances_ = distances;
}

template <class SCALAR, class STORAGE, class DIRECTION>
typename Graph<SCALAR,STORAGE,DIRECTION>::ordered_list_t BFS<SCALAR,STORAGE,DIRECTION>::getTraversalOrder () const {
  return final_;
}
template <class SCALAR, class STORAGE, class DIRECTION>
typename Graph<SCALAR,STORAGE,DIRECTION>::ordered_list_t BFS<SCALAR,STORAGE,DIRECTION>::getTraversalOrderMaxDistance (const idx_t& distance) const {
  ordered_list_t result;
  for (auto x : final_) {
    if (distances_[x] > distance) continue;
    result.push_back(x);
  }
  return result;
}

template <class SCALAR, class STORAGE, class DIRECTION>
typename Graph<SCALAR,STORAGE,DIRECTION>::idx_list_t BFS<SCALAR,STORAGE,DIRECTION>::getNodesExactDistance (const idx_t& distance) const {
  idx_list_t result;
  for (auto elem : final_) {
    if (distances_[elem] == distance) result.push_back(elem);
  }
  return result;
}

template <class SCALAR, class STORAGE, class DIRECTION>
typename Graph<SCALAR,STORAGE,DIRECTION>::idx_list_t BFS<SCALAR,STORAGE,DIRECTION>::getNodesMaxDistance (const idx_t& distance) const {
  idx_list_t result;
  for (auto elem : final_) {
    if (distances_[elem] <= distance) result.push_back(elem);
  }
  return result;
}

} /* namespace algorithm */
} /* namespace gl */

#endif /* GL_BFS_HPP */