#include <iostream>
#include <queue>
#include <ctime>
#include <cstdlib>
#include <set>
using namespace std;

enum EColour{
    C_BLACK,
    C_RED,
};

template<typename T>
struct TNode{
    TNode<T>* _parent;
    TNode<T>* _left;
    TNode<T>* _right;
    EColour _color;
    T _key;
    TNode(TNode<T>* parent=NULL,TNode<T>* left=NULL,TNode<T>* right=NULL,EColour color=C_BLACK,T key=T()):
		_parent(parent),_left(left),_right(right),_color(color),_key(key){}
};

template<typename T,typename TCompare=std::less<T> >
class TRBTree{
private:
    TNode<T>* _root;
    TCompare _cmp;
    int _size;
    friend class TRBTreeIterator;
    friend class TRBTreeConstIterator;
    void Minimum(TNode<T>* &x) const{
        while(x && x->_left){
            x=x->_left;
        }
    }

    void Maximum(TNode<T>* &x) const{
        while(x && x->_right){
            x=x->_right;
        }
    }

    void Successor(TNode<T>* &x) const{
        if(x){
            if(x->_right){
                x=x->_right;
                Minimum(x);
            }else{
                while(x->_parent && x!=x->_parent->_left){
                    x=x->_parent;
                }
                x=x->_parent;
            }
        }
    }
    
    void Predecessor(TNode<T>* &x) const{
        if(x){
            if(x->_left){
                x=x->_left;
                Minimum(x);
            }else{
                while(x->_parent && x!=x->_parent->_right){
                    x=x->_parent;
                }
                x=x->_parent;
            }
        }
    }

    void RightRotate(TNode<T>* x){
        if(!x || !x->_left){
            return;
        }
        TNode<T>* y=x->_left;
        x->_left=y->_right;
        if(x->_left){
            x->_left->_parent=x;
        }
        y->_parent=x->_parent;
        if(!x->_parent){
			_root=y;
		}else if(x==x->_parent->_right){
			x->_parent->_right=y;
		}else{
			x->_parent->_left=y;
		}
		y->_right=x;
		x->_parent=y;
    }

    void LeftRotate(TNode<T>* x){
        if(!x || !x->_right){
            return;
        }
        TNode<T>* y=x->_right;
        x->_right=y->_left;
        if(x->_right){
			x->_right->_parent=x;
        }
        y->_parent=x->_parent;
        if(!x->_parent){
			_root=y;
		}else if(x==x->_parent->_left){
			x->_parent->_left=y;
		}else{
			x->_parent->_right=y;
		}
		y->_left=x;
		x->_parent=y;
    }
    
    void InsertFixup(TNode<T>* x){
        while(x->_parent && x->_parent->_color==C_RED){
            if(x->_parent==x->_parent->_parent->_left){
                TNode<T>* y=x->_parent->_parent->_right;
                if(y && y->_color==C_RED){
                    x->_parent->_color=C_BLACK;
                    y->_color=C_BLACK;
                    x->_parent->_parent->_color=C_RED;
                    x=x->_parent->_parent;
                }else{
                    if(x==x->_parent->_right){
                        x=x->_parent;
                        LeftRotate(x);
                    }
                    x->_parent->_color=C_BLACK;
                    x->_parent->_parent->_color=C_RED;
                    RightRotate(x->_parent->_parent);
                }
            }else{
                TNode<T>* y=x->_parent->_parent->_left;
                if(y && y->_color==C_RED){
                    x->_parent->_color=C_BLACK;
                    y->_color=C_BLACK;
                    x->_parent->_parent->_color=C_RED;
                    x=x->_parent->_parent;
                }else{
                    if(x==x->_parent->_left){
                        x=x->_parent;
                        RightRotate(x);
                    }
                    x->_parent->_color=C_BLACK;
                    x->_parent->_parent->_color=C_RED;
                    LeftRotate(x->_parent->_parent);
                }
            }
        }
		_root->_color=C_BLACK;
    }
	
	void EraseFixup(TNode<T>* x,TNode<T>* y){
		while((!x && _root) || (x != _root && x->_color == C_BLACK)){
			if(x==y->_left){
				TNode<T>* w;
				w=y->_right;
				if(w && w->_color==C_RED){
					w->_color=C_BLACK;
                    y->_color=C_RED;
                    LeftRotate(y);
                    w=y->_right;
                }
                if((!w->_left || w->_left->_color==C_BLACK) && (!w->_right || w->_right->_color==C_BLACK)){
					w->_color=C_RED;
					x=y;
					y=y->_parent;
				}else{
					if(!w->_right || w->_right->_color==C_BLACK){
						w->_left->_color=C_BLACK;
						w->_color=C_RED;
						RightRotate(w);
						w=y->_right;
					}
					w->_color=y->_color;
					y->_color=C_BLACK;
					if(w->_right){
						w->_right->_color=C_BLACK;
					}
					LeftRotate(y);
					x=_root;
				}
			}else{
				TNode<T>* w;
				w=y->_left;
				if(w && w->_color==C_RED){
					w->_color=C_BLACK;
                    y->_color=C_RED;
                    RightRotate(y);
                    w=y->_left;
                }
                if((!w->_right || w->_right->_color==C_BLACK) && (!w->_left || w->_left->_color==C_BLACK)){
					w->_color=C_RED;
					x=y;
					y=y->_parent;
				}else{
					if(!w->_left || w->_left->_color==C_BLACK){
						w->_right->_color=C_BLACK;
						w->_color=C_RED;
						LeftRotate(w);
						w=y->_left;
					}
					w->_color=y->_color;
					y->_color=C_BLACK;
					if(w->_left){
						w->_left->_color=C_BLACK;
					}
					RightRotate(y);
					x=_root;
				}
			}
		}
		if(x){
			x->_color=C_BLACK;
		}
	}
	
public:
    TRBTree():_root(NULL),_cmp(),_size(0){}
    
    TRBTree(const TRBTree<T>& tr):_root(NULL),_cmp(tr._cmp),_size(0){
        for(TRBTree<T>::TRBTreeConstIterator itr=tr.Begin();itr!=tr.End();++itr){
            this->Insert(*itr);
        }        
	}
	
	TRBTree<T> &operator=(const TRBTree<T>& tr){
		Clear();
        for(TRBTree<T>::TRBTreeConstIterator itr=tr.Begin();itr!=tr.End();++itr){
            Insert(*itr);
        }
        return *this;
	}
    
    ~TRBTree(){
		Clear();
	}
	
	void Swap(TRBTree<T>& tr){
		swap(_root,tr._root);
        swap(_cmp,tr._cmp);
        swap(_size,tr._size);
    }
	
    class TRBTreeIterator{
		TNode<T>* _node;
		TRBTree<T>* _tr;
		friend class TRBTree;
	public:
		TRBTreeIterator(){
			_node=NULL;
		}
		
		TRBTreeIterator (const TRBTreeIterator& itr){
			_node=itr._node;
			_tr=itr._tr;
		}
		
		TRBTreeIterator (TNode<T>* node,TRBTree<T>* tr): _node(node),_tr(tr){}
		
		TRBTreeIterator& operator ++(){
			_tr->Successor(_node);
			return *this;
		}
		
		const TRBTreeIterator operator ++(int){
			TRBTreeIterator itr(*this);
			++*this;
			return itr;
		}
		
		TRBTreeIterator& operator --(){
			_tr->Predecessor(_node);
			return *this;
		}
		
		const TRBTreeIterator operator --(int){
			TRBTreeIterator itr(*this);
			--*this;
			return itr;
		}
		
		T& operator *(){
			return _node->_key;
		}
		
		bool operator ==(const TRBTreeIterator& itr){
			return _node==itr._node && _tr==itr._tr;
		}
		
		bool operator !=(const TRBTreeIterator& itr){
			return _node!=itr._node || _tr!=itr._tr;
		}
		
		TRBTreeIterator& operator=(const TRBTreeIterator& itr){
			_node=itr._node;
			_tr=itr._tr;
			return *this;
		}
	};

    class TRBTreeConstIterator{
        TNode<T>* _node;
		const TRBTree<T>* _tr;
		friend class TRBTree;
	public:
		TRBTreeConstIterator(){
			_node=NULL;
		}
		
		TRBTreeConstIterator (const TRBTreeConstIterator& itr){
			_node=itr._node;
			_tr=itr._tr;
		}
		
		TRBTreeConstIterator (TNode<T>* node,const TRBTree<T>* tr): _node(node),_tr(tr){}
		
		TRBTreeConstIterator& operator ++(){
			_tr->Successor(_node);
			return *this;
		}
		
		const TRBTreeConstIterator operator ++(int){
			TRBTreeConstIterator itr(*this);
			++*this;
			return itr;
		}
		
		TRBTreeConstIterator& operator --(){
			_tr->Predecessor(_node);
			return *this;
		}
		
		const TRBTreeConstIterator operator --(int){
			TRBTreeConstIterator itr(*this);
			--*this;
			return itr;
		}
		
		const T& operator *(){
			return _node->_key;
		}
		
		bool operator ==(const TRBTreeConstIterator& itr) const{
			return _node==itr._node && _tr==itr._tr;
		}
		
		bool operator !=(const TRBTreeConstIterator& itr) const{
			return _node!=itr._node || _tr!=itr._tr;
		}
		
		TRBTreeIterator& operator=(const TRBTreeConstIterator& itr){
			_node=itr._node;
			_tr=itr._tr;
			return *this;
		}
	};
    
    TRBTreeIterator Begin(){
		TNode<T>* x(_root);
		Minimum(x);
		return TRBTreeIterator(x,this);
    }
    
    TRBTreeConstIterator Begin() const{
		TNode<T>* x(_root);
        Minimum(x);
		return TRBTreeConstIterator(x,this);
    }

    TRBTreeIterator End(){
		return TRBTreeIterator(NULL,this);
    }
    
    TRBTreeConstIterator End() const{
		return TRBTreeConstIterator(NULL,this);
    }

    bool Empty(){
		return _size==0;
	}
	
    void Clear(){
		if(_root){
			queue<TNode<T>* > q;
			q.push(_root);
			while(!q.empty()){
				TNode<T>* temp=q.front();
				q.pop();
				if(temp->_left){
					q.push(temp->_left);
				}
				if(temp->_right){
					q.push(temp->_right);
				}
				delete temp;
			}
            _size=0;
            _root=NULL;
		}
	}
    
    TRBTreeIterator Find(const T& key){
		TNode<T>* x(_root);
        while(x && (_cmp(x->_key,key) || _cmp(key,x->_key))){
			if(_cmp(key,x->_key)){
                x=x->_left;
            }else{
                x=x->_right;
            }
        }
        return TRBTreeIterator(x,this);
    }
    
    TRBTreeConstIterator Find(const T& key) const{
		TNode<T>* x(_root);
        while(x && (_cmp(x->_key,key) || _cmp(key,x->_key))){
			if(_cmp(key,x->_key)){
                x=x->_left;
            }else{
                x=x->_right;
            }
        }
        return TRBTreeConstIterator(x,this);
    }

    void Insert(const T& key){
		TRBTreeIterator itr;
        itr=Find(key);
        if(itr==End()){
			TNode<T>* x1(NULL);
			TNode<T>* x2=_root;
			while(x2){
				x1=x2;
				if(_cmp(key,x2->_key)){
					x2=x2->_left;
				}else{
					x2=x2->_right;
				}
			}
			TNode<T>* x=new TNode<T>();
			x->_key=key;
			x->_parent=x1;
			x->_color=C_RED;
			if(!x1){
				_root=x;
			}else{
				if(_cmp(x->_key,x1->_key)){
					x1->_left=x;
				}else{
					x1->_right=x;
				}
			}
			InsertFixup(x);
			++_size;
		}
    }
    
    void Erase(const T& key){
        TNode<T>* z(NULL);
        TRBTreeIterator itr;
        itr=Find(key);
        if(itr!=End()){
			z=itr._node;
		}
        if(z){
            TNode<T> *y,*x;
            if(!z->_left || !z->_right){
                y=z;
            }else{
                y=z;
                Successor(y);
            }
            if(y->_left){
                x=y->_left;
            }else{
                x=y->_right;
            }
            if(x){
                x->_parent=y->_parent;
            }
			if(!y->_parent){
                _root=x;
            }else{
                if(y==y->_parent->_left){
                    y->_parent->_left=x;
                }else{
                    y->_parent->_right=x;
                }
            }
            if(y!=z){
                z->_key=y->_key;
            }
            if(y->_color==C_BLACK){
                EraseFixup(x,y->_parent);
            }
            delete y;
            --_size;
		}
    }
	
    void PrintTreeStruct(){
		if(_root){
			queue<TNode<T>* > q;
			q.push(_root);
			while(!q.empty()){
				TNode<T>* temp=q.front();
				q.pop();
				if(temp->_left){
					q.push(temp->_left);
				}
				if(temp->_right){
					q.push(temp->_right);
				}
            
				cout<<temp->_key;
				if(temp->_color==C_BLACK){
					cout<<" BLACK ";
				}else{
					cout<<" RED ";
				}
            
				if(temp->_left){
					cout<<"left: "<<temp->_left->_key;
				}
            
				if(temp->_right){
					cout<<" right: "<<temp->_right->_key;
				}
            
				if(temp->_parent){
					cout<<" parent: "<<temp->_parent->_key;
				}else{
					cout<<" i'm a root";
				}
				cout<<endl;
			}
		}else{
			cout<<"Tree is empty"<<endl;
		}
	}
	
	int Size(){
		return _size;
	}
};

int main(){
    srand((unsigned int)time(0));
    TRBTree<int> tree;
    set<int> s;
    int arr[5];
    cout<<"Elements of tree:"<<endl;
    for(int i=0;i<5;++i){
        arr[i]=rand()%100;
        cout<<arr[i]<<" ";
        tree.Insert(arr[i]);
        s.insert(arr[i]);
    }
    cout<<endl;
    tree.Insert(11);
    TRBTree<int> tree1(tree);
    if(tree.Find(11)!=tree.End()){
		cout<<"Find works correctly"<<endl;
	}else{
		cout<<"Find doesn't work correctly"<<endl;
	}
    cout<<endl;
    tree.Erase(11);
    
    cout<<"Vertices in the order of traversal in tree:"<<endl;
    for(TRBTree<int>::TRBTreeIterator itr=tree.Begin();itr!=tree.End();++itr){
		cout<<*itr<<" ";
	}
	cout<<endl;
	cout<<"Vertices in the order of traversal in set:"<<endl;
    for(set<int>::iterator itr=s.begin();itr!=s.end();++itr){
		cout<<*itr<<" ";
	}
	cout<<endl<<endl;
    
    
    cout<<"Structure of tree:"<<endl;
    tree.PrintTreeStruct();
    cout<<endl;
    int size=tree.Size();
    for(int i=0;i<size;++i){
		tree.Erase(arr[i]);
		cout<<"Structure of tree:"<<endl;
		tree.PrintTreeStruct();
		cout<<endl;
	}
	cout<<endl;
	
	
	cout<<"Structure of tree1:"<<endl;
	tree1.PrintTreeStruct();
	cout<<endl;
	TRBTree<int> tree2;
	for(int i=0;i<10;++i){
		tree2.Insert(rand()%100);
	}
	cout<<"Structure of tree2:"<<endl;
	tree2.PrintTreeStruct();
	cout<<endl;
	cout<<"Swap tree1 and tree2:"<<endl;
	tree1.Swap(tree2);
	cout<<"Structure of tree1:"<<endl;
	tree1.PrintTreeStruct();
	cout<<endl;
	cout<<"Structure of tree2:"<<endl;
	tree2.PrintTreeStruct();

    cout<<endl;//tests
    const int Size=200000;
    int size_my_rbt,size_set;
    int mas[Size];
    for(int i=0;i<Size;++i){
        mas[i]=rand();
    }
    TRBTree<int> my_rbt;
    clock_t t=clock();
    for(int i=0;i<Size;++i){
        my_rbt.Insert(mas[i]);
    }
    cout<<"Insert time of my_rbt: "<<(clock()-t)*1.0/CLOCKS_PER_SEC<<endl;
    size_my_rbt=my_rbt.Size();
    cout<<"Size of my_rbt: "<<size_my_rbt<<endl;
    set<int> ss;
    t=clock();
    for(int i=0;i<Size;++i){
        ss.insert(mas[i]);
    }
    cout<<"Insert time of set: "<<(clock()-t)*1.0/CLOCKS_PER_SEC<<endl;
    size_set=(int)ss.size();
    cout<<"Size of set: "<<size_set<<endl;
    TRBTree<int>::TRBTreeIterator itr1;
    set<int>::const_iterator itr2;
    if(size_my_rbt==size_set){
        for(itr1=my_rbt.Begin(),itr2=ss.begin();
            itr1!=my_rbt.End() && itr2!=ss.end();++itr1,++itr2){
                if(*itr1!=*itr2){
                    cout<<"Data does not match"<<endl;
                    break;
                }
        }
        cout<<"Data matches"<<endl;
    }
    t=clock();
    itr1=my_rbt.Find(mas[5]);
    if(*itr1==mas[5]){
        cout<<"Find time of my_rbt: "<<(clock()-t)*1.0/CLOCKS_PER_SEC<<endl;
    }
    t=clock();
    set<int>::iterator itr3=ss.find(mas[5]);
    if(*itr3==mas[5]){
        cout<<"Find time of set: "<<(clock()-t)*1.0/CLOCKS_PER_SEC<<endl;
    }
    t=clock();
    my_rbt.Clear();
    if(my_rbt.Empty()){
        cout<<"Clear time of my_rbt: "<<(clock()-t)*1.0/CLOCKS_PER_SEC<<endl;
    }
    t=clock();
    ss.clear();
    if(ss.empty()){
        cout<<"Clear time of set: "<<(clock()-t)*1.0/CLOCKS_PER_SEC<<endl;
    }
    return 0;
}