#include "algothrim.h"
#include <iostream>
#include <ctime>
#include <memory.h>
#include <stdio.h>

void TAlgorithmSortMi::QuickSort(int* a, int len)
{
    if(NULL == a) return;
    if(len<0) return;
    QuickSort(a, 0, len-1);
}

void TAlgorithmSortMi::QuickSort(int* a, int low, int high)
{
    if(low>high) return;
    int pos = partition(a, low, high);
    QuickSort(a,low,pos-1);
    QuickSort(a,pos+1, high);
}

int TAlgorithmSortMi::partition(int *a, int low, int high)
{
    int povit = a[high]; //标兵取分组最后一个
    int lit = low -1;
    for(int fa = low; fa<high; fa++)
    {
        if(a[fa]<povit)
        {
            lit += 1;
            swapInt(a[lit], a[fa]);
        }
    }
    swapInt(a[lit+1],a[high]); //标兵入位
    printSort(a, low, high-low);
    return  lit+1;
}
/*
int Partion(vector<int> &v ,int low ,int high)
{//对vector进行划分，返回枢轴下标
    int pivotkey;
    pivotkey = v[low]
    while ( low < high )
    {
        while (low < high && v[high] >= pivotkey)
            high --;
        v[low] = v[high];
        while (low < high && v[low] <= pivotkey )
            low ++;
        v[high] = v[low];
    }
    v[low] = pivotkey
    return low ;
}
*/
void TAlgorithmSortMi::InsertSort(int*a , int len)
{
    if(NULL == a) return;
    if(len<0) return;
    int x,y;
    for(int x=1; x<len; ++x)
    {
        int mid = a[x];
        for(y=x-1;y>=0; --y)
        {
            if(mid<a[y])
                a[y+1] = a[y];
            else
                break;
        }
        /*
        for(y=x-1;y>=0 && mid<a[y]; --y)
        {
            a[y+1] = a[y];
        }
        */
        a[y+1] = mid;
    }
}

void TAlgorithmSortMi::MaopaoSort(int* a, int len)
{
    if(NULL == a) return;
    if(len<0) return;
    for(int i=0;i<len-1;++i)
    {
        for(int j=i+1; j<len;++j)
        {
            if(a[i]>a[j])
                swapInt(a[i],a[j]);
        }
        printSort(a, len);
    }
}

void TAlgorithmSortMi::swapInt(int &a, int &b)
{
    a ^= b;
    b ^= a;
    a ^= b;
}

void TAlgorithmSortMi::swapChar(char &a, char& b)
{
    char d = a;
    a = b;
    b = d;
}

void TAlgorithmSortMi::swapCharPtr(char *a, char* b)
{
    char d = *a;
    *a = *b;
    *b = d;
}

void TAlgorithmSortMi::printSort(int *a, int len)
{
    if(NULL == a) return;
    if(len<0) return;
    std::cout<< "array: ";
    for(int i=0;i<len;++i)
    {
        std::cout<< "|"<< a[i];
    }
    std::cout<<std::endl;
}

void TAlgorithmSortMi::printSort(int *a, int pos,int len)
{
    if(NULL == a) return;
    if(len<0) return;
    std::cout<< "array: ";
    for(int i=pos;i<len+pos;++i)
    {
        std::cout<< "|"<< a[i];
    }
    std::cout<<std::endl;
}

void TAlgorithmSortMi::FindBitNum(int* a, int len)
{
    //
    if(a == NULL || len <2 )return ;
    int xorSum = 0;
    for(int pos=0; pos<len; pos++)
    {
        xorSum ^= a[pos];
    }
    int bitIndex = BitIndex(xorSum);
    int iNum1 = 0;
    int iNum2 = 0;
    for(int pos=0; pos<len; pos++)
    {
        if( HasBit(a[pos],bitIndex))
            iNum1 ^= a[pos];
        else
            iNum2 ^= a[pos];
    }
    std::cout<< "number1 ="<<iNum1<<"    number2="<<iNum2<<std::endl;
}

unsigned int TAlgorithmSortMi::BitIndex(int num)
{
    //std::cout<<"num  ="<<num<<"    num&1 ="<<(num&1)<<std::endl;
    unsigned int bitIndex = 0;
    while( (num&1)==0 && (bitIndex < 8*sizeof(int)) )   //&c运算符优先级高于 ==
    {
        num = num>>1;
        ++bitIndex;
    }
    //std::cout<<"index bit ="<<bitIndex<<std::endl;
    return bitIndex;
}

bool TAlgorithmSortMi::HasBit(int num, unsigned int index)
{
    num = num>>index;
    return  (num&1);
}

int TAlgorithmSortMi::HowManyOne(int number)
{
    int onenum = 0;
    if(number<0)
    {
        onenum += 1;
        number = -number;
    }

    while( number !=0 )
    {
        number = number & (number-1);
        onenum += 1;
    }
    return onenum;
}

int TAlgorithmSortMi::BinarySearch(int* a, int len, int aim)
{
    int low = 0;
    int high = len -1;
    while(low<=high)
    {
        int mid = (low+high)>>1;
        if(a[mid] == aim)
            return mid;
        if(a[mid] >aim)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return -1;
}

int TAlgorithmSortMi::SignReversal(int a)
{
    return ~a+1;
}

void TAlgorithmSortMi::HeapSort(int*a , int len)
{
    if(a == NULL || len < 1) return;

    BuildMaxHeap(a, len);
    for(int pos = len-1; pos>1; --pos)
    {
        swapInt(a[1], a[pos]);
        MaxHeapify(a, 1, pos-1);
    }
}

void TAlgorithmSortMi::MaxHeapify(int* a, int pos, int maxSize)
{
    int left = pos<<1;
    int right = left + 1;
    int largest = pos;
    if( left<=maxSize && a[largest]<a[left])
        largest = left;
    if(right<=maxSize && a[largest]<a[right])
        largest = right;
    if(largest != pos)
    {
        swapInt(a[pos], a[largest]);
        MaxHeapify(a, largest, maxSize);
    }

}

void TAlgorithmSortMi::BuildMaxHeap(int *a, int len)
{
    int beginIndex = ((len-1)>>1);
    for(int pos = beginIndex; pos>0; pos--)
    {
        MaxHeapify(a, pos, len-1);
    }
}


void TAlgorithmSortMi::MergeSort(int*a, int len)
{
    int* iBuffer = new int[len];
    MergeSort(a, 0, len-1, iBuffer);
    delete iBuffer;
}

void TAlgorithmSortMi::MergeArray(int *a, int beginPos, int midPos, int lastPos, int *temp)
{
    //初始化
    int iAbegin = beginPos;
    int iBegin = midPos+1;
    int iMbegin = 0;
    //比较

    while(iAbegin<=midPos && iBegin<=lastPos)
    {
        if(a[iAbegin] <= a[iBegin])
            temp[iMbegin++] = a[iAbegin++];
        else
            temp[iMbegin++] = a[iBegin++];
    }

    while(iAbegin <=midPos)
    {
        temp[iMbegin++] = a[iAbegin++];
    }
    while(iBegin <= lastPos)
    {
        temp[iMbegin++] = a[iBegin++];
    }
    //收尾
    for(int pos =0; pos<iMbegin; ++pos)
        a[beginPos+pos] = temp[pos];
    //赋值
}

void TAlgorithmSortMi::MergeSort(int *a, int beginPos, int lastPos, int* temp)
{
    if(beginPos>=lastPos) return;    ///beginPos>lastPos  没有“=”，陷入死循环
    //std::cout<<"beginPos:"<<beginPos<<" lastpos:"<<lastPos<<std::endl;
    int midPos = (beginPos + lastPos) >> 1;
    MergeSort(a, beginPos, midPos, temp);
    MergeSort(a, midPos+1,  lastPos, temp);
    MergeArray(a, beginPos, midPos, lastPos, temp);
}

void TAlgorithmSortMi::PrintFullCombination( char* str)
{
    int iLen = strlen(str);
    std::cout<<"=====iLen: "<<iLen<<std::endl;
    PrintFullCombination(str, 0, iLen-1);
}

void TAlgorithmSortMi::PrintFullCombination(char* str, int ibegin, int ilast)
{
    if(ibegin == ilast)
    {
        std::cout<<str<<std::endl;
        return ;
    }
    for(int ipos = ibegin; ipos<=ilast; ++ipos)
    {
        ///
        swapCharPtr(str+ipos, str+ibegin);
        ///
        PrintFullCombination(str, ibegin+1, ilast);
        ///
        swapCharPtr(str+ipos, str+ibegin);
    }
}

/**************************************/
/*** bitmap   *************************/
/**************************************/
///bitmap
BitMap::BitMap(unsigned int num)
{
    m_len = num;
    m_len = (m_len+31)/32;
    m_bitMap = new unsigned int[m_len];
    memset(m_bitMap, 0, m_len*8);
}

BitMap::~BitMap()
{
    delete m_bitMap;
}

bool BitMap::SetBit(unsigned int num)
{
    if(num > m_len*8) return false;
    m_bitMap[num/32] |= 1<<(num%32);
    return true;
}

bool BitMap::ClearBit(unsigned int num)
{
    if(num > m_len*8) return false;
    m_bitMap[num/32] &= ~(1<<(num%32));
}

bool BitMap::FindBit(unsigned int num)
{
    if(num > m_len*8) return false;
    return ((m_bitMap[num / 32] >> (num % 32)) & 1);

}

bool BitMap::ClearAllBit()
{
    memset(m_bitMap, 0, m_len*8);
    return true;
}

void BitMap::printBit()
{
    for (int i = 0; i < m_len*8; i++)
    {
        if(i%8==0)
            std::cout<<"\n arry["<<(i/8)<<"]:";
        if ((m_bitMap[i / 32] >> (i % 32)) & 1)
            putchar('1');
        else
            putchar('0');
    }
    putchar('\n');
}

    ///s输出最大n为十进制数据 1，2，3.。。。。999...999
void TAlgorithmSortMi::printMaxNDigits(int n)
{
    char* number = new char[n+1];
    memset(number, '0', n);
    number[n] = '\0';
    int nom =0;
    while(!Increment(number))
    {
        std::cout<<"    ";
        nom++;
        if(nom%5==0)
            std::cout<<std::endl;
        printCharNum(number);

    }
    delete []number;
}
bool TAlgorithmSortMi::Increment(char* number)
{

    //cout<<"increment +1 "<<endl;
    bool overflow = false;
    int takeover = 0; //进位
    int iLen = strlen(number);
    //cout<<"iLen="<<iLen<<endl;
    for(int i=iLen-1; i>=0; --i)
    {
        int iSum = number[i]-'0'+takeover;  //第i位数据加上进位数据
        if(i == iLen-1)
            iSum++;//最低位数据加一
        //cout<<"increment +1 iSum++  "<<endl;

        if(iSum >=10)
        {
            //cout<<"increment +1 iSum>=10  "<<endl;
            if(i==0)
            {
                overflow = true;
                break;
            }

            else
            {
                iSum -= 10;
                takeover = 1;
                number[i] = iSum + '0';
            }

        }
        else
        {
            //cout<<"increment +1 iSum<10  "<<endl;
            number[i] = iSum + '0';
            break;
        }
    }
    return overflow;
}

void TAlgorithmSortMi::printCharNum(char* number)
{
    bool beginflag = false;
    int iLen = strlen(number);
    for(int pos=0; pos<iLen; ++pos)
    {
        if(number[pos]!='0' && !beginflag)
            beginflag = true;

        if(beginflag)
            std::cout<<number[pos];
    }
}
///
///reverseWords
void TAlgorithmSortMi::ReverseWords(char* words)
{
    char* head = words;
    char* end = head;
    std::cout<<"&words[0]:"<<&words<<std::endl;
    while(*end!='\0')
        end++;
    ReverseWords(head, end-1);
    ///*
    head = end = words;
    while(*head!='\0')
    {
        if(*head == ' ')
        {
            head++;
            end++;// = head;
        }else if(*end == ' '|| *end==0x00)
        {
            //
            ReverseWords(head, end-1);
            head = end;
        }
        else
        {
            end++;
        }
    }
    ///*/
}

void TAlgorithmSortMi::ReverseWords(char* begin, char* end)
{
    ///
    if(begin==NULL || end==NULL)
        return;
    std::cout<<&begin<<":"<<*begin<<"|"<<&end<<":"<<*end<<"|"<<std::endl;
    while(begin<end)
    {
        std::cout<<"loop"<<*begin<<":"<<*end<<std::endl;
        swapChar(*begin++,*end--);
        //swapChar(*begin,*end);
        //begin++;
        //end--;


    }
}

int glocal_a;
