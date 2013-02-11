#include <iostream>
#include <vector>
#include <deque>
#include <list>

using namespace std;

enum EColour{
    C_WHITE,
    C_GRAY,
    C_BLACK,
};

struct TVertexBFS{
    int _depth;
    EColour _colour;
    int _parent;
    TVertexBFS(){
        _colour=C_WHITE;
        _parent=-1;
        _depth=-1;
    }
};

struct TVertexDFS{
    EColour _colour;
    int _parent;
    int _discoverTime;
    int _finishingTime;
    TVertexDFS(){
        _colour=C_WHITE;
        _parent=-1;
        _discoverTime=-1;
        _finishingTime=-1;
    }
};

typedef vector<TVertexBFS> TVerticesBFS;
typedef vector<TVertexDFS> TVerticesDFS;

class TGraph{
private:
    vector<vector<bool> > _adjMatrix;
    int _time;
public:
    TGraph(const vector<vector<bool> >& gr){
         _adjMatrix=vector<vector<bool> >(gr);
    }
	TGraph(const TGraph& gr){
        _adjMatrix=vector<vector<bool> >(gr._adjMatrix);
    }
	
    void BFS(int srcIdx,TVerticesBFS& verticesBFS)const{
        int n=(int)_adjMatrix.size();
        verticesBFS.resize(0);
        verticesBFS.resize(n);
        deque<int> q;
        q.push_back(srcIdx);
        verticesBFS[srcIdx]._colour=C_GRAY;
        verticesBFS[srcIdx]._depth=0;
        while(!q.empty()){
            int head=q.front();
            q.pop_front();
            verticesBFS[head]._colour=C_BLACK;
            for(int i=0;i<n;++i){
                if(_adjMatrix[head][i] && verticesBFS[i]._colour==C_WHITE){
                    q.push_back(i);
                    verticesBFS[i]._colour=C_GRAY;
                    verticesBFS[i]._depth=verticesBFS[head]._depth+1;
                    verticesBFS[i]._parent=head;
                }
            }
        }
    }

    void DFS_visit(int srcIdx,TVerticesDFS& verticesDFS){
        int n=(int)_adjMatrix.size();
        verticesDFS[srcIdx]._colour=C_GRAY;
        verticesDFS[srcIdx]._discoverTime=++_time;
        for(int i=0;i<n;++i){
            if(_adjMatrix[srcIdx][i] && verticesDFS[i]._colour==C_WHITE){
                verticesDFS[i]._parent=srcIdx;
                DFS_visit(i,verticesDFS);
            }
        }
        verticesDFS[srcIdx]._colour=C_BLACK;
        verticesDFS[srcIdx]._finishingTime=++_time;
    }

    void DFS(TVerticesDFS& verticesDFS){
        int n=(int)_adjMatrix.size();
        verticesDFS.resize(0);
        verticesDFS.resize(n);
        _time=0;
        for(int i=0;i<n;++i){
            if(verticesDFS[i]._colour==C_WHITE){
                DFS_visit(i,verticesDFS);
            }
        }
    }

    void TopSort_visit(int srcIdx,list<int>& l,vector<bool>& color){
        int n=(int)_adjMatrix.size();
        for(int i=0;i<n;++i){
            if (_adjMatrix[srcIdx][i] && !color[i]){
                color[i]=true;
                TopSort_visit(i,l,color);
                l.push_front(i);
            }
        }
    }

    void TopSort(list<int>& l){
        int n=(int)_adjMatrix.size();
        vector<bool> color(n);
        l.clear();
        for(int i=0;i<n;++i){
            if(!color[i]){
                color[i]=true;
                TopSort_visit(i,l,color);
                l.push_front(i);
            }
        }
    }

    TGraph Transpose(){
        TGraph gr(*this);
        int n=(int)_adjMatrix.size();
        for(int i=0;i<n;++i){
            for(int j=0;j<i;++j){
                bool b=gr._adjMatrix[i][j];
                gr._adjMatrix[i][j]=gr._adjMatrix[j][i];
                gr._adjMatrix[j][i]=b;
            }
        }
        return gr;
    }

    void SCC(vector<list<int> >& scc){
        int n=(int)_adjMatrix.size();
        vector<bool> color(n);
        scc.clear();
        list<int> ts,l;
        TopSort(ts);
        TGraph gr=Transpose();
        for(list<int>::const_iterator iter=ts.begin();iter!=ts.end();++iter){
            if(!color[*iter]){
                l.clear();
                color[*iter]=true;
                for (int i=0;i<n;++i){
                    if(gr._adjMatrix[*iter][i] && !color[i]){
                        color[i]=true;
                        gr.TopSort_visit(i,l,color);
                        l.push_front(i);
                    }
                }
                l.push_front(*iter);
                scc.push_back(l);
            }
        }
    }
};

int main(){
    int n,m;
    vector<vector<bool> > arr;
    cin>>n>>m;
    arr.resize(n);
    for(int i=0;i<n;++i){
        arr[i].resize(n);
    }
    int v1,v2;
    for(int i=0;i<m;++i){
        cin>>v1>>v2;
        arr[v1-1][v2-1]=true;
    }
    TGraph gr(arr);

    TVerticesBFS verticesBFS;//BFS
    gr.BFS(0,verticesBFS);
    cout<<endl<<"BFS:"<<endl;
    for(int i=0;i<(int)verticesBFS.size();++i){
        if(i!=0){
            if(verticesBFS[i]._parent>-1){
                cout<<i+1<<": depth="<<verticesBFS[i]._depth<<"\tparent="<<verticesBFS[i]._parent+1<<endl;
            }else{
                cout<<i+1<<" is undiscovered"<<endl;
            }
        }else{
            cout<<"1: depth="<<verticesBFS[i]._depth<<endl;
        }
    }

    TVerticesDFS verticesDFS;//DFS
    gr.DFS(verticesDFS);
    cout<<endl<<"DFS:"<<endl;
    for(int i=0;i<(int)verticesDFS.size();++i){
        if(verticesDFS[i]._parent>-1){
            cout<<i+1<<": dTime="<<verticesDFS[i]._discoverTime<<"\tfTime="<<verticesDFS[i]._finishingTime<<"\tparent="<<verticesDFS[i]._parent+1<<endl;
        }else{
            cout<<i+1<<": dTime="<<verticesDFS[i]._discoverTime<<"\tfTime="<<verticesDFS[i]._finishingTime<<"\tno parent"<<endl;
        }
    }

    list<int> l;//TopSort
    gr.TopSort(l);
	cout<<endl<<"TopSort:"<<endl;
    for(list<int>::const_iterator iter=l.begin();iter!=l.end();++iter){
        cout<<*iter+1<<" ";
    }
    cout<<endl;

    vector<list<int> > scc;//SCC
    gr.SCC(scc);
    cout<<endl<<"SCC:"<<endl;
    for(int i=0;i<(int)scc.size();++i){
        for(list<int>::const_iterator iter=scc[i].begin();iter!=scc[i].end();++iter){
            cout<<*iter+1<<" ";
        }
        cout<<endl;
    }
    return 0;
}
