#include "hashtree.h"
/*
template<class T1, class T2>
HashNode<T1,T2>::HashNode()
{
	occupied=false;
	memset(child, NULL, SIZE*sizeof(HashNode<T1,T2>*));
}

template<class T1, class T2>
HashNode<T1,T2>::HashNode(T1 key, T2 value)
{
	this->m_key = key;
	this->m_value = value;
	occupied=false;
	memset(child, NULL, SIZE*sizeof(HashNode<T1,T2>*));
}

template<class T1, class T2>
HashNode<T1,T2>::~HashNode()
{

}



//////////////////////////////////////
template<class T1, class T2>
HashTree<T1,T2>::HashTree()
{
	root = new HashNode<T1,T2>;
}

template<class T1, class T2>
HashTree<T1,T2>::~HashTree()
{

}

template<class T1, class T2>
void HashTree<T1,T2>::InsertNode(T1 key, T2 value)
{
	Insert(root,0,key,value);
}

template<class T1, class T2>
void HashTree<T1,T2>::Insert(HashNode<T1, T2> *hashNode, int level, T1 key, T2 value)//插入结点
{
     if(hashNode->occupied == false)
	 {
		 hashNode->m_key = key;
		 hashNode->m_value = value;
		 hashNode->occupied = true;
		 return;
	 }

	 int index = key%Prime[level];

	 if (hashNode->child[index] == NULL)
	 {
          hashNode->child[index] = new HashNode<T1,T2>;
	 }

     level += 1;
	 Insert(hashNode->child[index], level, key, value);

}

template<class T1, class T2>
bool HashTree<T1,T2>::FindNode(T1 key, T2 &value)
{
     return Find(root, 0, key, value);
}

template<class T1, class T2>
bool HashTree<T1,T2>::Find(HashNode<T1,T2> *hashNode, int level, T1 key, T2 value)//查找
{
	 if (hashNode->occupied == true)
	 {
		 if (hashNode->m_key == key)
		 {
			 value = hashNode->m_value;
			 return true;
		 }
	 }

	 int index = key%Prime[level];
	 if (hashNode->child[index] == NULL)
	 {
		 return false;
	 }

	 level += 1;
	 return Find(hashNode->child[index], level, key, value);
}

template<class T1, class T2>
void HashTree<T1,T2>::DeleteNode(T1 key)
{
    Delete(root, 0, key);
}

template<class T1, class T2>
void HashTree<T1,T2>::Delete(HashNode<T1,T2> *hashNode, int level, T1 key)//删除结点
{
   if (hashNode->occupied == true)
   {
	   if (hashNode->m_key == key)
	   {
		   hashNode->occupied = false;
		   cout << "关键字为" << key << "结点已被删除！" << endl;
		   return;
	   }
   }

   int index = key%Prime[level];
   if (hashNode->child[index] == NULL)
   {
	   cout << "该关键字不存在！" << endl;
	   return;
   }

   level += 1;
   Delete(hashNode->child[index], level, key);
}
*/
