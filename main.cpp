//#include "EdgeNodeDLL.h"
//#include "PointNodeDLL.h"
#include "PointNodeLL.h"
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h>

struct PolyNode
{
    string command;//"Draw/Flash"
    int id;
    string str;//"dark/clear"
    string type; //"[0]/[1]/[2]"
    PE_cirLinkedList *PELL;
};

string getWord(ifstream& in)
{
    int c;
    string word;
    while( !in.eof() )
    {
        c = in.get();
        switch( c ){
        case ' ':
        case ',':
        case '\n':
        case '{':
        case '}':
        case '(':
        case ')':
        //case '[':
        case ']':
            if (!word.empty())
                return word;
            else
                break;
        default:
            word += c;
        }
    }
}

int main(int argc, char *argv[])
{
    ifstream file(argv[1]);//開啟input檔案
    if(!file){     //檢查檔案是否成功開啟
        cout << "Can't open file!\n";
    }
    else{
        vector<PolyNode*> polygonset;
        Pt_LinkedList *XList=new Pt_LinkedList(), *YList=new Pt_LinkedList();
        polygonset.reserve(1000);
        unsigned int sz=polygonset.capacity();
        int polygon_cnt=0,len;
        string word;
        PEnode* t;
        long double cx,cy,r,x,y;
        bool c;

        getline(file,word);
        word=getWord(file);
        while(word.length()>=4){
            PolyNode *p=new PolyNode;
            PE_cirLinkedList *PEList = new PE_cirLinkedList();

            p->command = word;//command
            p->id = atoi(&(getWord(file))[0u]);//id
            p->str = getWord(file);//"dark/clear"
            //point-edge set
            x=atof(&(getWord(file))[0u]);
            y=atof(&(getWord(file))[0u]);
            word = getWord(file);
            do{
                switch (word[0])
                {
                case 'a'://arc
                    cx=atof(&(getWord(file))[0u]);
                    cy=atof(&(getWord(file))[0u]);
                    word=getWord(file);
                    if (word.length()==2){//'CW'
                        c=0;
                    }
                    else{//'CCW'
                        c=1;
                    }
                    r=atof(&(getWord(file))[0u]);
                    t=PEList->appendNodeBack(x,y,0,cx,cy,c,r);
                    XList->InsertNodeInc(x,y,t);
                    YList->InsertNodeDec(y,x,t);
                    x=atof(&(getWord(file))[0u]);
                    y=atof(&(getWord(file))[0u]);
                    word = getWord(file);
                    continue;
                case 'l'://line
                    t=PEList->appendNodeBack(x,y,1,(long double)0.0,(long double)0.0,0,(long double)0.0);
                    XList->InsertNodeInc(x,y,t);
                    YList->InsertNodeDec(y,x,t);
                    x=atof(&(getWord(file))[0u]);
                    y=atof(&(getWord(file))[0u]);
                    word = getWord(file);
                    continue;
                default:
                    break;
                }
            }
            while(word[0]!='[');

            p->PELL=PEList;
            //type: 0/1/2....
            len= word.length()-1;
            p->type=word.substr(1,len);

            word=getWord(file);

            polygonset.push_back(p);
            ++polygon_cnt;
            if(polygon_cnt%1000==0){
                polygonset.reserve(sz+(unsigned int)1000);
                sz=polygonset.capacity();
            }

        }
        //check
/*
        for (unsigned int i=0;i<polygonset.size();++i){
            cout<<"Polygon No. "<<i+1;
            cout<<": ["<< polygonset[i]->command<<", "<<polygonset[i]->id<<", "<<polygonset[i]->str<<", "<<polygonset[i]->type <<"]";
            polygonset[i]->PELL->dispNodesForward();
            //polygonset[i]->PELL->dispNodesReverse();
            cout<<"----------------------------------------------------------------------"<<endl;
        }
        cout << "X axes list: \n";
        XList->dispVTNodesForward();
        cout << "\nY axes list: \n";
        YList->dispHZNodesForward();*/

    }

    file.close();
}
