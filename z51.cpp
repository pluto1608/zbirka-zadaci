#include <iostream>
using namespace std;
//neam vishe ✨ mozocnni kletki ✨
struct jazol{
    int pod;
    jazol *sled,*preth;
};

struct lista{
    jazol *head,*tail;
    void init(){head=tail=nullptr;}
    void vnesiNapred(int n){
        jazol *p=new jazol;
        p->pod=n;
        p->preth=nullptr;
        if(head==nullptr){
            p->sled=nullptr;
            head=tail=p;
        }else{
            p->sled=head;
            head->preth=p;
            head=p;
        }
    }
    void brishiNapred(){
        if(head!=nullptr){
            if(head->sled==nullptr){
                delete head;
                head=tail=nullptr;
                cout<<"prazno"<<endl;
            }else{
                jazol *p=head;
                head=head->sled;
                head->preth=nullptr;
                delete p;
            }
        }
    }
    void vnesiPozadi(int n){
        jazol *p=new jazol,*b=head;
        p->pod=n;
        p->sled=nullptr;
        if(head==nullptr){
            p->preth=nullptr;
            head=tail=p;
        }else{
            p->preth=tail;
            tail->sled=p;
            tail=p;
        }
    }
    void brishiPozadi(){
        if(head!=nullptr){
            if(head->sled==nullptr){
                delete head;
                head=tail=nullptr;
            }else{
                jazol *p=tail;
                tail=tail->preth;
                tail->sled=nullptr;
                delete p;
            }
        }
    }
    void brishi(){
        while(head!=nullptr)brishiPozadi();
    }
    void pechati(){
        for(jazol *p=head;p!=nullptr;p=p->sled)cout<<p->pod<<"\t";
        cout<<endl;
    }
    int len(){
        int n=0;
        for(jazol *p=head;p!=nullptr;p=p->sled)n++;
        return n;
    }
    void brishiKonk(jazol *p){
        jazol *b=p,*bp=p->preth,*bs=p->sled;
        if(p==head)brishiNapred();
        else if(p==tail)brishiPozadi();
        else{
            bp->sled=bs;
            bs->preth=bp;
            delete b;
        }
    }
};

void promeni(lista &a,lista &b){
    jazol *pa=a.head,*ppa=nullptr,*pb=b.head,*brishiB[b.len()];
    int n=0;
    while(pa!=nullptr && pb!=nullptr){
        if(pa->pod==pb->pod){
            jazol *nov=new jazol;
            nov->pod=pb->pod;
            nov->sled=pa;
            pa->preth=nov;
            if(ppa!=nullptr){
                ppa->sled=nov;
                nov->preth=ppa;
            }else a.vnesiNapred(nov->pod);
            ppa=nov;
            pa=pa->sled;
            brishiB[n++]=pb;
            pb=pb->sled;
        }else{
            ppa=pa;
            pa=pa->sled;
            pb=pb->sled;
        }
    }
    pb=b.head;
    for(int i=0;i<n;i++){
        while(pb!=nullptr){
            if(pb==brishiB[i])b.brishiKonk(pb);
            pb=pb->sled;
        }
        pb=b.head;
    }
}

int main(){
    lista a,b;
    int n,m;
    a.init();
    b.init();
    cout<<"Lista 1"<<endl;
    cin>>m;
    for(int i=0;i<m;i++){
        cin>>n;
        a.vnesiPozadi(n);
    }
    cout<<"Lista 2"<<endl;
    cin>>m;
    for(int i=0;i<m;i++){
        cin>>n;
        b.vnesiPozadi(n);
    }
    promeni(a,b);
    a.pechati();
    b.pechati();
}