/**************** Order Set *************/
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace __gnu_pbds;
template<typename T>
using orderset = tree<
    T, null_type, less<T>, rb_tree_tag,
    tree_order_statistics_node_update>;
orderset<int>os;
/*
Insert -> os.insert(value)
Delete -> os.erase(value)
Find kth element *os.find_by_order(k) , 0 based indexing
Number of items that are strictly smaller than x, os.order_of_key(x)
*/
/************ Rope ***********/
///https://www.sgi.com/tech/stl/Rope.html
///Include in the header file
///crope data input neoa jai na,char array input niye insert korte hoi
#include<ext/rope>
using namespace __gnu_cxx;
///Declare as
crope version[N],r,str;///Works like a string
char s[N];
rope<char>alternate;
struct Rope{
    void Insert(int id, char s[]){
        r.insert(id, s);
        //alternate.insert(alt.mutable_begin() + id, s);
        //char s[N] is inserted from position p..string cannot be inserted,has to b char array
        //suppose r="abcd" and char s[]="xyz",p=2 then r will be r="abxyzcd"
    }
    void Erase(int id, int c){
        r.erase(id, c);
        //Removes c character from the position p
    }
    void Substring(int id, int c){
        str=r.substr(id, c);
        //Takes c character from p position
    }
    int Count(char a){
        int cnt = count(r.begin(), r.end(), a);
        //Return how many a is there in r;
        return cnt;
    }
}rop;
