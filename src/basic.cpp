#include <gemm_exp.h> 

typedef int mat_t;  

/* 
 * This is a super basic, naive implementation of general matrix multiplication. I used a double pointer
 * allocation for matrix building, and the standard O(n^3) algorithm for matrix multiplication.
 *  
 */ 

int main() {

  const int ROWS = 4096;
  const int COLS = 4096; 
  
  const int mat_a_val = 100; 
  const int mat_b_val = 200; 

  int i,j,k;
/* 
 * Super inefficent implementation using double pointers 
 * This implementation calls the heap allocator *N* times, where N is the number of columns
 * Each row points to an array of ints allocated in the heap, but successive row arrays are not contiguous in memory
 *
 * i.e i can go from mat[n][x] to mat [n][y] fine, but going to mat[n][a] to mat[m][a] will probably 
 * result in a cache miss, reducing performance */ 

  mat_t **mat_a = new int*[ROWS]; 
  mat_t **mat_b = new int*[ROWS]; 
  mat_t **mat_c = new int*[ROWS];
  
  for (i = 0; i < ROWS; i++){
    mat_a[i] = new int [COLS];
    mat_b[i] = new int [COLS];
    mat_c[i] = new int [COLS];
  }

  /* Fill arrays */
  /*
   * Seems like I need to initialize all the array elements to a defined value before computation, 
   * does it not already preload this with garbage during memory allocation? Wonder why this causes a segfault
   *
   * Update:
   *    Figured out why it's causing a segfault. I'm trying to allocate 12 MB worth of data to the stack, and 
   *    my current stack limit is only ~8MB. (checked using ulimit -a | grep stack ). Should've been obvious in 
   *    valgrind and gdb. 
   *
   *    Looks like just creating a variable like int var [dim][dim] automatically allocates stack memory. 
   *    I thought the compiler would determine the variable size @compile time and automatically allocate
   *    memory on the heap based on the determined size. Guess this isn't the case. 
   *
   * Update 2: 
   *    Turns out the compiler *does* know the var size. The variables get allocated to the stack because
   *    we explicitly told it to (all function variables get mapped to the stack by default)
   */

  for (i = 0; i < ROWS; i++){
    for (j = 0; j < COLS; j++){
      mat_a[i][j] = mat_a_val; 
      mat_b[i][j] = mat_b_val; 
      mat_c[i][j] = 0; 
    }
  }

  clock_t tic = clock(); 

  // Naive Matrix Multiplication
  for (i = 0; i < ROWS; i++){
    for (j = 0; j< COLS; j++) {

      mat_c[i][j] = 0; 

      for (k = 0; k < ROWS; k++){

        mat_c[i][j] += mat_a[i][k] * mat_b[k][j]; 

      }
    }
  }

  clock_t toc = clock();
  
  std::cout << "Untiled Computation Time for " << ROWS << "x" << COLS <<  ": "  <<  (double) (toc-tic) /CLOCKS_PER_SEC << "sec" << std::endl; 

} 
