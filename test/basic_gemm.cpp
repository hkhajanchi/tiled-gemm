#include <gemm_exp.h> 
#include "stdlib.h"

typedef int mat_t; 

const mat_t initVal = 100; 

MatrixBase<mat_t>* matMultScope(const int dim) {

  auto &w  = *(new MatrixBase<mat_t>(initVal,dim,dim));
  auto &x = *(new MatrixBase<mat_t>(initVal,dim,dim)); 

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
  std::cout << "Computation Time for " << MATRIX_SQ_SIZE << " GEMM: " << double( end - tic ) / CLOCKS_PER_SEC << "sec \n" << std::endl; 

};  
