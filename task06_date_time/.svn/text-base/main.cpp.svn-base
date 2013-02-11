#include <iostream>
#include <stdio.h>
#include <ctime> 
using namespace std;

bool isLeap(int year){
    return ((year%4==0 && year%100!=0) || year%400==0);
}

class TTimeSpan{
public:
    time_t _time;
    
    TTimeSpan(){
        _time=0;
    }

    TTimeSpan(time_t time){
        _time=time;
    }

    TTimeSpan(int year,int month,int day,int h,int m,int s){
        _time=0;
        if(year>=1970){
            int dop_year=year;
            --dop_year;
            while(dop_year>=1970){
                if(isLeap(dop_year)){
                    _time+=366*24*3600;
                }else{
                    _time+=365*24*3600;
                }
                --dop_year;
            }
            int months[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
            if(isLeap(year)){
                months[2]=29;
            }
            for(int i=1;i<month;++i){
                _time+=months[i]*24*3600;
            }
            _time+=(day-1)*24*3600+h*3600+m*60+s;
        }
    }
    
    friend std::ostream& operator<<(std::ostream& stream,TTimeSpan tts){ 
        stream<<tts._time;
        return stream;
    }
      
    friend std::istream& operator>>(std::istream& stream,TTimeSpan &tts){
        int year,month,day,h,m,s;
        stream>>year>>month>>day>>h>>m>>s;
        TTimeSpan t(year,month,day,h,m,s);
        tts._time=t._time;
        return stream;
    }
};

class TDateTime{
private:
    time_t _time;
public:
    TDateTime(){
        _time=time(NULL)+4*3600;//смещение из-за часового пояса
    }

    TDateTime(time_t time){
        _time=time;
    }
    
    TDateTime(int year,int month,int day,int h,int m,int s){
        TTimeSpan tts(year,month,day,h,m,s);
        _time=tts._time;
    }
    
    TDateTime(int year,int month,int day){
        TTimeSpan tts(year,month,day,0,0,0);
        _time=tts._time;
    }

    TDateTime(string st){//Example date format: 2012.12.24 12:24:36
        int year,month,day,h,m,s;
        sscanf(&st[0],"%d.%d.%d %d:%d:%d",&year,&month,&day,&h,&m,&s);
        TTimeSpan tts(year,month,day,h,m,s);
        _time=tts._time;
    }
    
    friend std::ostream& operator<<(std::ostream& stream,TDateTime tdt){
        stream<<asctime(gmtime(&tdt._time));
        return stream;
    }
      
    friend std::istream& operator>>(std::istream& stream,TDateTime &tdt){
        int year,month,day,h,m,s;
        stream>>year>>month>>day>>h>>m>>s;
        TTimeSpan tts(year,month,day,h,m,s);
        tdt._time=tts._time;
        return stream;
    }

    int Year(){
        return gmtime(&_time)->tm_year+1900;
    }
    int Month(){
        return gmtime(&_time)->tm_mon+1;
    }
    int Day(){
        return gmtime(&_time)->tm_mday;
    }
    int Hour(){
        return gmtime(&_time)->tm_hour;
    }
    int Minute(){
        return gmtime(&_time)->tm_min;
    }
    int Second(){
        return gmtime(&_time)->tm_sec;
    }

    int DayOfWeek(){
        int wday;
        if((wday=gmtime(&_time)->tm_wday)==0){
            wday+=7;
        }
        return wday;
    }

    static TDateTime Now(){
        return TDateTime();
    }

    bool operator<(const TDateTime& tdt){
        return _time<tdt._time;
    }

    TDateTime operator+(const TTimeSpan& delta){
        TDateTime time(_time+delta._time);
        return time;
    }

    TDateTime operator-(const TTimeSpan& delta){
        TDateTime time(_time-delta._time);
        return time;
    }

    TTimeSpan operator-(const TDateTime& tdt){
        TTimeSpan tts(_time-tdt._time);
        return tts;
    }
};

int main(){
    TDateTime time_now;
    cout<<"Date and Time now: "<<time_now;
    cout<<"Today is "<<time_now.DayOfWeek()<<" day of week"<<endl;
    cout<<"Date and Time now in another format:"<<time_now.Year()<<"/"<<time_now.Month()<<"/"<<time_now.Day()<<" "<<time_now.Hour()<<":"<<time_now.Minute()<<":"<<time_now.Second()<<endl;
    cout<<endl;

    TDateTime tdt1(2012,12,12,12,12,12),tdt2(2012,12,11,12,12,12);
    cout<<"tdt1: "<<tdt1;
    cout<<"tdt2: "<<tdt2;
    cout<<"tdt1-tdt2: "<<(tdt1-tdt2)._time<<" seconds"<<endl;
    TTimeSpan tts=tdt1-tdt2;
    cout<<"tts: "<<tts<<" seconds"<<endl;
    return 0;
}

