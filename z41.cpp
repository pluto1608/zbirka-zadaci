#include <iostream>
using namespace std;

struct jazol{
    int pod;
    jazol *sled;
};

struct list{
    jazol *head;
    void init(){head=nullptr;}
    void kreiraj(int n){
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
        if(head!=nullptr){//go napraiv bolje 😙
            /*if(head->sled==nullptr)head=head->sled;
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
    void pechati(){
        for(jazol *p=head;p!=nullptr;p=p->sled)cout<<p->pod<<" ";
    }
};

int main(){
    int n;
    list a;
    a.init();
    a.vnesiNapred(1);
    a.pechati();
    cout<<endl;
    a.brishiNapred();
    if(a.head==nullptr)cout<<"freak"<<endl;
    a.pechati();
}