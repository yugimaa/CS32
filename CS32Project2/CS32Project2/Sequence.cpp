#include "Sequence.h"
#include <iostream>
using namespace std;



Sequence::Sequence()
{
	m_size = 0;
	head = nullptr; //sets head as a null pointer
	tail = nullptr; //sets tail as null pointer
}

Sequence::~Sequence()
{
	Node* p = head;
	while (p != nullptr)
	{
		Node* toBeDeleted = p;
		p = p->next;
		delete toBeDeleted;
	}
	head = nullptr;
	tail = nullptr;
	m_size = 0;
}

//for testing purposes:
void Sequence::dump() const
{
	Node* p = head;
	while (p != nullptr)
	{
		cerr << p->value << " ";
		p = p->next;
	}
	cout << endl;
}

bool Sequence::empty() const
{
	if (m_size == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Sequence::size() const
{
	return m_size;
}

int Sequence::insert(const ItemType& value)
{
	//creates a new node for item
	Node* newNode = new Node{ value, nullptr, nullptr };
	Node* p;

	//if first item (WORKS!)
	if (head == nullptr && tail == nullptr) //empty list
	{
		//set head to point to newNode
		head = newNode;
		tail = newNode;
	}

	//if not first item
	else
	{
		//goes through head to end and finds the value where p>value and sets p as that value
		for (p = head; p != nullptr; p = p->next)
		{
			if (p->value >= value) //if such values exists
			{
				if (p->prev == nullptr) //first item on list
				{
					Node* temp = head;
					head = newNode;
					newNode->next = temp;
				}
				else
				{
					p->prev->next = newNode;
					newNode->prev = p->prev;
					p->prev = newNode;
					//have newNode.next point to p
					newNode->next = p;
				}

				//have nnewNode.prev to point to p.prev (which is previous of p)
				break;
			}

			//if such values does not exist and it goes to nullptr, add to end
			else if (p->next == nullptr)
			{
				p->next = newNode;

				newNode->next = nullptr;

				newNode->prev = p;

				tail = newNode;

				//missing break caused issue 
				break;
			}
		}
	}

	m_size++;

	//sets position number and returns pos
	int m_pos = 0;
	for (p = head; p != newNode; p = p->next)
	{
		m_pos++;
	}
	return m_pos;
}

int Sequence::insert(int pos, const ItemType& value)
{

	//returns -1 if position is not valid
	if (pos<0 || pos>size())
	{
		return -1;
	}

	//creates a new node for item
	Node* newNode = new Node{ value, nullptr, nullptr };
	Node* q = head;

	if (pos == size()) //insert at end if position is at the end of list
	{
		q = tail;
		if (tail == nullptr) //meaning list is empty
		{
			head = newNode;
			tail = newNode;
		}
		else
		{
			q->next = newNode;
			newNode->prev = q;
			tail = newNode;
		}
	}
	else //not at end of list
	{
		//goes through head to end and finds the value where p>value and sets p as that value
		for (int i = 0; i < pos; i++)	//repeats until position
		{
			q = q->next;
		}
		//once at position, change the pointers
		newNode->next = q;

		if (q->prev == nullptr) //meaning q is first item
		{
			newNode->prev = nullptr; //set the item to null (first item)
			head = newNode;
		}
		else
		{
			newNode->prev = q->prev;
			q->prev->next = newNode;
		}
	}

	//calibrate the list
	m_size++;

	//sets position number and returns pos
	int m_pos = 0;
	for (q = head; q != newNode; q = q->next)
	{
		m_pos++;
	}
	return m_pos;
}

int Sequence::find(const ItemType& value) const
{
	Node* p;
	//goes through the list until value matches the value of pointer
	for (p = head; p != nullptr; p = p->next)
	{
		if (p->value == value)
		{
			break;
		}
		else if (p->next == nullptr) //return -1 if no value is dound
		{
			return -1;
		}
	}

	int m_pos = 0;
	for (Node* q = head; q != p; q = q->next)
	{
		m_pos++;
	}
	return m_pos;
}

bool Sequence::erase(int pos)
{
	if (0 <= pos && pos < size()) //checks if valid inpute
	{
		Node* p = head;
		if (pos == 0) //if pos = 0 (first item)
		{
			Node* toBeDeleted = p; //what head points to 
			
			if (size() == 1) //the item being deleted is the only one that exists (WORKS!)
			{
				tail = nullptr;
				head = nullptr;
			}
			else //WORKS!
			{
				head = toBeDeleted->next;
				head->prev = nullptr; //these two sets new head
			}
			delete toBeDeleted;
		}

		else //if pos is not first item
		{
			//move to positon (p is set to 1 before item to be deleted)
			for (int i = 0; i < pos; i++)
			{
				p = p->next;
			}

			//test code
			//cout << p->prev->value << " " << p->value << " " << p->next->value;

			Node* toBeDeleted = p;

			if (p->next != nullptr) 
			{
				p->next->prev = p->prev;
			}
			else 
			{
				tail = p; // if the item being deleted is last item, set tail to point to p instead.
			}
			p->prev->next = p->next;
			delete toBeDeleted;
		}

		m_size--;

		return true;
	}
	else
	{
		return false;
	}
}

int Sequence::remove(const ItemType& value)
{
	int numItemRemoved = 0;
	while (find(value) != -1)
	{
		erase(find(value));
		numItemRemoved++;
	}
	return numItemRemoved;
}

bool Sequence::get(int pos, ItemType& value) const
{
	if (0 <= pos && pos < size())
	{
		Node* p = head;
		for (int i = 0; i < pos; i++)	//repeats until position
		{
			p = p->next;
		}

		value = p->value;
		return true;
	}
	else
	{
		return false;
	}
}

bool Sequence::set(int pos, const ItemType& value)
{
	if (0 <= pos && pos < size())
	{
		Node* p = head;
		for (int i = 0; i < pos; i++)	//repeats until position
		{
			p = p->next;
		}

		p->value = value;
		return true;
	}
	else
	{
		return false;
	}
}

void Sequence::swap(Sequence& other)
{
	//swap size
	int tempSize = m_size;
	m_size = other.m_size;
	other.m_size = tempSize;

	//swap head
	Node* tempHead = head;
	head = other.head;
	other.head = tempHead;

	Node* tempTail = tail;
	tail = other.tail;
	other.tail = tempTail;
}


int subsequence(const Sequence& seq1, const Sequence& seq2)
{
	ItemType item1, item2;
	//compare two sequences until one reaches end
	for (int i = 0; i < seq1.size(); i++)
	{
		seq1.get(i, item1);
		if (seq2.find(item1) != -1) //match is found
		{
			seq1.get(i + 1, item2); //get next item
			if (seq2.find(item2) != -1 && (seq2.find(item2) == (seq2.find(item1) +1 ))) //match is found and its +1 position from previoeus item
			{
				seq1.get(i + 2, item1); //get 3rd item and store in item 1
				if (seq2.find(item1) != -1 && (seq2.find(item1) == (seq2.find(item2) + 1))) //match is found three consecutive positions
				{
					return i; //return i (smallest number)
				}
			}
		}
	}
	return -1;
}

void concatReverse(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
	ItemType temp;
	int j = 0;
	int size = result.size();

	for (int i = 0; i < size; i++) //clears reuslt list
	{
		result.erase(0);
	}


	for (int i = seq1.size() -1; i >= 0; i--) //transcrives from seq1
	{
		seq1.get(i, temp); //gets item from last spot
		result.insert(j, temp);
		j++;
	}

	for (int i = seq2.size() - 1; i >= 0; i--) //transcribes from seq2
	{
		seq2.get(i, temp); //gets item from last spot
		result.insert(j, temp);
		j++;
	}
}