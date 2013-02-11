#include <iostream>
using namespace std;

template<class T>
class TNode{
public:
    TNode<T>* _prev;
    TNode<T>* _next;
    T _value;
    TNode(){
        _prev=NULL;
        _next=NULL;
        _value=T();
    }
    TNode(TNode<T>* next,TNode<T>* prev,T value){
		_next=next;
		_prev=prev;
		_value=value;
	}
    ~TNode(){
    }
};

template<class T> class TList;
template<class T>
class TListIterator{
    TNode<T>* _node;
public:
    friend class TList<T>;
    TListIterator(TNode<T>* n){ 
        _node=n;
    }
    TListIterator(){
        _node=NULL;
    }
    ~TListIterator() {
    }
    TListIterator& operator ++(){
        _node=_node->_next;
        return *this;
    }
    const TListIterator operator ++(int){
        TListIterator<T> itr=*this;
        _node=_node->_next;
        return itr;
    }
    TListIterator& operator --(){
        _node=_node->_prev;
        return *this;
    }
    const TListIterator operator --(int){
        TListIterator<T> itr=*this;
        _node=_node->_prev;
        return itr;
    }
    T& operator *(){
        return _node->_value;
    }
    bool operator ==(const TListIterator& itr){
        return _node==itr._node;
    }
    bool operator !=(const TListIterator& itr) {
        return (_node!=itr._node);
    }
    TListIterator& operator=(const TListIterator& itr){
        _node=itr._node;
        return *this;
    }
};

template<class T>
class TListConstIterator{
	const TNode<T>* _node;
public:
	TListConstIterator(){
		_node=NULL;
	}
	TListConstIterator(const TNode<T>* n){
		_node=n;
	}
	TListConstIterator& operator ++(){
		_node=_node->_next;
		return *this;
	}
	const TListConstIterator operator ++(int){
		TListConstIterator itr=*this;
		_node=_node->_next;
		return itr;
	}
	TListConstIterator& operator --(){
		_node=_node->_prev;
		return *this;
	}
	const TListConstIterator operator --(int){
		TListConstIterator itr=*this;
		_node=_node->_prev;
		return itr;
	}
	const T& operator *(){
		return _node->_val;
	}
	bool operator ==(const TListConstIterator& itr){
		return _node==itr._node;
	}
	bool operator!= (const TListConstIterator& itr){
		return _node!=itr._node;
	}
	TListConstIterator& operator=(TListConstIterator& itr){
		_node=itr._node;
		return *this;
	}
};

template<class T>
class TList{
private:
    TNode<T>* _beg;
    TNode<T>* _end;
public:
    TList(){
        _beg=NULL;
        _end=NULL;
    }
    ~TList(){
        this->Clear();
    }
    bool empty() const{
        return(_beg==NULL);
    }
    T& front(){
        return _beg->_value;
    }
    T& back(){
        return _end->_value;
    }
    const T& front()const{
        return _beg->_value;
    }
    const T& back()const{
        return _end->_value;
    }
    void Clear(){
		if(_beg!=NULL){
			TNode<T>* ptr;
			do{
				ptr=_beg;
				_beg=_beg->_next;
				delete ptr;
			}while(_beg!=_end);
			_beg=NULL;
			_end=NULL;
		}
	}
    void push_front(const T& elem){
        TNode<T>* temp=new TNode<T>(_beg,NULL,elem);
        if(_beg==NULL){
            _beg=temp;
            _end=temp;
			_end->_next=NULL;
        }else{
            _beg->_prev=temp;
            _beg=temp;
        }
    }
    void pop_front(){
        if(_beg==_end){
            delete _beg;
            _beg=NULL;
            _end=NULL;
        }else{
            _beg=_beg->_next;
            delete _beg->_prev;
            _beg->_prev=NULL;
        }
    }
    void push_back(const T& elem){
        TNode<T>* temp=new TNode<T>(NULL,_end,elem);
        if(_beg==NULL){
            _beg=temp;
            _end=temp;
        }else{
            _end->_next=temp;
            _end=temp;
        }
    }
    void pop_back(){
        if(_beg==_end){
            delete _beg;
            _beg=NULL;
            _end=NULL;
        }else{
            _end=_end->_prev;
            delete _end->_next;
            _end->_next=NULL;
        }
    }
    void insert(TListIterator<T>& itr,const T& elem){
       if(itr._node==_beg){
	        TNode<T>* _new=new TNode<T>(_beg,NULL,elem);
			_beg->_prev=_new;
			_beg=_new;
			--itr;
            return;
       }
       if(itr._node==NULL){
			this->push_back(elem);
			--itr;
            return;
       }
       TListIterator<T> ptr=itr--;
       TNode<T>* node=new TNode<T>(ptr._node,itr._node,elem);
	   ptr._node->_prev=node;
	   itr._node->_next=node;
	   ++itr;
    }
    template<class InputIter>
	void insert(TListIterator<T>& itr,InputIter first,InputIter last){
		if(itr._node==_beg)  {
			do{
				--last;
				TNode<T>* _new=new TNode<T>(_beg,NULL,*last);
				_beg->_prev=_new;
				_beg=_new;
			}while(last!=first);
			return;
		}
		if(itr._node==NULL){
			TNode<T>* _new;
			if(_end!=NULL){
				for(;first!=last;++first){
					_new=new TNode<T>(NULL,_end,*first);
					_end->_next=_new;
					_end=_new;
				}
				_end->_next=NULL;
			}else{
				TNode<T>* _new=new TNode<T>(NULL,NULL,*first);
				_beg=_new;
				_end=_new;
				++first;
				for(;first!=last;++first){
					TNode<T>* _new=new TNode<T>(_beg,NULL,*first);
					_end->_next=_new;
					_end=_new;
				}
				_end->_next=NULL;
			}
			return;
		}
		TListIterator<T> ptr=itr--;
		for(;first!=last;++first){
			TNode<T>* res=new TNode<T>(NULL,itr.node,*first);
			itr._node->_next=res;
			++itr;
		}
		itr._node->_next=ptr._node;
		ptr._node->_prev=itr._node;
	}
    void erase(TListIterator<T>& itr){
	    if(_beg==_end){
            ++itr;
    		delete _beg;
            _beg=_end=NULL;
	    }else if(itr._node==NULL){
            this->pop_back();
    	}else if(itr._node==_beg){
            ++itr;
            this->pop_front();
        }else{
    		TNode<T>* next=itr._node->_next;
		    TNode<T>* prev=itr._node->_prev;
            TNode<T>* cur=itr._node;
            ++itr;
		    next->_prev=prev;
		    prev->_next=next;
		    delete cur;
        }
    }
    void erase(TListIterator<T>& itr_beg,TListIterator<T>& itr_end){
		if(itr_beg._node==_beg && itr_end._node==NULL){
			this->Clear();
		}else{
			if(itr_beg._node==_beg){
				_beg=itr_end._node;
				itr_end._node->_prev=NULL;
				TListIterator<T> itr=itr_beg;
				while(itr_beg!=itr_end){
					itr=itr_beg;
					++itr_beg;
					delete itr._node;
				}
			}else if(itr_end._node==NULL){
				_end=itr_beg._node->_prev;
				_end->_next=NULL;
				TListIterator<T> itr=itr_beg;
				while(itr_beg!=itr_end){
					itr=itr_beg;
					++itr_beg;
					delete itr._node;
				}
			}else{
				TListIterator<T> itr=itr_beg--;
				itr_beg._node->_next=itr_end._node;
				itr_end._node->_prev=itr_beg._node;
				while(itr!=itr_end){
					itr_beg=itr;
					++itr;
					delete itr_beg._node;
				}
			}
		}
	}
    TListConstIterator<T> begin() const{
		return TListConstIterator<T>(_beg);
	}
	TListConstIterator<T> end() const{
		return TListConstIterator<T>(NULL);
	}
    TListIterator<T> begin(){
        return TListIterator<T>(_beg);
    }
    TListIterator<T> end(){
        return TListIterator<T>(NULL);
    }
    void swap(TList& list) {
		swap(_beg,list._beg);
		swap(_end,list._end);
	}
};

int main(){
    TList<int> mylist;

    cout<<"Is list empty?";
    if(mylist.empty())
        cout<<" yes"<<endl;
    else
        cout<<"no"<<endl;

    for(int i=-1;i>-6;--i){ 
        mylist.push_front(i);
	}
    for(int i=0;i<6;++i){ 
        mylist.push_back(i);
	}

    TListIterator<int> itr;
    cout<<"Elements:"<<endl;
    for(itr=mylist.begin();itr!=mylist.end();++itr){
        cout<<*itr<<endl;
    }
    if(!mylist.empty()){
        mylist.pop_back();
    }
    if(!mylist.empty()){
        mylist.pop_front();
    }
    cout<<"Elements:"<<endl;
    for(itr=mylist.begin();itr!=mylist.end();++itr){
        cout<<*itr<<endl;
    }
    
    cout<<"First element:"<<mylist.front()<<endl;
    cout<<"Last element:"<<mylist.back()<<endl;

    cout<<"Is list empty?";
    if(mylist.empty())
        cout<<" yes"<<endl;
    else
        cout<<"no"<<endl;
    
    itr=mylist.begin();
    mylist.erase(itr);
    cout<<"First element:"<<mylist.front()<<endl;
    
    mylist.insert(itr,100500);
    cout<<"First element:"<<mylist.front()<<endl;
    return 0;
}