#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <vector>

#include "SparseMatrix.h"
using namespace std;

int SparseMatrix::max(vector<int> vec){// gonderilen vektor un maximum elemanını return eder
	int max=0;
	for (int i = 0; i < vec.size(); ++i)
	{
		if (vec[i] >= max)
			max=vec[i];
	}
	return max;
}
int SparseMatrix::NumOfSatir(string fileName){ // file deki satir sayisini bulur ona göre islem yapacak
	string line;
	int satirSayisi=0;
	ifstream myFile;
	myFile.open(fileName);
	if (myFile.is_open())
	{
		while(!myFile.eof()){
			getline(myFile,line);
			satirSayisi++; 
		}
	}
	myFile.close();
	return satirSayisi;
}
void SparseMatrix::bosluk(vector<int>& Bosluk,string fileName){// bir satırdaki bosluk sayısını bulur ona gore sutun sayısi belirlenecek
	string line;
	ifstream myFile;
	myFile.open(fileName);
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
			Bosluk.push_back((counter-1) );// her satirdaki bosluk sayisini bulup bu array e atar
		}
	}
	myFile.close();
}
double SparseMatrix::get(int a,int b)const{
	return matrix[a][b];
}
void SparseMatrix::set(int a,int b,double d){
	matrix[a][b] = d;
}
void SparseMatrix::print(){
	for (int i = 0; i <satir ; ++i)
	{
		for (int j = 0; j <sutun ; ++j){
			cout<<get(i,j);
		}
		cout<<endl;
	}
}
/* getter lar setter lar*/
int SparseMatrix::getSatir()const{
	return satir;
}
int SparseMatrix::getSutun()const{
	return sutun;
}
void SparseMatrix::setSatir(int a){
	if (a>0)
		satir=a;
	else
		cout<<"satir cannot be negative number."<<endl;
}
void SparseMatrix::setSutun(int a){
	if (a>0)
		sutun=a;
	else
		cout<<"sutun cannot be negative number."<<endl;
}
SparseMatrix::SparseMatrix():satir(4),sutun(4){// 4x4 luk matrix
	matrix=new double*[satir];
	for (int i = 0; i < satir; ++i)
		matrix[i]=new double[sutun];
	for (int i = 0; i < satir; ++i)
	{
		for (int j = 0; j < sutun; ++j)
			matrix[i][j]=0.0;
	}
}
void SparseMatrix::fillRowAndColumn(vector<int>& row,vector<int>& column,string fileName){
	ifstream myFile;
	int a,b;
	char c;
	double d;
	vector<double> value;
	int satirSayisi=NumOfSatir(fileName);
	myFile.open(fileName);
	if (myFile.is_open())
	{
		int index=0;
		vector<int> Bosluk;
		bosluk(Bosluk,fileName);
		int boslukSayisi = Bosluk[index];
		for (unsigned int i = 0; i < satirSayisi; ++i)
		{
			int counter=0;
			myFile>>a; // baştaki row ve boşluk okundu imleci ilerletmiş oldum
			row.push_back(a);
			while (counter < boslukSayisi){ // bir satırdaki boşluk sayısı kadar){
				myFile>>b>>c>>d;	// column ,: yı okudu,double value yi okudu
				column.push_back(b);
				value.push_back(d);		// aynı zamanda value leri de bulup vectore push back eder
				counter++;	
			}
			index++;
			boslukSayisi=Bosluk[index];	//satırdaki bosluk sayısını update ettim
		}
	}
	myFile.close();	
}
SparseMatrix::SparseMatrix(string fileName){
	fillRowAndColumn(row,column,fileName);
	int max1=max(row);
	int max2=max(column);
	satir=max1;
	sutun=max2;
	matrix=new double*[max1];
	for (int i = 0; i < max1; ++i)
		matrix[i]=new double[max2];
	for (unsigned int i = 0; i < max1; ++i)
	{
		for (unsigned int j = 0; j < max2; ++j)
			matrix[i][j]=0.0;
	}
	ifstream myFile;
	int a,b;
	char c;
	double d;
	int satirSayisi=NumOfSatir(fileName);	
	myFile.open(fileName);
	if (myFile.is_open())
	{
		int index=0;
		vector<int> Bosluk;
		bosluk(Bosluk,fileName);
		int boslukSayisi = Bosluk[index];
		for (int i = 0; i < satirSayisi; ++i)
		{
			int counter=0;
			myFile>>a; // baştaki row ve boşluk okundu imleci ilerletmiş oldum
			while (counter < boslukSayisi){ // bir satırdaki boşluk sayısı kadar
				myFile>>b>>c>>d;	// column u okudu,: yı okudu,double value yi okudu
				matrix[a-1][b-1]=d;
				counter++;	
			}
			index++;
			boslukSayisi=Bosluk[index];	//satırdaki bosluk sayısını update ettim
		}
	}
	myFile.close();
}		
SparseMatrix::SparseMatrix(int r,int c):satir(r),sutun(c){
	matrix=new double*[satir];
	for (int i = 0; i < satir; ++i)
		matrix[i]=new double[sutun];
	for (int i = 0; i < satir; ++i)
	{
		for (int j = 0; j < sutun; ++j)
			matrix[i][j]=0.0;
	}
}						
void SparseMatrix::setRowOrColumnVector(const vector<int>& v,char select,string sec){
	if (sec == "column")
	{
		if (select == 'c')		//copy constr. icin column doldurma
		{
			for (int i = 0; i < v.size(); ++i)
			{
				column.resize(v.size());
				column.push_back(v[i]);
			}
		}
		else if (select == 'a')		//assignment operatoru icin column u doldurma
		{
			for (int i = 0; i < v.size(); ++i)
			{
				column.clear();
				column.resize(v.size());
				column[i]=v[i];
			}
		}
	}
	else if (sec == "row")
	{
		if (select == 'c')		//copy constr. icin row doldurma
		{
			for (int i = 0; i < v.size(); ++i)
			{
				row.resize(v.size());
				row.push_back(v[i]);
			}
		}
		else if (select == 'a')	//assignment operatoru icin row u doldurma
		{
			for (int i = 0; i < v.size(); ++i)
			{
				row.clear();
				row.resize(v.size());
				row[i]=v[i];
			}
		}
	}
}			
void SparseMatrix::setValueVector(const vector<double>& v,char select){
	if (select == 'c')
	{
		for (int i = 0; i < v.size(); ++i)
		{
			value.resize(v.size());
			value.push_back(v[i]);
		}
	}
	else if (select == 'a')
	{
		for (int i = 0; i < v.size(); ++i)
		{
			value.clear();
			value.resize(v.size());
			value[i]=v[i];
		}
	}
}
SparseMatrix::SparseMatrix(const SparseMatrix& right){ //copy constr.
	satir=right.satir;
	sutun=right.sutun; 
	setRowOrColumnVector(right.row,'c',"row"); // c harfi copy constr icin setRowOrColumnVector fonksiyonunun cagirildigini belirtir
	setRowOrColumnVector(right.column,'c',"column");
	setValueVector(right.value,'c');
	matrix=new double*[satir];
	for (int i = 0; i < satir; ++i)
		matrix[i]=new double[sutun];
	for (int a = 0; a < satir; ++a)
	{
		for (int b = 0; b < sutun; ++b)
			matrix[a][b]=right.matrix[a][b];
	}
}	
SparseMatrix& SparseMatrix::operator=(const SparseMatrix& right){//assignment operator
	if (&right == this)
		return *this;
	satir=right.satir;
	sutun=right.sutun; 
	setRowOrColumnVector(right.row,'a',"row");// a harfi assignment operatoru icin setRowOrColumnVector fonksiyonunun cagirildigini belirtir
	setRowOrColumnVector(right.column,'a',"column");
	setValueVector(right.value,'a');
	if (satir != right.satir || sutun != right.sutun)
	{
		for (int i = 0; i < satir; ++i)
			delete[] matrix[i];
		delete[] matrix;
		matrix=NULL;
		matrix=new double*[satir];
		for (int i = 0; i < satir; ++i)
			matrix[i]=new double[sutun];
	}
	for (int a = 0; a < satir; ++a)
	{
		for (int b = 0; b < sutun; ++b)
			matrix[a][b]=right.matrix[a][b];
	}
	return *this;
}
SparseMatrix::~SparseMatrix(){
	for (int i = 0; i < satir; ++i)
		delete[] matrix[i];
	delete[] matrix;
	matrix=NULL;
}
void valueFill(const double temp[],int size1,double* value){
	int a=0;
	for (int i = 0; i < size1; ++i)
	{
		if (temp[i] != 0.0)
		{
			value[a]=temp[i];
			a++;
		}
	}
}
int sutunFill(const double temp[],int size1,int* sutunIndex){
	int a=0;
	for (int i = 0; i < size1; ++i)
	{
		if (temp[i] != 0.0)
		{
			sutunIndex[a]=(i+1);
			a++;
		}
	}
	return a;	//sutunIndex in size'i
}
ostream& operator<<(ostream& output,const SparseMatrix& obj){
	int rowIndex[obj.satir];
	int n=0;
	int size1;
	ofstream myFile;

		for (int i = 0; i < obj.satir; ++i)
		{
			for (int b = 0; b < obj.sutun; ++b)// satir sabit yani aynı satirda sutunları dolasip 0 a esit olmayan ilk degeri bulur
			{
				if (obj.matrix[i][b] != 0.0)
				{
					rowIndex[n]=(i+1);//deger olan satir in, hangi satir oldugu bu array de tutulur i+1 cunku index+1 matrisin kendi row sirasi
					n++;
					double temp[obj.sutun];// bir satirlik yer ayirdim
					for (int t = 0; t < obj.sutun; ++t){

						temp[t]=obj.matrix[i][t];//deger bulunan ,satirin tamamini temp e assign ettim
					}
					int sutunIndex[obj.sutun];
					size1 = sutunFill(temp,obj.sutun,sutunIndex);
					double value[obj.sutun];//satir değişl surun yağtom
					valueFill(temp,obj.sutun,value);
					output<<rowIndex[n-1]<<" "; // n i yukarida artirdigim icin n-1 yapıp satirin sayisini yazar
					myFile<<rowIndex[n-1]<<" ";
					for (int d = 0; d < size1; ++d){
						output<<sutunIndex[d]<<':'<< value[d]<<" ";
						myFile<<sutunIndex[d]<<':'<< value[d]<<" ";
					}
					output<<endl;
					myFile<<endl;
					b=obj.sutun-1;// icteki for dongusu bitsin, bastan baslasin diye
				}
			}
		}
	
	output<<endl;// en sonda bir alt satira gecer
	myFile.close();
	return output;
}
SparseMatrix SparseMatrix::operator+(const SparseMatrix& obj){	//matrixleri toplayip yeni bir matrix elde edecek
	if (obj.satir == satir && obj.sutun == sutun)
	{

		SparseMatrix temp(satir,sutun);
		for (int i = 0; i < satir; ++i)
		{
			for (int f = 0; f < sutun ; ++f)
				temp.matrix[i][f]=matrix[i][f]+obj.matrix[i][f];
		}
		int n=0;
		int size1;
		for (int i = 0; i < temp.satir; ++i)
		{
			for (int b = 0; b < temp.sutun; ++b)
			{
				if (temp.matrix[i][b] != 0.0)
				{
					temp.row.push_back(i+1);
					double temp1[temp.satir];
					for (int t = 0; t < temp.sutun; ++t)
						temp1[t]=temp.matrix[i][t];//satirin tamamini temp1 e push ettim
					int sutunIndex[temp.sutun];
					size1 = sutunFill(temp1,temp.sutun,sutunIndex);
					for (int k = 0; k < size1; ++k)
						temp.column.push_back(sutunIndex[k]);
					double value[temp.satir];
					valueFill(temp1,temp.sutun,value);
					for (int k = 0; k < size1; ++k)
						temp.value.push_back(value[k]);
					b=temp.sutun;
				}
			}
		}
		return temp;
	}
	else{
		cout<<"matrices with different numbers of rows and columns can not be summed "<<endl;
		return obj;
	}
}	
SparseMatrix SparseMatrix::operator-(const SparseMatrix& obj){	//matrixleri toplayip yeni bir matrix elde edecek
	if (obj.satir == satir && obj.sutun == sutun)
	{
		SparseMatrix temp(satir,sutun);
		for (int i = 0; i < satir; ++i)
		{
			for (int f = 0; f < sutun ; ++f)
			{
				temp.matrix[i][f]=matrix[i][f]-obj.matrix[i][f];
			}
		}
		int n=0;
		int size1;
		for (int i = 0; i < temp.satir; ++i)
		{
			for (int b = 0; b < temp.sutun; ++b)
			{
				if (temp.matrix[i][b] != 0.0)
				{
					temp.row.push_back(i+1);
					double temp1[temp.satir];
					for (int t = 0; t < temp.sutun; ++t)
						temp1[t]=temp.matrix[i][t];//satirin tamamini temp1 e push ettim
					int sutunIndex[temp.sutun];
					size1 = sutunFill(temp1,temp.sutun,sutunIndex);
					for (int k = 0; k < size1; ++k)
						temp.column.push_back(sutunIndex[k]);
					double value[temp.satir];
					valueFill(temp1,temp.sutun,value);
					for (int k = 0; k < size1; ++k)
						temp.value.push_back(value[k]);
					b=temp.sutun;
				}
			}
		}
		return temp;
	}
	else{
		cout<<"matrices with different numbers of rows and columns cannot be subtracted "<<endl;
		return obj;
	}
}
SparseMatrix SparseMatrix::operator*(const SparseMatrix& obj){	//matrixleri carpip yeni bir matrix elde edecek
	SparseMatrix temp(satir,obj.sutun);
	if (sutun == obj.satir)
	{
		int a=0,c=0;
		int b=0;
		vector<double> tempRow(sutun,0);
		vector<double> tempColumn(obj.satir,0);
		vector<double> element(obj.satir,0);
		for (int k = 0; k < obj.sutun; k++)// sutun kez satir x sutunlar apacak
		{
			for (int i = 0; i < sutun; ++i){
				tempRow[i]=matrix[a][i];
			}
			for (int j = 0; j < obj.satir; ++j){
				tempColumn[j]=obj.matrix[j][b];
			}
			for (int i = 0; i < sutun; ++i){
				element[i]=(tempRow[i]*tempColumn[i]);
			}
			int sum=0;
			for (int i = 0; i < element.size(); ++i)
			{
				sum+=element[i];
			}
			
			temp.matrix[a][b]=sum;
			b++; // sonuc matrixinin sutununu bir ilerletir bir dahaki islem icin
			if (b == (obj.sutun))// eger ki sonuc matrixinin bir satrıdaki sutunları dolduysa if e girer
			{
				a++; // sonuc matrixinin satir sayisini 1 artirir
				b=0; // sonuc matrixinin sutununu da ilk sutundan baslasin diye 0 yapar
				k=-1; // k yı bu scope dan cikica 1 artırıp 0 a getirecek ve distaki döngü devam edecek
				if (a == satir){ // egerki sonuc matrixinin satirinin indexi tasmissa donguden cikilacak
					break;
				}	
			}
		}
		/* temp objesine row column value bilgilerini atama islemi */
		int size1;
		for (int i = 0; i < temp.satir; ++i)
		{
			for (int b = 0; b < temp.sutun; ++b)
			{
				if (temp.matrix[i][b] != 0.0)
				{
					temp.row.push_back(i+1);
					double temp1[temp.satir];
					for (int t = 0; t < temp.sutun; ++t)
						temp1[t]=temp.matrix[i][t];//satirin tamamini temp1 e push ettim
					int sutunIndex[temp.sutun];
					size1 = sutunFill(temp1,temp.sutun,sutunIndex);
					for (int k = 0; k < size1; ++k)
						temp.column.push_back(sutunIndex[k]);
					double value[temp.satir];
					valueFill(temp1,temp.sutun,value);
					for (int k = 0; k < size1; ++k)
						temp.value.push_back(value[k]);
					b=temp.sutun;
				}
			}
		}
	}
	else{
		cout<<"Gonderilen sayilar carpilamaz"<<endl;
		return temp;
	}
	return temp;
}
SparseMatrix SparseMatrix::operator-(){ 	// elemanlari negatif yapacak 
	for (int i = 0; i < satir; ++i)
	{
		for (int j = 0; j < sutun ; ++j)
		{
			if (matrix[i][j] != 0.0)
				matrix[i][j] *=(-1);
		}
	}
	for (int i = 0; i < this->value.size(); ++i)
		this->value[i] *= (-1);

	return *this;
}
SparseMatrix SparseMatrix::transpose(){	//matrixin transposunu alır yeni bir matrix elde eder
	SparseMatrix temp(sutun,satir);
	vector<double> tempRow((this->sutun),0);
	int index=0;
	for (int i = 0; i < this->satir; ++i)
	{
		for (int j = 0; j < this->sutun; ++j)
			tempRow[j]=this->matrix[i][j]; 	//this->in matrixinin satiri tempRow a atılıyor.
		for (int e = 0; e < tempRow.size(); ++e)
			temp.matrix[e][index]=tempRow[e];
		index++;
	}
	int size1;
	for (int i = 0; i < temp.satir; ++i)
	{
		for (int b = 0; b < temp.sutun; ++b)
		{
			if (temp.matrix[i][b] != 0.0)
			{
				temp.row.push_back(i+1);
				double temp1[temp.satir];
				for (int t = 0; t < temp.sutun; ++t)
					temp1[t]=temp.matrix[i][t];//satirin tamamini temp1 e push ettim
				int sutunIndex[temp.sutun];
				size1 = sutunFill(temp1,temp.sutun,sutunIndex);
				for (int k = 0; k < size1; ++k)
					temp.column.push_back(sutunIndex[k]);
				double value[temp.satir];
				valueFill(temp1,temp.sutun,value);
				for (int k = 0; k < size1; ++k)
					temp.value.push_back(value[k]);
				b=temp.sutun;
			}
		}
	}
	return temp;
}