
#ifndef _ALGORITHM_SORT_H
#define _ALGORITHM_SORT_H
extern int glocal_a;

class TAlgorithmSortMi
{
public:
    ///��������
    static void QuickSort(int* a, int len);
    ///ð������
    static void MaopaoSort(int* a, int len);
    ///��������
    static void InsertSort(int*a , int len);
    ///������
    static void HeapSort(int*a , int len);
    ///�鲢����
    static void MergeSort(int*a, int len);
    ///��ż�������ֶ��в���ֻ������������������
    static void FindBitNum(int* a, int len);
    ///���ֲ���
    static int BinarySearch(int* a, int len, int aim);
    ///�鿴number�ж��ٸ�1
    static int HowManyOne(int number);
    ///tools
    ///��ӡ����
    static void printSort(int *a, int len);
    ///��ӡ����ָ������
    static void printSort(int *a, int pos,int len);
    ///������ 1 -> -1
    static int SignReversal(int a);
    ///��ӡ�ַ���ȫ����
    static void PrintFullCombination(char* str);

    ///s������nΪʮ�������� 1��2��3.��������999...999
    static void printMaxNDigits(int n);
    static bool Increment(char* number);
    static void printCharNum(char* number);

    ///reverseWords
    static void ReverseWords(char* words);
private:
    ///�ָ�
    static int partition(int *a, int low, int high);
    ///����
    static void QuickSort(int* a, int be, int hi);
    ///����
    static void swapInt(int &a, int& b);
    static void swapChar(char &a, char& b);
    static void swapCharPtr(char *a, char* b);
    ///����
    static void MaxHeapify(int* a, int pos, int maxSize);
    ///���󶥶�
    static void BuildMaxHeap(int *a, int len);
    ///�������ֵ�һ��bit��1��λ��
    static unsigned int BitIndex(int num);
    ///�鿴����ָ��bit�ǲ���1
    static bool HasBit(int num, unsigned int index);
    ///�ϲ�������������
    static void MergeArray(int *a, int beginPos, int midPos, int lastPos, int *temp);
    ///�鲢����
    static void MergeSort(int *a, int beginPos, int lastPos, int* temp);
    ///ȫ����
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


