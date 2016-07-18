//An example of a simple double linked list using OOP techniques
#include <iostream>
#include <iomanip>
using namespace std;
class Eg_doubleLinkedList
{
  public:
      Eg_doubleLinkedList();
      ~Eg_doubleLinkedList();
      //void appendNodeFront(bool, double, double, bool, double);
      void appendNodeBack(bool, long double, long double, bool, long double);
      void dispNodesForward();
      //void dispNodesReverse();
      void destroyList();
  private:
    struct EgNode
    {
        bool segment;
        long double center_x;
        long double center_y;
        bool dir;
        long double radius;
        EgNode *N,*P;
        EgNode(bool, long double, long double, bool, long double);
    };
    EgNode *firstNode;
    EgNode *endNode;
};
inline Eg_doubleLinkedList::EgNode::EgNode(bool s, long double vx, long double vy, bool c, long double r):
            segment(s), center_x(vx), center_y(vy), dir(c), radius(r), N(NULL), P(NULL){}
inline Eg_doubleLinkedList::Eg_doubleLinkedList():firstNode(NULL),endNode(NULL){}
inline Eg_doubleLinkedList::~Eg_doubleLinkedList(){ destroyList();}
/*
void Eg_doubleLinkedList::appendNodeFront(bool s, long double x, long double y, bool c, long double r)
  {
        EgNode *n = new EgNode(s,x,y,c,r);
        if( firstNode == NULL)
        {
            firstNode = n;
            endNode = n;
        }
        else
        {
            firstNode->P = n;
            n->N = firstNode;
            firstNode = n;
        }
  }*/
  void Eg_doubleLinkedList::appendNodeBack(bool s, long double x, long double y, bool c, long double r)
  {
        EgNode *n = new EgNode(s,x,y,c,r);
        if( endNode == NULL)
        {
            firstNode = n;
            endNode = n;
        }
        else
        {
            endNode->N = n;
            n->P = endNode;
            endNode = n;
        }

  }

  void Eg_doubleLinkedList::dispNodesForward()
  {
      EgNode *temp = firstNode;
      cout<<fixed<< setprecision(10);
      cout << "\nSegments in forward order:" << endl;
      int cnt=1;
      while(temp != NULL)
      {
         if (temp->segment==0){
             cout <<"("<<cnt<< ") Arc, Center(" << temp->center_x << "," << temp->center_y << "), Dir:" << int(temp->dir) << ", Radius:" << temp->radius << ".\n" ;
             temp = temp->N;
         }
         else{
             cout<<"("<<cnt<< ") Line.\n";
             temp = temp->N;
         }
         ++cnt;
      }
      temp = firstNode;
  }
  /*
  void Eg_doubleLinkedList::dispNodesReverse()
  {
      EgNode *temp = endNode;
      cout << "\n\nEdgeNodes segments in reverse order:" << endl;
      while(temp != NULL)
      {
         cout << "("<<int(temp->segment) << "," << int(temp->dir) << "," << temp->radius << ")   " ;
         temp = temp->P;
      }
      temp = endNode;
      cout << "\n\nEdgeNodes centers in reverse order:" << endl;
      while(temp != NULL)
      {
         cout << "(" << temp->center_x << "," << temp->center_y << ")" << "   " ;
         temp = temp->P;
      }
  }*/
void Eg_doubleLinkedList::destroyList()
{
    EgNode *T = endNode;
    while(T != NULL)
    {
        EgNode *T2 = T;
        T = T->P;
        delete T2;
    }
    firstNode = NULL;
    endNode = NULL;
}
