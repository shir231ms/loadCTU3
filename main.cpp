//#include "EdgeNodeDLL.h"
//#include "PointNodeDLL.h"
#include "PointNodeLL.h"
#include <vector>
#include <string>
#include <stdlib.h>
#include <pthread.h>
#define Thread_NUM 4
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
struct PolyNode
{
    string command;//"Draw/Flash"
    int id;
    string str;//"dark/clear"
    string type; //"[0]/[1]/[2]"
    PE_cirLinkedList *PELL;
};

Pt_LinkedList *XList=new Pt_LinkedList(), *YList=new Pt_LinkedList();
vector<PolyNode*> polygonset;
string linebuf[Thread_NUM];

string getWord(string input,int& index)
{
    string word;
    while( 1 )
    {
        //c = in.get();
        switch( input[index] ){
        case ' ':
        case ',':
        case '\n':
        case '{':
        case '}':
        case '(':
        case ')':
        //case '[':
        case ']':
            if (!word.empty()){
                ++index;
                return word;
            }
            else{
                ++index;
                break;
            }
        default:
            word += input[index];
            ++index;
        }
    }
}

void* work(void* arg)
{
    string line=*(string *)arg;
    int len,line_index=0;
    string word;
    PEnode* t;
    double cx,cy,r,x,y;
    bool c;
    word=getWord(line,line_index);
    //cout<<word<<endl;
    PolyNode *p=new PolyNode;
    PE_cirLinkedList *PEList = new PE_cirLinkedList();

    p->command = word;//command
    p->id = atoi(&(getWord(line,line_index))[0u]);//id
    //cout<<p->id<<endl;
    p->str = getWord(line,line_index);//"dark/clear"

    //point-edge set
    x=atof(&(getWord(line,line_index))[0u]);
    y=atof(&(getWord(line,line_index))[0u]);
    word = getWord(line,line_index);
    do{
        switch (word[0])
        {
        case 'a'://arc
            cx=atof(&(getWord(line,line_index))[0u]);
            cy=atof(&(getWord(line,line_index))[0u]);
            word=getWord(line,line_index);
            if (word.length()==2){//'CW'
                c=0;
            }
            else{//'CCW'
                c=1;
            }
            r=atof(&(getWord(line,line_index))[0u]);
            t=PEList->appendNodeBack(x,y,0,cx,cy,c,r);
            XList->InsertNodeInc(x,y,t);
            YList->InsertNodeDec(y,x,t);
            x=atof(&(getWord(line,line_index))[0u]);
            y=atof(&(getWord(line,line_index))[0u]);
            word = getWord(line,line_index);
            continue;
        case 'l'://line
            t=PEList->appendNodeBack(x,y,1,(double)0.0,(double)0.0,0,(double)0.0);
            XList->InsertNodeInc(x,y,t);
            YList->InsertNodeDec(y,x,t);
            x=atof(&(getWord(line,line_index))[0u]);
            y=atof(&(getWord(line,line_index))[0u]);
            word = getWord(line,line_index);
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

    pthread_mutex_lock(&mutex);
    polygonset.push_back(p);
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
    return 0;
}

int main(int argc, char *argv[])
{
    ifstream file(argv[1]);//開啟input檔案
    if(!file){     //檢查檔案是否成功開啟
        cout << "Can't open file!\n";
    }
    else{
        string str;
        int polygon_cnt=0;
        polygonset.reserve(1000);
        unsigned int sz=polygonset.capacity();
        getline(file,str);//ignore first line
        //getline(file,line);
        //word=getWord(line,line_index);
        int n=0;
        //void *ret;
        bool b=0;
        pthread_t id[Thread_NUM];
        while(getline(file,linebuf[n])){
            pthread_create(&id[n],NULL,work,&linebuf[n]);
            b=0;
            ++n;
            ++polygon_cnt;
            //cout<<polygon_cnt<<" ";
            if(polygon_cnt%1000==0){
                cout<<polygonset.capacity()<<" ";
                polygonset.reserve(sz+(unsigned int)1000);
                sz=polygonset.capacity();
            }
            if (n%Thread_NUM==0){
                n=0;
                for(int i=0;i<Thread_NUM;i++)
                    pthread_join(id[i],NULL);
                b=1;
            }
        }
        if(b==0){
            for(int i=0;i<n;i++)
                pthread_join(id[i],NULL);
        }
        //check
        cout<<polygonset.size();
        /*for (unsigned int i=0;i<polygonset.size();++i){
            cout<<"Polygon No. "<<i+1;
            /*cout<<": ["<< polygonset[i]->command<<", "<<polygonset[i]->id<<", "<<polygonset[i]->str<<", "<<polygonset[i]->type <<"]"<<endl;
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
