#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

template<class T>
class TPoint{
public:
    T _x;
    T _y;
    
    TPoint(){
        this->_x=T();
        this->_y=T();
    }

    TPoint(const T& x,const T& y){
        this->_x=x;
        this->_y=y;
    }

    TPoint<T> operator-(const TPoint<T>& p) const{
        TPoint<T> res;
        res._x=this->_x-p._x;
        res._y=this->_y-p._y;
        return res;
    }

    TPoint<T>& operator=(const TPoint<T>& p){
        this->_x=p._x;
        this->_y=p._y;
        return *this;
    }
    
    T operator*(const TPoint<T>& p) const {
        return (this->_x*p._y-p._x*this->_y);
    }
};

template<class U,class V>
class Compare{
public:
    bool operator ()(const pair<U,V>& pa1,const pair<U,V>& pa2) const{
        return pa1.first>pa2.first;
    }
};

template <class T>
vector<TPoint<T> > MakeConvexHull(vector<pair<float,TPoint<T> > >& arr){
    for(size_t i=1;i<arr.size();++i){
        if(arr[i].second._y<=arr[0].second._y){
            if(arr[i].second._y<arr[0].second._y){
                swap(arr[i],arr[0]);
            }else{
                if(arr[i].second._x<arr[0].second._x){
                    swap(arr[i],arr[0]);
                }
            }
        }
    }

    for(size_t i=1;i<arr.size();++i){
        TPoint<T> p=arr[i].second-arr[0].second;
        if(p._y!=0){
            arr[i].first=((float)p._x)/p._y;
        }else{
            arr[i].first=numeric_limits<float>::max();
        }
    }
    
    arr[0].first=-numeric_limits<float>::max();
    Compare<float,TPoint<T> > compare;
    sort(arr.begin(),arr.end(),compare);

    pair<float,TPoint<T> > pa=arr[arr.size()-1];
    for(int i=(int)arr.size()-1;i>0;--i){
        arr[i]=arr[i-1];
    }
    arr[0]=pa;

    vector<TPoint<T> > arr_dop,res;
    float f=arr[0].first;
    for(size_t i=0;i<arr.size();++i){
        if(arr_dop.empty()){
            arr_dop.push_back(arr[i].second);
        }else{
            if(arr[i].first==f){
                if(arr[i].second._x>arr_dop[arr_dop.size()-1]._x){
                    arr_dop[arr_dop.size()-1]=arr[i].second;
                }
            }else{
                arr_dop.push_back(arr[i].second);
                f=arr[i].first;
            }
        }
    }

    res.push_back(arr_dop[0]);
    res.push_back(arr_dop[1]);
    for(size_t i=2;i<arr_dop.size();++i){
        while(res.size()>2 && (res[res.size()-1]-res[res.size()-2])*(arr_dop[i]-res[res.size()-1])<0){
            res.pop_back();
        }
        res.push_back(arr_dop[i]);
    }
    return res;
}

int main(){
    int n,x,y;
    cin>>n;
    vector<pair<float,TPoint<int> > > arr(n);
    for(int i=0;i<n;++i){
        cin>>x>>y;
        arr[i].second._x=x;
        arr[i].second._y=y;
    }
    vector<TPoint<int> > res=MakeConvexHull(arr);
    cout<<endl<<"Points:"<<endl;
    for(size_t i=0;i<res.size();++i){
        cout<<res[i]._x<<"\t"<<res[i]._y<<endl;
    }
	return 0;
}