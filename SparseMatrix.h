#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <vector>
using namespace std;
class SparseMatrix
{
public:
	void print();
	double get(int a,int b)const;
	void set(int a,int b,double d);
	int getSatir()const;
	int getSutun()const;
	void setSatir(int a);
	void setSutun(int a);
	void setRowOrColumnVector(const vector<int>& v,char select,string sec);
	void setValueVector(const vector<double>& v,char select);

	SparseMatrix();
	SparseMatrix(string fileName);
	SparseMatrix(int r,int c);
	SparseMatrix(const SparseMatrix& right);	//copy constr.
	SparseMatrix& operator=(const SparseMatrix& right);//assignment operator
	/* operator overloading */
	SparseMatrix operator+(const SparseMatrix& obj);	//matrixleri toplayip yeni bir matrix elde edecek
	SparseMatrix operator-(const SparseMatrix& obj);	//matrixleri cikartip yeni bir matrix elde edecek
	SparseMatrix operator*(const SparseMatrix& obj);	//matrixleri carpip yeni bir matrix elde edecek
	SparseMatrix operator-(); 	// elemanlari negatif yapacak 
	SparseMatrix transpose(); 	//matrixin transposunu alır yeni bir matrix elde eder
	friend ostream& operator<<(ostream& output,const SparseMatrix& obj); // dosyaya matrixi yazar , terminale de yazabilir
	~SparseMatrix(); // destructor

private:
	/* member functions */
	friend void valueFill(const double temp[],int size1,double* value);
	friend int sutunFill(const double temp[],int size1,int* sutunIndex);
	int max(vector<int> vec);
	int NumOfSatir(string fileName);
	void bosluk(vector<int>& Bosluk,string fileName);//,string fileName
	void fillRowAndColumn(vector<int>& row,vector<int>& column,string fileName);
	/* data members */
	vector<int> row;	//dosyadan okuyup matrixe koymak icin lazım vesaire, row ların indexlerini tutar
	vector<int> column;	//dosyadan okuyup matrixe koymak icin lazım vesaire, column ların indexlerini tutar
	vector<double> value;	//dosyadan okuyup matrixe koymak icin lazım vesaire, sıfırdan farklı dataları leri tutar
	double** matrix;
	int satir;
	int sutun;

};
#endif