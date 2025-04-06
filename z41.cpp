#include <iostream>
using namespace std;
/*Да се напише функција за работа со NULL терминирани единечно поврзани листи, која на влез
добива две пополнети листи. Функцијата треба да ги измине истовремено листите и доколку
наиде на јазли со иста вредност, јазлите ги брише од двете листи. Изминувањето на листите да
се направи во глобална функција promeni.
Како дел од програмата да се напишат структури за имплементација на јазол и листа, како и
функциите за поддршка на листата: функција за иницијализација, функции за додавање и
бришење на елемент на почеток од листата, додавање и бришење на елемент на крај од
листата, бришење на цела листа, печатење на елементите од листата и додавање на јазол пред
даден јазол. Адресата на јазолот пред кој треба да се додаде новиот јазол се добива како прв
аргумент, а вредноста на инфо полето на јазолот кој треба да се додаде се добива како втор
аргумент на влез од функцијата.*/

struct jazol{
    int pod;//podatok
    jazol *sled;//sleden jazol
};

struct list{
    jazol *head;
    void init(){head=nullptr;}
    void kreiraj(int n){
        head=new jazol;
        head->pod=n;
        head->sled=nullptr;
    }
    void vnesiNapred(int n){
        jazol *p=new jazol;
        p->pod=n;
        p->sled=head;
        head=p;
    }
    void brishiNapred(){
        if(head!=nullptr){//ne mora da se proveri dali head->sled==nullptr zasho ako e samo se stava head
            //da e nullptr
            /*vaka e vo prez:
            if(head->sled==nullptr)head=head->sled;
            else{
                jazol *p=head;
                head=head->sled;
                delete p;
            }*/
           jazol *p=head;
           head=head->sled;
           delete p;
        }
    }
    void vnesiNazad(int n){
        if(head!=nullptr){
            jazol *p=head;
            while(p->sled!=nullptr)p=p->sled;
            p->sled=new jazol;
            p=p->sled;
            p->pod=n;
            p->sled=nullptr;
        }else{//ova mi e za da nemoram kreiraj koga e prazna listata, ne mi tekna mozhe samo kreiraj da se povika tuka
            head=new jazol;
            head->pod=n;
            head->sled=nullptr;
        }
    }
    void brishiPozadi(){
        if(head!=nullptr){
            if(head->sled==nullptr){
                delete head;
                head=nullptr;
            }else{
                jazol *p=head;
                while(p->sled->sled!=nullptr)p=p->sled;
                delete p->sled;
                p->sled=nullptr; 
            }
        }else cout<<"Nema clenovi"<<endl;
    }
    void brishi(){
        while(head!=nullptr)brishiPozadi();
        cout<<"Izbrishano"<<endl;
    }
    void vnesiPred(jazol *j,int n){
        if(head!=nullptr && j!=head){
            jazol *p=new jazol,*b=head;
            p->pod=n;
            while(b!=nullptr && b->sled!=j)b=b->sled;
            if(b!=nullptr){
                p->sled=j;
                b->sled=p;
            }
        }else cout<<"ne";
    }
    void pechati(){
        for(jazol *p=head;p!=nullptr;p=p->sled)cout<<p->pod<<" ";
        cout<<endl;
    }
    int len(){
        jazol *p=head;
        int n=0;
        while(p!=nullptr){
            p=p->sled;
            n++;
        }
        return n;
    }
};

void brishiIsti(list &a,list &b){
    int na=a.len(),nb=b.len();
    jazol *pa=a.head,*pb=b.head,*pretha=nullptr,*prethb=nullptr;
    bool pomesteno=false;
    for(int i=0;i<(na>nb?nb:na);i++){//ternarniot e za da se najde koja e pomala lista i tolku pati da
        //izvrti for ciklustot pr. ako imame listi so 4 i 5 clena for vrti 4 pati
        jazol *ba,*bb;//jazli shto gi brisham
        if(pa->pod==pb->pod && pretha!=nullptr){
            ba=pa;
            bb=pb;
            pretha->sled=pa->sled;//prethodniot na clenot shto e ist vo a da pokazuva na clenot posle toj
            //shto e ist so toj vo lista b
            prethb->sled=pb->sled;//istoto za lista b
            delete ba,bb;
            pomesteno=true;
        }else if(pa->pod==pb->pod){//ako nema prethoden toa znaci prvite se isti i se pomestuva head
            ba=pa;
            bb=bb;
            a.head=a.head->sled;
            b.head=b.head->sled;
            delete ba,bb;
        }else pomesteno=false;
        if(pomesteno){//ako sme izbrishale nema potreba prethodnite da se pomestat samo pa i pb treba
            pa=pa->sled;
            pb=pb->sled;
        }else{
            pretha=pa;
            prethb=pb;
            pa=pa->sled;
            pb=pb->sled;
        }
    }
}

int main(){
    int n,na,nb;
    list a,b;
    a.init();
    b.init();

    cout<<"Dolzhina na l1 "<<endl;
    cin>>na;
    for(int i=0;i<na;i++){// so for ciklusi zasho ne mi raboteshe da prestane so char kako vo preth 
        //zadaci 😭
        cin>>n;
        a.vnesiNazad(n);
    }
    cout<<"Dolzh na l2 "<<endl;
    cin>>nb;
    for(int i=0;i<nb;i++){
        cin>>n;
        b.vnesiNazad(n);
    }
    a.pechati();
    b.pechati();
    brishiIsti(a,b);
    a.pechati();
    b.pechati();
}
