// Trie.cpp : �������̨Ӧ�ó������ڵ㡣
//Trie ��Ϊ�ֵ��������ʲ���������ǰ׺��fx.h"

#include <assert.h>

#include <iostream>
#include <string>
#include <list>
using namespace std;
#include <ext/hash_map>
using namespace __gnu_cxx;


//charǰ׺��
const int MAX_NUM = 26;
//Trie ���Ľ������
struct Node
{
      bool COMPLETED ;//COMPLETEDΪ trueʱ��ʾĿǰ������һ���ַ���
      char ch ;
      Node* child[ MAX_NUM]; //26-tree->a, b ,c, .....z
};
//Trie ������
class Trie
{
public :
      Trie();
     ~ Trie();
      Node* CreateNewNode (char ch);// ����һ���½��
      void InitTrie ();//��ʼ�� Trie��
      int CharToindex (char ch);// �ҵ���ĸ��Ӧ�������±�
      int Find (const char chars [], int len);// �ҵ�����Ϊ len���ַ���
      void Insert (const char chars [], int len);// ���볤��Ϊ len���ַ���
      void Delete ();//ɾ��������

private :
      void DeleteTree (Node *& root);
      Node* root ; //�����
};


//ǰ׺��
struct StrHashFunc
{
    size_t operator()(const string& singleWord)const
    {
        const char* __s = singleWord.c_str();
        unsigned long __h = 0;
        for ( ; *__s; ++__s)
        __h = 5*__h + *__s;

        return size_t(__h);
        //return __stl_hash_string(singleWord.c_str());
    }
};

struct YsTreeNode;

class YsTreeMapOper
{
public:
    YsTreeMapOper();
    ~YsTreeMapOper();
    YsTreeNode* FindPrefix(const string& name);
    bool InsertPrefix(const string& name, YsTreeNode* value);
    bool ClearMap();
private:
    typedef hash_map<string,YsTreeNode*, StrHashFunc> YsTree_Map;
    typedef hash_map<string,YsTreeNode*, StrHashFunc>::iterator YsTree_Map_Iter;
    typedef hash_map<string,YsTreeNode*, StrHashFunc>::value_type YsTree_Map_Pair;
    YsTree_Map m_hashMap;
};

typedef list<string> STR_LIST;
typedef STR_LIST::iterator STR_LIST_ITER;
typedef STR_LIST::const_iterator STR_LIST_CONST_ITER;
//Trie ���Ľ������
struct YsTreeNode
{
      bool COMPLETED ;//COMPLETEDΪ trueʱ��ʾĿǰ������һ���ַ���
      string strValue ;
      string strClassName;
      YsTreeMapOper m_child; //
};

//Trie ������
class YsTireTree
{
public :

      YsTireTree();
     ~ YsTireTree();
      YsTreeNode* CreateNewNode (const string& str);// ����һ���½��
      bool InitTrie ();//��ʼ�� Trie��
      bool Find(const STR_LIST&, string& value);// �ҵ�����Ϊ len���ַ���
      bool Insert(const STR_LIST&, const string& value);// ���볤��Ϊ len���ַ���
      void Delete();//ɾ��������

private :
      void DeleteTree (YsTreeNode* item);
      //YsTreeMapOper m_tireTreeRoot ; //�����
      YsTreeNode* m_treeRoot;
};


