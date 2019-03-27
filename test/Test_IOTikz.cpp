#include <graphlib/io>
#include <iostream>
int main(int argc, char const *argv[]) {
  using mgraph = gl::MGraph<double>;
  mgraph g(10);
  g.readFile("test/Input_edges"); //generated by python file
  std::ofstream out("build/test/OUTPUT.tex");
  gl::writeTikzToStream2(out, g);
  out.close();
  std::cout << "output written to build/test/OUTPUT.tex\n"
            << "Compile with:\n"
            << "cd build\n" 
            << "pdflatex test/OUTPUT.tex" <<  std::endl;
  return 0;
}
