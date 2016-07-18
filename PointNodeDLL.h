//An example of a simple double linked list using OOP techniques
#include <iostream>
#include <iomanip>
using namespace std;
class Pt_doubleLinkedList
{
  public:
      Pt_doubleLinkedList();
      ~Pt_doubleLinkedList();
      //void appendNodeFront(double, double);
      void appendNodeBack(long double, long double);
      void dispNodesForward();
      //void dispNodesReverse();
      void destroyList();
  private:
    struct PtNode
    {
      long double x;
      long double y;
      PtNode *N,*P;
      PtNode(long double, long double);
    };
    PtNode *firstNode;
    PtNode *endNode;
};
inline Pt_doubleLinkedList::PtNode::PtNode(long double vx, long double vy): x(vx),y(vy),N(NULL),P(NULL){}
inline Pt_doubleLinkedList::Pt_doubleLinkedList(): firstNode(NULL),endNode(NULL){}
inline Pt_doubleLinkedList::~Pt_doubleLinkedList(){ destroyList();}
/*
void Pt_doubleLinkedList::appendNodeFront(long double x, long double y)
  {
        PtNode *n = new PtNode(x,y);
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
  void Pt_doubleLinkedList::appendNodeBack(long double x, long double y)
  {
        PtNode *n = new PtNode(x,y);
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

  void Pt_doubleLinkedList::dispNodesForward()
  {
      PtNode *temp = firstNode;
      cout<<fixed<< setprecision(10);
      cout << "\n\nVertexes in forward order:" << endl;
      int cnt=1;
      while(temp != NULL)
      {
         cout <<"("<<cnt<< ") (" <<temp->x << "," <<temp->y << ")\n";
         temp = temp->N;
         ++cnt;
      }
  }/*
  void Pt_doubleLinkedList::dispNodesReverse()
  {
      PtNode *temp = endNode;
      cout << "\n\nPointNodes points in reverse order :" << endl;
      while(temp != NULL)
      {
         cout << "(" << temp->x << "," << temp->y << ")" << "   " ;
         temp = temp->P;
      }
  }*/
void Pt_doubleLinkedList::destroyList()
{
    PtNode *T = endNode;
    while(T != NULL)
    {
        PtNode *T2 = T;
        T = T->P;
        delete T2;
    }
    firstNode = NULL;
    endNode = NULL;
}
