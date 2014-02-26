

#ifndef _TOOLS__H
#define __TOOLS_H

#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdio.h>
#include <tchar.h>
#include <math.h>

#include <string>
#include<iostream>
#include <map>
#include <string>

using namespace std;


#define _DEBUG  //debug flag


int _debug( int info );
int _debug( const char *info );
int _debug( float info );
int _debug( const string &info );
int _loginfo( const char *fmt, ... );

//使用字符 cc 代替字符串 str 中的字符 c
int _replace( char c, char* str, char cc);

char *  casestrstr (const char * str1,const char * str2);

char* checkStr(const char* sql, const char* begin, const char* end, const char* aim);

char* delblank( char* str );
//////////////////////////////////////////

int strToTime(const char * str, long long &_time);

int timeToStr(long long &_time,char* timeStr);


int getLevel(int mark);
float getValue( char* str );
char* getNumStrFromStr( char* str );

void gethaha( char* haha);

enum const_val
{
	ORI = 0,
	MAX,
	MIN,
	AVA,
	SUM
};


enum T_VALUE_TYPE { TYPE_WRONG=-1 , TYPE_INT=0, TYPE_FLOAT=1 };


T_VALUE_TYPE isFloat( char* value );

T_VALUE_TYPE getNumType( char* value );

//////////////////////////////typedef////////////////////////////////////////
typedef struct TMiffa
{
    TMiffa* son;
};

//////////////////////////////////////////////////////////////////////
bool cmpDayofTime2(time_t begTime, time_t endTime, int diff);

/*
struct ltstr
{
  bool operator()(const TInfo& s1, const TInfo& s2) const
  {
    return s1<s2;
  }
};


*/

//////////////////////////////////////////////////////////////////////

//快速排序
//low_ptr指向数组下标最小的元素，high_ptr指向数组下标最大的元素
void quick_sort(float *low_ptr,float *high_ptr);


float *partition(float *low_ptr,float *high_ptr);


void swap(float& value1,float& value2);


void display_data(float data[], int size);


//////////////////////////////////////////////////////////////////////
//字符串比较(忽略大小写)
int strNoCaseCmp(const char *s1, const char *s2);

int strcasecmp(char *s1, char *s2);

//////////////////////////////////////////////////////////////////////
void printBinary(unsigned char tmp); //打印二进制

void  ShowBytes( void *  s,  int  n);  //打印16进制

#define P(N)  std::cout<<#N<<"="<<N<<endl;
#define PP(N)  printf("%s=%d", #N, N);

void* operator new (size_t sz);


void operator delete (void* m);


/////////////////////////////////////////////////////
int funcStatic();

class TBase
{
public:
	TBase(int ii) : i(ii) {}
	virtual int value() const { return i; }
private:
	int i;
};

class TDerived : public TBase
{
public:
	TDerived(int ii) : TBase( ii ) {}
	int value() const { return TBase::value() * 2; }
	virtual int shift( int x ) const { return TBase::value() << x; }
private:


};

class TAccess
{
public:
	TAccess(){ i=0; };
	~TAccess(){};
private:
	int i;
};
class TAccessSon:public TAccess
{
public:
	TAccessSon(){ i=100;}
	~TAccessSon(){}
	int get()
	{
	    return 0;
		//return TAccess::i;
	}
private:
	int i;
};

class myConst
{
public:
	myConst(int vv){};
private:
	static const int size= 20;
	char mychar[size];
};

//////////////////////////////////

class test{
  static int x;
  static int y;
public:
	void print()
	{
		printf("==%d \n,", x);
		printf("==%d \n", y);
	};
};
class A
{

public:
	A(int v, int number):value(v){num = number;};
	A():value(5){;};
      int getValue(){return value;};
	  void setValue(int i){/*value = i;*/}
	  void print(){printf("value==%d, num==%d\n", value, num);}
      ~A(){printf("==destory A==\n");}
protected:
	  int num;
private:
      const int value;
};

class B
{
public:
      B():a(1,2)
      {
           b = new A(1, 2);
      }
      A* getValue()
      {
           return b;
      }
	  int setValue(A& a){a.setValue(15); return 0;}
      ~B(){delete b; printf("==destory B==\n");}
private:
      A a;
      A* b;
};

class A1:public A
{
public:
	A1(int v, int n):A(v, n){}
    void printInfo(){printf("value==%d, num==%d\n", this->getValue(), num);}
private:

};
class A2:private A
{
public:
	A2(int v, int n):A(v, n){}
	void printInfo(){A::print();}
private:

};
///////////////////
class Bunch
{
	enum { size=1000};
	int i[size];

};
///////////////////////////////////////////////////////
///////////////////////////静态常量测试///////////////////////////////////////////
class constTest
{
private:
    static const int ARRAYLEN =6  ;
	int num[ARRAYLEN];
public:
	constTest(int len);

};

//const int constTest::ARRAYLEN=2;



//静态类对象
class intStaticT
{
private:
    int data;
public:
	static intStaticT*  hello;
	intStaticT(){ data=100; cout<<"intStaticT construct"<<endl; }
    ~intStaticT(){ cout<<"~intStaticT called"<<endl; }
	static intStaticT* getStatic()
	{
		if(hello == NULL )
			hello = new intStaticT();
		return hello;
	}
	void print(){ cout<<"intStaticT::data="<<data<<endl; }
};

//公共函数


//////////////////////////////////////////////////////////////////////
#define FIELD(a) char*a##_string; int a##_size

class Record
{
    FIELD(one);
	FIELD(two);
	FIELD(three);
};

class intStatic
{
private:
    int data;
	static int counter;
	static int num;
	const int weight;
public:
	static intStatic hello;
	intStatic():weight(100){ counter++; cout<<"intStatic construct"<<endl; }
	intStatic(const intStatic& hi):weight(hi.weight){  cout<<"intStatic copy  construct"<<endl; }
    ~intStatic(){ --counter; ++num; cout<<"~intStatic called";  print("析构"); cout<<"析构对象个数= "<< num<<endl;}
	static intStatic* getStatic(){ return &hello; }
	intStatic& operator= (const intStatic&  ){ cout<<"intStatic 赋值 copy  construct    "<<endl;   return *this; }
	void print()const{ cout<<"data="<<data<<endl;  cout<<"counter="<<counter<<endl;}
	static void print(char* haha){ if( haha!=NULL) cout<<haha;  cout<<"counter="<<counter<<endl;}
};


intStatic funf(intStatic x);           //调用拷贝构造函数
intStatic funfs();
void funhaha();
void funhahaha();

///////////////////////////////////////////////////////////////////
class Tprinter
{
public:
	void print(const intStatic& hello)
	{ return hello.print();}

};
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//
class declass{};
class defaclass
{
    declass *haha;
	declass hehe;
	static const char* maomao[2]; //={"hello", "hi"};
	static defaclass hello;
};



//////////////////////////////////////////////////////////////////////


class SS
{
    int i[100];
public:
	SS(){ puts("SS::SS()");}
	~SS(){ puts("SS::~SS()");}
};
class SSS
{
    int i[100];
	static int number;
public:
	SSS(){ puts("SS::SS()");}
	~SSS(){ puts("SS::~SS()");}
};


class FA
{

public:
	int f()const{ cout<<"FA::f()"<<endl; return 0; }
	int f(string ){ cout<<"FA::f(string)"<<endl; return 1; }
	void g(){ cout<<"FA::g()"<<endl;  }
};
class FA_1: public FA
{
public:
	void g()const{ cout<<"FA_1::g()"<<endl;  }    //FA::g() 被隐藏
};
class FA_2: public FA
{
public:
	int f()const{ cout<<"FA_2::f()"<<endl; return 2; }  //FA::f() FA::f(string)被隐藏
};
class FA_3: public FA
{
public:
	void f()const{ cout<<"FA_3::f()"<<endl;  }  //FA::f() FA::f(string)被隐藏
};
class FA_4: public FA
{
public:
	int f(int)const{ cout<<"FA_4::f()"<<endl; return 4; }  //FA::f() FA::f(string)被隐藏
};

//////////////////////////////////////////////////////////////////////
class TInfo
{
public:
	int age;
	string name;
	float weight;
	TInfo(const string& nam, int ag, float we)
	{
	    name = nam;
		age = ag;
		weight = we;
		cout<<" TInfo 构造函数 called "<<name<<endl;
	}
	TInfo( const TInfo& info)
	{
	    name = info.name;
		age = info.age;
		weight = info.weight;
		cout<<" TInfo copy构造函数 called "<<name<<endl;
	}

	TInfo()
	{
	    name = "lost";
		age = 0;
		weight = 0.0;
		cout<<" TInfo 默认构造函数 called "<<name<<endl;
	}

	virtual ~TInfo(){};
	void setName(const string& nam){ name = nam; }
	bool operator == ( const TInfo&  haha)const
	{
		cout<<"TInfo operator == called"<<endl;
		return (haha.name == name);
	}
	TInfo& operator = ( const TInfo&  info)
	{
		cout<<"TInfo  赋值函数 called "<<info.name<<endl;
		if( this == &info )
			return *this;
		else
		{
			//如果有指针,释放以前的
	        name = info.name;
		    age = info.age;
		    weight = info.weight;
			return *this;
		}

	}
	bool operator < ( const TInfo&  haha) const     //const 不能省略
	{
		cout<<"TInfo operator <  called"<<endl;
		return (haha.age < age);
	}

	virtual void print()const
	{
        cout<<"/===================/"<<endl;
	    cout<<" *  name   = "<<name<<endl;
		cout<<" *  age    = "<<age<<endl;
		cout<<" *  weight = "<<weight<<endl;
		cout<<"/===================/"<<endl;
	}
};

class PostTInfo: public TInfo
{
public:
	string m_post;
	PostTInfo(const string& post, const string& nam, int ag, float we):TInfo( nam,  ag,  we)
	{ m_post= post; }

	PostTInfo( const PostTInfo& hi ):TInfo(hi)   //调用基类的拷贝构造函数
	{
		cout<<"PostTInfo copy construct called"<<endl;
	    m_post = hi.m_post;
	}

	virtual ~PostTInfo()
	{}

	PostTInfo& operator =(PostTInfo& hi)
	{
		if(&hi == this) return *this;

		TInfo::operator =(hi);        //调用基类的赋值运算符
	    m_post = hi.m_post;
		return *this;
	}

	void print()
	{
        cout<<"/===================/"<<endl;
	    cout<<" *  name   = "<<name<<endl;
		cout<<" *  age    = "<<age<<endl;
		cout<<" *  weight = "<<weight<<endl;
		cout<<" *  post  =" << m_post<<endl;
		cout<<"/===================/"<<endl;
	}
};

class TAlarm
{
public:
    TAlarm(){}
    virtual ~TAlarm(){}
    virtual int sendAlarm();
	virtual int printAlarm();
	virtual int dealAlalrm();
	virtual int receiveAlarm();

private:

	int m_alaemId;
	char* m_info;

};

class TUdpAlarm:public TAlarm
{
    virtual ~TUdpAlarm(){}
	virtual int printAlarm();
	virtual int dealAlalrm();
};

class TSanAlarm:public TAlarm
{
    virtual ~TSanAlarm(){}
	virtual int printAlarm();
	virtual int dealAlalrm();
	virtual int receiveAlarm();
};

class TUspAlarm:public TAlarm
{
    virtual ~TUspAlarm(){}
	virtual int printAlarm();
};

class base {
public:
virtual int foo( int ival = 1024 ) {
cout << "base::foo() -- ival: " << ival << endl;
return ival;
}
// ...
};
class derived : public base {
public:
    virtual int foo( int ival = 2048 )
    {
        cout << "derived::foo() -- ival: " << ival << endl;
        return ival;
    }
};

static int printIval1111(base& tem)
{
	cout<<tem.foo()<<endl;
	return tem.foo();
};

static int printIval2222(base* temp)
{
	cout<<temp->foo()<<endl;
	return temp->foo();
};

static int getG(const char * buf)
{
	printf("====find G in %s===\n", buf);
       char *GM = (char*)buf;
        while(*GM != '\0')
        {
			printf("====finding===\n");
           if(*GM =='G')
           {
			   printf("====find G===\n");
               return 1;
           }
		   GM++;
        }
		printf("===can't find G \n");
        return 0;
};


static void swapP(int *a,int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
};

static int partition(int data[],int lo,int hi)
{
    printf("low  %d:%d     high  %d:%d \n", lo,data[lo], hi,data[hi] );
    int key=data[hi];  //以最后一个元素，data[hi]为主元
    int i=lo-1;
    for(int j=lo;j<hi;j++)   ///注，j从p指向的是r-1，不是r。
    {
        if(data[j]<=key)
        {
            i=i+1;
            printf("-->swap [%d]%d   [%d]%d\n", i,data[i],j,data[j]);
            swapP(&data[i],&data[j]);
        }
    }
    printf("-->swap [%d]%d   [%d]%d\n", i+1,data[i+1],hi,data[hi]);
    swapP(&data[i+1],&data[hi]);   //不能改为swap(&data[i+1],&key)
    return i+1;
};

static int partition2(int data[],int lo,int hi)
{
    printf("low  %d:%d     high  %d:%d \n", lo,data[lo], hi,data[hi] );
    int key=data[hi];  //以最后一个元素，data[hi]为主元
    int i=lo-1;
    for(int j=lo;j<=hi;j++)   ///注，j从p指向的是r-1，不是r。
    {
        if(data[j]<=key)
        {
            i=i+1;
            printf("-->swap [%d]%d   [%d]%d\n", i,data[i],j,data[j]);
            swapP(&data[i],&data[j]);
        }
    }
    //printf("-->swap [%d]%d   [%d]%d\n", i+1,data[i+1],hi,data[hi]);
    swapP(&data[i+1],&data[hi]);   //不能改为swap(&data[i+1],&key)
    return i+1;
};

 static void QuickSort2(int data[], int lo, int hi)
{
    if (lo<hi)
    {
        int k = partition(data, lo, hi);
        QuickSort2(data, lo, k-1);
        QuickSort2(data, k+1, hi);
    }
};


static int partition3(int data[],int lo,int hi)
{
        int key=data[lo];
        int l=lo;
        int h=hi;
        while(l<h)
       {
           while(key<=data[h] && l<h) h--;   //高位找小，找到了，就把它弄到前面去
              data[l]=data[h];
           while(data[l]<=key && l<h) l++;    //低位找大，找到了，就把它弄到后面去
             data[h]=data[l];
       }                                                   //如此，小的在前，大的在后，一分为二
        data[l]=key;
        return l;
}

 static void QuickSort3(int data[], int lo, int hi)
{
    if (lo<hi)
    {
        int k = partition3(data, lo, hi);
        QuickSort3(data, lo, k-1);
        QuickSort3(data, k+1, hi);
    }
};

long getLongFromJavaToC(long data);


int getIntFromJavaToC(int data);





#endif

