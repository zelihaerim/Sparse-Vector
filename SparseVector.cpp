
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include "SparseVector.h"
#define MAX 100

using namespace std;

SparseVector::SparseVector(){// default constructur
	// empty
}
void SparseVector::bosluk(vector<int>& Bosluk,string fileName){
	string line;
	ifstream myFile;
	myFile.open(fileName.c_str());
	if (myFile.is_open())
	{
		while(!myFile.eof()){
			getline(myFile,line);
			char array[40];
			for (int i = 0; i < line.length(); ++i) 	
				array[i]=line[i];
			int counter=0;
			char * pch;
			pch = strtok(array," ");
			while (pch != NULL)
			{
				counter++;
				pch = strtok(NULL, " ");
			}
			Bosluk.push_back((counter-1) );
		}
	}
	myFile.close();
}
SparseVector::SparseVector(const SparseVector& right){	//copy constr
	for (int i = 0; i < right.sparseVector.size(); ++i)
		sparseVector.push_back(right.sparseVector[i]);// bunu yapabilmek icin element classin da operator= overload edilmis olmali
}
SparseVector::Element::Element(const Element& right){ // Elementin vector unu oluşturdugum icin copy constr kesinlikle gerekiyor.
	this->index=right.index;
	this->ikinokta=right.ikinokta;
	this->value=right.value;
}
SparseVector::Element& SparseVector::Element::operator=(const Element& right){
	if (&right != this)
		return *this;
	
	this->index=right.index;
	this->ikinokta=right.ikinokta;
	this->value=right.value;
	return *this;
}	
SparseVector& SparseVector::operator=(const SparseVector& right){
	if (&right == this)
		return *this;
	this->sparseVector.clear();
	for (int i = 0; i < right.sparseVector.size(); ++i)
		sparseVector.push_back(right.sparseVector[i]);// element classindaki ASSİgnment operatoru kullanildi 
	return *this;
}
SparseVector::~SparseVector(){
	/* empty */
}
/* inner class Element */
SparseVector::Element::Element(){ /* empty */}
SparseVector::Element::Element(int in,double deger){
	setIndex(in);	// it constrols is data appropriate  
	setValue(deger); // it constrols is data appropriate 
}

void SparseVector::Element::setIndex(int a){
	if (a >= 0)
		index=a;
	else
		cout<<"index negatif olamaz"<<endl;	
}
void SparseVector::Element::setValue(double a){
	value=a;
}
void SparseVector::Element::set2sini(int a,double d){
	setIndex(a);
	setValue(d);
}
int SparseVector::Element::getIndex(void)const{
	return index;
}
double SparseVector::Element::getValue(void)const{
	return value;
}
char SparseVector::Element::getIkinokta(void)const{
	return ikinokta;
}
SparseVector::SparseVector(string fileName){
	int b;
	char c;
	double d;
	ifstream myFile;
	myFile.open(fileName);
	if (myFile.is_open())
	{
		int index=0;
		vector<int> Bosluk;
		bosluk(Bosluk,fileName);
		int boslukSayisi = Bosluk[index];
		int counter=0;
		while (counter <= boslukSayisi){ // bir satirdaki boşluk sayisi kadar){
			myFile>>b>>c>>d;	// sutun ,: yi okudu,double value yi okudu
			Element temp(b,d);
			sparseVector.push_back(temp);
			counter++;	
		}
	}
	myFile.close();
}
bool SparseVector::findI(int a,const vector<Element>& foo3){
	bool find=false;
	for (unsigned int i = 0; i < foo3.size(); ++i)
	{
		if (foo3[i].getIndex() == a)
		{
			find =true;
			return find;
		}
	}
	return find;
}
void SparseVector::fillFoo3(const SparseVector& obje,const vector<Element>& foo1,vector<Element>& foo3){
	vector<Element> temp;
	vector<Element> temp1;
	bool find;
	for (unsigned int i = 0; i < obje.sparseVector.size(); ++i){
		temp.push_back(obje.sparseVector[i]);
		temp1.push_back(obje.sparseVector[i]);
	}
	for (unsigned int i = 0; i < foo1.size(); ++i)
	{
		for (unsigned int j = 0; j <temp.size() ; ++j)
		{
			if (foo1[i].getIndex()==temp[j].getIndex())
				temp1[j].setIndex(0); // 0 lar sadece var olanlari ayirmak icin
		}
	}
	for (unsigned int i = 0; i < temp1.size(); ++i)
	{
		if (temp1[i].getIndex() != 0)
			foo3.push_back(temp1[i]);
	}
}
void SparseVector::foo(const SparseVector& o1,const SparseVector& o2,vector<Element>& foo1,vector<Element>& foo2,vector<Element>& foo3){
	bool boolean;
	int flag=1,size1,size2;
	
	if ( (o1.sparseVector.size()) >= (o2.sparseVector.size()) )
		boolean = true; // o1 in size i daha buyukse boolean true edilir.
	else
		boolean=false;	// o2 nin size i daha buyukse boolean false edilir.
	if (boolean == true)
	{
		for (int i = 0; i < o1.sparseVector.size() ; ++i)
		{
			bool find=false;
			for (int j = 0; j < o2.sparseVector.size() && flag==1 ; ++j)
			{
				if (o1.sparseVector[i].getIndex()  == o2.sparseVector[j].getIndex())
				{
					find=true;
					foo1.push_back(o1.sparseVector[i]); // ayni indexleri push etti
					flag=0;// ayni indexleri bulduysa diğer indexleri donmeye gerek yok içteki j li for u bitirir distaki i li for devam eder.
				}
			}
			if (find == false)
				foo2.push_back(o1.sparseVector[i]);	// o1 in farkli elemanlarini push ettim
			flag=1;		// j li dongu tekrar baslasin diye
		}
		fillFoo3(o2,foo1,foo3); // o2 nin farkli elemanlari ni push ettim
	}
	if (boolean == false)
	{
		for (int i = 0; i < o2.sparseVector.size() ; ++i)
		{
			bool find=false;
			for (int j = 0; j < o1.sparseVector.size()  && flag==1 ; ++j)
			{
				if (o1.sparseVector[j].getIndex()  == o2.sparseVector[i].getIndex())
				{
					find=true;
					foo1.push_back(o2.sparseVector[i]); // iki obje nin de ayni elemanlari
					flag=0;// ayni indexleri bulduysa diğer indexleri donmeye gerek yok içteki j li for u bitirir distaki i li for devam eder.
				}
			}
			if (find == false)
				foo2.push_back(o2.sparseVector[i]);//foo2 1. objenin farkli elemanlari
			flag=1;		// j li dongu tekrar baslasin diye
		}
		fillFoo3(o1,foo1,foo3); // foo3 diğer objenin farkli elemanlari
	}
}
void SparseVector::bubblesort(SparseVector& object){
	int tmp;
	double value;
    for(int i=0; i<object.sparseVector.size(); i++){
    	int sirali=1;
    	for(int j= (object.sparseVector.size()-1) ; j>i;j--)  //i. geçiş için i eksik dönüş
      	{
	        if(object.sparseVector[j-1].getIndex()>object.sparseVector[j].getIndex()) //şayet buraya girmiyorsak dizi sirali demektir
	        {
		        sirali=0;  //şayet giriyorsak sirali değil demektir
		        tmp=object.sparseVector[j-1].getIndex();
		        value = object.sparseVector[j-1].getValue();
		        object.sparseVector[j-1].setIndex(object.sparseVector[j].getIndex());
		        object.sparseVector[j-1].setValue(object.sparseVector[j].getValue());
		        object.sparseVector[j].setIndex(tmp);
	        	object.sparseVector[j].setValue(value);
	        }
      	}
	    if(sirali){
	    	break;
	    }
    }
}
SparseVector SparseVector::operator+(const SparseVector& obj){
	SparseVector temp;
	vector<Element> first,second,third; //first ortak indeksliler, second ve third farklilar
	if (this == &obj)
	{
		for (int i = 0; i < this->sparseVector.size(); ++i)
		{
			Element ele;
			ele.setIndex(obj.sparseVector[i].getIndex());
			ele.setValue(2* (obj.sparseVector[i].getValue()));
			temp.sparseVector.push_back(ele);
		}
		return temp;
	}
	foo(*this,obj,first,second,third);
	for (int i = 0; i <second.size() ; ++i)
		temp.sparseVector.push_back(second[i]);
	for (int i = 0; i <third.size() ; ++i)
		temp.sparseVector.push_back(third[i]);
	for (int i = 0; i < first.size(); ++i)
	{
		for (int j = 0; j < this->sparseVector.size() ; ++j)
		{
			if ( (this->sparseVector[j].getIndex()) == first[i].getIndex())
			{
				for (int k = 0; k < obj.sparseVector.size() ; ++k)
				{
					if ( (obj.sparseVector[k].getIndex()) == first[i].getIndex() )
					{
						Element ele;
						ele.setIndex(first[i].getIndex());
						ele.setValue(obj.sparseVector[k].getValue() + this->sparseVector[j].getValue());
						temp.sparseVector.push_back(ele);
					}
				}
			}
		}
	} 
	bubblesort(temp);
	return temp;
}
SparseVector SparseVector::operator-(const SparseVector& obj){
	SparseVector temp;
	vector<Element> first,second,third; //first ortak indeksliler, second ve third farklilar
	foo(*this,obj,first,second,third);
	for (int i = 0; i <second.size() ; ++i)
		temp.sparseVector.push_back(second[i]);
	for (int i = 0; i <third.size() ; ++i)
		temp.sparseVector.push_back(third[i]);
	for (int i = 0; i < first.size(); ++i)
	{
		for (int j = 0; j < this->sparseVector.size() ; ++j)
		{
			if ( (this->sparseVector[j].getIndex()) == first[i].getIndex())
			{
				for (int k = 0; k < obj.sparseVector.size() ; ++k)
				{
					if ( (obj.sparseVector[k].getIndex()) == first[i].getIndex() )
					{
						Element ele;
						ele.setIndex(first[i].getIndex());
						ele.setValue(obj.sparseVector[k].getValue() - this->sparseVector[j].getValue());
						temp.sparseVector.push_back(ele);
					}
				}
			}
		}
	}
	bubblesort(temp);
	return temp;
}
SparseVector SparseVector::operator-(){
	for (int i = 0; i < sparseVector.size(); ++i)
		this->sparseVector[i].setValue((this->sparseVector[i].getValue())*(-1));
	return *this;
}
double dot(const SparseVector& obj1,const SparseVector& obj2){ // classin icinde tanimladim
	double sum=0.0;
	bool boolean;
	int flag=1;
	vector<SparseVector::Element> foo1;
	for (int i = 0; i < obj1.sparseVector.size() ; ++i)
	{
		for (int j = 0; j < obj2.sparseVector.size() && flag==1 ; ++j)
		{
			if (obj1.sparseVector[i].getIndex()  == obj2.sparseVector[j].getIndex())
			{
				foo1.push_back(obj1.sparseVector[i]); // ayni indexleri push etti
				flag=0;// ayni indexleri bulduysa diğer indexleri donmeye gerek yok içteki j li for u bitirir distaki i li for devam eder.
			}
		}
		flag=1;		// j li dongu tekrar baslasin diye
	}
	for (int i = 0; i < foo1.size(); ++i)
	{
		for (int j = 0; j <obj1.sparseVector.size() ; ++j)
		{
			if (obj1.sparseVector[j].getIndex()==foo1[i].getIndex())
			{
				for (int t = 0; t < obj2.sparseVector.size() ; ++t)
				{
					if (obj2.sparseVector[t].getIndex() == foo1[i].getIndex())
					{
						sum += (obj1.sparseVector[j].getValue() * obj2.sparseVector[t].getValue());
					}
				}
			}
		}
	}
	return sum;
}
SparseVector::Element::~Element(){ /* ; */}
ostream& operator<<(ostream& output,const SparseVector& obj){
	ofstream myFile;
	for (unsigned int i = 0; i < obj.sparseVector.size(); ++i)
	{
		output<<obj.sparseVector[i].getIndex();
		myFile<<obj.sparseVector[i].getIndex();
		output<<obj.sparseVector[i].getIkinokta();
		myFile<<obj.sparseVector[i].getIkinokta();
		output<<obj.sparseVector[i].getValue();
		myFile<<obj.sparseVector[i].getValue();
		output<<" ";
		myFile<<" ";
	}
	myFile<<endl;
	myFile.close();
	return output;
}