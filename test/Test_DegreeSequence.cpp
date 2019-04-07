#include <graphlib/gl>

int main(int argc, char const *argv[])
{
  using mgraph = gl::MGraph<int>;
  using lgraph = gl::LGraph<int>;
  mgraph tree(12,1);
  lgraph cycle(10,1);
  tree.readFile("test/Input_tree12"); // assumes running from project root folder
  cycle.readFile("test/Input_graph10"); // assumes running from project root folder

  std::cout << "degrees(tree):         " << gl::algorithm::degrees(tree);
  std::cout << "degreeSequence(tree):  " << gl::algorithm::degreeSequence(tree);
  std::cout << "degrees(cycle):        " << gl::algorithm::degrees(cycle);
  std::cout << "degreeSequence(cycle): " << gl::algorithm::degreeSequence(cycle);

  return 0;
}
