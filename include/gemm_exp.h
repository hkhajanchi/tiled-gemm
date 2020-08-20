#include <iostream> 
#include <time.h> 
#include <stdlib.h> 
#include <assert.h> 

#ifndef _gemm_exp_H 
#define _gemm_exp_H

template <typename T> 
class MatrixBase {

/*
 * Creates a basic 2D matrix of size (rows, cols) 
 * Uniformly populated with value specified in constructor arg element_val (must be same as matrix type) 
 *
 * Implements a naive O(n^3) algorithm for matrix multipliaction
 */ 

  public: 
    MatrixBase (T init_val, int rows, int cols)  {

      this -> rows = rows; 
      this -> cols = cols; 

    // Pointer to large flattened static array, will use some math for 2d indexing
      this ->data = new T[rows*cols];

      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

          this->at(i,j) = init_val;
        }
      }
    };  

    int getRows() const { return this -> rows; }; 
    int getCols() const { return this -> cols; };

   
    inline T& at (int row, int col) {
      /* Since we want to access the (i,j) element of the 2d array we need to convert the indexing to match
       * the 1D array. We need to account for column-major ordering in memory, where each contiguous column
       * is a separate line in memory 
       *
       *   [ -- col 0 --
       *     -- col 1 --
       *     -- col 2 --
       *         .. 
       *     -- col n -- ]  
       *
       *   to get to (i,j), we first need to get to the column we want. This is accomplished by doing
       *                j*num_rows 
       *
       *   num_rows is our column width, so multiplying j by num_rows will navigate to our desired column
       *   to get to i, we simply need to add it to (j*num_rows) and voila 
       *
       *   mat_2d(i,j) --> mat_1d(j*num_rows + i) 
       */ 
      
      return data[ (col * this->rows) + row ]; }; 

    MatrixBase& operator* (const MatrixBase& x) {
    
      assert(this->cols == x.getRows()); // dims must match for gemm 
      MatrixBase<T> ans(this->rows, x.getCols(), 0); 

      // Naive GEMM algorithm with no optimizations 
      for (int i = 0; i < this.getRows(); i++) {
        for (int j = 0; j < x.getCols(); j++) {
          
          T buf = 0; 
          for (int k = 0; k < this.getCols(); k++) {

            buf += this->at(i,k) * x->at(k,j) ; 
          } 

          ans->at(i,j) = buf; 
        } 
      }  
        return ans; 
    };  


    ~MatrixBase() { delete[] data; }; 
    
  private: 
    int rows; 
    int cols; 

    T* data; 


}; 

#endif 
