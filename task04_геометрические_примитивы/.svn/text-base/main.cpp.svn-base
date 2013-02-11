#include <iostream>
#include <vector>
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

template<class T>
class TSegment{
public:    
    TPoint<T> _p1;
    TPoint<T> _p2;

    TSegment(){
        this->_p1._x=T();
        this->_p1._y=T();
        this->_p2._x=T();
        this->_p2._y=T();
    }

    TSegment(const TPoint<T> p1,const TPoint<T> p2){
        this->_p1._x=p1._x;
        this->_p1._y=p1._y;
        this->_p2._x=p2._x;
        this->_p2._y=p2._y;
    }

    TSegment<T>& operator=(const TSegment<T>& s){
        this->_p1=s._p1;
        this->_p2=s._p2;
        return *this;
    }
    
    bool onSegment(const TPoint<T>& p) const{
        return min(this->_p1._x,this->_p2._x)<=p._x && max(this->_p1._x,this->_p2._x)>=p._x && 
            min(this->_p1._y,this->_p2._y)<=p._y && max(this->_p1._y,this->_p2._y)>=p._y;
    }

    T din(const TPoint<T>& p) const{
        T res=(this->_p2-this->_p1)*(p-this->_p1);
        return res;
    }

    bool hasPoint(const TPoint<T>& p) const{
        T d=(*this).din(p);
        if(d==0 && this->onSegment(p)){
            return true;
        }
        return false;
    }

    bool segmentsIntersect(const TSegment<T>& s) const{
        T d1=s.din(this->_p1);
        T d2=s.din(this->_p2);
        T d3=this->din(s._p1);
        T d4=this->din(s._p2);
        if(d1*d2<0 && d3*d4<0){
            return true;
        }
        if(s.hasPoint(this->_p1) || s.hasPoint(this->_p2) ||
            this->hasPoint(s._p1) || this->hasPoint(s._p2)){
                return true;
        }
        return false;
    }
};

template<class T>
class TPolygon{
private:
    vector<TPoint<T> > _vertices;
public:
    TPolygon(int size,TPoint<T>* vertices){
        for(int i=0;i<size;++i){
            _vertices.push_back(vertices[i]);
        }
    }

    TPolygon<T>& operator=(const TPolygon<T>& t){
        _vertices=t._vertices;
    }
    
    bool hasPoint(const TPoint<T>& p) const{
        int _size=(int)_vertices.size();
        for(int i=0;i<_size;++i){
            TSegment<T> seg(_vertices[i],_vertices[(i+1)%_size]);
            if(seg.hasPoint(p)){
                return true;
            }
        }
        T min_y=_vertices[0]._y;
        for(int i=1;i<_size;++i){
            if(_vertices[i]._y<min_y){
                min_y=_vertices[i]._y;
            }
        }
        min_y-=1;
        
        bool has_point=false;
        TSegment<T> seg(TPoint<T>(p._x,min_y),p);
        for(int i=0;i<_size;++i){
            TSegment<T> sg(_vertices[i],_vertices[(i+1)%_size]);
            if(sg.segmentsIntersect(seg)){
                bool p1=seg.hasPoint(_vertices[i]);
                bool p2=seg.hasPoint(_vertices[(i+1)%_size]);
                if(p1 && !p2){
                    if(seg.din(_vertices[(i+_size-1)%_size])*seg.din(_vertices[(i+1)%_size])<=0){
                        has_point=!has_point;
                    }
                }else if(!p1 && p2){
                    if(seg.din(_vertices[i])*seg.din(_vertices[(i+2)%_size])<=0){
                        has_point=!has_point;
                    }
                }else if(!p1 && !p2){
                    has_point=!has_point;
                }
            }
        }
        return has_point;
    }

    bool intersects(const TSegment <T> &s) const{
        for(int i=1;i<(int)_vertices.size();++i){
            TSegment<T> seg(_vertices[i-1],_vertices[i]);
            if(seg.segmentsIntersect(s)){
                return true;
            }
        }
        TSegment<T> seg(_vertices.front(),_vertices.back());
        if(seg.segmentsIntersect(s)){
            return true;
        }
        return false;
    }
};

template<class T>
class TCircle{
private:
    T _rad;
    TPoint<T> _center;
public:
    TCircle(){
        this->_rad=T();
        this->center=TPoint<T>();
    }

    TCircle(const T rad,const TPoint<T>& p){
        this->_rad=rad;
        this->_center=p;
    }

    TCircle<T>& operator=(const TCircle<T>& c){
        this->_rad=c._rad;
        this->center=c._center;
        return *this;
    }

    bool hasPoint(const TPoint<T>& p) const{
        if(((this->_center._x-p._x)*(this->_center._x-p._x)+(this->_center._y-p._y)*(this->_center._y-p._y))<=
            this->_rad*this->_rad){
            return true;
        }
        return false;
    }

    bool intersects(const TSegment <T> &s) const{
        if(((this->_center._x-s._p1._x)*(this->_center._x-s._p1._x)+(this->_center._y-s._p1._y)*(this->_center._y-s._p1._y))==
            this->_center*this->_center || ((this->_center._x-s._p2._x)*(this->_center._x-s._p2._x)+
            (this->_center._y-s._p2._y)*(this->_center._y-s._p2._y))==this->_rad*this->_rad){
                return true;
        }
        if((this->hasPoint(s._p1) && !(this->hasPoint(s._p2))) || (this->hasPoint(s._p2) && !(this->hasPoint(s._p1)))){
            return true;
        }
        return false;
    }
};

int main(){
    TPoint<int> p1(0,0),p2(2,2),p3(1,1),p4(1,0),p5(0,10),p6(-4,-5);
    cout<<"p1: ("<<p1._x<<","<<p1._y<<")"<<endl;
    cout<<"p2: ("<<p2._x<<","<<p2._y<<")"<<endl;
    cout<<"p3: ("<<p3._x<<","<<p3._y<<")"<<endl;
    cout<<"p4: ("<<p4._x<<","<<p4._y<<")"<<endl;
    cout<<"p5: ("<<p5._x<<","<<p5._y<<")"<<endl;
    cout<<"p6: ("<<p6._x<<","<<p6._y<<")"<<endl;

    vector<TPoint<int> > arr(3);
    arr[0]=p6;
    arr[1]=p5;
    arr[2]=p4;
    TSegment<int> s1(p1,p2),s2(p4,p5);
    TPolygon<int> pol(3,&arr[0]);
    cout<<"pol: p6,p5,p4"<<endl;

    if(s1.hasPoint(p3)){
        cout<<"Segment s1 has point p3"<<endl;
    }else{
        cout<<"Segment s1 doesn't have point p3"<<endl;
    }
    if(s1.hasPoint(p4)){
        cout<<"Segment s1 has point p4"<<endl;
    }else{
        cout<<"Segment s1 doesn't have point p4"<<endl;
    }

    if(s1.segmentsIntersect(s2)){
        cout<<"Segment s1 and Segment s2 intersect"<<endl;
    }else{
        cout<<"Segment s1 and Segment s2 don't intersect"<<endl;
    }

    TCircle<int> c(5,p1);
    if(c.hasPoint(p4)){
        cout<<"Circle c consists point p4"<<endl;
    }else{
        cout<<"Circle c doesn't consist point p4"<<endl;
    }
    if(c.hasPoint(p5)){
        cout<<"Circle c consists point p5"<<endl;
    }else{
        cout<<"Circle c doesn't consist point p5"<<endl;
    }
    if(c.intersects(s2)){
        cout<<"Circle c intersects with s2"<<endl;
    }else{
        cout<<"Circle c doesn't intersects with s2"<<endl;
    }

    if(pol.intersects(s1)){
        cout<<"Polygon pol intersects segment s1"<<endl;
    }else{
        cout<<"Polygon pol doesn't intersect segment s1"<<endl;
    }
    if(pol.hasPoint(p1)){
        cout<<"Polygon pol consists point p1"<<endl;
    }else{
        cout<<"Polygon pol doesn't consist point p1"<<endl;
    }
    if(pol.hasPoint(p2)){
        cout<<"Polygon pol consists point p2"<<endl;
    }else{
        cout<<"Polygon pol doesn't consist point p2"<<endl;
    }
    return 0;
}