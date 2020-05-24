#ifndef SPARSEVECTOR_H
#define SPARSEVECTOR_H

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <vector>
#define MAX 100

using namespace std;
class SparseVector{
public:
	SparseVector();// default constructur
	/* Big 3 */
	SparseVector(const SparseVector& right);
	SparseVector& operator=(const SparseVector& right);
	SparseVector(string fileName);
	~SparseVector();
	friend ostream& operator<<(ostream& output,const SparseVector& obj);
	SparseVector operator+(const SparseVector& obj);
	SparseVector operator-(const SparseVector& obj);
	SparseVector operator-();
	friend double dot(const SparseVector& obj1,const SparseVector& obj2); // classin icinde tanimladim friend ve 2 obje almali
	void bubblesort(SparseVector& object);
private:
	class Element{
		public:
			Element();
			Element(int in,double deger);
			/* big3 */
			Element(const Element& right);
			Element& operator=(const Element& right);
			void setIndex(int a);
			void setValue(double a);
			void set2sini(int a,double d);
			int getIndex(void)const;
			double getValue(void)const;
			char getIkinokta(void)const;
			friend ostream& operator<<(ostream& output,Element const& obj){
				output<<obj.getIndex()<<obj.getIkinokta()<<obj.getValue()<<endl;
				return output;
			}
			~Element();
		private:
			int index;
			char ikinokta=':';
			double value;
	};
	bool findI(int a,const vector<Element>& foo3);
	void foo(const SparseVector& o1,const SparseVector& o2,vector<Element>& foo1,vector<Element>& foo2,vector<Element>& foo3);
	void fillFoo3(const SparseVector& obje,const vector<Element>& foo1,vector<Element>& foo3);
	void bosluk(vector<int>& Bosluk,string fileName);		

	vector<Element> sparseVector;

};
#endif