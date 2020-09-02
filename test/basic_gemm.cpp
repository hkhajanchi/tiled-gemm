#include <ctime>
#include <gemm_exp.h> 
#include "Eigen/src/Core/util/Constants.h"
#include "stdlib.h"
#include <Eigen/Core>  

// can't use eigen's namespace bc my class implementation is called MatrixBase, rip 
// Type and value global variables 
typedef int mat_t; 
const mat_t initVal = 100; 

// function that runs my implemented naive GEMM 
MatrixBase<mat_t>* matMultScope(const int dim) {

  auto &w  = *(new MatrixBase<mat_t>(initVal,dim,dim));
  auto &x  = *(new MatrixBase<mat_t>(initVal,dim,dim)); 

  auto *ans = MatrixBase<mat_t>::mul(w,x); 
  return ans;
}

int main(int argc, char* argv[]){

  // get matrix dim from cmd
  // argv[0] returns './gemm_exp for some reason'
  const int MATRIX_SQ_SIZE = atoi (argv[1]) ;  
  std::cout << "Computing GEMM for " << MATRIX_SQ_SIZE << "x" << MATRIX_SQ_SIZE << "\n"; 

  // timed basic gemm
  clock_t tic = clock(); 
  MatrixBase<mat_t>* ans = matMultScope(MATRIX_SQ_SIZE); 
  clock_t end = clock(); 
  delete ans; 

  // Eigen GEMM 
  clock_t eigen_tic = clock(); 
  Eigen::Matrix<mat_t, Eigen::Dynamic, Eigen::Dynamic> x = Eigen::Matrix<mat_t, Eigen::Dynamic, Eigen::Dynamic>::Constant(MATRIX_SQ_SIZE,MATRIX_SQ_SIZE,initVal);  
  Eigen::Matrix<mat_t, Eigen::Dynamic, Eigen::Dynamic> w = Eigen::Matrix<mat_t, Eigen::Dynamic, Eigen::Dynamic>::Constant(MATRIX_SQ_SIZE,MATRIX_SQ_SIZE,initVal);
  clock_t eigen_end = clock(); 
  
  std::cout << "Computation Time for " << MATRIX_SQ_SIZE << " Naive GEMM: " << double( end - tic ) / CLOCKS_PER_SEC << "sec \n" << std::endl; 
  std::cout << "Computation Time for " << MATRIX_SQ_SIZE << " Eigen GEMM: " << double( eigen_end - eigen_tic ) / CLOCKS_PER_SEC << "sec \n" << std::endl; 

};  
