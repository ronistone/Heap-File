#ifndef _EXTENSIBLE_HASH_
#define _EXTENSIBLE_HASH_

#include <bits/stdc++.h>
using namespace std;

#include "HeapFile.hpp"
#include "page.hpp"
#include "standard_reg.hpp"


struct regID{
  int key;
  RID r;

  regID(){}
  regID(int slot, int page, int _key): key(_key){
    r.setPage(page);
    r.setSlot(slot);
  }
  int setSlot(int slot){
    return r.setSlot(slot);
  }
  int setPage(int page){
    return r.setPage(page);
  }
  int getSlot(){
    return r.getSlot();
  }
  int getPage(){
    return r.getPage();
  }

  bool operator <(regID b){ this->key < b.key; }
  bool operator >(regID b){ this->key > b.key; }
  bool operator ==(regID b){ this->key == b.key; }
};

class BucketType{
      int depth, size;

    public:
      BucketType(){}
      BucketType(int d, int s): depth(d), size(s){}
      int getDepth(){
        return depth;
      }
      int getSize(){
        return size;
      }
      int setDepth(int d){
        return depth = d;
      }
      int setSize(int s){
        return size = s;
      }
      int increaseDepth(){
          depth++;
          return depth;
      }

      int decreaseDepth(){
          depth--;
          return depth;
      }

};

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
        Directory(int depth, char* path);
        void remove(int key);
        void insert(reg R, bool reinserted);
        reg search(int key);
        void display(bool duplicates);
};

template<class reg, int size_bucket>
Directory<reg,size_bucket>::Directory(int depth, char* path)
{
    this->global_depth = depth;
    this->bucket_size = size_bucket;
    heap = new heap_file<reg,sizeof(reg)*size_bucket>(path);
    for(int i = 0 ; i < 1<<depth ; i++ )
    {
        heap->insert_page();
        buckets.push_back(BucketType(depth,this -> bucket_size));
    }
}

template<class reg, int size_bucket>
int Directory<reg,size_bucket>::hash(int n)
{
    return n%(1<<global_depth);
    //return (n&((1<<global_depth)-1))? (n&((1<<global_depth)-1))-1:0;
}

template<class reg, int size_bucket>
int Directory<reg,size_bucket>::pairIndex(int bucket_no, int depth)
{
    return bucket_no^(1<<(depth-1));
}

template<class reg, int size_bucket>
void Directory<reg,size_bucket>::grow(void)
{
    int id;
    for(int i = 0 ; i < 1<<global_depth ; i++ ){
        id = heap->insert_page();
        heap->set_page(id,heap->get_page(i));
        buckets.push_back(buckets[i]);
    }
    global_depth++;
}


template<class reg, int size_bucket>
void Directory<reg, size_bucket>::remove(int key)
{
    int bucket_no = hash(key);
    if(heap->remove_regByKey(bucket_no,key))
        cout<<"Deleted key "<< key <<" from bucket "<< bucket_no <<endl;
    else
      cout << "Key not found" << endl;
}

template<class reg, int size_bucket>
void Directory<reg, size_bucket>::insert(reg R, bool reinserted)
{
    int bucket_no = hash(R.getKey());
    int status = heap->insert_into(bucket_no, R);

    if(status!=-1)
    {
        if(!reinserted)
            cout<<"Inserted key "<< R.getKey() <<" in bucket "<< bucket_no <<endl;
        else
            cout<<"Moved key "<< R.getKey() <<" to bucket "<< bucket_no <<endl;
    }
    else
    {
        split(bucket_no);
        insert(R,reinserted);
    }
}

template<class reg, int size_bucket>
void Directory<reg, size_bucket>::split(int bucket_no)
{
    int local_depth,pair_index,index_diff,dir_size,i;
    page<reg, size_bucket*sizeof(reg)> temp;


    local_depth = buckets[bucket_no].increaseDepth();

    if(local_depth>global_depth)
        grow();

    pair_index = pairIndex(bucket_no,local_depth);
    buckets[pair_index] = BucketType(local_depth,this -> bucket_size);

    temp = heap->get_page(bucket_no);

    heap->clear_page(bucket_no);

    index_diff = 1<<local_depth;
    dir_size = 1<<global_depth;

    for( i=pair_index-index_diff ; i>=0 ; i-=index_diff ){
        heap->set_page(i, heap->get_page(pair_index));
        buckets[i] = buckets[pair_index];
    }

    for( i=pair_index+index_diff ; i<dir_size ; i+=index_diff ){
        heap->set_page(i, heap->get_page(pair_index));
        buckets[i] = buckets[pair_index];
    }

    for(int i=0;i<this -> bucket_size;i++)
        insert(temp.getAt(i),1);
}

template<class reg, int size_bucket>
reg Directory<reg, size_bucket>::search(int key)
{
    int bucket_no = hash(key);
    cout<<"Searching key "<< key <<" in bucket "<< bucket_no <<endl;
    reg result = heap->search(bucket_no,key);
    if(!result.empty()){
      cout << "it found" << endl;
    }else{
      cout << "This key does not exists" << endl;
    }
    return result;
}

template<class reg, int size_bucket>
void Directory<reg, size_bucket>::display(bool duplicates)
{
    for(int i=0;i < (1 << global_depth);i++){
      cout << "entrou" << endl;
      heap->display(i);
    }
    // int i,j,d;
    // string s;
    // set<string> shown;
    // cout<<"Global depth : "<<global_depth<<endl;
    // for(i=0;i<buckets.size();i++)
    // {
    //     d = buckets[i].getDepth();
    //     s = i;
    //     if(duplicates || shown.find(s)==shown.end())
    //     {
    //         shown.insert(s);
    //         for(j=d;j<=global_depth;j++)
    //             cout<<" ";
    //         cout<<s<<" => ";
    //         heap->display(i);
    //     }
    // }
}



/* Bucket class functions */

// Bucket::Bucket(int depth, int size)
// {
//     this->depth = depth;
//     this->size = size;
// }
//
// int Bucket::insert(int key, string value)
// {
//     map<int,string>::iterator it;
//     it = values.find(key);
//     if(it!=values.end())
//         return -1;
//     if(isFull())
//         return 0;
//     values[key] = value;
//     return 1;
// }
//
// int Bucket::remove(int key)
// {
//     map<int,string>::iterator it;
//     it = values.find(key);
//     if(it!=values.end())
//     {
//         values.erase(it);
//         return 1;
//     }
//     else
//     {
//         cout<<"Cannot remove : This key does not exists"<<endl;
//         return 0;
//     }
// }
//
// int Bucket::update(int key, string value)
// {
//     map<int,string>::iterator it;
//     it = values.find(key);
//     if(it!=values.end())
//     {
//         values[key] = value;
//         cout<<"Value updated"<<endl;
//         return 1;
//     }
//     else
//     {
//         cout<<"Cannot update : This key does not exists"<<endl;
//         return 0;
//     }
// }
//
// void Bucket::search(int key)
// {
//     map<int,string>::iterator it;
//     it = values.find(key);
//     if(it!=values.end())
//     {
//         cout<<"Value = "<<it->second<<endl;
//     }
//     else
//     {
//         cout<<"This key does not exists"<<endl;
//     }
// }
//
// int Bucket::isFull(void)
// {
//     if(values.size()==size)
//         return 1;
//     else
//         return 0;
// }
//
// int Bucket::isEmpty(void)
// {
//     if(values.size()==0)
//         return 1;
//     else
//         return 0;
// }
//
// int Bucket::getDepth(void)
// {
//     return depth;
// }
//
// int Bucket::increaseDepth(void)
// {
//     depth++;
//     return depth;
// }
//
// int Bucket::decreaseDepth(void)
// {
//     depth--;
//     return depth;
// }
//
// vector<regID> Bucket::copy(void)
// {
//     vector<regID> temp(values.begin(),values.end());
//     //map<int, string> temp(values.begin(),values.end());
//     return temp;
// }
//
// void Bucket::clear(void)
// {
//     values.clear();
// }
//
// void Bucket::display()
// {
//     map<int,string>::iterator it;
//     for(it=values.begin();it!=values.end();it++)
//         cout<<it->first<<" ";
//     cout<<endl;
// }


#endif
