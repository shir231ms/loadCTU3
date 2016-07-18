#include "EdgeNodeDLL.h"
#include "PointNodeDLL.h"
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;
struct Polygon
{
    Pt_doubleLinkedList *PDLL;
    Eg_doubleLinkedList *EDLL;
};
struct PolyNode
{
    string command;//"Draw/Flash"
    int id;
    string str;//"dark/clear"
    string type; //"[0]/[1]/[2]"
    Polygon data;
};

int main(int argc, char *argv[])
{
    ifstream file(argv[1]);//�}��input�ɮ�
    if(!file){     //�ˬd�ɮ׬O�_���\�}��
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
        polygonset.reserve(1000);
        unsigned int sz=polygonset.capacity();
        int polygon_cnt=0,len;
        string word,nextline="\n";
        long double cx,cy,r,x,y;
        bool c;
        getline(wordbuffer,nextline);
        wordbuffer>>word;
        while(word.length()>=4/*!wordbuffer.eof(),polygon_cnt<2*/){ //�Y��F�ɮ׵����h��wordbuffer>>str���N �Ǧ^0�A ���Xwhile�^��
            PolyNode *p=new PolyNode;
            Pt_doubleLinkedList *PList = new Pt_doubleLinkedList();
            Eg_doubleLinkedList *EList = new Eg_doubleLinkedList();

            p->command=word;//command
            wordbuffer>>p->id;//id
            wordbuffer>>p->str;//dark->ignore
            //point-edge set
            wordbuffer>>x;
            wordbuffer>>y;
            PList->appendNodeBack(x,y);
            wordbuffer>>word;
            while(word[0]!='['/*word.length()!=1*/){
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
                    EList->appendNodeBack(0,cx,cy,c,r);
                    wordbuffer>>x;
                    wordbuffer>>y;
                    PList->appendNodeBack(x,y);
                    wordbuffer>>word;
                    continue;
                case 'l'://line
                    EList->appendNodeBack(1,(long double)0.0,(long double)0.0,0,(long double)0.0);
                    wordbuffer>>x;
                    wordbuffer>>y;
                    PList->appendNodeBack(x,y);
                    wordbuffer>>word;
                    continue;
                default:
                    break;
                }
            }
            (p->data).PDLL=PList;
            (p->data).EDLL=EList;
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

        for (int i=0;i<polygonset.size();++i){
            cout<<"\nPolygon No. "<<i+1;
            cout<<": ["<< polygonset[i]->command<<", "<<polygonset[i]->id<<", "<<polygonset[i]->str<<", "<<polygonset[i]->type <<"]";
            polygonset[i]->data.PDLL->dispNodesForward();
            polygonset[i]->data.EDLL->dispNodesForward();
            cout<<"----------------------------------------------------------------------"<<endl;
        }

    }

    file.close();
}
