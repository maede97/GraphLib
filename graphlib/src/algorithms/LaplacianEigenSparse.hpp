#ifndef GL_LAPLACIAN_EIGEN_SPARSE_HPP
#define GL_LAPLACIAN_EIGEN_SPARSE_HPP

#include "../structures/Graph.hpp"
#include <vector>
#include <Eigen/Sparse>

namespace gl {
namespace algorithm {

/**
 * @brief Compute the Laplacian Matrix of a graph in Eigen::SparseMatrix format
 * @param g Graph whose Laplacian will be computed
 * @return Laplacian Matrix in Eigen::SparseMatrix format
 */
template <class Graph>
Eigen::SparseMatrix<float> LaplacianEigenSparse(const Graph& g)
{
  std::vector<Eigen::Triplet<float>> triplets;
  Eigen::VectorXf degs(g.numNodes());
  
  // build degree matrix
  for (typename Graph::idx_t i = 0; i < g.numNodes(); i++)
  {
    triplets.emplace_back(i, i, g.getNodeOutDegree(i));
  }
    
  // build adjacency matrix
  for (auto edge = g.edge_cbegin(); edge != g.edge_cend(); ++edge)
  {
    triplets.emplace_back(edge->source(), edge->dest(), -1);
    triplets.emplace_back(edge->dest(), edge->source(), -1);
  }

  Eigen::SparseMatrix<float> laplacian(g.numNodes(), g.numNodes());
  laplacian.setFromTriplets(triplets.begin(), triplets.end());
  laplacian.makeCompressed();
  return laplacian;
}

} // namespace algorithm
} // namespace gl

#endif // GL_LAPLACIAN_EIGEN_DENSE_HPP