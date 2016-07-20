//An example of a simple double linked list using OOP techniques
#include "PEdll.h"
struct PtNode
{
  long double value;
  PEnode *vertexHEAD;
  PtNode *N;
  PtNode(long double);
};
inline PtNode::PtNode(long double v): value(v),N(NULL),vertexHEAD(NULL){}

class Pt_LinkedList
{
  public:
      Pt_LinkedList();
      ~Pt_LinkedList();
      //void appendNodeBack(long double);
      void InsertNodeInc(long double);
      void InsertNodeDec(long double);
      void dispNodesForward();
      void destroyList();
  //private:
      PtNode *firstNode;
      PtNode *endNode;
};
inline Pt_LinkedList::Pt_LinkedList(): firstNode(NULL),endNode(NULL){}
inline Pt_LinkedList::~Pt_LinkedList(){ destroyList();}

void Pt_LinkedList::InsertNodeInc(long double v)
{
    PtNode *n = new PtNode(v);
    if (firstNode!=NULL){
        PtNode *p=firstNode,*temp=NULL;
        while(p!=NULL){
            if(p->value>v){
                n->N=p;
                if(temp==NULL){ //p==firstNode
                    firstNode=n;
                }
                else{
                    temp->N=n;
                }
                break;
            }
            else if(p->value<v){
                temp=p;
                p=p->N;
            }
            else
                break;
        }
    }
    else{
        firstNode=n;
        endNode=n;
    }

}

void Pt_LinkedList::InsertNodeDec(long double v)
{
    PtNode *n = new PtNode(v);
    if (firstNode!=NULL){
        PtNode *p=firstNode,*temp=NULL;
        while(p!=NULL){
            if(p->value<v){
                n->N=p;
                if(temp==NULL){ //p==firstNode
                    firstNode=n;
                }
                else{
                    temp->N=n;
                }
                break;
            }
            else if(p->value>v){
                temp=p;
                p=p->N;
            }
            else
                break;
        }
    }
    else{
        firstNode=n;
        endNode=n;
    }
}

void Pt_LinkedList::dispNodesForward()
{
  PtNode *temp = firstNode;
  cout<<fixed<< setprecision(7);
  int cnt=1;
  while(temp != NULL)
  {
     cout <<"("<<cnt<< ") value: " <<temp->value <<"\n";
     temp = temp->N;
     ++cnt;
  }
}

void Pt_LinkedList::destroyList()
{
    PtNode *T = firstNode;
    while(T != NULL)
    {
        PtNode *T2 = T;
        T = T->N;
        delete T2;
    }
    firstNode = NULL;
    endNode = NULL;
}

