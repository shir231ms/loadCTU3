//An example of a simple double linked list using OOP techniques
#include "PEdll.h"
struct PtNode
{
  double value;
  PEnode *vertexHEAD;
  PtNode *N;
  PtNode(double);
};
inline PtNode::PtNode(double v): value(v),N(NULL),vertexHEAD(NULL){}

class Pt_LinkedList
{
  public:
      Pt_LinkedList();
      ~Pt_LinkedList();
      //void appendNodeBack(long double);
      void InsertNodeInc(double,double,PEnode *);
      void InsertNodeDec(double,double,PEnode *);
      void dispVTNodesForward();
      void dispHZNodesForward();
      void destroyList();
  //private:
      PtNode *firstNode;
      PtNode *endNode;
};
inline Pt_LinkedList::Pt_LinkedList(): firstNode(NULL),endNode(NULL){}
inline Pt_LinkedList::~Pt_LinkedList(){ destroyList();}

void Pt_LinkedList::InsertNodeInc(double v,double v2,PEnode *q)
{
    PtNode *n = new PtNode(v);
    if (firstNode!=NULL){
        PtNode *p=firstNode,*temp=NULL;
        while(p!=NULL){
            if(p->value>v){
                n->N=p;
                n->vertexHEAD=q;
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
            else{
                delete n;
                PEnode* r=p->vertexHEAD,*temp2=NULL;
                //DEC value
                while(r!=NULL){
                    if(r->y<=v2){
                        //cout<<"append new VT pointor."<<endl;
                        q->vt=r;
                        if(temp2==NULL){//q==vertexHEAD
                            p->vertexHEAD=q;
                        }
                        else{
                            temp2->vt=q;
                        }
                        break;
                    }
                    else{//r->y>v2
                        //cout<<"next VT pointor."<<endl;
                        temp2=r;
                        r=r->vt;
                    }
                }
                if(r==NULL){
                    //cout<<"append last new VT pointor."<<endl;
                    temp2->vt=q;
                }
                break;
            }
        }

        if (p==NULL){//n==endNode
            //cout<<"X endNode: "<<n->value<<endl;
            temp->N=n;
            n->vertexHEAD=q;
            endNode=n;
        }
    }
    else{
        firstNode=n;
        n->vertexHEAD=q;
        endNode=n;
    }

}

void Pt_LinkedList::InsertNodeDec(double v,double v2,PEnode *q)
{
    PtNode *n = new PtNode(v);
    if (firstNode!=NULL){
        PtNode *p=firstNode,*temp=NULL;
        while(p!=NULL){
            if(p->value<v){
                n->N=p;
                n->vertexHEAD=q;
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
            else{
                delete n;
                PEnode* r=p->vertexHEAD,*temp2=NULL;
                //INC value
                while(r!=NULL){
                    if(r->x>=v2){
                        //cout<<"append new HZ pointor."<<endl;
                        q->hz=r;
                        if(temp2==NULL){//q==vertexHEAD
                            p->vertexHEAD=q;
                        }
                        else{
                            temp2->hz=q;
                        }
                        break;
                    }
                    else{//r->y>v2
                        //cout<<"next HZ pointor."<<endl;
                        temp2=r;
                        r=r->hz;
                    }
                }
                if(r==NULL){
                    //cout<<"append last new HZ pointor."<<endl;
                    temp2->hz=q;
                }
                break;
            }
        }
        if (p==NULL){//n==endNode
            //cout<<"Y endNode: "<<n->value<<endl;
            temp->N=n;
            n->vertexHEAD=q;
            endNode=n;
        }
    }
    else{
        firstNode=n;
        n->vertexHEAD=q;
        endNode=n;
    }
}

void Pt_LinkedList::dispVTNodesForward()
{
  PtNode *temp = firstNode;
  cout<<fixed<< setprecision(7);
  int cnt=1;
  while(temp != NULL)
  {
     cout <<"[Node"<<cnt<< "] value: " <<temp->value <<"\n";
     PEnode* w=temp->vertexHEAD;
     cout<<"       ";
     int cnt2=1;
     while(w!=NULL){
        if (cnt2%3==0&&w->vt!=NULL)
            cout<<"->("<<w->x<<","<<w->y<<") \n       ";
        else
            cout<<"->("<<w->x<<","<<w->y<<") ";
        w=w->vt;
        ++cnt2;
     }
     cout<<endl;
     temp = temp->N;
     ++cnt;
  }
}

void Pt_LinkedList::dispHZNodesForward()
{
  PtNode *temp = firstNode;
  cout<<fixed<< setprecision(7);
  int cnt=1;
  while(temp != NULL)
  {
     cout <<"[Node"<<cnt<< "] value: " <<temp->value <<"\n";
     PEnode* w=temp->vertexHEAD;
     cout<<"       ";
     int cnt2=1;
     while(w!=NULL){
        if(cnt2%3==0&&w->hz!=NULL)
            cout<<"->("<<w->x<<","<<w->y<<") \n       ";
        else
            cout<<"->("<<w->x<<","<<w->y<<") ";
        w=w->hz;
        ++cnt2;
     }
     cout<<endl;
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

