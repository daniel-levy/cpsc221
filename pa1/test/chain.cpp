#include "chain.h"
#include "chain_given.cpp"

// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain(){ 
	this->clear();
}  

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
void Chain::insertBack(const Block & ndata){

	Node *currentNode = this->tail_->prev;
	Node *newNode = new Node(ndata);
	
	currentNode->next = newNode;
	
	newNode->prev = currentNode;
	newNode->next = this->tail_;
	
	this->tail_->prev = newNode;
	this->length_++;
	
	newNode = NULL;
}

/**
 * Modifies the Chain by moving a contiguous subset of len Nodes
 * dist nodes toward the end of the chain beginning from startPos
 * (maintaining the sentinel at the end). Their order is
 * not changed in the move. You may assume that the startPos and
 * len parameters are kind: startPos + len -1 <= length. If there
 * are not enough nodes to shift by dist, just shift as many as
 * possible.
 */
void Chain::moveBack(int startPos, int len, int dist){

	int tempDist = dist;
	
	if(tempDist == 0){
		return;
	}
	
	if((startPos + (len-1) + tempDist) > this->length_){
		tempDist = this->length_ - (startPos + len - 1);
	}
	
	Node *firstNode = this->walk(this->head_, startPos);
	Node *lastNode = this->walk(firstNode, len-1);
	Node *insertAt = this->walk(lastNode, tempDist);
	
	firstNode->prev->next = lastNode->next;
	lastNode->next->prev = firstNode->prev;	
	
	firstNode->prev = insertAt;
	lastNode->next = insertAt->next;	
	
	insertAt->next = firstNode;
	lastNode->next->prev = lastNode;	
	
	firstNode = NULL;
	lastNode = NULL;
	insertAt = NULL;
}

/**
 * Rolls the current Chain by k nodes: removes the last
 * k nodes from the Chain and attaches them, in order, at
 * the start of the chain (maintaining the sentinel at the front).
 */
void Chain::roll(int k){

	Node *firstNode = this->walk(this->head_->next, (this->length_)-k);
	Node *lastNode = this->tail_->prev;
	
	firstNode->prev->next = this->tail_;
	this->tail_->prev = firstNode->prev;
	
	lastNode->next=this->head_->next;
	lastNode->next->prev = lastNode;
	
	firstNode->prev = this->head_;
	this->head_->next = firstNode;
}

/**
 * Modifies the current chain by reversing the subchain
 * between pos1 and pos2, inclusive. The positions are
 * 1-based. You may assume that pos1 and pos2 are valid
 * locations in the Chain, and that pos2 >= pos1.
 */
void Chain::reverseSub(int pos1, int pos2){
	
	int moveBackDist = pos2 - pos1;
	
	for(int i = moveBackDist; i > 0; i--){
		moveBack(pos1, 1, i);
	}
}

/*
* Modifies both the current and input chains by removing
* nodes from other, and interleaving them between the Nodes
* from the current Chain. The nodes from the other Chain
* should occupy the even locations in the result. length
* of the resulting chain should be the sums of the lengths
* of current and the other. The other chain should have only
* two sentinels and no data nodes at the end of the operation.
* the weave fails and the original
* chains should be unchanged if block sizes are different.
* in that case, the result of the function should be:
* cout << "Block sizes differ." << endl;
*/
void Chain::weave(Chain & other) { // leaves other empty.
	
	int a_size = this->size();
	int b_size = other.size();
	
	Node * a_curr = this->head_->next;
	Node * a_next;
	Node * b_curr = other.head_->next; 
	Node * b_next;
	
	if(this->width_ != other.width_){
		cout << "Block sizes differ" << endl;
	}
	
	while(a_curr->next != NULL && b_curr->next != NULL){
		
		a_next = a_curr->next;
		b_next = b_curr->next;
		
		a_curr->next = b_curr;
		b_curr->prev = a_curr;
	
		b_curr->next = a_next;
		a_next->prev = b_curr;
		
		a_curr = a_next;
		b_curr = b_next; 
		
		this->length_++;
		other.length_--; 
	}
	
	if(a_size < b_size){
		
		a_curr->prev->next = b_curr;
		a_curr->prev = other.tail_->prev;
		other.tail_->prev->next = a_curr;
	
		this->length_ += other.length_;
		other.length_ = 0;
	} 

	other.head_->next = other.tail_;
	other.tail_->prev = other.head_;
}

/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class.
 */

void Chain::clear() {
    Node *currentNode = this->head_; 
	Node *nextNode = currentNode->next;
	
	while(nextNode->next != NULL){	
		delete currentNode;
		currentNode = nextNode;
		nextNode = nextNode->next;
	}	
	
	delete this->tail_;
}

/* makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */

void Chain::copy(Chain const& other) {
	
	head_ = new Node();
	tail_ = new Node();
	
	head_->next = tail_; 
	head_->prev = NULL;
	tail_->prev = head_;
	tail_->next = NULL;
	
	length_ = other.length_; 
	height_ = other.height_; 
	width_ = other.width_;
	
	Node * otherNode = other.head_->next;
	
	while(otherNode->next != NULL){
		this->insertBack(otherNode->data);
		otherNode = otherNode->next;
	}
}

