#include <iostream>
#include <memory>
#include <functional>

template <typename KeyType, typename ValueType>
struct HashNode {
    KeyType key;
    ValueType value;
    HashNode* next;
    
    HashNode(const KeyType& k, const ValueType& v) : key(k), value(v), next(nullptr) {}
};

// 手写HashMap
template <typename KeyType, typename ValueType>
class HashMap {
private:
    HashNode<KeyType, ValueType>** table;  // 桶数组
    size_t capacity;      // 容量
    size_t elementCount;  // 元素个数
    double loadFactorThreshold = 0.75;

    // 计算哈希值
    size_t getHashIndex(const KeyType& key) const {
        return std::hash<KeyType>{}(key) % capacity;
    }

    // 释放链表内存
    void deleteLinkedList(HashNode<KeyType, ValueType>* head) {
        while (head != nullptr) {
            HashNode<KeyType, ValueType>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // 复制链表（深拷贝）
    HashNode<KeyType, ValueType>* copyLinkedList(HashNode<KeyType, ValueType>* head) {
        if (head == nullptr) return nullptr;
        
        HashNode<KeyType, ValueType>* newHead = new HashNode<KeyType, ValueType>(head->key, head->value);
        HashNode<KeyType, ValueType>* current = newHead;
        head = head->next;
        
        while (head != nullptr) {
            current->next = new HashNode<KeyType, ValueType>(head->key, head->value);
            current = current->next;
            head = head->next;
        }
        
        return newHead;
    }

    // 扩容操作
    void rehash() {
        size_t oldCapacity = capacity;
        capacity = capacity * 2;
        
        // 创建新表
        HashNode<KeyType, ValueType>** newTable = new HashNode<KeyType, ValueType>*[capacity]();
        
        // 重新哈希所有元素
        for (size_t i = 0; i < oldCapacity; i++) {
            HashNode<KeyType, ValueType>* current = table[i];
            while (current != nullptr) {
                HashNode<KeyType, ValueType>* next = current->next;
                
                // 计算在新表中的位置
                size_t newIndex = getHashIndex(current->key);
                
                // 插入到新表的链表头部
                current->next = newTable[newIndex];
                newTable[newIndex] = current;
                
                current = next;
            }
        }
        
        // 删除旧表数组，但保留节点（节点已经移动到新表）
        delete[] table;
        table = newTable;
    }

public:
    // 构造函数
    HashMap(size_t initialCapacity = 8) : capacity(initialCapacity), elementCount(0) {
        table = new HashNode<KeyType, ValueType>*[capacity]();
    }

    // 拷贝构造函数
    HashMap(const HashMap& other) : capacity(other.capacity), elementCount(other.elementCount) {
        table = new HashNode<KeyType, ValueType>*[capacity]();
        for (size_t i = 0; i < capacity; i++) {
            table[i] = copyLinkedList(other.table[i]);
        }
    }

    // 赋值运算符
    HashMap& operator=(const HashMap& other) {
        if (this != &other) {
            // 清理现有资源
            clear();
            delete[] table;
            
            // 复制新资源
            capacity = other.capacity;
            elementCount = other.elementCount;
            table = new HashNode<KeyType, ValueType>*[capacity]();
            for (size_t i = 0; i < capacity; i++) {
                table[i] = copyLinkedList(other.table[i]);
            }
        }
        return *this;
    }

    // 析构函数
    ~HashMap() {
        clear();
        delete[] table;
    }

    // 插入键值对
    void insert(const KeyType& key, const ValueType& value) {
        // 检查扩容
        if (static_cast<double>(elementCount) / capacity >= loadFactorThreshold) {
            rehash();
        }

        size_t index = getHashIndex(key);
        
        // 检查key是否已存在
        HashNode<KeyType, ValueType>* current = table[index];
        while (current != nullptr) {
            if (current->key == key) {
                current->value = value; // 更新值
                return;
            }
            current = current->next;
        }
        
        // 创建新节点并插入到链表头部
        HashNode<KeyType, ValueType>* newNode = new HashNode<KeyType, ValueType>(key, value);
        newNode->next = table[index];
        table[index] = newNode;
        elementCount++;
    }

    // 查找元素
    ValueType* find(const KeyType& key) {
        size_t index = getHashIndex(key);
        HashNode<KeyType, ValueType>* current = table[index];
        
        while (current != nullptr) {
            if (current->key == key) {
                return &(current->value);
            }
            current = current->next;
        }
        return nullptr;
    }

    // 删除元素
    bool erase(const KeyType& key) {
        size_t index = getHashIndex(key);
        HashNode<KeyType, ValueType>* current = table[index];
        HashNode<KeyType, ValueType>* prev = nullptr;
        
        while (current != nullptr) {
            if (current->key == key) {
                if (prev == nullptr) {
                    // 删除的是链表头节点
                    table[index] = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                elementCount--;
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false;
    }

    // 重载[]运算符
    ValueType& operator[](const KeyType& key) {
        ValueType* found = find(key);
        if (found != nullptr) {
            return *found;
        } else {
            // 如果key不存在，插入默认值
            insert(key, ValueType{});
            found = find(key);
            return *found;
        }
    }

    // 清空HashMap
    void clear() {
        for (size_t i = 0; i < capacity; i++) {
            deleteLinkedList(table[i]);
            table[i] = nullptr;
        }
        elementCount = 0;
    }

    // 获取元素数量
    size_t size() const {
        return elementCount;
    }

    // 获取容量
    size_t getCapacity() const {
        return capacity;
    }

    // 打印HashMap内容（用于调试）
    void print() const {
        for (size_t i = 0; i < capacity; i++) {
            std::cout << "Bucket " << i << ": ";
            HashNode<KeyType, ValueType>* current = table[i];
            while (current != nullptr) {
                std::cout << "[" << current->key << ":" << current->value << "] -> ";
                current = current->next;
            }
            std::cout << "nullptr" << std::endl;
        }
    }
};

int main() {
    HashMap<const char*, int> myMap;

    // 插入元素
    myMap.insert("apple", 1);
    myMap.insert("banana", 2);
    myMap.insert("orange", 3);

    // 使用[]操作符
    myMap["grape"] = 4;

    // 查找元素
    int* value = myMap.find("apple");
    if (value) {
        std::cout << "apple: " << *value << std::endl;
    }

    // 更新元素
    myMap["banana"] = 22;
    std::cout << "banana: " << myMap["banana"] << std::endl;

    // 删除元素
    myMap.erase("orange");
    std::cout << "size after erase: " << myMap.size() << std::endl;

    // 打印整个HashMap
    myMap.print();

    return 0;
}