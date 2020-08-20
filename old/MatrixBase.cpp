#include <gemm_exp.h> 


// Basic Constructor, creates a large static array in heap populated with init_val 
template <typename T, int rows, int cols> 
MatrixBase<T,rows,cols>::MatrixBase(T init_val) {
 

  /* Populate member matrix with init_val*/ 
  for (int i=0; i<rows; i++){
    for (int j=0; j<cols;j++){
      this->mat[i][j] = init_val; 
    }
  }
}


// Helper functions for matrix accessing 
template <typename T, int rows, int cols> 
inline T& MatrixBase<T,rows,cols>::at (int row, int col){
  /* Takes row/col arguments, and returns a reference to the column array containing the element 
   * (row,col) */ 

  return this->row(row)[col]; 
}

template <typename T, int rows, int cols> 
inline T* MatrixBase<T,rows,cols>::row (int row) {
  /* takes an argument for row, and returns a pointer to the row array in the member matrix */ 

  return this->mat[row];
}

// Implement matrix multiplication
template <typename T, int rows, int cols> 
MatrixBase<T,rows,cols>& MatrixBase<T,rows,cols>::operator* (const MatrixBase<T,rows,cols>& x) {
 
  assert( this->getCols() == x.getRows() ) ; 

  MatrixBase<T,rows,> ans (this->rows, x.getCols(), 0); 
  T buf; 

  for (int i = 0; i < this->rows; i++){
    for (int j=0; j < this->cols; j++) {

      buf = 0; 
      for (int k=0; k < this->rows; k++){
        buf += this->at(i,k) * x->at(k,j);
      }
      ans->at(i,j) = buf;

    }
  }
 return ans;  

}

