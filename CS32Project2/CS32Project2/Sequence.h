
#ifndef Sequence_h
#define Sequence_h
#include<string>

using ItemType = std::string;

class Sequence
{
public:
    Sequence();
    ~Sequence();
    bool empty() const;
    int size() const;
    int insert(int pos, const ItemType& value);
    int insert(const ItemType& value);
    bool erase(int pos);
    int remove(const ItemType& value);
    bool get(int pos, ItemType& value) const;
    bool set(int pos, const ItemType& value);
    int find(const ItemType& value) const;
    void swap(Sequence& other);

    //for testing
    void dump() const;

private:
    int m_size;

    struct Node
    {
        ItemType value;
        //value of item in node

        Node* next;
        //pointer to next item

        Node* prev;
        //pointer to previous item
    };

    Node* head;
    Node* tail;

};

int subsequence(const Sequence& seq1, const Sequence& seq2);

void concatReverse(const Sequence& seq1, const Sequence& seq2, Sequence& result);

#endif // !Sequence_h