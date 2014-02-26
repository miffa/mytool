#include <string>
#include <vector>
using namespace std;

/*************/
/**实体结点**/
/*************/
class CNode_s
{
public:
/*构造函数*/
    CNode_s();
    CNode_s(char * pIden , int pVNodeCount);

    bool SetAddr(const string& ip, int port);

    /*获取结点标示*/
    const char * getIden();

    /*获取实体结点的虚拟结点数量*/
    int getVNodeCount();

    /*设置实体结点数据值*/
    bool setData(const string& name, const string& value);
    /*获取实体结点数据值*/
    bool getData(const string& name, string& value);

    bool Connect();

    private:
        string m_ID;/*结点标示串*/
        int vNodeCount; /*虚拟结点数目*/
        int m_fd ;/*数据结点*/
        string m_ip;
        int m_port;
};

/*************/
/**虚拟结点**/
/*************/
class CVirtualNode_s
{
public:
    /*构造函数*/
    CVirtualNode_s();
    CVirtualNode_s(CNode_s * pNode);

    /*设置虚拟结点所指向的实体结点*/
    void setNode_s(CNode_s * pNode);

    /*获取虚拟结点所指向的实体结点*/
    CNode_s * getNode_s();

    /*设置虚拟结点hash值*/
    void setHash(long pHash);

    /*获取虚拟结点hash值*/
    unsigned long getHash()const;
    bool operator < (const CVirtualNode_s& ano);
    bool operator == (const CVirtualNode_s& ano);
    bool operator != (const CVirtualNode_s& ano);
private:
    unsigned long hash; /*hash值*/
    CNode_s * node; /*虚拟结点所指向的实体结点*/
};

/*****虚拟节点排序函数*******/
bool LessOperFunc(CVirtualNode_s* one, CVirtualNode_s* ano);

/********************/
/******哈希函数*****/
/********************/
/*定义Hash函数类接口，用于计算结点的hash值*/
class CHashFun
{
public:
virtual unsigned long getHashVal(const char *) = 0;
};


/*用MD5算法计算结点的hash值，继承CHashFun父类*/
class CMD5HashFun : public CHashFun
{
public:
virtual unsigned long getHashVal (const char * );
};


class CConHash
{
public:
    /*构造函数*/
    CConHash(CHashFun * pFunc);

    /*设置hash函数*/
    void setFunc(CHashFun * pFunc);

    /*增加实体结点 , 0代表成功 , -1代表失败*/
    int addNode_s(CNode_s * pNode);

    /*删除实体结点 , 0代表成功 , -1代表失败*/
    int delNode_s(CNode_s * pNode);

    bool SortNode();
    void print();

    /*查找实体结点*/
    CNode_s * lookupNode_s(const char * object);
    int FindNode_s(unsigned long hashval);

    /*获取一致性hash结构的所有虚拟结点数量*/
    int getVNodes();
private:
    /*Hash函数*/
    CHashFun * func;
    /*虚拟结点总个数*/
    int vNodes;
    /*存储虚拟结点的红黑树*/
    vector<CVirtualNode_s*> vnode_List;
};


