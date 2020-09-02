import numpy as np 
import time

'''
Simple script to evaluate blocking for GEMM operations
'''

def nonBlocked (x,w): 
    return np.matmul(x,w)

def blocked (w,x,N,block_size): 

    y = np.zeros([N,N])

    for matrixBlockXIndex in range(0, N-block_size + 1, block_size): 
        for matrixBlockYIndex in range(0, N-block_size + 1, block_size):

         # take a block_size x block_size chunk of the weight matrix (second operand) 
         matrixBlock = w[matrixBlockXIndex:matrixBlockXIndex+block_size, matrixBlockYIndex:matrixBlockYIndex+block_size]
         
         for verticalRowIndex in range(0,N): 

             # Go through each 1xblock_size fragment in the first matrix operand
             rowSlice = x[verticalRowIndex, matrixBlockXIndex:matrixBlockXIndex+block_size]
             y[verticalRowIndex, matrixBlockYIndex:matrixBlockYIndex+block_size] += np.matmul(rowSlice,matrixBlock) 

    return y



N = 4096 
block_size = 1024 

w = np.random.rand(N,N)
x = np.random.rand(N,N)

# Time both non-blocked and blocked matrix multiplication
tic = time.time()
y = nonBlocked(x,w)
toc = time.time()

tic_0 = time.time()
z = blocked(w,x,N,block_size)
toc_0 = time.time()

isEquiv = np.allclose(y,z,rtol=1)

if isEquiv :
    print("Blocked GEMM test passed!")
    print("Blocked {}x{} GEMM time: {} sec".format(N,N,toc_0-tic_0))
    print("Nonblocked {}x{} GEMM Time: {} sec".format(N,N,toc-tic))
else: 
    print("Blocked GEMM failed")
