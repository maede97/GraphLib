#ifndef GL_TEST_HPP
#define GL_TEST_HPP

#include <string>
#include <exception>
#include <iostream>
#include <vector>
#include "../graphlib/src/gl_assert.hpp"
#include "../graphlib/src/io/StreamOverload.hpp"

/**
 * @brief Used to signal the start of a test
 * @param TestName string used to identify a test.
 */
#define GL_TEST_BEGIN(TestName)                                               \
{                                                                             \
  std::cerr << "\033[32m-- Running test \"" << TestName << "\"...\033[00m\n"; \
}

/**
 * @brief Used to signal the end of a test
 */
#define GL_TEST_END()                        \
{                                            \
  std::cerr << "\033[32mfinished\033[00m\n"; \
}

/**
 * @brief Throws std::runtime_error with the defined message.
 * @param Message Error message.
 */
#define GL_FAIL(Message)                                        \
throw std::runtime_error(   std::string(__FILE__)               \
                          + std::string(":")                    \
                          + std::to_string(__LINE__)            \
                          + std::string(" in ")                 \
                          + std::string(__PRETTY_FUNCTION__)    \
                          + std::string(": ")                   \
                          + Message                             \
);

/**
 * @brief Operator that can be used to assert a condition.
 * @param Condition Predicate that is expected to be true.
 */
#define GL_ASSERT_THROW(Condition)                                \
{                                                                 \
  if( !(Condition) )                                              \
  {                                                               \
    throw std::runtime_error(   std::string(__FILE__)             \
                              + std::string(":")                  \
                              + std::to_string(__LINE__)          \
                              + std::string(" in ")               \
                              + std::string(__PRETTY_FUNCTION__)  \
    );                                                            \
  }                                                               \
}

/**
 * @brief Comparison operator that can be used for testing equality.
 * @param A First value in the binary comparison.
 * @param B Second value in the binary comparison.
 */
#define GL_ASSERT_EQUAL(A,B)                                     \
{                                                                \
  if( (A) != (B) )                                               \
  {                                                              \
    throw std::runtime_error(   std::string(__FILE__)            \
                              + std::string(":")                 \
                              + std::to_string(__LINE__)         \
                              + std::string(" in ")              \
                              + std::string(__PRETTY_FUNCTION__) \
                              + std::string(": ")                \
                              + std::to_string(A)                \
                              + std::string(" != ")              \
                              + std::to_string(B)                \
    );                                                           \
  }                                                              \
}
/**
 * @brief Comparison operator that can be used for testing equality of two graphs.
 * @param A First graph in the binary comparison.
 * @param B Second graph in the binary comparison.
 */
#define GL_ASSERT_EQUAL_GRAPH(A,B)                               \
{                                                                \
  if( (A) != (B) )                                               \
  {                                                              \
    std::stringstream ssA, ssB;                                  \
    ssA << A;                                                    \
    ssB << B;                                                    \
    throw std::runtime_error(   std::string(__FILE__)            \
                              + std::string(":")                 \
                              + std::to_string(__LINE__)         \
                              + std::string(" in ")              \
                              + std::string(__PRETTY_FUNCTION__) \
                              + std::string(":\n")               \
                              + ssA.str()                        \
                              + std::string("\n!=\n")            \
                              + ssB.str()                        \
    );                                                           \
  }                                                              \
}
/**
 * @brief Comparison operator that can be used for testing equality of two strings.
 * @param A First string in the binary comparison.
 * @param B Second string in the binary comparison.
 */
#define GL_ASSERT_EQUAL_STRING(A,B)                              \
{                                                                \
  if( (A) != (B) )                                               \
  {                                                              \
    throw std::runtime_error(   std::string(__FILE__)            \
                              + std::string(":")                 \
                              + std::to_string(__LINE__)         \
                              + std::string(" in ")              \
                              + std::string(__PRETTY_FUNCTION__) \
                              + std::string(":\n")               \
                              + A                                \
                              + std::string("\n!=\n")            \
                              + B                                \
    );                                                           \
  }                                                              \
}
/**
 * @brief Comparison operator that can be used for testing equality of a stream and a string.
 * @param A Object that will be read into a stream.
 * @param B Expected string.
 */
#define GL_ASSERT_EQUAL_STREAM(A,B)                              \
{                                                                \
  std::stringstream ssA, ssB (B);                                \
  ssA << A;                                                      \
  GL_ASSERT_EQUAL_STRING(ssA.str(), ssB.str())                   \
}

/**
 * @brief Comparison operator that can be used for testing equality.
 * @param A First value in the binary comparison.
 * @param B Second value in the binary comparison.
 * @param Description A string that can be used as an identifier for which comparison is performed.
 */
#define GL_ASSERT_EQUAL_DESC(A,B,Description)                    \
{                                                                \
  if( (A) != (B) )                                               \
  {                                                              \
    throw std::runtime_error(   std::string(__FILE__)            \
                              + std::string(":")                 \
                              + std::to_string(__LINE__)         \
                              + std::string(" in ")              \
                              + std::string(__PRETTY_FUNCTION__) \
                              + std::string(": (")               \
                              + std::string(Description)         \
                              + std::string(") ")                \
                              + std::to_string(A)                \
                              + std::string(" != ")              \
                              + std::to_string(B)                \
    );                                                           \
  }                                                              \
}

/**
 * @brief Comparison operator that can be used for testing equality for numerical values.
 * @param A First value in the binary comparison.
 * @param B Second value in the binary comparison.
 * @param AbsTol Absolute tolerance for the difference between the two values.
 */
#define GL_ASSERT_EQUAL_ABSTOL(A,B,AbsTol)                       \
{                                                                \
  if( std::max(A,B) - std::min(A,B) >= AbsTol )                  \
  {                                                              \
    throw std::runtime_error(   std::string(__FILE__)            \
                              + std::string(":")                 \
                              + std::to_string(__LINE__)         \
                              + std::string(" in ")              \
                              + std::string(__PRETTY_FUNCTION__) \
                              + std::string(": (Tolerance: ")    \
                              + std::to_string(AbsTol)           \
                              + std::string(") ")                \
                              + std::to_string(A)                \
                              + std::string(" != ")              \
                              + std::to_string(B)                \
    );                                                           \
  }                                                              \
}
/**
 * @brief Comparison operator that can be used for testing numerical equality of two containers.
 * @param Actual Computed container that will be compared to the expected container.
 * @param Expected Expected Value for the computed result.
 * @param AbsTol Absolute tolerance for numerical error.
 */
#define GL_NUMERIC_CONTAINER_COMPARE(Actual,Expected,AbsTol)            \
GL_ASSERT_EQUAL_DESC(Actual.size(),Expected.size(),"Container sizes")   \
{                                                                       \
  for (std::pair<typename decltype(Actual)::const_iterator,typename decltype(Expected)::const_iterator> it(Actual.cbegin(),Expected.cbegin()); it.first != Actual.cend(); ++it.first, ++it.second)        \
  {                                                                     \
    GL_ASSERT_EQUAL_ABSTOL(*(it.first),*(it.second),AbsTol)             \
  }                                                                     \
}

/**
 * @brief Macro that encapsulates a try/catch block and compares the producederror messages.
 * @param Expression Code block that is expected to produce an exception.
 * @param ExceptionType Expected Exception type.
 * @param ExpectedError Expected error message.
 */
#define GL_TEST_CATCH_ERROR(Expression,ExceptionType,ExpectedError) \
try                                                               \
{                                                                 \
  Expression                                                      \
  GL_FAIL("An exception was expected, but not thrown.")           \
}                                                                 \
catch(const ExceptionType& e)                                     \
{                                                                 \
  std::cerr << e.what() << std::endl;                             \
  GL_ASSERT_EQUAL_STRING(std::string(e.what()),ExpectedError)     \
}                                                                 \
catch (...)                                                       \
{                                                                 \
  GL_FAIL("Wrong exception type")                                 \
}

/**
 * @brief Macros that run a test function with all different types of graphs.
 * @param FunctionName Function that will be run.
 * @param ScalarType Scalar type that shall be used for the graph.
 * @param ... (optional) Any function arguments that need to be provided.
 */
#define GL_TEST_FUNCTION_WITH_DIRECTED_TYPES(FunctionName,ScalarType,...)                           \
FunctionName<ScalarType,gl::Matrix,gl::Directed  >(std::string(#ScalarType+std::string(" Matrix Directed")),  ##__VA_ARGS__); \
FunctionName<ScalarType,gl::List,  gl::Directed  >(std::string(#ScalarType+std::string(" List Directed")),    ##__VA_ARGS__);

#define GL_TEST_FUNCTION_WITH_UNDIRECTED_TYPES(FunctionName,ScalarType,...)                         \
FunctionName<ScalarType,gl::Matrix,gl::Undirected>(std::string(#ScalarType+std::string(" Matrix Undirected")),##__VA_ARGS__); \
FunctionName<ScalarType,gl::List,  gl::Undirected>(std::string(#ScalarType+std::string(" List Undirected")),  ##__VA_ARGS__);

#define GL_TEST_FUNCTION_WITH_MATRIX_TYPES(FunctionName,ScalarType,...)                             \
FunctionName<ScalarType,gl::Matrix,gl::Directed  >(std::string(#ScalarType+std::string(" Matrix Directed")),  ##__VA_ARGS__); \
FunctionName<ScalarType,gl::Matrix,gl::Undirected>(std::string(#ScalarType+std::string(" Matrix Undirected")),##__VA_ARGS__);

#define GL_TEST_FUNCTION_WITH_LIST_TYPES(FunctionName,ScalarType,...)                               \
FunctionName<ScalarType,gl::List,  gl::Directed  >(std::string(#ScalarType+std::string(" List Directed")),    ##__VA_ARGS__); \
FunctionName<ScalarType,gl::List,  gl::Undirected>(std::string(#ScalarType+std::string(" List Undirected")),  ##__VA_ARGS__);

#define GL_TEST_FUNCTION_WITH_ALL_STRUCTURE_TYPES(FunctionName,ScalarType,...) \
GL_TEST_FUNCTION_WITH_MATRIX_TYPES(FunctionName,ScalarType,##__VA_ARGS__)      \
GL_TEST_FUNCTION_WITH_LIST_TYPES  (FunctionName,ScalarType,##__VA_ARGS__)

#define GL_TEST_FUNCTION_WITH_ALL_TYPES(FunctionName,...)                      \
GL_TEST_FUNCTION_WITH_ALL_STRUCTURE_TYPES(FunctionName,int,   ##__VA_ARGS__)   \
GL_TEST_FUNCTION_WITH_ALL_STRUCTURE_TYPES(FunctionName,float, ##__VA_ARGS__)   \
GL_TEST_FUNCTION_WITH_ALL_STRUCTURE_TYPES(FunctionName,double,##__VA_ARGS__)

#endif // GL_TEST_HPP