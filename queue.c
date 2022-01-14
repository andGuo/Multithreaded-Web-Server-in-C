#include <common.h>

typedef struct {
  nodeType *head;
  nodeType *tail;
} queueType;

typedef struct node{
    struct node *next;
    int *clientFd;
} nodeType;

void initQueue(queueType *q)
{
  q->head = NULL;
  q->tail = NULL;
}

void addTask(queueType *q, int *clientSocket)
{
  nodeType *currentNode;
  nodeType *newNode;

  currentNode = q->tail;

  newNode = malloc(sizeof(nodeType));
  newNode->next = NULL;
  newNode->clientFd = clientSocket;

  if (isEmpty(q) == 0)
  {
    q->head = newNode;
    q->tail = newNode;
  }
  else 
  {
    q->tail = newNode;
    currentNode->next = newNode;
  }
}

int pollFirst(queueType *q, int **clientSocket)
{
  nodeType *currentNode;
  nodeType *nextNode;

  if (isEmpty(q) == 0)
  {
    return -1;
  }

  currentNode = q->head;
  nextNode = q->head->next;

  *clientSocket = currentNode->clientFd;

  free(currentNode); // Remove first (head)

  if (nextNode == NULL) // is now an empty list
  {
    q->head = NULL;
    q->tail = NULL;
  }
  else
  {
    q->head = nextNode;
  }

  return 0;
}

int isEmpty(queueType *q)
{
  if (q->head == NULL && q->tail == NULL)
  {
    return 0;
  }
  else
  {
    return -1;
  }
}

void cleanQueue(queueType *q)
{
  nodeType *currentNode;
  nodeType *nextNode;

  currentNode = q->head;

  while (currentNode != NULL)
  {
    nextNode = currentNode->next;
    cleanupSocket(currentNode->clientFd);
    free(currentNode);
    currentNode = nextNode;
  }

  q->head = NULL;
  q->tail = NULL;
}

