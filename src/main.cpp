#include <bits/stdc++.h>
using namespace std;

#include "page.hpp"
#include "HeapFile.hpp"
#include "B+Tree.hpp"


main(){
   page<standard_reg<10> , 64000> p;
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
  //HF.scan();
  //standard_reg<10> t1(1234567890,"000000",9876543210);
  //HF.update_reg(0,1,t1);
  //HF.scan();
  // HF.scan();

}