#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

template<typename T>
void Swap(T* arr1,T* arr2,int size){
    for(int i=0;i<size;++i){
        swap(arr1[i],arr2[i]);
    }
}

template<typename T>
void subtraction(T* arr1,T* arr2,int size,T arg){
    for(int i=0;i<size;++i){
        arr1[i]=arr1[i]-arr2[i]*arg;
    }
}

template<class T, int ROWS,int COLUMNS>
class TMatrix{
private:
    T** _matrix;
public:
    TMatrix(){
        _matrix=new T*[ROWS];
        for(int i=0;i<ROWS;++i){
            _matrix[i]=new T[COLUMNS];
            for(int j=0;j<COLUMNS;++j){
                _matrix[i][j]=T();
            }
        }
    }

    ~TMatrix(){
        for(int i=0;i<ROWS;++i){
            delete _matrix[i];
        }
        delete _matrix;
    }

    TMatrix(const TMatrix<T,ROWS,COLUMNS>& matrix){
        _matrix=new T*[ROWS];
        for(int i=0;i<ROWS;++i){
            _matrix[i]=new T[COLUMNS];
            for(int j=0;j<COLUMNS;++j){
                _matrix[i][j]=matrix(i,j);
            }
        }
    }

    void Fill(const T& t){
        for(int i=0;i<ROWS;++i){
            for(int j=0;j<COLUMNS;++j){
                this->_matrix[i][j]=t;
            }
        }
    }
    
    void Fill_rand(){
		srand(time(0));
		for(int i=0;i<ROWS;++i){
            for(int j=0;j<COLUMNS;++j){
                _matrix[i][j]=(T)(rand()%10);
            }
        }
    }

    const T& operator()(int i,int j)const{
        return this->_matrix[i][j];
    }

    T &operator()(int i, int j){
        return this->_matrix[i][j];
    }

    TMatrix<T,ROWS,COLUMNS>& operator=(const TMatrix<T,ROWS,COLUMNS>& matrix){
        for(int i=0;i<ROWS;++i){
            for(int j=0;j<COLUMNS;++j){
                this->_matrix[i][j]=matrix(i,j);
            }
        }
        return *this;
    }
	
	bool operator==(const TMatrix<T,ROWS,COLUMNS>& matrix)const{
		for(int i=0;i<ROWS;++i){
            for(int j=0;j<COLUMNS;++j){
                if(_matrix[i][j]!=matrix(i,j)){
					return false;
				}
            }
        }
        return true;
    }
		
    TMatrix<T,ROWS,COLUMNS> operator+(const TMatrix& matrix){
        TMatrix<T,ROWS,COLUMNS> result;
        for(int i=0;i<ROWS;++i){
            for(int j=0;j<COLUMNS;++j){
                result(i,j)=this->_matrix[i][j]+matrix(i,j);
            }
        }
        return result;
    }

    TMatrix<T,ROWS,COLUMNS> operator-(const TMatrix<T,ROWS,COLUMNS>& matrix){
        TMatrix<T,ROWS,COLUMNS> result;
        for(int i=0;i<ROWS;++i){
            for(int j=0;j<COLUMNS;++j){
                result(i,j)=this->_matrix[i][j]-matrix(i,j);
            }
        }
        return result;
    }

    TMatrix<T,ROWS,COLUMNS> operator*(const T& t){
        TMatrix<T,ROWS,COLUMNS> result;
        for(int i=0;i<ROWS;++i){
            for(int j=0;j<COLUMNS;++j){
                result(i,j)=this->_matrix[i][j]*t;
            }
        }
        return result;
    }

    template<int COLUMNS2>
    TMatrix<T,ROWS,COLUMNS2> operator*(const TMatrix<T,COLUMNS,COLUMNS2>& matrix){
        TMatrix<T,ROWS,COLUMNS2> result;
        for(int i=0;i<ROWS;++i){
            for(int j=0;j<COLUMNS2;++j){
                result(i,j)=this->_matrix[i][0]*matrix(0,j);
                for(int k=1;k<COLUMNS;++k){
                    result(i,j)+=this->_matrix[i][k]*matrix(k,j);
                }
            }
        }
        return result;
    }
    
    template<int N>
    TMatrix<T,N/2,N/2> Separation(const TMatrix<T,N,N>& matrix,int arg){
        TMatrix<T,N/2,N/2> result;
        int c1,c2,r1,r2;
        switch(arg){
            case 1:
                c1=0;
                c2=N/2;
                r1=0;
                r2=N/2;
                break;
            case 2:
                c1=N/2;
                c2=N;
                r1=0;
                r2=N/2;
                break;
            case 3:
                c1=0;
                c2=N/2;
                r1=N/2;
                r2=N;
                break;
            case 4:
                c1=N/2;
                c2=N;
                r1=N/2;
                r2=N;
                break;
        }
        for(int i=r1;i<r2;++i){
            for(int j=c1;j<c2;++j){
                result(i-r1,j-c1)=matrix(i,j);
            }
        }
        return result;
    }
    
    template<int N>
    TMatrix<T,N,N> Multiplication_Shtrassen(const TMatrix<T,N,N>& matrix){
        if(N<=128 && N>=32){
            return *this*matrix;
        }
        TMatrix<T,N,N> result;
        if(N==1){
            result(0,0)=this->_matrix[0][0]*matrix(0,0);
            return result;
        }
        TMatrix<T,N/2,N/2> A11,A12,A21,A22,B11,B12,B21,B22,C11,C12,C21,C22,P1,P2,P3,P4,P5,P6,P7;
        A11=Separation(*this,1);
        A12=Separation(*this,2);
        A21=Separation(*this,3);
        A22=Separation(*this,4);
   
        B11=Separation(matrix,1);
        B12=Separation(matrix,2);
        B21=Separation(matrix,3);
        B22=Separation(matrix,4);
        
        P1=(A11+A22).Multiplication_Shtrassen(B11+B22);
        P2=(A21+A22).Multiplication_Shtrassen(B11);
        P3=A11.Multiplication_Shtrassen(B12-B22);
        P4=A22.Multiplication_Shtrassen(B21-B11);
        P5=(A11+A12).Multiplication_Shtrassen(B22);
        P6=(A21-A11).Multiplication_Shtrassen(B11+B12);
        P7=(A12-A22).Multiplication_Shtrassen(B21+B22);

        C11=P1+P4-P5+P7;
        C12=P3+P5;
        C21=P2+P4;
        C22=P1-P2+P3+P6;

        for(int i=0;i<N/2;++i){
            for(int j=0;j<N/2;++j){
                result(i,j)=C11(i,j);
            }
        }
        for(int i=0;i<N/2;++i){
            for(int j=N/2;j<N;++j){
                result(i,j)=C12(i,j-N/2);
            }
        }
        for(int i=N/2;i<N;++i){
            for(int j=0;j<N/2;++j){
                result(i,j)=C21(i-N/2,j);
            }
        }
        for(int i=N/2;i<N;++i){
            for(int j=N/2;j<N;++j){
                result(i,j)=C22(i-N/2,j-N/2);
            }
        }
        return result;
    }

    TMatrix<T,ROWS,COLUMNS>& operator+=(const TMatrix<T,ROWS,COLUMNS>& matrix){
        *this=*this+matrix;
        return *this;
    }

    TMatrix<T,ROWS,COLUMNS>& operator-=(const TMatrix<T,ROWS,COLUMNS>& matrix){
        *this=*this+matrix;
        return *this;
    }

    template<int COLUMNS2>
    TMatrix<T,ROWS,COLUMNS2> operator*=(const TMatrix<T,COLUMNS,COLUMNS2>& matrix){
        TMatrix<T,ROWS,COLUMNS2> result=(*this)*matrix;
        return result;
    }

    template<class T1,int ROWS1,int COLUMNS1>
    friend ostream& operator<<(ostream& ostr,const TMatrix<T1,ROWS1,COLUMNS1>& matrix);
    TMatrix<T,COLUMNS,ROWS> Transposed() const{
        TMatrix<T,COLUMNS,ROWS> result;
        for(int i=0;i<COLUMNS;++i){
            for(int j=0;j<ROWS;++j){
                result(i,j)=this->_matrix[j][i];
            }
        }
        return result;
    }

    template<int N>
    T Det(TMatrix<T,N,N>& matrix)const{
        T matrix_dop[N][N];
        for(int i=0;i<N;++i){
            for(int j=0;j<N;++j){
                matrix_dop[i][j]=matrix(i,j);
            }
        }
        for(int i=0;i<N-1;++i){
            T tmp=matrix_dop[i][i];
            if(tmp!=0){
                for(int j=i+1;j<N;++j){
                    T m=matrix_dop[j][i];
                    for(int k=i;k<N;++k){
                        matrix_dop[j][k]-=((matrix_dop[i][k]*m)/tmp);
                    }
                }
            }else{
                for(int j=i+1;j<N;++j){
                    if(matrix_dop[i][j]!=0){
                        tmp=matrix_dop[j][i];
                        for(int k=0;k<N;++k){
                            swap(matrix_dop[i][k],matrix_dop[j][k]);
                        } 
                        break;
                    }
                }
                if(tmp==0){
                    return 0;
                }else{
                    for(int j=i+1;j<N;++j){
                        T m=matrix_dop[j][i];
                        for(int k=i;k<N;++k){
                            matrix_dop[j][k]-=((matrix_dop[i][k]*m)/tmp);
                        }
                    }
                }
            }
        }
        for(int i=1;i<N;++i){
            matrix_dop[0][0]*=matrix_dop[i][i];
        }
        return matrix_dop[0][0];
    }
};

template<class T,int ROWS,int COLUMNS>
ostream& operator<<(ostream& ostr,const TMatrix<T,ROWS,COLUMNS>& matrix){
    for(int i=0;i<ROWS;++i){
        for(int j=0;j<COLUMNS-1;++j){
            ostr<<matrix(i,j)<<' ';
        }
        ostr<<matrix(i,COLUMNS-1)<<endl;
    }
    return ostr;
}

int main(){
    TMatrix<double,2,2> matrix1;
    TMatrix<double,2,2>matrix2;
    matrix1.Fill(6.0);
    matrix2.Fill(3);
    matrix1(1,0)=5.0;
    matrix1(1,1)=7.0;
    matrix1(0,1)=11.0;
    cout<<"matrix1:"<<endl<<matrix1<<endl;
    cout<<"matrix2:"<<endl<<matrix2<<endl;
    double n=matrix1.Det(matrix1);
    cout<<"Det of matrix1:"<<n<<endl;
    matrix1+=matrix2;
    cout<<"Sum of matrix1 and matrix2:"<<endl<<matrix1<<endl;
    
    TMatrix<int,3,1>matrix4;
    TMatrix<int,1,3>matrix5; 
    matrix4.Fill(2);
    matrix5=matrix4.Transposed();
    cout<<"matrix4:"<<endl<<matrix4<<endl;
    cout<<"Transposed matrix4:"<<endl<<matrix5<<endl;

    clock_t time;
    TMatrix<int,512,512>matrix6,matrix7,matrix8,matrix9;
    matrix6.Fill_rand();
    matrix7.Fill_rand();
    time=clock();
    matrix9=matrix7*matrix6;
    cout<<"Time of usual multiplication: "<<(double)(clock()-time)/CLOCKS_PER_SEC<<endl;
    time=clock();
    matrix8=matrix7.Multiplication_Shtrassen(matrix6);
    cout<<"Time of shtrassen multiplication: "<<(double)(clock()-time)/CLOCKS_PER_SEC<<endl;
    if(matrix8==matrix9){
		cout<<"Shtrassen's algorithm works correctly"<<endl;
	}else{
		cout<<"Shtrassen's algorithm doesn't work correctly"<<endl;
	}
    return 0;
}
