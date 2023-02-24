/*
 * Our min-heap implementation.
 *
 * Author (starter code): A. Tafliovich.
 */

#include "minheap.h"

#define ROOT_INDEX 1
#define NOTHING -1

/*************************************************************************
 ** Suggested helper functions
 *************************************************************************/

/* Swaps contents of heap->arr[index1] and heap->arr[index2] if both 'index1'
 * and 'index2' are valid indices for minheap 'heap'. Has no effect
 * otherwise.
 */

///!!!!!!!!!!!!!!!!!!what contents, does it include priority
void swap(MinHeap* heap, int index1, int index2){
  if(index1>=1 && index2>=1 && index1<=heap->size && index2<=heap->size){
    HeapNode copy=heap->arr[index1];
    heap->arr[index1]=heap->arr[index2];
    heap->arr[index2]=copy;
  }
}

/* Bubbles up the element newly inserted into minheap 'heap' at index
 * 'nodeIndex', if 'nodeIndex' is a valid index for heap. Has no effect
 * otherwise.
 */
void bubbleUp(MinHeap* heap, int nodeIndex){
  int parentIdx;
  while (nodeIndex>ROOT_INDEX && nodeIndex<=heap->size){
    parentIdx=nodeIndex/2;
    if(heap->arr[parentIdx].priority>heap->arr[nodeIndex].priority){
      swap(heap,parentIdx,nodeIndex);
      nodeIndex=parentIdx;
    }
    else{
      break;
    }
  }
}

/* Bubbles down the element newly inserted into minheap 'heap' at the root,
 * if it exists. Has no effect otherwise.
 */
void bubbleDown(MinHeap* heap){
  if(heap->size<=ROOT_INDEX){
    return;
  }
  int p,l,r;
  int minIdx;
  p=ROOT_INDEX;
  while(p<=heap->size){
    l=2*p;
    r=2*p+1;
    minIdx=p;
    if(l<=heap->size && heap->arr[l].priority<heap->arr[p].priority){
      minIdx=l;
    }
    if(r<=heap->size && heap->arr[r].priority<heap->arr[minIdx].priority){
      minIdx=r;
    }
    if(minIdx!=p){
      swap(heap,p,minIdx);
      p=minIdx;
    }
    else{
      break;
    }
  }
}

/* Returns the index of the left child of a node at index 'nodeIndex' in
 * minheap 'heap', if such exists.  Returns NOTHING if there is no such left
 * child.
 */
int leftIdx(MinHeap* heap, int nodeIndex){
  int left=2*nodeIndex;
  if(left<=heap->size){
    return left;
  }
  else{
    return NOTHING;
  }
}

/* Returns the index of the right child of a node at index 'nodeIndex' in
 * minheap 'heap', if such exists.  Returns NOTHING if there is no such right
 * child.
 */
int rightIdx(MinHeap* heap, int nodeIndex){
  int right=2*nodeIndex+1;
  if(right<=heap->size){
    return right;
  }
  else{
    return NOTHING;
  }
}

/* Returns the index of the parent of a node at index 'nodeIndex' in minheap
 * 'heap', if such exists.  Returns NOTHING if there is no such parent.
 */
int parentIdx(MinHeap* heap, int nodeIndex){
  int parent=nodeIndex/2;
  if(parent>=1){
    return parent;
  }
  else{
    return NOTHING;
  }
}

/* Returns True if 'maybeIdx' is a valid index in minheap 'heap', and 'heap'
 * stores an element at that index. Returns False otherwise.
 */
bool isValidIndex(MinHeap* heap, int maybeIdx){
  if(ROOT_INDEX<=maybeIdx && maybeIdx<=heap->size){
    return true;
  }
  return false;
}

/* Doubles the capacity of minheap 'heap'.
 */
void doubleCapacity(MinHeap* heap){
  heap->capacity=heap->capacity*2;
  HeapNode* arr=malloc(heap->capacity*sizeof(HeapNode));
  for(int i=ROOT_INDEX;i<=heap->size;i++){
    arr[i]=heap->arr[i];
  }
  free(heap->arr);

  int* indexMap=malloc(heap->capacity*sizeof(int));
  for(int i=ROOT_INDEX;i<=heap->size;i++){
    indexMap[i]=heap->indexMap[i];
  }
  for(int i=heap->size+1;i<=heap->capacity;i++){
    indexMap[i]=-1;
  }
  free(heap->indexMap);

  heap->arr=arr;
  heap->indexMap=indexMap;
}

/* Returns priority of node at index 'nodeIndex' in minheap 'heap'.
 * Precondition: 'nodeIndex' is a valid index in 'heap'
 *               'heap' is non-empty
 */
int priorityAt(MinHeap* heap, int nodeIndex){
  return heap->arr[nodeIndex].priority;
}

/*********************************************************************
 * Required functions
 ********************************************************************/


/* Returns the node with minimum priority in minheap 'heap'.
 * Precondition: heap is non-empty
 */
HeapNode getMin(MinHeap* heap){
  return heap->arr[ROOT_INDEX];
}

/* Removes and returns the node with minimum priority in minheap 'heap'.
 * Precondition: heap is non-empty
 */
HeapNode extractMin(MinHeap* heap);

/* Inserts a new node with priority 'priority' and value 'value' into minheap
 * 'heap'. If 'heap' is full, double the capacity of 'heap' before inserting
 * the new node.
 */
void insert(MinHeap* heap, int priority, void* value);

/* Sets priority of node with ID 'id' in minheap 'heap' to 'newPriority', if
 * such a node exists in 'heap' and its priority is larger than
 * 'newPriority', and returns True. Has no effect and returns False, otherwise.
 * Note: this function bubbles up the node until the heap property is restored.
 */
bool decreasePriority(MinHeap* heap, int id, int newPriority);

/* Returns a newly created empty minheap with initial capacity 'capacity'.
 * Precondition: capacity > 0
 */
MinHeap* newHeap(int capacity){
  MinHeap* new=malloc(sizeof(MinHeap));
  new->size=0;
  new->capacity=capacity;
  new->arr=malloc(capacity*sizeof(HeapNode));
  new->indexMap=malloc(capacity*sizeof(int));
  for(int i=0;i<=capacity;i++){
    new->indexMap[i]=-1;
  }
}

/* Frees all memory allocated for minheap 'heap'.
 */
void deleteHeap(MinHeap* heap){
  free(heap->arr);
  free(heap->indexMap);
  free(heap);
}

/*********************************************************************
 ** Helper function provided in the starter code
 *********************************************************************/

void printHeap(MinHeap* heap) {
  printf("MinHip with size: %d\n\tcapacity: %d\n\n", heap->size,
         heap->capacity);
  printf("index: priority [ID]\t ID: index\n");
  for (int i = ROOT_INDEX; i <= heap->size; i++)
    printf("%d: %d [%d]\t\t%d: %d\n", i, heap->arr[i].priority, heap->arr[i].id,
           i, heap->indexMap[i]);
  for (int i = heap->size + 1; i <= heap->capacity; i++)
    printf("\t\t\t%d: %d\n", i, heap->indexMap[i]);
  printf("\n\n");
}

/*********************************************************************
 ** Helper functions not provided in the starter code
 *********************************************************************/
