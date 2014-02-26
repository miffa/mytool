#include "trietree.h"


Trie::Trie ()
{
    root = NULL ;
}

Trie::~Trie ()
{

}

Node* Trie ::CreateNewNode( char ch )//创建一个新的结点
{
    Node *new_node = new Node;
    new_node->ch = ch;
    new_node->COMPLETED = false;

    for(int i=0; i<MAX_NUM ; i++)
    {
        new_node->child [i] = NULL;
    }
    return new_node ;
}

void Trie ::InitTrie() //构建一棵空树
{
      root = CreateNewNode (' ');
}

int Trie ::CharToindex( char ch )
{
      return ch - 'a';
}

int Trie ::Find( const char chars[], int len )
{
      if (root == NULL)
     {
           cout<<" 树为空！"<< endl;
           return 0;
     }

      Node* ptr = root;
      int i = 0;
      while(i < len)
     {
           if(ptr ->child[ CharToindex(chars [i])] == NULL)
          {
               break;
          }
           ptr = ptr ->child[ CharToindex(chars [i])];
           i++;
     }
      return (i == len) && ( ptr->COMPLETED == true);
}

void Trie ::Insert( const char chars[], int len ) //向 Trie树中插入长度为len的字符串
{
      Node* ptr = root;

      for(int i = 0; i < len ; i++)
     {
           if(ptr ->child[ CharToindex(chars [i])] == NULL)
          {
               ptr->child [CharToindex( chars[i ])] = CreateNewNode (chars[ i]);
          }
           ptr = ptr ->child[ CharToindex(chars [i])];
     }
      ptr->COMPLETED = true;
}

void Trie ::Delete() //利用递归删除整棵树
{
   DeleteTree(root );
}

void Trie ::DeleteTree( Node *&Root )//利用递归删除整棵树 注意此处应该加上应用
{
      if (Root == NULL) //递归出口
     {
           return;
     }

      for (int i=0; i<MAX_NUM ; i++)
     {
           if (Root ->child[ i] != NULL )
          {
               DeleteTree(Root ->child[ i]);
          }
     }
//   if(Root->ch == ' ')
//   {
//        cout<<"zha'"<<endl;
//   }
      delete Root ;
      Root = NULL ;
}
/*
int _tmain (int argc, _TCHAR * argv[])
{
      char *a = "ten";
      char *b = "tea";
      Trie trie ;
      trie.InitTrie ();
      trie.Insert (a, 3);
      trie.Insert (b, 3);
      cout<<trie .Find( a,3)<<endl ;
      trie.Delete ();
    cout<<trie .Find( b,3)<<endl ;

      system("pause" );
      return 0;
}
*/


YsTreeMapOper::YsTreeMapOper()
{

}

YsTreeMapOper::~YsTreeMapOper()
{
    ClearMap();
}

YsTreeNode* YsTreeMapOper::FindPrefix(const string& str)
{
   YsTree_Map_Iter iter = m_hashMap.find(str);
   if(iter == m_hashMap.end())
        return NULL;
   else
        return iter->second;
}

bool YsTreeMapOper::InsertPrefix(const string& name, YsTreeNode* value)
{
    return m_hashMap.insert(YsTree_Map_Pair(name, value)).second;
}

bool YsTreeMapOper::ClearMap()
{
    for(YsTree_Map_Iter iter = m_hashMap.begin(); iter != m_hashMap.end(); ++iter)
    {
        if(iter->second != NULL)
        {
            delete iter->second;
            iter->second = NULL;
        }
    }
}

YsTireTree::YsTireTree()
{

}

YsTireTree::~YsTireTree()
{
    Delete();
}

YsTreeNode* YsTireTree::CreateNewNode (const string& str)// 创建一个新结点
{
    YsTreeNode* treeNode = new (nothrow) YsTreeNode();
    if(treeNode == NULL)
        return NULL;
    treeNode->COMPLETED = false;
    treeNode->strValue = str;
    treeNode->strClassName = "";
    return treeNode;
}

bool YsTireTree::InitTrie ()//初始化 Trie树
{
    m_treeRoot = CreateNewNode("");
}

bool YsTireTree::Find (const STR_LIST& strNameList, string& value)// 找到长度为 len的字符串
{
    if(m_treeRoot == NULL)
        return false;
    YsTreeNode* ptrNode = m_treeRoot;
    for(STR_LIST_CONST_ITER it = strNameList.begin(); it!=strNameList.end(); ++it)
    {
        YsTreeNode* ptrTmpNode = ptrNode->m_child.FindPrefix(*it);
        if(ptrTmpNode == NULL)
        {
            //没找到，停止
            cout<<"find "<<*it<<" failure "<<endl;
            break;
        }
        cout<<"find "<<*it<<" success, will find next word in its child "<<endl;
        //继续在相应节点下寻找
        ptrNode = ptrTmpNode;
    }
    //if(ptrNode == NULL)
    //   return false;
    if(!ptrNode->COMPLETED)
        return false;
    value = ptrNode->strClassName;
    return true;
}
bool YsTireTree::Insert (const STR_LIST& strNameList, const string& value)
{
    YsTreeNode* ptrNode = m_treeRoot;
    for(STR_LIST_CONST_ITER it = strNameList.begin(); it!=strNameList.end(); ++it)
    {
        YsTreeNode* ptrTmpNode = ptrNode->m_child.FindPrefix(*it);
        if(ptrTmpNode == NULL)
        {
            cout<< "insert action : not find  ["<<*it<<"]  in hash , will insert it"<<endl;
            //hashMap中没有， 新建节点，insert
            ptrTmpNode = CreateNewNode(*it);
            if(ptrTmpNode == NULL)
                return false;
            if(!ptrNode->m_child.InsertPrefix(*it, ptrTmpNode))
            {
                delete ptrTmpNode;
                cout<< "insert ["<<*it<<"]  failure"<<endl;
            }
            else
                cout<< "insert ["<<*it<<"]  success"<<endl;
        }
        else
             cout<< "insert action : find  ["<<*it<<"]  in hash, will insert next word in its child"<<endl;
        //继续在相应节点下寻找
        ptrNode = ptrTmpNode;
    }
    ptrNode->COMPLETED = true;
    ptrNode->strClassName = value;
    return true;
}
void YsTireTree::Delete ()//删除整棵树
{
    DeleteTree(m_treeRoot);
}


void YsTireTree::DeleteTree (YsTreeNode* item)
{
    item->m_child.ClearMap();
}

