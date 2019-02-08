/**
 * @file queue.cpp
 * Implementation of the Queue class.
 *
 */

/**
 * Adds the parameter object to the back of the Queue.
 *
 * @param newItem object to be added to the Queue.
 */
template <class T>
void Queue<T>::enqueue(T const& newItem)
{
    this->inStack.push(newItem);
}

/**
 * Removes the object at the front of the Queue, and returns it to the
 * caller.
 *
 * @return The item that used to be at the front of the Queue.
 */
template <class T>
T Queue<T>::dequeue()
{
    while(!this->inStack.isEmpty()){
		this->outStack.push(this->inStack.pop());
	}
	
	T tempVal = this->outStack.pop();
	
	while(!this->outStack.isEmpty()){
		this->inStack.push(this->outStack.pop());
	}
	
	return tempVal;
}

/**
 * Adds an element to the ordering structure.
 *
 * @see OrderingStructure::add()
 */
template <class T>
void Queue<T>::add(const T& theItem)
{
	this->enqueue(theItem);
}

/**
 * Removes an element from the ordering structure.
 *
 * @see OrderingStructure::remove()
 */
template <class T>
T Queue<T>::remove()
{
   return this->dequeue();
}

/**
 * Finds the object at the front of the Queue, and returns it to the
 * caller. Unlike pop(), this operation does not alter the queue.
 *
 * @return The item at the front of the queue.
 */
template <class T>
T Queue<T>::peek()
{
    while(!this->inStack.isEmpty()){
		this->outStack.push(this->inStack.pop());
	}
	
	T tempVal = this->outStack.pop();
	this->inStack.push(tempVal);
	
	while(!this->outStack.isEmpty()){
		this->inStack.push(this->outStack.pop());
	}
	
	return tempVal; 
}

/**
 * Determines if the Queue is empty.
 *
 * @return bool which is true if the Queue is empty, false otherwise.
 */
template <class T>
bool Queue<T>::isEmpty() const
{
    return this->inStack.isEmpty();	
}
