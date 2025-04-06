 #include <iostream>
 using namespace std;

struct jazol{
    char pod;
    jazol *sled;
 };

struct lista{
    jazol *head;
    void init(){head=nullptr;}
    void vnesiNapred(char a){
        jazol *p=new jazol;
        p->pod=a;
        p->sled=head;
        head=p;
    }
    void brishiNapred(){
        if(head!=nullptr){
            jazol *p=head;
            head=head->sled;
            delete p;
        }
    }
    void vnesiPozadi(char a){
        jazol *p=head;
        if(head!=nullptr){
            while(p->sled!=nullptr)p=p->sled;
            p->sled=new jazol;
            p->sled->pod=a;
            p->sled->sled=nullptr;
        }else{
            head=new jazol;
            head->pod=a;
            head->sled=nullptr;
        }
    }
    void brishiPozadi(){
        jazol *p=head;
        if(head!=nullptr){
            if(head->sled!=nullptr){
                while(p->sled->sled!=nullptr)p=p->sled;
                delete p->sled;
                p->sled=nullptr;
            }else{
                delete head;
                head=nullptr;
            }
        }
    }
    void brishi(){
        while(head!=nullptr)brishiPozadi();
    }
    void brishiPred(jazol *p){
        if(head!=nullptr){
            if(head!=p){
                jazol *b=head,*bp=nullptr;
                while(b->sled!=p && b!=nullptr){
                    bp=b;
                    b=b->sled;
                }
                if(b==head)head=p;
                if(bp!=nullptr)bp->sled=p;
                delete b;
            }else cout<<"jazolot e prv jazol nema prethoden"<<endl;
        }
    }
    void pechati(){
        for(jazol *p=head;p!=nullptr;p=p->sled)cout<<p->pod<<"\t";
        cout<<endl;
    }
};
void brish(char b, lista &a,lista &c){
    jazol *p=a.head;
    while(p!=nullptr && p->pod!=b)p=p->sled;//go stavame p da e jazolot kaj shto e b
    p=p->sled;//pomestuvame za edno zasho b ne treba da e vo lista c
    while(p!=nullptr){
        c.vnesiPozadi(p->pod);//se stavaat vo c site jazli posle b
        a.brishiPred(p);//gi brisheme site posle b osven posledniot zasho funkcijata brishe pred odreden jazol
        p=p->sled;
    }
    a.brishiPozadi();//go brisheme posledniot od a zasho ne go izbrishavme
}
int main(){
    lista a,c;
    char b;
    a.init();
    c.init();
    while(cin>>b){//se vnesuva se dur ne se vnese 1
        if(b=='1')break;
        a.vnesiPozadi(b);
    }
    cin>>b;//charot shto treba da go izbrisheme
    brish(b,a,c);
    a.pechati();
    c.pechati();
}