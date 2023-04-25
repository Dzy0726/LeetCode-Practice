/*** 
 * @Author: Zhenyu Dong
 * @Date: 2023-04-25 15:22:34
 * @LastEditors: Zhenyu Dong
 * @LastEditTime: 2023-04-25 15:22:44
 * @FilePath: /707.设计链表/MyLinkList.cpp
 * @Description: 
 * @
 * @Copyright (c) 2023 by Zhenyu Dong, All Rights Reserved. 
 */
class MyLinkedList {
public:
    struct LinkedNode {
        int val;
        LinkedNode* next;
        LinkedNode(int x) : val(x), next(nullptr) {}
    };

    MyLinkedList() {
        _dummyHead = new LinkedNode(0);
        _length = 0;
    }
    
    int get(int index) {
        if(index >= _length) {
            return -1;
        }
        LinkedNode * cur = _dummyHead;
        while(index--) {
            cur = cur->next;
        }
        return cur->next->val;
    }
    
    void addAtHead(int val) {
        LinkedNode* newNode = new LinkedNode(val);
        newNode->next = _dummyHead->next;
        _dummyHead->next = newNode;
        _length++;
    }
    
    void addAtTail(int val) {
        LinkedNode* cur = _dummyHead;
        LinkedNode* newNode = new LinkedNode(val);
        while(cur->next) {
            cur = cur->next;
        }
        cur->next = newNode;
        _length++;
    }
    
    void addAtIndex(int index, int val) {
        if(index > _length) {
            return;
        } else if(index == _length) {
            return addAtTail(val);
        } else {
            LinkedNode* newNode = new LinkedNode(val);
            LinkedNode* cur = _dummyHead;
            while(index--) {
                cur = cur->next;
            }
            newNode->next = cur->next;
            cur->next = newNode;
            _length++;
        }
    }
    
    void deleteAtIndex(int index) {
        if(index >= _length || index < 0) {
            return;
        }
        LinkedNode* cur = _dummyHead;
        while(index--) {
            cur = cur->next;
        }
        cur->next = cur->next->next;
        _length--;
    }

    private:
        int _length = 0;
        LinkedNode* _dummyHead;
};
