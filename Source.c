#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>
#pragma warning (disable:4996)
#define MAX_INDEX 100000
#define _CRTDBG_MAP_ALLOC
typedef struct vertex
{
    int index_vertex;
    struct vertex* next;
} vertex_t;
typedef struct graph
{
    int number_of_vertexes;
    int* visited;
    struct vertex_t** adjacency_list;
} graph_t;
int get_min_vertex(graph_t* graph, vertex_t* temp)
{
    vertex_t* current_vertex = temp;
    int min_size = MAX_INDEX;
    while (current_vertex)
    {
        if ((current_vertex->index_vertex < min_size) && (graph->visited[current_vertex->index_vertex] != 1))
        {
            min_size = current_vertex->index_vertex;
        }
        current_vertex = current_vertex->next;
    }
    if (min_size == MAX_INDEX) {
        return -1;
    }
    else {
        return min_size;
    }
}
int counter_not_visited(graph_t* graph, vertex_t* start_of_adjacency_list)
{
    int count = 0;
    vertex_t* current_vertex = start_of_adjacency_list;
    while (current_vertex)
    {
        if (graph->visited[current_vertex->index_vertex] != 1)
        {
            count++;
        }
        current_vertex = current_vertex->next;
    }
    return count;
}
void dfs(graph_t* graph, int index_started_vertex) {
    vertex_t* started_vertex = graph->adjacency_list[index_started_vertex];
    vertex_t* current_vertex = started_vertex;
    if (index_started_vertex == -1)
        return;
    int not_visited_vertexes = counter_not_visited(graph, current_vertex);
    graph->visited[index_started_vertex] = 1;
    printf("%d ", index_started_vertex);
    while (not_visited_vertexes) {
        int connected_vertex = get_min_vertex(graph, current_vertex);
        if (graph->visited[connected_vertex] == 0) {
            dfs(graph, connected_vertex);
        }
        not_visited_vertexes--;
    }
}
vertex_t* create_node(int index_number)
{
    vertex_t* vertex_created = (vertex_t*)malloc(sizeof(vertex_t));
    if (vertex_created == NULL) return NULL;
    vertex_created->index_vertex = index_number;
    vertex_created->next = NULL;
    return vertex_created;
}
graph_t* create_graph(int number)
{
    graph_t* graph = (graph_t*)malloc(sizeof(graph_t));
    if (graph == NULL) return NULL;
    graph->number_of_vertexes = number;
    graph->adjacency_list = malloc(number * sizeof(vertex_t*));
    if (graph->adjacency_list == NULL) return NULL;
    graph->visited = malloc(number * sizeof(int));
    if (graph->visited == NULL) return NULL;
    for (int i = 0; i < number; i++) {
        graph->adjacency_list[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}
void add_connection(graph_t* graph, int vertex_1, int vertex_2)
{
    vertex_t* new_node = create_node(vertex_2);
    new_node->next = graph->adjacency_list[vertex_1];
    graph->adjacency_list[vertex_1] = new_node;
    new_node = create_node(vertex_1);
    new_node->next = graph->adjacency_list[vertex_2];
    graph->adjacency_list[vertex_2] = new_node;
}


void free_graph(graph_t* graph) {
    int i = 0;
    for (; i < graph->number_of_vertexes; i++) {
        free(graph->adjacency_list[i]);
    }
    free(graph->adjacency_list);
    free(graph->visited);
    free(graph);
}
void MemoryLeaks(void) {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
}
int main()
{
    int vertex_edge;
    scanf("%d", &vertex_edge);
    graph_t* new_graph = create_graph(vertex_edge);
    for (int i = 0; i < vertex_edge; i++)
    {
        int vertex_1; char next_parse;
        scanf("%d%c", &vertex_1, &next_parse);
        while (next_parse == ' ')
        {
            int vertex_2;
            scanf("%d%c", &vertex_2, &next_parse);
            add_connection(new_graph, vertex_1, vertex_2);
        }
    }
    dfs(new_graph, 0);
    free_graph(new_graph);
    MemoryLeaks();
    return 0;
}