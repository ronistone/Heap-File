#ifndef _EXTENSIBLE_HASH_
#define _EXTENSIBLE_HASH_

#include <bits/stdc++.h>
using namespace std;

#include "HeapFile.hpp"
#include "page.hpp"
#include "BucketType.hpp"
#include "RegID.hpp"
#include "standard_reg.hpp"

template<class reg, int size_bucket>
class Directory {
        int global_depth, bucket_size;

        heap_file<reg, sizeof(reg)*size_bucket>* heap;
        vector<BucketType> buckets;
        int hash(int n);
        int pairIndex(int bucket_no, int depth);
        void grow(void);
        void split(int bucket_no);
    public:
        Directory(){}
        Directory(int depth, char* path, int* io = NULL);
        void remove(int key);
        void insert(reg R, bool reinserted, RID r = RID());
        reg search(int key);
        bool verify(int key);
        void display();
        void scan_heap();
        void build(int *io = NULL);
        BucketType* getAt(int bucketID);
};

template<class reg, int size_bucket>
Directory<reg,size_bucket>::Directory(int depth, char* path, int* io)
{
    this->global_depth = depth;
    this->bucket_size = size_bucket;
    heap = new heap_file<reg,sizeof(reg)*size_bucket>(path);
    for(int i = 0 ; i < 1<<depth ; i++ )
    {
        buckets.push_back(BucketType(depth,this -> bucket_size));
    }
    build(io);
}

template<class reg, int size_bucket>
int Directory<reg,size_bucket>::hash(int n)
{
    return n&((1<<global_depth)-1);
}

template<class reg, int size_bucket>
int Directory<reg,size_bucket>::pairIndex(int bucket_no, int depth)
{
    cout << "bucket_no: " << bucket_no << "  DEPTH: " << depth << "  pair: " << (bucket_no^(1<<(depth-1))) << endl;
    return bucket_no^(1<<(depth-1));
}

template<class reg, int size_bucket>
void Directory<reg,size_bucket>::grow(void)
{
    int id;
    cout << "GLOBAL " << endl;
    cout << global_depth << endl;
    for(int i = 0 ; i < 1<<global_depth ; i++ ){
        buckets.push_back(buckets[i]);
    }
    global_depth++;
}


template<class reg, int size_bucket>
void Directory<reg, size_bucket>::remove(int key)
{
    int bucket_no = hash(key);

    if(heap->remove_reg(buckets[bucket_no].getReg(key)) and buckets[bucket_no].remove(key)){
        cout<<"Deleted key "<< key <<" from bucket "<< bucket_no <<endl;
    }
    else
      cout << "Key not found" << endl;
}

template<class reg, int size_bucket>
void Directory<reg, size_bucket>::insert(reg R, bool reinserted, RID r)
{
    int bucket_no = hash(R.getKey());
    int status;

    if(!buckets[bucket_no].search(R.getKey())){
      if(!reinserted){
        r = heap->insert_reg(R);
        if(r.getSlot()==-1)
          status = -1;
      }
      if(status!=-1)
        status = buckets[bucket_no].insert(regID(R.getKey(),r));
    }else{
      status = -2;
    }

    if(status>-1)
    {
        if(!reinserted)
            cout<<"Inserted key "<< R.getKey() <<" in bucket "<< bucket_no <<endl;
        else
            cout<<"Moved key "<< R.getKey() <<" to bucket "<< bucket_no <<endl;
    }
    else if(status==-2){
      cout << "KEY " << R.getKey() << " already exists in bucket" << endl;
    }
    else
    {
        split(bucket_no);
        insert(R,reinserted,r);
    }
}

template<class reg, int size_bucket>
void Directory<reg, size_bucket>::split(int bucket_no)
{

    int local_depth,pair_index,index_diff,dir_size,i;
    vector<regID> temp;


    local_depth = buckets[bucket_no].increaseDepth();

    if(local_depth>global_depth)
        grow();

    pair_index = pairIndex(bucket_no,local_depth);
    buckets[pair_index] = BucketType(local_depth,this -> bucket_size);

    temp = buckets[bucket_no].copy();
    //temp = buckets[bucket_no];
    buckets[bucket_no].clear();


    index_diff = 1<<local_depth;
    dir_size = 1<<global_depth;

    for( i=pair_index-index_diff ; i>=0 ; i-=index_diff ){
        buckets[i] = buckets[pair_index];
    }

    for( i=pair_index+index_diff ; i<dir_size ; i+=index_diff ){
        buckets[i] = buckets[pair_index];
    }
    reg rTemp;
    int hashTemp;
    for(int i=0;i<buckets[bucket_no].getSize();i++){
      if(!temp[i].empty()){
        rTemp = heap->getReg(temp[i].getRID());
        hashTemp = hash(rTemp.getKey());
        buckets[hashTemp].remove(rTemp.getKey());
        insert(rTemp, 1, temp[i].getRID());
      }
    }
}

template<class reg, int size_bucket>
reg Directory<reg, size_bucket>::search(int key)
{
    int bucket_no = hash(key);
    reg result;
    cout<<"Searching key "<< key <<" in bucket "<< bucket_no <<endl;
    for(int i=0;i<buckets[bucket_no].getSize();i++){
      if(buckets[bucket_no].getAt(i).getKey() == key){
        result = heap->search(buckets[bucket_no].getAt(i).getRID());
        break;
      }
    }
    if(!result.empty()){
      cout << "it found" << endl;
    }else{
      cout << "This key does not exists" << endl;
    }
    return result;
}

template<class reg, int size_bucket>
bool Directory<reg, size_bucket>::verify(int key)
{
    int bucket_no = hash(key);
    bool result = false;
    for(int i=0;i<buckets[bucket_no].getSize();i++){
      if(buckets[bucket_no].getAt(i).getKey() == key){
        result = true;
        break;
      }
    }
    return result;
}

template<class reg, int size_bucket>
void Directory<reg, size_bucket>::display()
{
    regID a;
    cout << "\n\n";
    for(int i=0;i < (1 << global_depth);i++){
      cout << "SHOW BUCKET " << i << " DEPTH " << buckets[i].getDepth() << endl;
      for(int j=0;j<buckets[i].getSize();j++){
        a = buckets[i].getAt(j);
        if(!a.empty()){
          heap->getReg(a.getRID()).scan();
          cout << endl;
        }
      }
      cout << endl;
    }
    cout << "\n\n";
}

template<class reg, int size_bucket>
void Directory<reg, size_bucket>::scan_heap(){
  heap->scan();
}

template<class reg, int size_bucket>
void Directory<reg, size_bucket>::build(int* io){

  page<reg, sizeof(reg)*size_bucket>* p;
  reg aux;

  for(int i=0;;i++){
      if(io!=NULL)
        (*io)++;
      p = heap->get_page(i);
      if(p == NULL)
        break;

      for(int j=0;j < p->slotsPage();j++){
        aux = p->getAt(j);
        if(aux.empty())
          continue;
        insert(aux,1,RID(j,i));
      }

  }
}

template<class reg, int size_bucket>
BucketType* Directory<reg,size_bucket>::getAt(int bucketID){
  if(bucketID >=0 and bucketID < (1<<global_depth) )
    return &buckets[bucketID];
  else
    return NULL;
}

#endif
