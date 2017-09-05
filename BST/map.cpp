#ifndef MAP_H
#define MAP_H

namespace custom
{

template <class K, class V>
class map
{
private:
   template <class T>
   class BST;
}; // map

}; // namespace custom

#endif // MAP_H

// custom :: map <K, V> :: insert (const K &k, const V &v)
// {
//    insert(pair <K,V> (k,v));
// }

/*

bool Weird :: operator > (const Weird &rhs) const
{
   return *data > *(rhs.data); 
}

*/

/*
For the assignment:

- Takes in a key (string) of the word we are looking for
   - Adds one to the value (int) when we find another instance of the word

*/
