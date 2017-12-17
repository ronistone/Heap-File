#ifndef __JOIN_OP__
#define __JOIN_OP__

#include "HeapFile.hpp"
//#include "ExtensibleHash.hpp"


template<typename typeIdx, typename reg, int size_page>
heap_file<reg,sizeof(reg)*size_page> nestedIndex(typeIdx idx,
                                      heap_file<reg,sizeof(reg)*size_page> b,
                                        string path){
  heap_file<reg,sizeof(reg)*size_page> heap(path);
  page<reg, sizeof(reg)*size_page>* p;
  reg aux;

  for(int i=0;;i++){
      p = b.get_page(i);
      if(p == NULL)
        break;
      for(int j=0;j < p->slotsPage();j++){
        aux = p->getAt(j);
        if(aux.empty())
          continue;
        if(!idx.search(aux.getKey()).empty()){
          heap.insert_reg(aux);
        }
      }

  }
  return heap;
}

#endif