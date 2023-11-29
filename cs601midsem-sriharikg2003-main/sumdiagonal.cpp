/** @file sumdiagonal.cpp
 * @brief Midsem - PartII Question 1 - GDB, Valgrind, Doxygen 
 *
 * This file contains two flavors matmul: ijk and ikj loop orderings. matmul_ijk and matmuk)ikj are the names of the functions.This erroneous program is supposed to initialize a square matrix of given dimensions with numbers ranging from -10 to 9 and print the sum of the diagonal elements of the matrix
 *
 * @author Srihari K G
 * @bug Fixed  added namespace std, double** , and & removed fro m &vec also double *[n], and changed fill_vectors.
 */ 



#include <cstdlib>
#include <cmath>
#include <iostream>
using namespace std;
/** DO NOT CHANGE THE BELOW 4 LINES **/
double** initialization(int);
double* fill_vectors(double*, int);
void print_matrix(double** , int);
double* sumdiagonal(double** , int);
/************************************/


/**
 * @brief Main function no parameters
 */
 int main()
{
  int i, j, n;
  double **matrix;
  double* sum ;

  cout << endl << "Enter the Dimension for a square matrix: " << flush;
  cin >> n;
  
  cout <<n;
  matrix = initialization(n);
  cout << matrix;
  for(i = 0 ; i < n ; i++)
      matrix[i] =  fill_vectors(matrix[i] , n);
  sum = sumdiagonal(matrix , n);
  print_matrix(matrix , n);
  cout << endl << "Sum of the diagonal elements are: " << sum;
  return 0;
}




/*! @fn double** initialization(int n)
    @brief The initialization routine is supposed to allocate memory for a n-by-n matrix and return a pointer to the allocated matrix.
    @param n, reference to size n
*/


double** initialization(int n) {
  int i;
  double** matrix ;
  matrix = new double*[n];
  for(i=0 ; i< n ; ++i)
    matrix[i] = new double[n];
  cout <<"HELLO";
  return matrix;
}



/*! @fn double* fill_vectors(double* vec , int n)
    @brief  The fill_vector routine is supposed to fill a given vector with
 random numbers ranging from -10 to 9.

  @param vec, reference to vec
  @param n, reference to size n

*/


double* fill_vectors(double* vec , int n) {
  int i ;
  for(i = 0 ; i < n ; i++)
    vec[i] = rand() % 20 - 10 ;
  return vec;
}

/* The print_matrix routine is supposed to print out the elements of
*  a given matrix in a nice format using printf.
*/ 


/*! @fn void print_matrix(double** matrix , int n)
    @brief  The print_matrix routine is supposed to print out the elements of a given matrix in a nice format using printf.

  @param matrix, reference to matrix
  @param n, reference to size n

*/
void print_matrix(double** matrix , int n) {
  int i,j;
  for (i= 0 ; i< n ; i++)
    {
    for(j = 0 ; j < n ; j++)
	cout << matrix[i][j] << ", ";
    cout << endl;
    }
}




/*! @fn double* sumdiagonal(double** matrix , int n)
    @brief The sumdiagonal routine is supposed to return the sum of the diagonal
 elements if a given matrix.
  @param matrix, reference to matrix
  @param n, reference to size n

*/
double* sumdiagonal(double** matrix , int n) {
  int i ;
  double sum = 0.0;
  for(i=1 ; i<=n ; i++)
    sum+=matrix[i][i];
  return &sum;
}
