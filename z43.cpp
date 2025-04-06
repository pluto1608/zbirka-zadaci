#include <iostream>
using namespace std;

int mozhniPremini[10] = {2, 5, 7, 4, 8, 2, 6, 9, 3, 1};

struct jazol{
    int pod;
    jazol *sled;
};

struct list{
    jazol *head,*end;
    int el;
    void init(){
        head=end=nullptr;
        el=0;
    }
    void vnesiNapred(int n){
        jazol *p=new jazol;
        p->pod=n;
        if(head=nullptr){
            p->sled=p;
            head=end=p;
        }else{
            p->sled=end->sled;
            end->sled=p;
            head=p;
        }
        el++;
    }
    void brishiNapred(){
        if(head!=nullptr){
            if(head->sled==head){
                delete head;
                end=head=nullptr;
            }else{
                end->sled=head->sled;
                delete head;
                head=end->sled;
            }
            el--;
        }
    }
    void vnesiNazad(int n){
        jazol *p=new jazol;
        p->pod=n;
        if(head==nullptr){
            p->sled=p;
            end=head=p;
        }else{
            p->sled=head;
            end->sled=p;
            end=p;
        }
        el++;
    }
    void brishiNazad(){
        jazol *p=head;
        if(head!=nullptr){
            if(head->sled==head){
                delete end;
                end=head=nullptr;
            }else{
                while(p->sled!=end)p=p->sled;
                delete p->sled;
                end=p;
                end->sled=head;
            }
            el--;
        }
    }
    void brishi(){
        while(head!=nullptr)brishiNazad();
    }
    void vnesiPred(jazol *p,int n){
        jazol *nov=new jazol,*b=end->sled;//jazolot pred toj shto go baram
        nov->pod=n;
        if(head!=nullptr){
            if(p!=head){
                while(b->sled!=end->sled && b->sled!=p)b=b->sled;
                b->sled=nov;
                nov->sled=p;
            }else if(p==head)vnesiNapred(n);
        }
    }
    void pechati(){
        if(head==nullptr)cout<<"prazno"<<endl;
        else{
            jazol *p=head;
            cout<<p->pod<<"\t";
            p=p->sled;
            for(;p!=head;p=p->sled)cout<<p->pod<<"\t";
            cout<<endl;
        }
    }
};

void smeni(list &a,int n){//ZASHTO E TOLKU PROSTO JA KE SE FRLAM💢
    int premini=0;
    jazol *p=a.end->sled;//end->sled zasho drugo ne raboteshe ko sho treba koa staiv head a so end->sled
    //raboteshe sho e sig e sig
    for(int i=0;i<10 && premini<n;i++){//prekinuva ako se premine dozvoleniot broj premini ili ako 
        //nema vishe clenovi vo nizata gore
        for(int j=0;j<mozhniPremini[i];j++)p=p->sled;//se pomestuva spored nizata
        a.vnesiPred(p,p->pod);
        premini++;
    }
}

int main(){
    list a;
    int n;
    a.init();
    while(cin>>n)a.vnesiNazad(n);
    smeni(a,4);
    a.pechati();
}