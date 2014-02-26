



#include "tools.h"

int  _debug(int info)
{
#ifdef _DEBUG
    printf( "%d\n", info);
#endif
    return 0;
};

int _debug(const char* info)
{
#ifdef _DEBUG
    printf( "%s\n", info);
#endif
    return 0;
};

int _debug(float info)
{
#ifdef _DEBUG
    printf( "%f\n", info);
#endif
    return 0;
};

int _debug(const string& info)
{
#ifdef _DEBUG
    printf( "%s\n", info.c_str());
#endif
    return 0;
}

int _loginfo(const char *fmt, ...)
{
    int printed = 0;
#ifdef _DEBUG
    char printf_buf[1024];
    va_list args;

    va_start(args, fmt);
    printed = vsprintf(printf_buf, fmt, args);
    va_end(args);

    puts(printf_buf);
#endif
    return printed;
}

int _replace( char c, char* str, char cc)
{
    if( str==NULL || strlen(str)==0 )
        return -1;

    char * temstr = str;
    while( *temstr != '\0' )
    {
        _loginfo( "==%p==\n", temstr );
        if( *temstr == c )
        {
            *temstr = cc;
        }
        temstr++;
    }

    return 0;
}

char *  casestrstr (
        const char * str1,
        const char * str2
        )
{
        char *cp = (char *) str1;
        char *s1, *s2;

        if ( !*str2 )
            return((char *)str1);
        while (*cp)
        {
                s1 = cp;
                s2 = (char *) str2;
                while ( *s1 && *s2 && !(toupper(*s1)-toupper(*s2)) )
                {
                        s1++, s2++;
                }
                if (!*s2)
                        return(cp);
                cp++;
        }
        return(NULL);
}

char* checkStr(const char* sql, const char* begin, const char* end, const char* aim)
{
    if( sql == NULL || begin == NULL || end == NULL || aim == NULL)
        return NULL;

    char* _begin =NULL;
    if( (_begin=casestrstr( sql, begin)) == NULL)
        return NULL;
    //move _begin to tail of "begin"
    for ( int i=0; i<strlen(begin);i++)
        _begin++;

    char* _end = NULL;
    if( (_end=casestrstr(sql, end)) == NULL)
        return NULL;

    if ( _begin>=_end )
        return NULL;

    char tempstr[ _end-_begin+1 ];
    memset( tempstr, 0 , _end-_begin+1 );
    strncpy( tempstr, _begin, _end-_begin );

    return casestrstr( tempstr, aim );

}

char* delblank( char* str )
{
    int len = strlen(str);
    char aim[ len+1];
    memset( aim, 0, len+1);

    for(int i=0,j=0; i<len; i++)
    {

        if( isspace(str[i]) )
            continue;
        else
        {
            aim[j]=str[i];
            j++;
        }

    }
    return strcpy( str, aim );
}

int timeToStr(long long &_time,char* timeStr)
{
	struct tm *newtime;
	time_t long_time = _time;
    newtime = localtime(&long_time); /* Convert to local time. */
	sprintf(timeStr,"%04d-%02d-%02d %02d:%02d:%02d",
		newtime->tm_year+1900,newtime->tm_mon+1,newtime->tm_mday,
		newtime->tm_hour,newtime->tm_min,newtime->tm_sec );
	return 0;
};

int strToTime(const char * str, long long &_time)
{
	char cha[32];
	strcpy( cha, str );
	struct tm etime;
	cha[4] = '\0';
	//printf("cha:++%s++\n",cha);
	etime.tm_year = atoi(cha)-1900;
	strcpy( cha, str );
	cha[7] = '\0';
	//printf("cha:%s\n",cha+5);
	etime.tm_mon=atoi(cha+5)-1;
	strcpy( cha, str );
	cha[10] = '\0';
	//printf("cha:%s\n",cha+8);
	etime.tm_mday = atoi(cha+8);
	strcpy( cha, str );
	cha[13] = '\0';
	//printf("cha:%s\n",cha+11);
	etime.tm_hour = atoi(cha+11);
	//printf("hour:%d\n",etime.tm_hour);
	strcpy(cha, str);
	cha[16] = '\0';
	//printf("cha:%s\n",cha+14);
	etime.tm_min = atoi(cha+14);
	strcpy(cha, str);
	//printf("cha:%s\n",cha+17);
	etime.tm_sec = atoi(cha+17);
	etime.tm_isdst = 0;
	_time = mktime(&etime);
	return 0;
};

int getLevel(int mark)
{
	int level[] = {60, 40, 20, 10};
    int i = 1;
	while(mark < level[i-1])
		++i;
	return i;
};


char* getNumStrFromStr( char* str )
{
    char* catStr;
    catStr =  str;

    while(*catStr)
    {
    	if ( isdigit(*catStr) )
    	{
    		break;
    	}
    	catStr++;
    }
    for (int i = 0; catStr[i];)
    {
    	if (isdigit(catStr[i]) || (catStr[i] == '.'))
    	{
    		i++;
    	}
    	else
    	{
    	    catStr[i] = 0;
    	    break;
    	}
	}
	return catStr;
};

float getValue( char* str )
{
	float value = -1.0;
            char* catStr;
			catStr =  str;
			printf("catStr is==%s===",catStr);
			while(*catStr)
			{
				if ( isdigit(*catStr) )
				{
					break;
				}
				catStr++;
			}
			if(!isdigit(*catStr))
			{
				printf("无效的 字符转换 \n");
				return -1.0;
			}
			for (int i = 0; catStr[i];)
			{
				if (isdigit(catStr[i]) || (catStr[i] == '.'))
				{
					i++;
				}
				else
				{
				    catStr[i] = 0;
				    break;
				}
			}
			value = atof(catStr);
			printf( "value = %f \n", value);
           return value;
};

void gethaha(char* catCmd)
{

	       printf("============================================\n");
		   printf("=======%s=========\n",catCmd );
        	char* catStr = catCmd;
    		char* temp = NULL;

    		while(*catStr == ' ' || *catStr == '	')  //跳除空格，tab
    		{
    			catStr++;
    		}
    		if(*catStr == '\0')  //排除空格行
            {
            	printf("getAIXDiskStatusFromFile::there's no data in str \n");
            	return;  //读取分析下一行
            }
			for (int i = 0; catStr[i];)
			{
				//if ( (catStr[i]!=' ') || (catStr[i] != '	'))
				//{
				//	i++;
				//}
				if (  !(isspace(catStr[i]) ) )
				{
					i++;
				}
				else
				{
				    catStr[i] = '\0';
					while(isspace(catStr[i+1]))
						i++;
				    temp = &catStr[i+1];
					printf(" temp get value !!!\n");

				    break;
				}
			}
					if( temp == NULL || temp[0]=='\0' )
					{
						printf(" temp is NULl======\n");
						//return;
					}
    		printf(" ==================name==%s==,  value=%s=====   \n", catStr, temp);
			return;
}

T_VALUE_TYPE getNumType( char* value )
{


    return TYPE_WRONG;
}

T_VALUE_TYPE isFloat( char* value )
{//返回值-1:非法，0：整型；1：浮点型
	if ( value == NULL )
		return TYPE_WRONG;
	bool findDot = false;
	int dotPos = -1;
	int i;
	int firstZeroInEnd = -1;
	int firstBlankInEnd = -1;
	int firstNum = -1;
	for( i=0; value[i]!=0 && i<100; i++ ){
		//检查空格
		if ( value[i] == ' ' || value[i] == '\t' || value[i]=='-' )
		{
			if ( firstBlankInEnd == -1 && firstNum == -1)
			{
				if(value[i+1] != ' ' && value[i+1] != '\t' && value[i+1]!='-' )
			    {
				    //printf("===value[%d] = %c \n",i,value[i] );
				    firstBlankInEnd = i;
			    }
				else
					continue;
			}
			else
			{
				//printf("TYPE_WRONG1===value[%d] = %c \n",i,value[i] );
				return TYPE_WRONG;
			}
			continue;
		}
		else if ( value[i] < '0' || value[i] > '9' )
		{//检查非法字符
			if ( !findDot && value[i] == '.' )
			{
				findDot = true;
				dotPos = i;
				firstZeroInEnd = -1;//找到小数点，firstZeroInEnd无效
				//检查是否已经发现过blank             ///////////////
				continue;
			}
			else
			{
				//printf("TYPE_WRONG2===value[%d] = %c \n",i,value[i] );
				return TYPE_WRONG;
			}
		}
		else
			firstNum = i;

		//检查数字
		if ( value[i] == '0' ){//找到一个0
			if ( firstZeroInEnd == -1 )
				firstZeroInEnd = i;
		}else{
			firstZeroInEnd = -1;//找到非0数字，firstZeroInEnd无效
		}
	}
	if ( i == 100 )//超长
		return TYPE_WRONG;

	if ( findDot ){
		if ( firstZeroInEnd != -1 ){
			value[firstZeroInEnd] = 0;
			if ( value[firstZeroInEnd-1] == '.' ){//小数点后全为0。
				value[firstZeroInEnd-1] = 0;
				findDot = false;
			}
		}else if ( value[dotPos+1] == 0 ){//最后一个为.
			value[dotPos] = 0;
			findDot = false;
		}
	}
	if ( findDot )
		return TYPE_FLOAT;
	else
		return TYPE_INT;
};

intStatic funf(intStatic x)           //调用拷贝构造函数
{
	x.print("==========x in  funf()");
	return x;
}

intStatic funfs()
{
   // intStatic x;                  //调用构造函数
	//x.print("=========x in  funfs==()");
	return intStatic();
}

void funhaha()
{
	//cout<<"====funfs will be called ==============f"<<endl;
	//intStatic s2222 = funfs();   //调用拷贝构造函数, 将临时对象的值拷贝给s2222,  临时对象析构
	intStatic::print("==================funhaha:: test begin===========>");
    intStatic s111;      //构造函数
	intStatic::print("after s111 construct!!!!===============================================");
	intStatic s222 = funf( s111 );  //funcf进入时调用拷贝构造函数拷贝s111 , funf退出时调用拷贝构造函数将临时对象的值拷贝给s2222,  临时对象析构

	cout<<"===s3333==="<<endl;
	intStatic s333;   //构造函数
	s333= funf( s111 );
	funf( s111 );
	intStatic::print("after call funf !!!==========================================");
    cout<<"======funhaha over=============================="<<endl;
}     //s111, s222 s333 析构

void funhahaha(){ funhaha();  cout<<" last over============"<<endl; 	funfs(); intStatic x = funfs();}

int strNoCaseCmp(const char *s1, const char *s2)
{
    //toupper();
    //tolower();
    char *str1 = (char *)s1;
    char *str2 = (char *)s2;
    while(*str1 != 0 && *str2!= 0)
    {
        int check = toupper(*str1++) - toupper(*str2++);
        if (check == 0)
        {
            continue;
        }
        else if (check > 0)
        {
            return -1;
        }
        else
        {
            return 1;
        }
    }
    if(*str2 != 0)
    {
        return -1;
    }
    else if(*str1 != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int strcasecmp(char *s1, char *s2)
{
  while (toupper((unsigned char)*s1) == toupper((unsigned char)*s2++))
	  if (*s1++ == '\0')  return 0;
  return(toupper((unsigned char)*s1) - toupper((unsigned char)*--s2));
}

void printBinary(unsigned char tmp)
{
	for(int i = 7; i >= 0; i--)
        if(tmp & (1 << i))
            std::cout << "1";
        else
            std::cout << "0";
	std::cout<<endl;
}

void  ShowBytes( void *  s,  int  n)
{
    unsigned  char *  start  =  (unsigned  char * )s;

    printf( " [OFFSET] ADDRESS: VALUE\n\n " );

    for  ( int  i  =   0 ; i  <  n; i ++ )
    {
        printf( "  [%.4d] %.8X: %.2X\n " , i, start  +  i,  * (start  +  i));

        if  ((i  +   1 )  %   4   ==   0 )
        {
            printf( " ----------------------\n " );
        }
    } // for
 }

void quick_sort(float *low_ptr,float *high_ptr)
 {
	float *pivot_ptr;
	extern float * partition(float *low_ptr,float *high_ptr);
	if(low_ptr<high_ptr)
	{
		pivot_ptr=partition(low_ptr,high_ptr);
		quick_sort(low_ptr,pivot_ptr-1);
		quick_sort(pivot_ptr,high_ptr);
	}
}

float *partition(float *low_ptr,float *high_ptr)
{
	void swap(float& value1,float& value2);
	float pivot=*(low_ptr+(high_ptr-low_ptr)/2);
	while(low_ptr<=high_ptr)
	{
		while(*low_ptr<pivot)
			low_ptr++;
		while(*high_ptr>pivot)
			high_ptr--;
		if(low_ptr<=high_ptr)
			swap(*low_ptr++,*high_ptr--);
	}
	return low_ptr;
}

bool cmpDayofTime2(time_t begTime, time_t endTime, int diff)
{
	char timeStr[32];
    time_t nowE = time(NULL);                  //有效结束时间
    time_t nowB = time(NULL) - diff*24*3600L;  //有效开始时间
	printf("nowE =  %ld   ", nowE);
	printf("nowB = %ld   ", nowB);

    /*
    //范围内   开始或者结束时间 位于 有效结束时间 与 有效开始时间 之间
    if( (beginTimeT>=nowB && beginTimeT <=nowE) || (endTimeT>=nowB && endTimeT<=nowE) )
    	return true;
    else if( beginTimeT<nowB && endTimeT>nowE )
    	return true;
    else
    	return false;
    */
    if( begTime>nowE || endTime<nowB )
    	return false;


	return true;
}

int funcStatic()
{
    static int i=0;
	return i++;
}



void* operator new (size_t sz)
{
	//printf("operator new: %d Bytes\n", sz);
    void* m = malloc(sz);
	if(!m) { puts("out of memery");}
	return m;
}

void operator delete (void* m)
{
    //{ puts("operator delete");}
	//delete m;  //使用delete, 陷入死循环
	free(m);
}

void swap(float& value1,float& value2)
{
	float temp=value1;
	value1=value2;
	value2=temp;
}

void display_data(float* data, int size)
{
	for(int i=0;i<size;i++)
		printf("\n%f",data[i]);
}
 intStaticT* intStaticT::hello = NULL;

int SSS::number = 1000;

intStatic intStatic::hello;
int intStatic::counter=-1;
int intStatic::num=0;

const char* defaclass::maomao[2]={"hello", "hi"};

int test::x = 1;
int test::y = test::x+1;



long getLongFromJavaToC(long data)
{
	long ret = 0;
	char* ptr = (char*)&ret;
	ptr[7] = (char) (data & 0xff);      //java位置1  对应C++ 位置8
	ptr[6] = (char) (data >> 8 & 0xff); //java位置2  对应C++ 位置7
	ptr[5] = (char) (data >> 16 & 0xff);//java位置3  对应C++ 位置6
	ptr[4] = (char) (data >> 24 & 0xff);//java位置4  对应C++ 位置5
	ptr[3] = (char) (data >> 32 & 0xff);//java位置5  对应C++ 位置4
	ptr[2] = (char) (data >> 40 & 0xff);//java位置6  对应C++ 位置3
	ptr[1] = (char) (data >> 48 & 0xff);//java位置7  对应C++ 位置2
	ptr[0] = (char) (data >> 56 & 0xff);//java位置8  对应C++ 位置1

	return ret;
}

int getIntFromJavaToC(int data)
{
	long ret = 0;
	char* ptr = (char*)&ret;
	ptr[3] = (char) (data & 0xff);//java位置5  对应C++ 位置4
	ptr[2] = (char) (data >> 8 & 0xff);//java位置6  对应C++ 位置3
	ptr[1] = (char) (data >> 16 & 0xff);//java位置7  对应C++ 位置2
	ptr[0] = (char) (data >> 24 & 0xff);//java位置8  对应C++ 位置1

	return ret;
}

