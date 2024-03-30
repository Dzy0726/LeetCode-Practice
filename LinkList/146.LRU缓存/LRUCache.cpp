class LRUCache {
private:
    struct LinkedNode{
        int key, val;
        LinkedNode* next;
        LinkedNode* prev;
        LinkedNode(): key(0), val(0), next(nullptr), prev(nullptr) {}
        LinkedNode(int k, int v) : key(k), val(v), next(nullptr), prev(nullptr) {}
    };
    int _capacity;
    int _size;
    unordered_map<int, LinkedNode*> _cache;
    LinkedNode* _dummyHead;
    LinkedNode* _dummyTail;

public:
    LRUCache(int capacity) {
        _capacity = capacity;
        _size = 0;
        _dummyHead = new LinkedNode();
        _dummyTail = new LinkedNode();
        _dummyHead -> next = _dummyTail;
        _dummyTail -> prev = _dummyHead;
    }
    
    int get(int key) {
        if (_cache.count(key) == 0) {
            return -1;
        }
        LinkedNode* node = _cache[key];
        moveToHead(node);
        return node -> val;
    }
    
    void put(int key, int value) {
        if (_cache.count(key) == 0) {
            LinkedNode* node = new LinkedNode(key, value);
            _cache[key] = node;
            _size++;
            addToHead(node);
            if (_size > _capacity) {
                LinkedNode* deletedNode = removeTail();
                _cache.erase(deletedNode -> key);
                delete deletedNode;
                _size--;
            }
        } else {
            LinkedNode* node = _cache[key];
            node -> val = value;
            moveToHead(node);
        }
    }

    void addToHead(LinkedNode* node) {
        node -> prev = _dummyHead;
        node -> next = _dummyHead -> next;
        _dummyHead -> next -> prev = node;
        _dummyHead -> next = node;
    }

    void moveToHead(LinkedNode* node) {
        node -> next -> prev = node -> prev;
        node -> prev -> next = node -> next;
        node -> prev = _dummyHead;
        node -> next = _dummyHead -> next;
        _dummyHead -> next -> prev = node;
        _dummyHead -> next = node;
    }

    LinkedNode* removeTail() {
        LinkedNode* node = _dummyTail -> prev;
        _dummyTail -> prev = node -> prev;
        node -> prev -> next = _dummyTail;
        node -> prev = nullptr;
        node -> next = nullptr;
        return node;
    }

};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */