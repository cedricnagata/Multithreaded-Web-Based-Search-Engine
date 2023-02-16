// Cedric Nagata
// nagatac@uw.edu

#include "SimpleQueue.h"

static pthread_mutex_t queue_lock; // queue lock

SimpleQueue::SimpleQueue() {
  size = 0;
  front = nullptr;
  end = nullptr;

  pthread_mutex_init(&queue_lock, NULL); // create lock
}

SimpleQueue::~SimpleQueue() {
  while (front != nullptr) {
    node *next = front->next;
    delete front;
    front = next;
  }

  pthread_mutex_destroy(&queue_lock); // destroy lock
}

void SimpleQueue::Enqueue(string item) {
  pthread_mutex_lock(&queue_lock); // lock queue for enqueue function
  
  node *new_node = new node();
  new_node->next = nullptr;
  new_node->item = item;
  if (end != nullptr) {
    end->next = new_node;
  } else  {
    front = new_node;
  }
  end = new_node;
  size++;

  pthread_mutex_unlock(&queue_lock); // unlock after function is done
}

bool SimpleQueue::Dequeue(string *result) {  
  if (size == 0) {
    return false;
  }

  pthread_mutex_lock(&queue_lock); // lock queue for dequeue function

  *result = front->item;
  node *next = front->next;
  delete front;
  if (end == front) {
    end = front = next;
  } else {
    front = next;
  }
  size--;

  pthread_mutex_unlock(&queue_lock); // unlock after function is done

  return true;
}

int SimpleQueue::Size() const {
  return size;
}

bool SimpleQueue::IsEmpty() const {
  return size == 0;
}
