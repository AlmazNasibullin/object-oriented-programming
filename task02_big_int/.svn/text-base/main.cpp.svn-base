#include <iostream>
#include <vector>
using namespace std;

class TBigUint{
private:
	static const long int BASE=10000;
	vector<int> a;
public:
	TBigUint():a(0){
	}
	template <class T>
	TBigUint(T x){
		if(!x){
			a.push_back(0);
			return;
		}
		while(x!=0){
			a.push_back(x%BASE);
			x/=BASE;
		}
	}
	TBigUint(const TBigUint& x){
		a=x.a;
	}

    TBigUint& operator=(const TBigUint& x){
		a=x.a;
		return *this;
    }

	friend ostream& operator<<(ostream& ostr,const TBigUint& x);
    
    bool operator>=(const TBigUint& b){
        int size_a=this->a.size(),size_b=b.a.size();
        if(size_a>size_b){
            return true;
        }
        if(size_b>size_a){
            return false;
        }
        typedef vector<int>::const_reverse_iterator TIter_reverse;
        TIter_reverse aB=this->a.rbegin();
        TIter_reverse aE=this->a.rend();
        TIter_reverse bB=b.a.rbegin();
        while(aB!=aE){
            if(*aB>*bB){
                return true;
            }
            if(*bB>*aB){
                return false;
            }
            ++aB;
            ++bB;
        }
        return true;
    }

    bool operator<=(const TBigUint& b){
        int size_a=this->a.size(),size_b=b.a.size();
        if(size_a<size_b){
            return true;
        }
        if(size_b<size_a){
            return false;
        }
        for(int i=size_a-1;i>=0;--i){
            if(b.a[i]>this->a[i]){
                return true;
            }
            if(b.a[i]<this->a[i]){
                return false;
            }
        }
        return true;
    }

    bool operator==(const TBigUint& b){
        if(*this<=b && *this>=b){
            return true;
        }
        return false;
    }

    bool operator!=(const TBigUint& b){
        if(*this==b){
            return false;
        }
        return true;
    }

    bool operator<(const TBigUint&b){
        if(*this<=b && *this!=b){
            return true;
        }
        return false;
    }
    
    bool operator>(const TBigUint&b){
        if(*this>=b && *this!=b){
            return true;
        }
        return false;
    }

    TBigUint operator+(const TBigUint& b){//сложность О(n)
	    TBigUint result;
	    int carry=0;
	    typedef vector<int>::const_iterator TIter;
	    TIter aIter=this->a.begin();
	    TIter aEnd=this->a.end();
	    TIter bIter=b.a.begin();
	    TIter bEnd=b.a.end();
	    while(aIter!=aEnd || bIter!=bEnd){
		    int sum;
		    if(aIter!=aEnd && bIter!=bEnd){
			    sum=*aIter+*bIter+carry;
			    ++aIter;
			    ++bIter;
		    }else if(aIter!=aEnd){
			    sum=*aIter+carry;
			    ++aIter;
		    }else{
			    sum=*bIter+carry;
			    ++bIter;
		    }
		    result.a.push_back(sum%result.BASE);
		    carry=sum/result.BASE;
	    }
	    if(carry>0)
		    result.a.push_back(carry);
	    return result;
    }

    TBigUint operator-(const TBigUint& b){//сложность О(n)
        TBigUint result;
        int carry1=0,carry2=0;
        if(*this>=b){
            for(size_t i=0;i<this->a.size();++i){
		        int sum;
                if(i<b.a.size()){
                    if(this->a[i]-carry1<b.a[i]){
                        carry2=1;
                        sum=(this->a[i]-carry1+carry2*result.BASE)-b.a[i];
                    }else{
                        carry2=0;
                        sum=this->a[i]-carry1-b.a[i];
                    }
                    carry1=carry2;
                }else{
                    if(this->a[i]-carry1<0){
                        carry2=1;
                        sum=this->a[i]-carry1+carry2*result.BASE;
                    }else{
                        carry2=0;
                        sum=this->a[i]-carry1;
                    }
                    carry1=carry2;
		        }
		        result.a.push_back(sum);
	        }
        }else{
            for(size_t i=0;i<b.a.size();++i){
		        int sum;
                if(i<this->a.size()){
                    if(b.a[i]-carry1<this->a[i]){
                        carry2=1;
                        sum=(b.a[i]-carry1+carry2*result.BASE)-this->a[i];
                    }else{
                        carry2=0;
                        sum=b.a[i]-carry1-this->a[i];
                    }
                    carry1=carry2;
                }else{
                    if(b.a[i]-carry1<0){
                        carry2=1;
                        sum=b.a[i]-carry1+carry2*result.BASE;
                    }else{
                        carry2=0;
                        sum=b.a[i]-carry1;
                    }
                    carry1=carry2;
		        }
		        result.a.push_back(sum);
            }
            for(size_t i=0;i<result.a.size();++i){
                result.a[i]=9999-result.a[i];
            }
        }
        for(size_t i=result.a.size()-1;i>0;--i){
            if(result.a[i]==0){
                result.a.pop_back();
            }else{
                break;
            }
        }
	    return result;
    }

    TBigUint operator*(const TBigUint& b){//сложность О(n^2),т.к.идет n раз суммирование,а сложность суммирования-О(n)
        TBigUint res1,res2=0;
        int carry=0;
	    typedef vector<int>::const_iterator TIter;
	    TIter aIter=this->a.begin();
	    TIter aEnd=this->a.end();
	    TIter bIter=b.a.begin();
	    TIter bEnd=b.a.end();

        vector<int>::const_reverse_iterator a1,b1;
        a1=this->a.rbegin();
        b1=b.a.rbegin();
        if(*a1==0 && *aIter==0 || *b1==0 && *bIter==0){
            return res2;
        }
        int count=-1;
        for(TIter itr1=bIter;itr1!=bEnd;++itr1){
            for(TIter itr2=aIter;itr2!=aEnd;++itr2){
                int sum;
                sum=(*itr1)*(*itr2)+carry;
                res1.a.push_back(sum%res1.BASE);
                carry=sum/res1.BASE;
            }
            if(carry>0){
                res1.a.push_back(carry);
            }
            ++count;
            res2=res2+res1;
            res1=0;
            for(int i=0;i<count;++i){
                res1.a.push_back(0);
            }
        }
        return res2;
    }
    
    template <class T>
    TBigUint operator*(T x){
        TBigUint tmp(x),res;
        res=*this*tmp;
        return res;
    }
    
    TBigUint operator/(const TBigUint& b){
        TBigUint n(0);
        if(n==b){
            cout<<"Error: division by 0!"<<endl;
            exit(1);
        }
        TBigUint res,curValue(*this);
        if(*this<b){
            res=0;
            return res;
        }
        int size_c=(int)curValue.a.size();
        int size_b=(int)b.a.size();
        while(curValue>=b){
            TBigUint b_copy(b);
            if(curValue.a[size_c-1]>=b.a[size_b-1]){
                for(int i=0;i<size_c-size_b;++i){
                    b_copy=b_copy*b_copy.BASE;
                }
            }else{
                for(int i=0;i<size_c-size_b-1;++i){
                    b_copy=b_copy*b_copy.BASE;
                }
            }
            int x=0,l=0,r=b_copy.BASE;
            while(l<=r){
                int m=(l+r)>>1;
                TBigUint cur=b_copy*m;
                if(cur<=curValue){
                    x=m;
                    l=m+1;
                }else{
                    r=m-1;
                }
            }
            res.a.resize(res.a.size()+1);
            for(int i=(int)res.a.size()-1;i>0;--i){
                res.a[i]=res.a[i-1];
            }
            res.a[0]=x;
            if(curValue==b_copy*x){
                for(int i=0;i<(int)b_copy.a.size()-(int)b.a.size();++i){
                    res.a.resize(res.a.size()+1);
                    for(int i=(int)res.a.size()-1;i>0;--i){
                        res.a[i]=res.a[i-1];
                    }
                    res.a[0]=0;
                }
                return res;
            }
            curValue-=b_copy*x;
            if(curValue>=b){
                for(int i=0;i<size_c-(int)curValue.a.size()-1;++i){
                    res.a.resize(res.a.size()+1);
                    for(int i=(int)res.a.size()-1;i>0;--i){
                        res.a[i]=res.a[i-1];
                    }
                    res.a[0]=0;
                }
                if(curValue.a[(int)curValue.a.size()-1]<b.a[size_b-1] && size_c-(int)curValue.a.size()>0){
                    res.a.resize(res.a.size()+1);
                    for(int i=(int)res.a.size()-1;i>0;--i){
                        res.a[i]=res.a[i-1];
                    }
                    res.a[0]=0;
                }
            }
            size_c=(int)curValue.a.size();
        }
        return res;
    }

    TBigUint& operator+=(const TBigUint& x){//аналогично суммированию сложность O(n)
		*this=*this+x;
		return *this;
	}

	TBigUint& operator-=(const TBigUint& x){//аналогично вычитанию сложность O(n)
		*this=*this-x;
		return *this;
	}

	TBigUint& operator*=(const TBigUint& x){
		*this=*this*x;
		return *this;
	}
    
    TBigUint& operator++(){
        *this=*this+1;
        return *this;
    }

    const TBigUint operator++(int){
        TBigUint x=*this;
        *this=*this+1;
        return x;
    }

    TBigUint& operator--(){
        *this=*this-1;
        return *this;
    }

    const TBigUint operator--(int){
        TBigUint x=*this;
        *this=*this-1;
        return x;
    }
};

ostream& operator<<(ostream& ostr,const TBigUint& x){
    for(vector<int>::const_reverse_iterator it=x.a.rbegin();it!=x.a.rend();++it){
        char buf[10];
		if(it==x.a.rbegin()){
		    ostr<<*it;
		}else{
			sprintf(buf,"%04d",*it);
			ostr<<buf;
		}
	}
	return ostr;
}

int main(){
	TBigUint big1(1200);
	TBigUint big2(250);
    TBigUint big3=big1+big2;
    cout<<big1<<"+"<<big2<<"="<<big3<<endl;
    big3=big1-big2;
    cout<<big1<<"-"<<big2<<"="<<big3<<endl;
    big3=big1*big2;
    cout<<big1<<"*"<<big2<<"="<<big3<<endl;
    big2=0;
    big3=big1*big2;
    cout<<big1<<"*"<<big2<<"="<<big3<<endl;

    big1=1923440019234400;
	big2=19234400;
    big3=big1/big2;
    cout<<big3<<endl;
    big3=20000;
    big1=++big3;
    cout<<"Prefics addition"<<endl<<"big1="<<big1<<endl;
    --big3;
    big1=big3++;
    cout<<"Postfics addition"<<endl<<"big1="<<big1<<endl;
    return 0;
}