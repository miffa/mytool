
#include "consistHash.h"
#include "md5.h"
#include <algorithm>
#include <iostream>
#include <string.h>
#include <assert.h>

//实体节点
    CNode_s::CNode_s()
    {

    }
    CNode_s::CNode_s(char * pIden , int pVNodeCount)
    {
        m_ID = pIden;
        vNodeCount = pVNodeCount;
    }

    bool CNode_s::SetAddr(const string& ip, int port)
    {
        m_ip = ip;
        m_port = port;
    }

    /*获取结点标示*/
    const char * CNode_s::getIden()
    {
        return m_ID.c_str();
    }

    /*获取实体结点的虚拟结点数量*/
    int CNode_s::getVNodeCount(){ return vNodeCount;}

    /*设置实体结点数据值*/
    bool CNode_s::setData(const string& name, const string& value)
    {
        return true;
    }
    /*获取实体结点数据值*/
    bool CNode_s::getData(const string& name, string& value)
    {
        return true;
    }

//虚拟类
    CVirtualNode_s::CVirtualNode_s()
    {
        node = NULL;
    }
    CVirtualNode_s::CVirtualNode_s(CNode_s * pNode)
    {
        node = pNode;
    }

    /*设置虚拟结点所指向的实体结点*/
    void CVirtualNode_s::setNode_s(CNode_s * pNode)
    {
        node = pNode;
    }

    /*获取虚拟结点所指向的实体结点*/
    CNode_s * CVirtualNode_s::getNode_s()
    {
        return node;
    }

    /*设置虚拟结点hash值*/
    void CVirtualNode_s::setHash(long pHash)
    {
        hash = pHash;
    }

    /*获取虚拟结点hash值*/
    unsigned long CVirtualNode_s::getHash()const
    {
        return hash;
    }
    /*
    bool CVirtualNode_s::operator < (const CVirtualNode_s& ano)
    {
        return hash < ano.getHash();
    }
    bool CVirtualNode_s::operator == (const CVirtualNode_s& ano)
    {
        cout<<"CVirtualNode_s::operator =="<<endl;
        return hash == ano.getHash();
    }
    bool CVirtualNode_s::operator != (const CVirtualNode_s& ano)
    {
        cout<<"CVirtualNode_s::operator !="<<endl;
        return hash != ano.getHash();
    }*/

bool LessOperFunc(CVirtualNode_s* one, CVirtualNode_s* ano)
{
    return one->getHash() < ano->getHash();
}
//哈希类
unsigned long CMD5HashFun::getHashVal(const char * instr)
{
    int i;
    unsigned long hash = 0;
    unsigned char digest[16];

    /*调用MD5相关函数，生成instr的MD5码，存入digest*/
	MD5_CTX context;
	MD5Init(&context);
    MD5Update(&context, (unsigned char *)instr, strlen(instr));
    MD5Final(digest, &context);

    /* 每四个字节构成一个32位整数，
    将四个32位整数相加得到instr的hash值（可能溢出） */
    for(i = 0; i < 4; i++)
    {
        hash += ((unsigned long)(digest[i*4 + 3]&0xFF) << 24)
                | ((unsigned long)(digest[i*4 + 2]&0xFF) << 16)
                | ((unsigned long)(digest[i*4 + 1]&0xFF) << 8)
                | ((unsigned long)(digest[i*4 + 0]&0xFF));
    }
    cout<<"instr("<<instr<<") gethashval=" <<hash<<"\""<< endl;
    return hash;
}

//consist hash class
CConHash::CConHash(CHashFun * pFunc)
{
    /*设置hash函数*/
    assert(pFunc!=NULL);
    this->func = pFunc;
    this->vNodes = 0;
    /*初始化红黑树*/
    vnode_List.reserve(1000);
}

int CConHash::addNode_s(CNode_s * pNode)
{
    if(pNode==NULL) return -1;
    int vCount = pNode->getVNodeCount();
    if(vCount<=0) return -1;
    CVirtualNode_s * virtualNode ;
    char str [100];
    char num[10];
    strcpy(str,pNode->getIden());
    long hash = 0;
    /*生成虚拟结点并插入到红黑树中*/
    for(int i=0;i<vCount;i++)
    {
        virtualNode = new CVirtualNode_s(pNode);
        /*采用str+“i”的方法产生不同的iden串，用于后面的hash值计算*/
        itoa(i,num,10);
        strcat(str,num);
        hash = func->getHashVal(str);
        virtualNode->setHash(hash);
        //vector<CVirtualNode_s*>::iterator iter = find(vnode_List.begin(), vnode_List.end(), virtualNode);
        //if(iter != vnode_List.end())
        if(FindNode_s(hash) >= 0)
        {
            cout<<" "<<str<<":"<<hash<<" has already in list "<<endl;
            delete virtualNode;
            virtualNode = NULL;
            continue;
        }
        else
            vnode_List.push_back(virtualNode); //所有数据插入完成后，需要调用SortNode进行排序
        vNodes++;
    }
    return 0;
}

int CConHash::delNode_s(CNode_s * pNode)
{
    if(pNode==NULL) return -1;
    char str [100];
    char num [10];
    strcpy(str,pNode->getIden());
    int vCount = pNode->getVNodeCount();
    unsigned long hash = 0;
    CVirtualNode_s * node = NULL;
    /*将该实体结点产生的所有虚拟结点进行删除*/
    for(int i=0;i<vCount;i++)
    {
        itoa(i,num,10);
        strcat(str,num);/*采用该方法产生不同的iden串*/
        hash = func->getHashVal(str);
        int pos = 0;
        if((pos=FindNode_s(hash)) >= 0)
        {
            cout<<" "<<str<<":"<<hash<<"  in list delete it!!! "<<endl;
            delete vnode_List[pos];
            vnode_List[pos] = NULL;
            vnode_List.erase(vnode_List.begin()+pos);
            vNodes--;
        }
        else
             cout<<" "<<str<<":"<<hash<<" not  in list , not need delete it!!! "<<endl;
    }
    return 0;
}

int CConHash::FindNode_s(unsigned long hashval)
{
    int len = vnode_List.size();
    int low  = 0;
    int high  = len-1;
    int midPos = 0;
    while(low<=high)   //low<high 会导致查找漏掉 low=high
    {
        midPos = (high+low) >>1;
        if(vnode_List[midPos]->getHash() == hashval)
            return midPos;
        if(vnode_List[midPos]->getHash() > hashval)
            high = midPos - 1;
        else
            low = midPos + 1;
    }
    return -1;
}

bool CConHash::SortNode()
{
    if(vnode_List.size() == 0)
        return false;
    std::sort(vnode_List.begin(), vnode_List.end(), LessOperFunc);
    return true;
}
void CConHash::print()
{
    cout<<"hash:"<<endl;
    vector<CVirtualNode_s*>::iterator iter = vnode_List.begin();
    for(; iter!=vnode_List.end(); ++iter)
    {
        cout<<(*iter)->getHash()<<":"<<(*iter)->getNode_s()->getIden()<<"  "<<endl;
    }
    cout<<endl;
}

CNode_s * CConHash::lookupNode_s(const char * object)
{
    if(object==NULL||this->vNodes==0) return NULL;
    long key = this->func->getHashVal(object);
    CNode_s* retNode = NULL;
    /*在红黑树中查找key值比key大的最小的结点*/
    vector<CVirtualNode_s*>::iterator iter = vnode_List.begin();
    for(; iter!=vnode_List.end(); ++iter)
    {
        if((*iter)->getHash() > key)
        {
            cout<<object<<"get  node("<<(*iter)->getHash()<<")  "<<endl;
            break;
        }
        else
            retNode = (*iter)->getNode_s();
    }
    if(retNode == NULL)
    {
        cout<<object<<"get default node"<<endl;
        retNode = (*(vnode_List.begin()))->getNode_s();
    }
    return retNode;
}

int CConHash::getVNodes()
{
    return this->vNodes;
}


