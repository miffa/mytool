#include "trietree.h"


Trie::Trie ()
{
    root = NULL ;
}

Trie::~Trie ()
{

}

Node* Trie ::CreateNewNode( char ch )//����һ���µĽ��
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

void Trie ::InitTrie() //����һ�ÿ���
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
           cout<<" ��Ϊ�գ�"<< endl;
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

void Trie ::Insert( const char chars[], int len ) //�� Trie���в��볤��Ϊlen���ַ���
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

void Trie ::Delete() //���õݹ�ɾ��������
{
   DeleteTree(root );
}

void Trie ::DeleteTree( Node *&Root )//���õݹ�ɾ�������� ע��˴�Ӧ�ü���Ӧ��
{
      if (Root == NULL) //�ݹ����
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

YsTreeNode* YsTireTree::CreateNewNode (const string& str)// ����һ���½��
{
    YsTreeNode* treeNode = new (nothrow) YsTreeNode();
    if(treeNode == NULL)
        return NULL;
    treeNode->COMPLETED = false;
    treeNode->strValue = str;
    treeNode->strClassName = "";
    return treeNode;
}

bool YsTireTree::InitTrie ()//��ʼ�� Trie��
{
    m_treeRoot = CreateNewNode("");
}

bool YsTireTree::Find (const STR_LIST& strNameList, string& value)// �ҵ�����Ϊ len���ַ���
{
    if(m_treeRoot == NULL)
        return false;
    YsTreeNode* ptrNode = m_treeRoot;
    for(STR_LIST_CONST_ITER it = strNameList.begin(); it!=strNameList.end(); ++it)
    {
        YsTreeNode* ptrTmpNode = ptrNode->m_child.FindPrefix(*it);
        if(ptrTmpNode == NULL)
        {
            //û�ҵ���ֹͣ
            cout<<"find "<<*it<<" failure "<<endl;
            break;
        }
        cout<<"find "<<*it<<" success, will find next word in its child "<<endl;
        //��������Ӧ�ڵ���Ѱ��
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
            //hashMap��û�У� �½��ڵ㣬insert
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
        //��������Ӧ�ڵ���Ѱ��
        ptrNode = ptrTmpNode;
    }
    ptrNode->COMPLETED = true;
    ptrNode->strClassName = value;
    return true;
}
void YsTireTree::Delete ()//ɾ��������
{
    DeleteTree(m_treeRoot);
}


void YsTireTree::DeleteTree (YsTreeNode* item)
{
    item->m_child.ClearMap();
}
