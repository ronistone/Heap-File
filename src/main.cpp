#include <bits/stdc++.h>
using namespace std;

#include "page.hpp"
#include "HeapFile.hpp"

struct ab{
  int tam;
  char* a;
  ab(){}
  ab(int t, char* c): tam(t), a(c){}
};

main(){
  //  page<standard_reg<10> > p;
  //  char e[] = "12231";
  //  standard_reg<10> aux(123,e,1234);
  //  p.insert(aux);
  //
  //  heap_file<standard_reg<10> > HF("dados.d");
  //  RID registroID;
  //   for(int i=0;i<3202;i++){
  //     registroID = HF.insert_reg(aux);
  //     cout << "slot: " << registroID.getSlot() << endl
  //          << "page: " << registroID.getPage() << endl;
  //    HF.remove_reg(registroID.getSlot()-1,registroID.getPage());
  // }

  ab a(3,"abc");

  ofstream f("teste");
  if(f.good()){
    f.write((char*)&a,sizeof(ab));
    f.close();
    ab aux;

    fstream fi("teste");
    fi.seekp(0,f.beg);

    fi.read((char*)&aux,sizeof(ab));

    cout << aux . tam << endl
         << aux . a << endl;
    fi.close();
  }else{
    cout << "FALHA" << endl;
  }
  //HF.scan();
  //standard_reg<10> t1(1234567890,"000000",9876543210);
  //HF.update_reg(0,1,t1);
  //HF.scan();
  // HF.scan();

}