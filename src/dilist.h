#ifndef __DILIST_H__
#define __DILIST_H_


template <typename T>
class INode {
	public:
		T data;
		INode* prev;
		INode* next;

		INode(const T& t):data(t), prev(NULL), next(NULL) {};
		~INode() {};

};

template<typename T>
class Dilist{
	public:

		Dilist();
		~Dilist();
		bool IsEmpty();
		int Clear();
		void Insert(INode<T> * const node);
		void Delete(INode<T>* node);
		T* Front();
		int GetSize();
		void Shift();

	private:
		INode<T>* _head;
		INode<T>* _tail;
		int _size;

};

template <typename T>
Dilist<T>::Dilist()
{
	_head = NULL;
	_tail = NULL;
	_size = 0;
}

template <typename T>
Dilist<T>::~Dilist(){
	if ( _head ) {
		Clear();
	}
}



//判断链表是否为空
	template <typename T>
bool Dilist<T>::IsEmpty()
{
	//如果头指针指向的是空，链表为空

	return (0 >= _size) ? true : false;
}

//清空链表
	template <typename T>
int Dilist<T>::Clear()
{
	//删除所有数据，并把头指针指向为空
	INode<T>* temp = _head;

	//遍历链表的数据。如果有数据，删除，然后进入下一个数据
	while(_head)
	{
		_head = _head->next;
		if ( _head ) {
			_head->prev = NULL;
		}
		delete temp;
		temp = _head;
	}

	_tail = NULL;
	_size = 0;

	return 1;
}

template <typename T>
void Dilist<T>::Insert(INode<T> * const node)
{
	if ( NULL == node ) {
		return ;
	}

	if ( _head ) {
		node->next = _head;
		_head->prev = node;
		_head = node;
	} else {
		_head = node;
		_tail = node;
	}
	_size += 1;
}


template <typename T>
void Dilist<T>::Delete(INode<T>* node)
{
	if ( node == NULL ) {
		return;
	}

	INode<T>* temp = node;


	if ( _head == node ) {
		_head = _head->next;
		if ( _head ) {
			_head->prev = NULL;
		}
		else {
			_tail = NULL;
		}
	}
	else if ( _tail == node ) {
		_tail = _tail->prev;
		if (_tail){
			_tail->next = NULL;
		}else {
			_head = NULL;
		}
	}
	else {

		node->prev->next = node->next;
		node->next->prev = node->prev;
	}

	delete temp;
	temp = NULL;

	_size -= 1;

	return;

}

template <typename T>
T*  Dilist<T>::Front()
{
	return &(_head->data);
}


template <typename T>
void Dilist<T>::Shift()
{
	if (_size > 1) {
		INode<T>* temp = _head;
		_head = _head->next;
		_head->prev = NULL;

		_tail->next = temp;
		temp->prev = _tail;
		_tail = _tail->next;
		_tail->next = NULL;
	}

	return;
}

template <typename T>
int Dilist<T>::GetSize()
{
	return _size;
}


#endif

