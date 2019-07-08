#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
static int prime[28] =
{
    57,        97,         193,        389,        769,
    1543,      3079,       6151,       12289,      24593,
    49157,     98317,      196613,     393241,     786433,
    1572869,   3145739,    6291469,    12582917,   25165843,
    50331653,  100663319,  201326611,  402653189,  805306457,
    1610612741
};
int genPrime(int* p){
    int cnt=0;
    int n=10000;
    vector<int> isPrime(n+1);
    for(int i=2;i<=n;i++){
        if(isPrime[i]==0){
            p[cnt++]=i;
            for(int j=i*i;j<=n;j+=i){
                isPrime[j]=1;
            }
        }
    }
}
int find_next(int cur){
    int i=0;
    for(;i<28;i++){
        if(cur<prime[i])break;

    }
    return prime[i];
}
template <class Key>
struct Hash{};
template<> struct Hash<int>{
    int operator()(int x) const{return x;}
};
template<class Key,class Value,class HashFunc=Hash<Key>>
class HashMap
{
public:
    template<class _Key,class _Value>
    struct Node{
        _Value value;
        _Key key;
        Node* next;
    };
    typedef Node<Key,Value> node;
    vector<node*> buckets;
    int nums;
    HashFunc Hash;

public:
    HashMap(){
        buckets.reserve(29);
        buckets.insert(buckets.end(),29,(node*)0);
        nums=0;
    }
    int bkt_num_key(const Key& key, int n)
    {
        return Hash(key) % n;
    }
	inline int getNext(int n)
    {
        int* pos = lower_bound(prime, prime+28, n);
        return *pos;
    }
    void resize(int num_elements){
        int old_n=buckets.size();

        if(num_elements>old_n){

            int n=find_next(num_elements);
            vector<node*> tmp(n,(node*)0);
            for (int bucket = 0; bucket < old_n; ++bucket) {
					node* first = buckets[bucket];
					while (first) {
						int new_bucket = bkt_num_key(first->key, n);
						buckets[bucket] = first->next;
						first->next = tmp[new_bucket];
						tmp[new_bucket] = first;
						first = buckets[bucket];
					}
            }
				buckets.swap(tmp);

        }
    }

    bool insertKV(const Key& key,const Value& value){
        resize(nums+1);
        int len=buckets.size();
        int n = bkt_num_key(key,len);
        node* first = buckets[n];
        for (node* cur = first; cur; cur = cur->next)
        if (cur->key==key)
            return false;
        node* tmp = new Node<Key,Value>;
        tmp->key=key;tmp->value=value;
        tmp->next = first;
        buckets[n] = tmp;
        ++nums;
        cout<<"true"<<endl;
        return true;
    }
    Value get(const Key& key){
        int len=buckets.size();
        int n = bkt_num_key(key,len);
        cout<<n<<endl;
        node* first;
        for(first=buckets[n];first&&key!=first->key;first=first->next);
        cout<<first->value<<endl;
        return first->value;
    }
    Value& operator[](const Key& key){

    }
};
int main()
{
    HashMap<int,int> mp;

    mp.insertKV(3,4);
    mp.insertKV(1,3);
    mp.insertKV(0,3);


    return 0;

}



















