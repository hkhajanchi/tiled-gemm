#include <iostream> 
#include <stdlib.h> 
#include <assert.h>
#include <gemm_exp.h>

#ifndef _gemm_tiled_H
#define _gemm_tiled_H

template<typename T> 
class MatrixTiled : MatrixBase<T> {

  public: 

    static MatrixTiled<T>* mul (MatrixTiled<T>& x, MatrixTiled<T>& w, int block_size) {
 
      assert(x.getCols() == w.getRows()); // dims must match for gemm 
      assert(x.getCols() % block_size == 0);  // block size must be a factor of the matrix dimension
      assert(w.getRows() % block_size == 0); 

      auto ans = new MatrixBase<T>(0, x.getRows(), w.getCols());

      // blocked matmul operation to improve cache locality

      return ans; 
    }



}; 



#endif 
