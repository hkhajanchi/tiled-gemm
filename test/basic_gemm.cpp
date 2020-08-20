#include <gemm_exp.h> 


int main() {

  typedef float mat_t; 
  const int ROWS = 2048; 
  const int COLS = 2048;
  const float initVal = 100; 

  // new() operator creates two objects on the heap 
  auto *w = new MatrixBase<mat_t>(initVal,ROWS,COLS);
  auto *x = new MatrixBase<mat_t>(initVal,ROWS,COLS);
  clock_t tic = clock(); 
  MatrixBase<mat_t> y = w * x; 

//  std::cout << "Computation Time for 2048x2048 GEMM: " << double( clock() - tic ) / CLOCKS_PER_SEC << "sec \n" << std::endl; 
};  
