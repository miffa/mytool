#include <string>
#include <vector>
using namespace std;

/*************/
/**ʵ����**/
/*************/
class CNode_s
{
public:
/*���캯��*/
    CNode_s();
    CNode_s(char * pIden , int pVNodeCount);

    bool SetAddr(const string& ip, int port);

    /*��ȡ����ʾ*/
    const char * getIden();

    /*��ȡʵ���������������*/
    int getVNodeCount();

    /*����ʵ��������ֵ*/
    bool setData(const string& name, const string& value);
    /*��ȡʵ��������ֵ*/
    bool getData(const string& name, string& value);

    bool Connect();

    private:
        string m_ID;/*����ʾ��*/
        int vNodeCount; /*��������Ŀ*/
        int m_fd ;/*���ݽ��*/
        string m_ip;
        int m_port;
};

/*************/
/**������**/
/*************/
class CVirtualNode_s
{
public:
    /*���캯��*/
    CVirtualNode_s();
    CVirtualNode_s(CNode_s * pNode);

    /*������������ָ���ʵ����*/
    void setNode_s(CNode_s * pNode);

    /*��ȡ��������ָ���ʵ����*/
    CNode_s * getNode_s();

    /*����������hashֵ*/
    void setHash(long pHash);

    /*��ȡ������hashֵ*/
    unsigned long getHash()const;
    bool operator < (const CVirtualNode_s& ano);
    bool operator == (const CVirtualNode_s& ano);
    bool operator != (const CVirtualNode_s& ano);
private:
    unsigned long hash; /*hashֵ*/
    CNode_s * node; /*��������ָ���ʵ����*/
};

/*****����ڵ�������*******/
bool LessOperFunc(CVirtualNode_s* one, CVirtualNode_s* ano);

/********************/
/******��ϣ����*****/
/********************/
/*����Hash������ӿڣ����ڼ������hashֵ*/
class CHashFun
{
public:
virtual unsigned long getHashVal(const char *) = 0;
};


/*��MD5�㷨�������hashֵ���̳�CHashFun����*/
class CMD5HashFun : public CHashFun
{
public:
virtual unsigned long getHashVal (const char * );
};


class CConHash
{
public:
    /*���캯��*/
    CConHash(CHashFun * pFunc);

    /*����hash����*/
    void setFunc(CHashFun * pFunc);

    /*����ʵ���� , 0����ɹ� , -1����ʧ��*/
    int addNode_s(CNode_s * pNode);

    /*ɾ��ʵ���� , 0����ɹ� , -1����ʧ��*/
    int delNode_s(CNode_s * pNode);

    bool SortNode();
    void print();

    /*����ʵ����*/
    CNode_s * lookupNode_s(const char * object);
    int FindNode_s(unsigned long hashval);

    /*��ȡһ����hash�ṹ����������������*/
    int getVNodes();
private:
    /*Hash����*/
    CHashFun * func;
    /*�������ܸ���*/
    int vNodes;
    /*�洢������ĺ����*/
    vector<CVirtualNode_s*> vnode_List;
};


