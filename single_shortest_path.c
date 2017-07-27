#include<stdio.h>
#include<stdlib.h>

#define UNKNOWN_VERTEX -99
#define MAX_WEIGHT 9999

struct node
{
    int vertex;
    int weight;
    struct node *next;
};

struct pq_node
{
    int vertex;
    int weight;
};

void swap(struct pq_node*, struct pq_node*);
void heapify(struct pq_node*,int);
int search_in_heap(struct pq_node *array, int node_to_search, int array_size);
int* dijkstra_algo(struct node**, int);
void insert_graph(struct node**, int, int);
void display_graph(struct node**, int);
void shortest_path(int *prev, int first, int last);

int main()
{
    int num_vertices;
    int vertex;
    int i;
    int weight;
    int *prev = NULL;
    struct node **graph = NULL;
        
    printf("Enter number of vertices in Graph:");
    scanf("%d", &num_vertices);

    graph = (struct node**)malloc(num_vertices * sizeof(struct node*));

    for(i = 0; i < num_vertices; i++) {
        while(1) {
            printf("Enter the vertex adjacent to %d vertex(To stop press -1):", i);
            scanf("%d", &vertex);
            if(vertex == -1) {
                break;
            } else {
                printf("Enter the weight from %d to %d vertex:", i, vertex);
                scanf("%d", &weight);
 
                insert_graph(&graph[i], vertex, weight);
            }
        }
    }

    printf("Displaying Graph\n");
    display_graph(graph, num_vertices);

    printf("Triggering Dijkstra algorithm for single shortest path\n");
    prev = dijkstra_algo(graph, num_vertices);

    for(i = 1; i < num_vertices; i++) {
        printf("shortest path from 0 to %d vertex\n", i);
        shortest_path(prev, 0, i);
        printf("\n");
    }
    return 0;
}

void shortest_path(int *prev, int first, int last)
{
    if(last == UNKNOWN_VERTEX) {
        return;
    } else {
        shortest_path(prev, last, prev[last]);
        printf("%d--", last);
        return;
    }
}

void insert_graph(struct node **head, int vertex, int weight)
{
    struct node *tmp_node = NULL;
    struct node *tmp_head = NULL;

    tmp_node = (struct node*)malloc(sizeof(struct node));
    tmp_node->vertex = vertex;
    tmp_node->weight = weight;
    tmp_node->next = NULL;

    tmp_head = *head;
    if(tmp_head == NULL) {
        *head = tmp_node;
    } else {
        while(tmp_head->next) {
            tmp_head = tmp_head->next;
        }
        tmp_head->next = tmp_node;
    }
}

void display_graph(struct node** graph, int num_vertices)
{
    int i = 0;
    struct node* temp = NULL;


    for(i = 0; i < num_vertices; i++) {
        printf("%d==>", i);
        temp = graph[i];
        while(temp) {
            printf("%d(%d)--", temp->vertex, temp->weight);
            temp = temp->next;
        }
        printf("\n");
    }
}

int* dijkstra_algo(struct node **graph, int num_vertices)
{
    struct pq_node *array = NULL;
    int *prev = NULL;
    int i;
    struct pq_node min;
    int node_loc;
    int adj_node;
    int *visited = NULL;

    array = (struct pq_node*)malloc(num_vertices * sizeof(struct pq_node));
    prev = (int*)malloc(num_vertices * sizeof(int));
    visited = (int*)malloc(num_vertices * sizeof(int));
    
    for(i = 0; i < num_vertices; i++) {
        array[i].vertex = i;
        array[i].weight = MAX_WEIGHT;
        prev[i] = UNKNOWN_VERTEX;
        visited[i] = 0;
    }

    /*Taking 0th vertex as start vertex*/
    array[0].weight = 0;
    visited[0] = 1;
    heapify(array, num_vertices-1);

    for(i = num_vertices-1; i >= 0; i--) {
        min = array[0];

        while(graph[min.vertex]) {
            adj_node = graph[min.vertex]->vertex;

            node_loc = search_in_heap(array, adj_node, i);
            if(visited[adj_node] == 0 && ((array[0].weight + graph[min.vertex]->weight) < array[node_loc].weight)) {
                array[adj_node].weight = graph[min.vertex]->weight + array[min.vertex].weight;
                prev[adj_node] = min.vertex;
            }
            graph[min.vertex] = graph[min.vertex]->next;
        }

        visited[min.vertex] = 1;
        swap(&array[0], &array[i]);
        heapify(array, i-1);
    }
    
    return prev;
}

int search_in_heap(struct pq_node *array, int node_to_search, int array_size)
{
    int i = 0;

    for(i = 0; i < array_size; i++) {
        if(array[i].vertex == node_to_search) {
            return i;
        }
    }
    return -1;
}

void heapify(struct pq_node *array, int num)
{
    int i,j;
    int min, left, right;

    for(i=num/2; i>=0; i--) {
        left = 2*i;
        right = 2*i + 1;

        if(left <= num && right <= num) {
            if(array[left].weight < array[right].weight) {
                min = left;
            } else {
                min = right;
            }
            if(array[min].weight < array[i].weight) { 
                swap(&array[min], &array[i]);
            }
        } else if(left <= num && right > num) {
            if(array[left].weight < array[i].weight) {
                swap(&array[left], &array[i]);
            }
        }
    } 
}

void swap(struct pq_node *a, struct pq_node *b)
{
    int tmp_weight;
    int tmp_vertex;

    tmp_weight = a->weight;
    tmp_vertex = a->vertex;

    (*a).vertex = (*b).vertex;
    (*a).weight = (*b).weight;

    (*b).weight = tmp_weight;
    (*b).vertex = tmp_vertex;
}
