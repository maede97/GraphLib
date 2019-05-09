#include <graphlib/gl>
#include <graphlib/external>
#include <iostream>
int main(int argc, char const *argv[])
{
  gl::graphMiu g(20);
  g.setEdge(14, 15, 1, gl::Color(0.9035309556062865, 0.8847333016944611, 0.8497420161568926));
  g.setEdge(3, 5, 1, gl::Color(0.7464577960782566, 0.6728212493237934, 0.6405986204823357));
  g.setEdge(4, 8, 1, gl::Color(0.3492089909251179, 0.6195816914436305, 0.14368258298650116));
  g.setEdge(16, 10, 1, gl::Color(0.9274390883041551, 0.07019915137894428, 0.8760827044808088));
  g.setEdge(8, 5, 1, gl::Color(0.60671850016608, 0.2657809130005693, 0.1742879945027378));
  g.setEdge(17, 15, 1, gl::Color(0.3097354874218453, 0.3417181015633537, 0.5927503207467602));
  g.setEdge(19, 12, 1, gl::Color(0.828914252859762, 0.7016690429832086, 0.5556272111016118));
  g.setEdge(9, 12, 1, gl::Color(0.1989143358511417, 0.038345581020354236, 0.13148324071141848));
  g.setEdge(4, 14, 1, gl::Color(0.6898337968310778, 0.9791422000690099, 0.9243397945350098));
  g.setEdge(18, 16, 1, gl::Color(0.3757370568883509, 0.26811434539782664, 0.7127217744789861));
  g.setEdge(11, 0, 1, gl::Color(0.3533592063905576, 0.7585939823812091, 0.3564649942943794));
  g.setEdge(6, 9, 1, gl::Color(0.228628148343898, 0.09843250430353345, 0.8915077278417594));
  g.setEdge(9, 5, 1, gl::Color(0.38218755096238455, 0.40066432287824627, 0.367651908093116));
  g.setEdge(4, 5, 1, gl::Color(0.21854790648805944, 0.5625890950775027, 0.9261784002865805));
  g.setEdge(17, 0, 1, gl::Color(0.663301127953112, 0.33656483263386416, 0.5647092664437032));
  g.setEdge(19, 16, 1, gl::Color(0.5890784601903599, 0.5680497057368525, 0.7537556999715378));
  g.setEdge(13, 5, 1, gl::Color(0.22044819632591406, 0.7002920503523853, 0.5149781900735101));
  g.setEdge(13, 12, 1, gl::Color(0.5727783779006234, 0.5153961942039581, 0.4486696974311195));
  g.setEdge(2, 5, 1, gl::Color(0.9327488005665094, 0.42156604493535343, 0.2888057648927559));
  g.setEdge(9, 8, 1, gl::Color(0.2944459449120942, 0.2875212940901656, 0.997614511740156));
  g.setEdge(9, 4, 1, gl::Color(0.7950436229916779, 0.9679155397640129, 0.12882427737431923));
  g.setEdge(3, 9, 1, gl::Color(0.4659689224724455, 0.2410514837629305, 0.3130320753914593));
  g.setEdge(1, 2, 1, gl::Color(0.062028782961955464, 0.7121927271340431, 0.8207831690039187));
  g.setEdge(0, 6, 1, gl::Color(0.7801428679628506, 0.5653101531456045, 0.6653790753016835));
  g.setEdge(0, 2, 1, gl::Color(0.25272222414639545, 0.2753390460389127, 0.9535129477614329));
  g.setEdge(2, 17, 1, gl::Color(0.2861355014782492, 0.3004621923222581, 0.23163145032251575));
  g.setEdge(8, 16, 1, gl::Color(0.6482603817963102, 0.8659689413605316, 0.36318175484498527));
  g.setEdge(9, 2, 1, gl::Color(0.3407489344989464, 0.3355538470110391, 0.9904966156571368));
  g.setEdge(1, 4, 1, gl::Color(0.22879340472878118, 0.8934097127254315, 0.9691368135495997));
  g.setEdge(12, 15, 1, gl::Color(0.3551315625822826, 0.2502639233288645, 0.9128565673725849));
  g.setEdge(12, 7, 1, gl::Color(0.22052506535195016, 0.8368671656986386, 0.3251286985553653));
  g.setEdge(6, 19, 1, gl::Color(0.18066572831732597, 0.4763249455490929, 0.9454023196586794));
  g.setEdge(3, 13, 1, gl::Color(0.36376376463902516, 0.9434075364792681, 0.10837703956648426));

  gl::algorithm::SpectralPlacingSparse(g);
  std::ofstream out("build/test/IOTikz_sparse.tex");
  gl::external::writeTikzToStream2(out, g);
  out.close();
  gl::io::compileLatex("build/test/IOTikz_sparse.tex", "--output-directory=build/test/");
  gl::algorithm::SpectralPlacingDense(g);
  std::ofstream out2("build/test/IOTikz_dense.tex");
  gl::external::writeTikzToStream2(out2, g);
  out2.close();
  gl::io::compileLatex("build/test/IOTikz_dense.tex", "--output-directory=build/test/");

  return 0;
}
