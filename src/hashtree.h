
// HashTree.cpp : �������̨Ӧ�ó������ڵ㡣
//ѡ�������ֱ��㷨����һ�ù�ϣ��
#include <iostream>
using namespace std;

const int mSIZE = 32;//��10������Ϊ29�����������ܴ���32����������Ĺ̶���������Ϊ32
const int Prime[10] = {2,3,5,7,11,13,17,19,23,29};
//��ϣ�������
template<class T1, class T2>
class HashNode
{
public:
	HashNode();//Ĭ�Ϲ��캯��
	HashNode(T1 key, T2 value);//һ�㹹�캯��
	~HashNode();

public:
    T1 m_key;  //���Ĺؼ���
	T2 m_value; //�������ݶ���
	bool occupied; //����Ƿ�ռ�ݣ�����Ǳ�ʾ���Ĺؼ�����Ч
	HashNode *child[mSIZE];  //�����ӽ������
};

template<class T1, class T2>
HashNode<T1,T2>::HashNode()
{
	occupied=false;
	memset(child, NULL, mSIZE*sizeof(HashNode<T1,T2>*));
}

template<class T1, class T2>
HashNode<T1,T2>::HashNode(T1 key, T2 value)
{
	this->m_key = key;
	this->m_value = value;
	occupied=false;
	memset(child, NULL, mSIZE*sizeof(HashNode<T1,T2>*));
}

template<class T1, class T2>
HashNode<T1,T2>::~HashNode()
{

}

//��ϣ������
template<class T1, class T2>
class HashTree
{
public:
	HashTree();
	~HashTree();
	void InsertNode(T1 key, T2 value);
	bool FindNode(T1 key, T2 &value);
	void DeleteNode(T1 key);


private:
	HashNode<T1,T2> *root;
	void Insert(HashNode<T1,T2> *hashNode, int level, T1 key, T2 value);//������
	bool Find(HashNode<T1,T2> *hashNode, int level, T1 key, T2 value);//����
	void Delete(HashNode<T1,T2> *hashNode, int level,T1 key);//ɾ�����
};

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
void HashTree<T1,T2>::Insert(HashNode<T1, T2> *hashNode, int level, T1 key, T2 value)//������
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
bool HashTree<T1,T2>::Find(HashNode<T1,T2> *hashNode, int level, T1 key, T2 value)//����
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
void HashTree<T1,T2>::Delete(HashNode<T1,T2> *hashNode, int level, T1 key)//ɾ�����
{
   if (hashNode->occupied == true)
   {
	   if (hashNode->m_key == key)
	   {
		   hashNode->occupied = false;
		   cout << "�ؼ���Ϊ" << key << "����ѱ�ɾ����" << endl;
		   return;
	   }
   }

   int index = key%Prime[level];
   if (hashNode->child[index] == NULL)
   {
	   cout << "�ùؼ��ֲ����ڣ�" << endl;
	   return;
   }

   level += 1;
   Delete(hashNode->child[index], level, key);
}

/*
int _tmain(int argc, _TCHAR* argv[])
{
	HashTree<int, int> ht;
	ht.InsertNode(1, 8);
    ht.InsertNode(2, 0);
	ht.InsertNode(3, 4);
	ht.InsertNode(4, 7);
	ht.InsertNode(5, 4);
	ht.InsertNode(6, 3);
	ht.InsertNode(7, 8);

	int nvalue = 0;
	cout << ht.FindNode(5,nvalue) << endl;
	cout << ht.FindNode(9,nvalue) << endl;

	ht.DeleteNode(4);
	ht.DeleteNode(10);

	cout<<"baasdfas"<<endl;
	system("pause");
	return 0;
}
*/
