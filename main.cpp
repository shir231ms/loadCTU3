//#include "EdgeNodeDLL.h"
//#include "PointNodeDLL.h"
#include "PointNodeLL.h"
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

struct PolyNode
{
    string command;//"Draw/Flash"
    int id;
    string str;//"dark/clear"
    string type; //"[0]/[1]/[2]"
    PE_cirLinkedList *PELL;
};

int main(int argc, char *argv[])
{
    ifstream file(argv[1]);//開啟input檔案
    if(!file){     //檢查檔案是否成功開啟
        cout << "Can't open file!\n";
    }
    else{
        stringstream buffer;// origin file strings
        stringstream wordbuffer;// modify file strings
        buffer << file.rdbuf();
        //Modify: turn signs to space.
        string contentstr(buffer.str());
        for (unsigned int i=0;i<contentstr.length();++i){
            switch (contentstr[i])
            {
            case ',':
            case '{':
            case '}':
            case '(':
            case ')':
            //case '[':
            case ']':
                contentstr[i]=' ';
                continue;
            default:
                continue;
            }
        }
        wordbuffer << contentstr;

        vector<PolyNode*> polygonset;
        Pt_LinkedList *XList=new Pt_LinkedList(), *YList=new Pt_LinkedList();
        polygonset.reserve(1000);
        unsigned int sz=polygonset.capacity();
        int polygon_cnt=0,len;
        string word,nextline="\n";
        long double cx,cy,r,x,y;
        bool c;
        getline(wordbuffer,nextline);
        wordbuffer>>word;
        while(word.length()>=4/*!wordbuffer.eof(),polygon_cnt<2*/){ //若到達檔案結尾則”wordbuffer>>str”將 傳回0， 跳出while回圈
            PolyNode *p=new PolyNode;
            PE_cirLinkedList *PEList = new PE_cirLinkedList();

            p->command=word;//command
            wordbuffer>>p->id;//id
            wordbuffer>>p->str;//dark->ignore
            //point-edge set
            wordbuffer>>x;
            wordbuffer>>y;
            wordbuffer>>word;
            while(word[0]!='['){
                switch (word[0])
                {
                case 'a'://arc
                    wordbuffer>>cx;//CX
                    wordbuffer>>cy;//CY
                    wordbuffer>>word;//DIR
                    if (word.length()==2){//'CW'
                        c=0;
                    }
                    else{//'CCW'
                        c=1;
                    }
                    wordbuffer>>r;//RADIUS
                    XList->InsertNodeInc(x);
                    YList->InsertNodeDec(y);
                    PEList->appendNodeBack(x,y,0,cx,cy,c,r);
                    wordbuffer>>x;
                    wordbuffer>>y;
                    wordbuffer>>word;
                    continue;
                case 'l'://line
                    XList->InsertNodeInc(x);
                    YList->InsertNodeDec(y);
                    PEList->appendNodeBack(x,y,1,(long double)0.0,(long double)0.0,0,(long double)0.0);
                    wordbuffer>>x;
                    wordbuffer>>y;
                    wordbuffer>>word;
                    continue;
                default:
                    break;
                }
            }
            p->PELL=PEList;
            //type: 0/1/2....
            len= word.length()-1;
            p->type=word.substr(1,len);

            wordbuffer>>word;//command

            polygonset.push_back(p);
            ++polygon_cnt;
            if(polygon_cnt%1000==0){
                polygonset.reserve(sz+(unsigned int)1000);
                sz=polygonset.capacity();
            }
        }
        //check

        for (unsigned int i=0;i<polygonset.size();++i){
            cout<<"Polygon No. "<<i+1;
            cout<<": ["<< polygonset[i]->command<<", "<<polygonset[i]->id<<", "<<polygonset[i]->str<<", "<<polygonset[i]->type <<"]";
            polygonset[i]->PELL->dispNodesForward();
            //polygonset[i]->PELL->dispNodesReverse();
            cout<<"----------------------------------------------------------------------"<<endl;
        }
        cout << "X axes list: \n";
        XList->dispNodesForward();
        cout << "Y axes list: \n";
        YList->dispNodesForward();

    }

    file.close();
}
