#include <gemm_exp.h> 


// Basic Constructor, creates a large static array in heap populated with init_val 
template <typename T> 
MatrixBase<T>::MatrixBase(int rows, int cols, T init_val) {
 
  this->rows = rows; 
  this->cols = cols; 

  /* Populate member matrix with init_val*/ 
  for (int i=0; i<rows; i++){
    for (int j=0; j<cols;j++){
      this->mat[i][j] = init_val; 
    }
  }
}

// Getter Methods for row/col members
template<typename T> 
int MatrixBase<T>::getRows() { 
  return this->rows; 
}

template<typename T> 
int MatrixBase<T>::getCols() { 
  return this->cols; 
}

// Helper functions for matrix accessing 
template<typename T> 
inline T& MatrixBase<T>::at (int row, int col){
  /* Takes row/col arguments, and returns a reference to the column array containing the element 
   * (row,col) */ 

  return this->row(row)[col]; 
}

template<typename T> 
inline T* MatrixBase<T>::row (int row) {
  /* takes an argument for row, and returns a pointer to the row array in the member matrix */ 

  return this->mat[row];
}

// Implement matrix multiplication
template<typename T> 
MatrixBase<T>& MatrixBase<T>::operator* (const MatrixBase<T>& x) {
 
  assert( this->getCols() == x.getRows() ) ; 

  MatrixBase<T> ans (this->rows, x.getCols(), 0); 
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

