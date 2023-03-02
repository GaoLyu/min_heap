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
  if(index1>=ROOT_INDEX && index2>=ROOT_INDEX && index1<=heap->size && index2<=heap->size){
    HeapNode copy=heap->arr[index1];
    int id1=heap->arr[index1].id;
    int id2=heap->arr[index2].id;
    int c=heap->indexMap[id1];
    heap->arr[index1]=heap->arr[index2];
    heap->arr[index2]=copy;
    heap->indexMap[id1]=heap->indexMap[id2];
    heap->indexMap[id2]=c;
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
    l=leftIdx(heap,p);
    r=rightIdx(heap,p);
    minIdx=p;
    if(l!=NOTHING && heap->arr[l].priority<heap->arr[p].priority){
      minIdx=l;
    }
    if(r!=NOTHING && heap->arr[r].priority<heap->arr[minIdx].priority){
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
  heap->arr=realloc(heap->arr,(heap->capacity+1)*sizeof(HeapNode));
  printf("test1\n\n");
  
  heap->indexMap=realloc(heap->indexMap,(heap->capacity+1)*sizeof(int));
  printf("test2\n\n");
  for(int i=heap->size+1;i<=heap->capacity;i++){
    heap->indexMap[i]=NOTHING;
    printf("test3\n\n");
  }
  
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
HeapNode extractMin(MinHeap* heap){
  HeapNode min=getMin(heap);
  int size=heap->size;
  int idlast=heap->arr[size].id;
  int idmin=heap->arr[1].id;
  heap->arr[1]=heap->arr[size];
  heap->indexMap[idlast]=heap->indexMap[idmin];
  heap->indexMap[idmin]=NOTHING;
  heap->size--;
  bubbleDown(heap);
  return min;
}

/* Inserts a new node with priority 'priority' and value 'value' into minheap
 * 'heap'. If 'heap' is full, double the capacity of 'heap' before inserting
 * the new node.
 */
void insert(MinHeap* heap, int priority, void* value){
  if(heap->size==heap->capacity){
    doubleCapacity(heap);
  }
  heap->size++;
  int size=heap->size;
  heap->arr[size].priority=priority;
  heap->arr[size].value=value;
  heap->arr[size].id=size;
  heap->indexMap[size]=size;
  bubbleUp(heap,size);
}

/* Sets priority of node with ID 'id' in minheap 'heap' to 'newPriority', if
 * such a node exists in 'heap' and its priority is larger than
 * 'newPriority', and returns True. Has no effect and returns False, otherwise.
 * Note: this function bubbles up the node until the heap property is restored.
 */
bool decreasePriority(MinHeap* heap, int id, int newPriority){
  
  int index=heap->indexMap[id];
  if(!(isValidIndex(heap,index))){
    return false;
  }
  if(heap->arr[index].priority<=newPriority){
    return false;
  }
  else{
    heap->arr[index].priority=newPriority;
    bubbleUp(heap,index);
    return true;
  }
  
}
  
/* Returns a newly created empty minheap with initial capacity 'capacity'.
 * Precondition: capacity > 0
 */
MinHeap* newHeap(int capacity){
  MinHeap* new=malloc(sizeof(MinHeap));
  new->size=0;
  new->capacity=capacity;
  new->arr=malloc((capacity+1)*sizeof(HeapNode));
  new->indexMap=malloc((capacity+1)*sizeof(int));
  for(int i=0;i<=capacity;i++){
    new->indexMap[i]=NOTHING;
  }
  return new;
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
