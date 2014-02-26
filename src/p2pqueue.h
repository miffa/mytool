
#ifndef _P2PQUEUE_H
#define _P2PQUEUE_H

template<class T>
struct P2PChain
{
  P2PChain(T *v)
  {
    value = v;
    next = NULL;
  }

  ~P2PChain() { }

  T *value;
  P2PChain *next;
};

template<class T>
class P2PQueue
{
public:
  P2PQueue()
  {
    head_ = tail_ = NULL;
  }

  ~P2PQueue()
  {
    P2PChain<T> *tmp;
    while(head_)
    {
      tmp = head_;
      head_ = head_->next;
      delete tmp->value;
      delete tmp;
    }
  }

  bool Add(P2PChain<T> *head, P2PChain<T> *tail)
  {
    if (!head_)
    {
      head_ = head;
      tail_ = tail;
      return true;
    }

    tail_->next = head;
    tail_ = tail;
    return true;
  }

  P2PChain<T> * Remove()
  {
    P2PChain<T> *tmp = head_;
    head_ = tail_ = NULL;
    return tmp;
  }

private:

  P2PChain<T> *head_;
  P2PChain<T> *tail_;

};


#endif // _P2PQUEUE_H
