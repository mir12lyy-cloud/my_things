#pragma once

/*Notes:
    1.Please check you operations are valid, otherwise it will be terminated very often.
    2.You can use two ways to do operations. I offer functions inside struct and outside the struct except multiplying matrix. I think that defining "A *= B" is unnecessary, but if B isn't a matrix, you can use "A *= B".
    3.If you include the header file, you needn't include the vector and the iostream.
    4.You must offer rows and cols in creating a matrix. And you could never append it by yourself in used.
    5.Using Matrix<Matrix> still could build a matrix, but never use it to do operations with other matrix, otherwise you can't pass the compilation.
    6.I didn't inhibit Matrix<Matrix> because building a block matrix might need to use Matrix<Matrix>.
    7.The block matrix is built as normal matrix.
    8.All in all, you have six functions to build a matrix.
    9.Other features will come soon.
    10.The matrix is based on 0-indexed.
    11.Most of functions based on [left, right).
    12.Assign() can only be used to assign the matrix built by default constructor.
    13.Inner pow() is O(log n), you can use it to compute the power. But actually is introduced to compute norm.
    14.If you think it is troublesome to build identity matrix, you can use getE().
    15.Now the matrix and vector move to the linerAlgebra namespace, the pow() move into the extraFunc namespace. Please mind it.
    16.The subMatrix serves as a span for a matrix. So it's operations is limit. If you want full operations, get Matrix not a sub Matrix.(Now it's lock.)*/
    
/*Versions Note:
  0.5: 1. Could build matrix from init number, or a matrix.
       2. Support some basic operations, such as additions, subtractions and multiplications.
       3. Could get rows, cols and trace of the matrix.
       4. Could compare two matrix are same type or not and judging  a matrix is square matrix.
  0.6: 1. Now user can not build matrix from a matrix to a normal matrix.
  0.7: 1. Change the method to store the matrix, using 1D-Vector now.
       2. Now user can get matrixSize from function.
       3. Now user can not call the easterEgg() from member function. And change the macro name to unlock the easterEgg().
  1.0: 1. Add iterator now! Now user can use iterator to traverse the data.
       2. User can transpose matrix now.
       3. User can get determinant of the matrix.
       4. Add default constructor to build a matrix.
       5. User can initialize the matrix from a vector.
       6. User can get row vectors and col vectors now.
       7. User can print the matrix directly now.
  1.1: 1. User can calculate the power of the square matrix.
       2. User now can build diagonal matrix now. Initialize them from a number or a vector!
  1.2: 1. User can do divisions with a scalar, and do modulo operations with an integer.
  1.3: 1. Add row iterator.
       2. Add col iterator.
       3. Now user can use matrix[i][j] to visit the matrix.
  1.4  1. Reshape some functions in operations, to simplify the code.
       2. Adding Basic Gaussian Elimination now.
       3. You can fill a matrix by another a same type matrix now, though their values may be unmatched.
  1.4.1:1. Change some function in FunTimes.
  1.5: 1. Could link two matrix now. with two functions.
       2. Could judge a matrix can be inverse now and inverse it.
       3. User can get children Matrix now.
       4. User can split Matrix now.
       5. User can cut Matrix now.
       6. Change the method two enable the funtime functions.
       7. Fix errors in getColVector().
  1.5.1: 1. Fix a bug in constructors. To avoid confusing the constructor of normal matrix and diagonal matrix.
  1.6: 1. Rewrite some Codes.
       2. cutMatrix() now have different behaviour.
       3. assign() can be use to assign the matrix constructed by default constructor.
  1.7: 1. Now User can move the matrix.
       2. Add swap().
  1.7.1: 1. Introduce the contractor to copy the matrix.
         2. Fix the rowIterator.
  1.8: 1. Add pow() to compute the power, but is used for to compute the norm.
       2. User can compute the norm of vector now.
       3. Now user can compute the adjoint matrix if the matrix can be inversed.
       4. Fix bugs.
  1.8.1 1. Add getE() to build a identity Matrix. (Actually I don't know whether it is useful.)
       2. Fix bugs.
  1.9: 1. Add getPLU(), user can get PLU matched PA = LU.
       2. Add other way to print Matrix.
  1.9-C: 1. No more C++20 features now.
  1.10-C: 1. Rewrite the swapRow() and swapCol().
          2. Delete iterators. Temporarily.
          3. Delete operator[]. Temporarily.
  1.11-C: 1. Introduce Col and Row Vectors. For the future function getQR().
          2. But the Vectors temporarily can not do operators with Matrix now.
  1.12-C 1.Add operations between Vectors and Matrix.
  1.12.1-C 1. Fix errors.
           2. Change codes in operator* between two Matrix.
  1.12.2-C 1. Move the function to a namespace. The pow is in extraFunc, and the main into linerAlgebra.
  1.12.3-C 1. Fix bugs in get norms.
  1.12.4-C: 1. Sperate the whole header into the 6 headers now.
  1.12.5-C 1. Now can get block of a Matrix. The splitMatrix() turn to the getBlock().
  1.12.6-C 1. Some minor change in Vectors.
  1.12.7-C 1. Some locked features.
  1.13-C 1. Finally have getQR() (But without the Matrix_view, the function isn't elegant in my imagination. But the error less than 1e-18, accpetable.)*/

#include "algFunc.hpp"

#ifdef _FUN_TIME  //If you want to enable it, define the _FUN_TIME.
#endif