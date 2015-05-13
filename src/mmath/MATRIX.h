#ifndef MATRIX_H
#define MATRIX_H

#include <fstream>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <stdlib.h>
#include <vector>

using namespace std;

namespace libmmath{

//============================================================
// Forward declared dependencies
class VECTOR;
class MATRIX;

//===============================================================================

class MATRIX{
    
  double *Orthogonalization_Matrix;
    
public:
  // Data; 
  int num_of_rows;
  int num_of_cols;
  int num_of_elems;
  double *M;
    
  void set(int,double);
  double get(int);
  void set(int,int,double);
  double get(int,int);
          
  double NonOrtMeasure;
  // Constructors;
  MATRIX() 
  {  MATRIX_PRECISION=8;
     MATRIX_WIDTH=15;
     num_of_rows=3;
     num_of_cols=3;
     num_of_elems=9;    
     M = new double[9];
     for(int i=0;i<9;i++) { M[i]=0.0;}
  } 
  
  MATRIX(int m,int n);
  MATRIX(const MATRIX& ob);   // Copy constructor;
  MATRIX(const VECTOR&, const VECTOR&, const VECTOR&);
 ~MATRIX();

  // Initializations;
  void Init(double x);            // Çàïîëíÿåò âñþ ìàòðèöó ÷èñëîì x;
  void InitSquareMatrix(int dim,double x);  // Âûäåëÿåò ïàìÿòü äëÿ ìàòðèöû è çàïîëíÿåò åå ÷èñëîì x.
  bool Init_Unit_Matrix(double x);// Ãåíåðèðóåò äèàãîíàëüíóþ ìàòðèöó 1*x;
  bool Load_Matrix_From_File(char * FileName); 
  void init(VECTOR&, VECTOR&, VECTOR&);
  void init(const VECTOR&, const VECTOR&, const VECTOR&);
  void init(MATRIX&);
  void init(const MATRIX&);

  // Rotation matrices
  void Rotation(const VECTOR&); // Create a rotation matrix for rotation around direction given by direction
                                // of the argument vector, and on the amount given by the norm of the vector
  // Rotation matrixes around corresponding axes
  void Rx(double);
  void Ry(double);
  void Rz(double);

  // Manipulations with colomns, rows and elements;               
  int show_num_of_rows() { return num_of_rows;}
  int show_num_of_cols() { return num_of_cols;}
  int show_num_of_elems(){ return num_of_elems;}

  double   Element(int row,int col)          {int n=row*num_of_cols+col; return *(M+n);}
  void Set_Element(int row,int col,double x) {int n=row*num_of_cols+col; *(M+n)=x;     }
  void Add_To_Element(int row,int col,double x) {int n=row*num_of_cols+col; *(M+n)+=x;}
  void FindMaxNondiagonalElement(int& rw,int& cl,double& value);

  // Tehniques for ortogonalization and decomposition;
  double NonOrtogonality_Measure();
  void Show_Orthogonalization_Matrix();
  void Show_Orthogonalization_Matrix(char *Output_File);
  void Delete_Orthogonalization_Matrix();
  void RightRotation(int i,int j,double sine,double cosine);
  void LeftRotation(int i,int j,double sine,double cosine);
  void Ortogonalization(double Eps);
  void RL_Decomposition(MATRIX *L,MATRIX *R);

  // Basic matrix operations;
  void Transpose();
  MATRIX T();
  void Inverse(MATRIX* INV);
  void Inverse(MATRIX& INV);
//  void tensor_product(VECTOR v1,VECTOR v2);
  void tensor_product(VECTOR v1,VECTOR v2);

  double dot_product(MATRIX&);
  double dot_product(MATRIX*);
/*
  inline void tensor_product(VECTOR& v1,VECTOR& v2){
    M[0] = v1.x*v2.x;   M[1] = v1.x*v2.y;  M[2] = v1.x*v2.z;
    M[3] = v1.y*v2.x;   M[4] = v1.y*v2.y;  M[5] = v1.y*v2.z;
    M[6] = v1.z*v2.x;   M[7] = v1.z*v2.y;  M[8] = v1.z*v2.z;
  }
*/
  double& operator[](const int indx);
  MATRIX operator-();                                           // Negation;
  MATRIX operator*(const MATRIX&);
  MATRIX operator+(const MATRIX&);
  MATRIX operator-(const MATRIX&);
  MATRIX& operator+=(const MATRIX&);
  MATRIX& operator-=(const MATRIX&);
  MATRIX& operator*=(double);
  MATRIX operator/(double num);
  MATRIX& operator=(const MATRIX&);
  MATRIX& operator=(double num);

  friend int operator == (const MATRIX& m1, const MATRIX& m2);  // Are matrices equal;
  friend int operator != (const MATRIX& m1, const MATRIX& m2);  // Are matrices not equal;

  friend double operator%(MATRIX& m1, MATRIX& m2);  // Scalar product of matrices;
  friend MATRIX operator^(VECTOR& v1,VECTOR& v2);   // Tensor product of two vectors
  friend VECTOR operator*(const MATRIX& m,  const VECTOR& v);   // Multiplication of vector and matrix;
//  friend VECTOR operator*(const VECTOR& v,  const MATRIX& m);   // Multiplication of vector and matrix; 
  friend MATRIX operator*(const double& f,  const MATRIX& m1);  // Multiplication of matrix and double;
  friend MATRIX operator*(const MATRIX &m1, const double  &f);  // Multiplication of matrix and double;


  // Input & output functions;
  void Show_Matrix();
  void Show_Matrix(char *Output_File);
  friend ostream &operator<<(ostream &strm,MATRIX ob);
  friend istream& operator>>(istream& strm,MATRIX &ob);
  void Delete_Matrix();

  // Additional methods for matrixes.
  void get_vectors(VECTOR&,VECTOR&,VECTOR&);
  void skew(VECTOR);
  void skew1(VECTOR);
  void exp(MATRIX&);
  void exp(const MATRIX&);
  void JACOBY_EIGEN(MATRIX&, MATRIX&);
  void JACOBY_EIGEN(MATRIX&, MATRIX&,double);

  // Properties;
  int MATRIX_PRECISION;
  int MATRIX_WIDTH;
  double Determinant();
  double tr();
  double max_elt();

  // Binary output/input
  void bin_dump(std::string filename);
  void bin_load(std::string filename);
};


  typedef std::vector<MATRIX> MATRIXList;

}// libmmath

#endif // MATRIX.h

