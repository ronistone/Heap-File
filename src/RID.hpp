#ifndef __RID__
#define __RID__

#include <bits/stdc++.h>

struct RID{
  private:
    int slotId,pageId;
  public:
    RID(){
      slotId = -1;
      pageId = -1;
    }
    RID(int slot, int page): slotId(slot), pageId(page){}
    int setSlot(int slot){
      return slotId = slot;
    }
    int setPage(int page){
      return pageId = page;
    }
    int getSlot(){
      return slotId;
    }
    int getPage(){
      return pageId;
    }
    void print(){
      cout << "SlotID: " << slotId << endl;
      cout << "PageID: " << pageId << endl;
    }
};

#endif