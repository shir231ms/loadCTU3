#include "PointNodeLL.h"
#include "Vector2D.h"
#include <vector>
#include <string>
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
        double cx,cy,r,x,y;
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
                    t=PEList->appendNodeBack(x,y,1,(double)0.0,(double)0.0,0,(double)0.0);
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
        for (unsigned int i=0;i<polygonset.size();++i){
            //cout<<"Polygon No. "<<i+1;
            //cout<<": ["<< polygonset[i]->command<<", "<<polygonset[i]->id<<", "<<polygonset[i]->str<<", "<<polygonset[i]->type <<"]";
            polygonset[i]->PELL->dispNodesForward();
            //polygonset[i]->PELL->dispNodesReverse();
            //cout<<"----------------------------------------------------------------------"<<endl;
        }/*
        cout << "X axes list: \n";
        XList->dispVTNodesForward();
        cout << "\nY axes list: \n";
        YList->dispHZNodesForward();*/

    //show intersecting points
        vector<PEnode*> seg_pool;
        vector<Point2D*> intersectionPt;
        outfile<<fixed<< setprecision(7);

        seg_pool.reserve(1000);
        intersectionPt.reserve(1000);
        unsigned int seg_pool_sz=seg_pool.capacity();
        unsigned int inter_sz=intersectionPt.capacity();
        PtNode* moveY=YList->firstNode;//scan from top to bottom
        PEnode* new_seg[2];
        bool init=true;

        while(moveY!=NULL){//yList
            PEnode* moveVerX=moveY->vertexHEAD;
            while(moveVerX!=NULL){//xList
                //calculating intersecting points for new two segments
                new_seg[0]=moveVerX->P;
                new_seg[1]=moveVerX;
                if(init==false){
                    for(int j=0;j<2;++j){
                        //judge for seg_ment[0] whether in seg_pool
                        if((j==0)&&
                           (new_seg[0]->y > new_seg[1]->y)||
                           ((new_seg[0]->y==new_seg[1]->y)&&(new_seg[0]->x<new_seg[1]->x))){
                            for(int i=0;i<seg_pool.size();++i){
                                if(seg_pool[i]==new_seg[0]){
                                    seg_pool.erase(seg_pool.begin()+i);
                                    break;
                                }
                            }
                            continue;
                        }
                        //judge for seg_ment[1] whether in seg_pool
                        if((j==1)&&
                           (new_seg[1]->N->y > new_seg[1]->y)||
                           ((new_seg[1]->N->y==new_seg[1]->y)&&(new_seg[1]->N->x<new_seg[1]->x))){
                            for(int i=0;i<seg_pool.size();++i){
                                if(seg_pool[i]==new_seg[1]){
                                    seg_pool.erase(seg_pool.begin()+i);
                                    break;
                                }
                            }
                            break;
                        }
                        //haven't been in seg_pool
                        for(int i=0;i<seg_pool.size();i++){
                            if(seg_pool[i]->segment==true){//line
                                Point2D a1(seg_pool[i]->x,seg_pool[i]->y);
                                Point2D a2(seg_pool[i]->N->x,seg_pool[i]->N->y);
                                Point2D b1(new_seg[j]->x,new_seg[j]->y);
                                Point2D b2(new_seg[j]->N->x,new_seg[j]->N->y);
                                if(new_seg[j]->segment==true){//line-line
                                    Point2D* tm=new Point2D;
                                    if(intersect(a1,a2,b1,b2,*tm)==true){
                                        intersectionPt.push_back(tm);
                                        outfile<<tm->x<<" "<<tm->y<<endl;
                                    }
                                }
                                else{//line-arc
                                    Point2D center(new_seg[j]->x,new_seg[j]->y);
                                    intersect(b1,b2,a1,a2,new_seg[j]->radius,center,intersectionPt);
                                }
                            }
                            else{//arc
                                Point2D a1(seg_pool[i]->x,seg_pool[i]->y);
                                Point2D a2(seg_pool[i]->N->x,seg_pool[i]->N->y);
                                Point2D center(seg_pool[i]->x,seg_pool[i]->y);
                                Point2D c1(new_seg[j]->x,new_seg[j]->y);
                                Point2D c2(new_seg[j]->N->x,new_seg[j]->N->y);
                                if(new_seg[j]->segment==true){//arc-line
                                    intersect(a1,a2,c1,c2,seg_pool[i]->radius,center,intersectionPt);
                                }
                            }
                        }
                        seg_pool.push_back(new_seg[j]);
                    }
                }
                else{//first time
                    seg_pool.push_back(moveVerX->P);
                    seg_pool.push_back(moveVerX);
                    init=false;
                }
                //go next
                moveVerX=moveVerX->hz;
                if((seg_pool_sz+1)%1000==0){
                    seg_pool.reserve(seg_pool_sz+(unsigned int)1000);
                    seg_pool_sz=seg_pool.capacity();
                }
                if((inter_sz+1)%1000==0){
                    intersectionPt.reserve(inter_sz+(unsigned int)1000);
                    inter_sz=intersectionPt.capacity();
                }
            }
            moveY=moveY->N;
        }
    }

    file.close();
}
