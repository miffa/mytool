
#ifndef _ALGORITHM_SORT_H
#define _ALGORITHM_SORT_H
extern int glocal_a;

class TAlgorithmSortMi
{
public:
    ///快速排序
    static void QuickSort(int* a, int len);
    ///冒泡排序
    static void MaopaoSort(int* a, int len);
    ///插入排序
    static void InsertSort(int*a , int len);
    ///堆排序
    static void HeapSort(int*a , int len);
    ///归并排序
    static void MergeSort(int*a, int len);
    ///在偶数个数字对中查找只有奇数个的两个数字
    static void FindBitNum(int* a, int len);
    ///二分查找
    static int BinarySearch(int* a, int len, int aim);
    ///查看number有多少个1
    static int HowManyOne(int number);
    ///tools
    ///打印数组
    static void printSort(int *a, int len);
    ///打印数字指定内容
    static void printSort(int *a, int pos,int len);
    ///数字求反 1 -> -1
    static int SignReversal(int a);
    ///打印字符串全排列
    static void PrintFullCombination(char* str);

    ///s输出最大n为十进制数据 1，2，3.。。。。999...999
    static void printMaxNDigits(int n);
    static bool Increment(char* number);
    static void printCharNum(char* number);

    ///reverseWords
    static void ReverseWords(char* words);
private:
    ///分割
    static int partition(int *a, int low, int high);
    ///快排
    static void QuickSort(int* a, int be, int hi);
    ///交换
    static void swapInt(int &a, int& b);
    static void swapChar(char &a, char& b);
    static void swapCharPtr(char *a, char* b);
    ///建堆
    static void MaxHeapify(int* a, int pos, int maxSize);
    ///建大顶堆
    static void BuildMaxHeap(int *a, int len);
    ///查找数字第一个bit是1的位置
    static unsigned int BitIndex(int num);
    ///查看数字指定bit是不是1
    static bool HasBit(int num, unsigned int index);
    ///合并两个有序数组
    static void MergeArray(int *a, int beginPos, int midPos, int lastPos, int *temp);
    ///归并排序
    static void MergeSort(int *a, int beginPos, int lastPos, int* temp);
    ///全排列
    static void PrintFullCombination(char* str, int ibegin, int ilast);

    ///
    static void ReverseWords(char* begin, char* end);
};

/****    bitmap   ***/
    class BitMap
    {
    public:
        BitMap(unsigned int num);
        ~BitMap();
        bool SetBit(unsigned int num);
        bool ClearBit(unsigned int num);
        bool FindBit(unsigned int num);
        bool ClearAllBit();
        void printBit();

    private:
        unsigned int* m_bitMap;
        unsigned int m_len;
    };

#endif


