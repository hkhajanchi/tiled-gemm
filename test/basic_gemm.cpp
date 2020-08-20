#include <gemm_exp.h> 

typedef int mat_t; 

const int ROWS = 2048; 
const int COLS = 2048;
const float initVal = 100; 

MatrixBase<mat_t>* matMultScope() {

  auto &w  = *(new MatrixBase<mat_t>(initVal,ROWS,COLS));
  auto &x = *(new MatrixBase<mat_t>(initVal,ROWS,COLS)); 

  auto *ans = MatrixBase<mat_t>::mul(w,x); 

  return ans;
}

int main() {


  clock_t tic = clock(); 
  MatrixBase<mat_t>* ans = matMultScope(); 
  clock_t end = clock(); 

  for (int i =0; i< ans->getRows(); i++) {
    for (int j=0; j< ans-> getCols(); j++) {
      std::cout << "Value at " << i << " " << j << " " << ans->at(i,j) << "\n" << std::endl; 
    }
  }

  delete ans; 

  std::cout << "Computation Time for 2048x2048 GEMM: " << double( end - tic ) / CLOCKS_PER_SEC << "sec \n" << std::endl; 
};  
