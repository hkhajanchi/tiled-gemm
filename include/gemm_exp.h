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
    MatrixBase (int rows, int cols, T init_val);  

    MatrixBase& operator* (const MatrixBase& x);  
   
    int getRows(); 
    int getCols();

    inline T& at (int row, int col);  

    ~MatrixBase();
    
  private: 

    inline T *row (int row); 
    int rows; 
    int cols; 

    // large static array 
    T mat[rows][cols]; 

}

#endif 
