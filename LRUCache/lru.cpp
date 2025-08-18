#include "DLL.cpp"
#include <unordered_map>
#include "Node.cpp"


class lru{
     private:
      int capacity;
      DLL cache;
      std::unordered_map<int, Node*> map;

      public:
      lru(int cap) : capacity(cap) {}

     Node* get(int key){
         if (map.find(key) != map.end()) {
             // Key is in the cache, move it to the front
             Node* node = map[key];
             cache.removeNode(node);
             cache.addFront(node->key, node->value);
             return node;
         }
         return nullptr;
     }

     Node* put(int key, int value) {
         if (map.find(key) != map.end()) {
             // Key already exists, update the value and move to front
             Node* node = map[key];
             node->value = value;
             cache.removeNode(node);
             cache.addFront(node->key, node->value);
             return node;
         } else {
             // Key does not exist, check capacity
             if (cache.getSize() >= capacity) {
                 // Remove the least recently used item
                 Node* lruNode = cache.getTail();
                 map.erase(lruNode->key);
                 cache.removeBack();
             }
             // Add new node to the front
             Node* newNode = new Node(key, value);
             cache.addFront(newNode->key, newNode->value);
             map[key] = newNode;
             return newNode;
         }
     }

     void clear(){
         cache.clear();
         map.clear();
     }

     int getSize() const {
         return cache.getSize();
     }
};