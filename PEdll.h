//An example of a simple double linked list using OOP techniques
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
//ofstream output("data.txt");
struct PEnode
{
    double x;
    double y;
    bool segment;
    double center_x;
    double center_y;
    bool dir;
    long double radius;
    PEnode *N,*P,*hz,*vt;
    PEnode(double, double, bool, double, double, bool, double);
};
inline PEnode::PEnode(double xx, double yy, bool s, double vx, double vy, bool c, double r):
            x(xx), y(yy), segment(s), center_x(vx), center_y(vy), dir(c), radius(r), N(this), P(this),hz(NULL),vt(NULL){}

class PE_cirLinkedList
{
  public:
      PE_cirLinkedList();
      ~PE_cirLinkedList();
      PEnode* appendNodeBack(double, double, bool, double, double, bool, double);
      void dispNodesForward();
      void dispNodesReverse();
      void destroyList();
      PEnode *firstNode;
      PEnode *endNode;
};
inline PE_cirLinkedList::PE_cirLinkedList():firstNode(NULL),endNode(NULL){}
inline PE_cirLinkedList::~PE_cirLinkedList(){ destroyList();}

  PEnode* PE_cirLinkedList::appendNodeBack(double xx, double yy, bool s, double x, double y, bool c, double r)
  {
        PEnode *n = new PEnode(xx,yy,s,x,y,c,r);
        if( endNode == NULL)
        {
            firstNode = n;
            endNode = n;
        }
        else
        {
            endNode->N = n;
            n->P = endNode;
            n->N = firstNode;
            firstNode->P = n;
            endNode = n;
        }
        return endNode;
  }

  void PE_cirLinkedList::dispNodesForward()
  {
      PEnode *temp = firstNode;
      cout<<fixed<< setprecision(7);
      //output<<fixed<< setprecision(7);
      //cout << "\n\nDetails in forward order:" << endl;
      int cnt=0;
      do{
         cout <<"("<<cnt+1<< ") Vertex(" <<temp->x << "," <<temp->y << "),\n";
         if (temp->segment==0){
             cout<<"    Arc, Center(" << temp->center_x << "," << temp->center_y << "), Dir:" << int(temp->dir) << ", Radius:" << temp->radius << ".\n" ;

         }
         else{
             cout<<"    Line.\n";

         }/*
         output<<temp->x<<" "<<temp->N->x<<" "<<temp->y<<" "<<temp->N->y<<endl;*/
         temp = temp->N;
         ++cnt;
      }
      while(temp != firstNode/*temp != firstNode->N || cnt==1*/);
  }

void PE_cirLinkedList::dispNodesReverse()
  {
      PEnode *temp = endNode;
      cout<<fixed<< setprecision(7);
      //output<<fixed<< setprecision(7);
      //cout << "\n\nDetails in reverse order:" << endl;
      int cnt=0;
      do{

         cout <<"("<<cnt+1<< ") Vertex(" <<temp->x << "," <<temp->y << "),\n";
         if (temp->segment==0){
             cout<<"    Arc, Center(" << temp->center_x << "," << temp->center_y << "), Dir:" << int(temp->dir) << ", Radius:" << temp->radius << ".\n" ;

         }
         else{
             cout<<"    Line.\n";

         }/*
         output<<temp->x<<" "<<temp->y<<endl;*/
         temp = temp->P;
         ++cnt;
      }
      while(temp != endNode/*temp != endNode->P || cnt==1*/);
  }

void PE_cirLinkedList::destroyList()
{
    PEnode *T = endNode;
    while(T != endNode)
    {
        PEnode *T2 = T;
        T = T->P;
        firstNode->P = T;
        T->N = firstNode;
        delete T2;
    }
    firstNode = NULL;
    endNode = NULL;
}
