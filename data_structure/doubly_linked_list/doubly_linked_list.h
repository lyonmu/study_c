#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node *prev;
  struct Node *next;
} Node;

typedef struct DoublyLinkedList {
  Node *head;
  Node *tail;
  int size;
} DoublyLinkedList;

// 创建和初始化
DoublyLinkedList *dll_create(void);
void dll_init(DoublyLinkedList *list);
void dll_destroy(DoublyLinkedList *list);

// 节点操作
Node *dll_create_node(int data);
void dll_destroy_node(Node *node);

// 插入操作
bool dll_insert_at_head(DoublyLinkedList *list, int data);
bool dll_insert_at_tail(DoublyLinkedList *list, int data);
bool dll_insert_at_index(DoublyLinkedList *list, int index, int data);
bool dll_insert_after_node(DoublyLinkedList *list, Node *node, int data);
bool dll_insert_before_node(DoublyLinkedList *list, Node *node, int data);

// 删除操作
bool dll_delete_at_head(DoublyLinkedList *list);
bool dll_delete_at_tail(DoublyLinkedList *list);
bool dll_delete_at_index(DoublyLinkedList *list, int index);
bool dll_delete_by_value(DoublyLinkedList *list, int value);
bool dll_delete_node(DoublyLinkedList *list, Node *node);

// 查找操作
Node *dll_find_by_value(DoublyLinkedList *list, int value);
Node *dll_find_by_index(DoublyLinkedList *list, int index);
int dll_get_value_at_index(DoublyLinkedList *list, int index);

// 查询操作
int dll_get_size(DoublyLinkedList *list);
bool dll_is_empty(DoublyLinkedList *list);

// 遍历和打印
void dll_print_forward(DoublyLinkedList *list);
void dll_print_backward(DoublyLinkedList *list);
void dll_traverse_forward(DoublyLinkedList *list, void (*callback)(Node *));
void dll_traverse_backward(DoublyLinkedList *list, void (*callback)(Node *));

// 其他操作
void dll_clear(DoublyLinkedList *list);
void dll_reverse(DoublyLinkedList *list);

#endif // DOUBLY_LINKED_LIST_H
