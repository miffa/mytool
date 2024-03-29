// Trie.cpp : 定义控制台应用程序的入口点。
//Trie 称为字典树，单词查找树或者前缀树fx.h"

#include <assert.h>

#include <iostream>
#include <string>
#include <list>
using namespace std;
#include <ext/hash_map>
using namespace __gnu_cxx;


//char前缀树
const int MAX_NUM = 26;
//Trie 树的结点类型
struct Node
{
      bool COMPLETED ;//COMPLETED为 true时表示目前产生的一个字符串
      char ch ;
      Node* child[ MAX_NUM]; //26-tree->a, b ,c, .....z
};
//Trie 树类型
class Trie
{
public :
      Trie();
     ~ Trie();
      Node* CreateNewNode (char ch);// 创建一个新结点
      void InitTrie ();//初始化 Trie树
      int CharToindex (char ch);// 找到字母对应的数组下标
      int Find (const char chars [], int len);// 找到长度为 len的字符串
      void Insert (const char chars [], int len);// 插入长度为 len的字符串
      void Delete ();//删除整棵树

private :
      void DeleteTree (Node *& root);
      Node* root ; //根结点
};


//前缀树
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
//Trie 树的结点类型
struct YsTreeNode
{
      bool COMPLETED ;//COMPLETED为 true时表示目前产生的一个字符串
      string strValue ;
      string strClassName;
      YsTreeMapOper m_child; //
};

//Trie 树类型
class YsTireTree
{
public :

      YsTireTree();
     ~ YsTireTree();
      YsTreeNode* CreateNewNode (const string& str);// 创建一个新结点
      bool InitTrie ();//初始化 Trie树
      bool Find(const STR_LIST&, string& value);// 找到长度为 len的字符串
      bool Insert(const STR_LIST&, const string& value);// 插入长度为 len的字符串
      void Delete();//删除整棵树

private :
      void DeleteTree (YsTreeNode* item);
      //YsTreeMapOper m_tireTreeRoot ; //根结点
      YsTreeNode* m_treeRoot;
};


