
#include "consistHash.h"
#include "md5.h"
#include <algorithm>
#include <iostream>
#include <string.h>
#include <assert.h>

//ʵ��ڵ�
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

    /*��ȡ����ʾ*/
    const char * CNode_s::getIden()
    {
        return m_ID.c_str();
    }

    /*��ȡʵ���������������*/
    int CNode_s::getVNodeCount(){ return vNodeCount;}

    /*����ʵ��������ֵ*/
    bool CNode_s::setData(const string& name, const string& value)
    {
        return true;
    }
    /*��ȡʵ��������ֵ*/
    bool CNode_s::getData(const string& name, string& value)
    {
        return true;
    }

//������
    CVirtualNode_s::CVirtualNode_s()
    {
        node = NULL;
    }
    CVirtualNode_s::CVirtualNode_s(CNode_s * pNode)
    {
        node = pNode;
    }

    /*������������ָ���ʵ����*/
    void CVirtualNode_s::setNode_s(CNode_s * pNode)
    {
        node = pNode;
    }

    /*��ȡ��������ָ���ʵ����*/
    CNode_s * CVirtualNode_s::getNode_s()
    {
        return node;
    }

    /*����������hashֵ*/
    void CVirtualNode_s::setHash(long pHash)
    {
        hash = pHash;
    }

    /*��ȡ������hashֵ*/
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
//��ϣ��
unsigned long CMD5HashFun::getHashVal(const char * instr)
{
    int i;
    unsigned long hash = 0;
    unsigned char digest[16];

    /*����MD5��غ���������instr��MD5�룬����digest*/
	MD5_CTX context;
	MD5Init(&context);
    MD5Update(&context, (unsigned char *)instr, strlen(instr));
    MD5Final(digest, &context);

    /* ÿ�ĸ��ֽڹ���һ��32λ������
    ���ĸ�32λ������ӵõ�instr��hashֵ����������� */
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
    /*����hash����*/
    assert(pFunc!=NULL);
    this->func = pFunc;
    this->vNodes = 0;
    /*��ʼ�������*/
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
    /*���������㲢���뵽�������*/
    for(int i=0;i<vCount;i++)
    {
        virtualNode = new CVirtualNode_s(pNode);
        /*����str+��i���ķ���������ͬ��iden�������ں����hashֵ����*/
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
            vnode_List.push_back(virtualNode); //�������ݲ�����ɺ���Ҫ����SortNode��������
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
    /*����ʵ����������������������ɾ��*/
    for(int i=0;i<vCount;i++)
    {
        itoa(i,num,10);
        strcat(str,num);/*���ø÷���������ͬ��iden��*/
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
    while(low<=high)   //low<high �ᵼ�²���©�� low=high
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
    /*�ں�����в���keyֵ��key�����С�Ľ��*/
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

