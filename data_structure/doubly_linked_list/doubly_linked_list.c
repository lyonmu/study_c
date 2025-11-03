#include "doubly_linked_list.h"

// 创建和初始化
DoublyLinkedList *dll_create(void) {
  DoublyLinkedList *list = (DoublyLinkedList *)malloc(sizeof(DoublyLinkedList));
  if (list == NULL) {
    return NULL;
  }
  dll_init(list);
  return list;
}

void dll_init(DoublyLinkedList *list) {
  if (list == NULL) {
    return;
  }
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
}

void dll_destroy(DoublyLinkedList *list) {
  if (list == NULL) {
    return;
  }
  dll_clear(list);
  free(list);
}

// 节点操作
Node *dll_create_node(int data) {
  Node *node = (Node *)malloc(sizeof(Node));
  if (node == NULL) {
    return NULL;
  }
  node->data = data;
  node->prev = NULL;
  node->next = NULL;
  return node;
}

void dll_destroy_node(Node *node) {
  if (node != NULL) {
    free(node);
  }
}

// 插入操作
bool dll_insert_at_head(DoublyLinkedList *list, int data) {
  if (list == NULL) {
    return false;
  }

  Node *new_node = dll_create_node(data);
  if (new_node == NULL) {
    return false;
  }

  if (list->head == NULL) {
    // 空链表
    list->head = new_node;
    list->tail = new_node;
  } else {
    new_node->next = list->head;
    list->head->prev = new_node;
    list->head = new_node;
  }
  list->size++;
  return true;
}

bool dll_insert_at_tail(DoublyLinkedList *list, int data) {
  if (list == NULL) {
    return false;
  }

  Node *new_node = dll_create_node(data);
  if (new_node == NULL) {
    return false;
  }

  if (list->tail == NULL) {
    // 空链表
    list->head = new_node;
    list->tail = new_node;
  } else {
    new_node->prev = list->tail;
    list->tail->next = new_node;
    list->tail = new_node;
  }
  list->size++;
  return true;
}

bool dll_insert_at_index(DoublyLinkedList *list, int index, int data) {
  if (list == NULL || index < 0 || index > list->size) {
    return false;
  }

  if (index == 0) {
    return dll_insert_at_head(list, data);
  }

  if (index == list->size) {
    return dll_insert_at_tail(list, data);
  }

  // 找到目标位置的节点
  Node *current = dll_find_by_index(list, index);
  if (current == NULL) {
    return false;
  }

  return dll_insert_before_node(list, current, data);
}

bool dll_insert_after_node(DoublyLinkedList *list, Node *node, int data) {
  if (list == NULL || node == NULL) {
    return false;
  }

  Node *new_node = dll_create_node(data);
  if (new_node == NULL) {
    return false;
  }

  new_node->prev = node;
  new_node->next = node->next;

  if (node->next != NULL) {
    node->next->prev = new_node;
  } else {
    // node 是尾节点
    list->tail = new_node;
  }

  node->next = new_node;
  list->size++;
  return true;
}

bool dll_insert_before_node(DoublyLinkedList *list, Node *node, int data) {
  if (list == NULL || node == NULL) {
    return false;
  }

  Node *new_node = dll_create_node(data);
  if (new_node == NULL) {
    return false;
  }

  new_node->next = node;
  new_node->prev = node->prev;

  if (node->prev != NULL) {
    node->prev->next = new_node;
  } else {
    // node 是头节点
    list->head = new_node;
  }

  node->prev = new_node;
  list->size++;
  return true;
}

// 删除操作
bool dll_delete_at_head(DoublyLinkedList *list) {
  if (list == NULL || list->head == NULL) {
    return false;
  }

  Node *node_to_delete = list->head;
  list->head = list->head->next;

  if (list->head != NULL) {
    list->head->prev = NULL;
  } else {
    // 链表变为空
    list->tail = NULL;
  }

  dll_destroy_node(node_to_delete);
  list->size--;
  return true;
}

bool dll_delete_at_tail(DoublyLinkedList *list) {
  if (list == NULL || list->tail == NULL) {
    return false;
  }

  Node *node_to_delete = list->tail;
  list->tail = list->tail->prev;

  if (list->tail != NULL) {
    list->tail->next = NULL;
  } else {
    // 链表变为空
    list->head = NULL;
  }

  dll_destroy_node(node_to_delete);
  list->size--;
  return true;
}

bool dll_delete_at_index(DoublyLinkedList *list, int index) {
  if (list == NULL || index < 0 || index >= list->size) {
    return false;
  }

  if (index == 0) {
    return dll_delete_at_head(list);
  }

  if (index == list->size - 1) {
    return dll_delete_at_tail(list);
  }

  Node *node_to_delete = dll_find_by_index(list, index);
  if (node_to_delete == NULL) {
    return false;
  }

  return dll_delete_node(list, node_to_delete);
}

bool dll_delete_by_value(DoublyLinkedList *list, int value) {
  if (list == NULL) {
    return false;
  }

  Node *node_to_delete = dll_find_by_value(list, value);
  if (node_to_delete == NULL) {
    return false;
  }

  return dll_delete_node(list, node_to_delete);
}

bool dll_delete_node(DoublyLinkedList *list, Node *node) {
  if (list == NULL || node == NULL) {
    return false;
  }

  // 更新前驱节点
  if (node->prev != NULL) {
    node->prev->next = node->next;
  } else {
    // node 是头节点
    list->head = node->next;
  }

  // 更新后继节点
  if (node->next != NULL) {
    node->next->prev = node->prev;
  } else {
    // node 是尾节点
    list->tail = node->prev;
  }

  dll_destroy_node(node);
  list->size--;
  return true;
}

// 查找操作
Node *dll_find_by_value(DoublyLinkedList *list, int value) {
  if (list == NULL) {
    return NULL;
  }

  Node *current = list->head;
  while (current != NULL) {
    if (current->data == value) {
      return current;
    }
    current = current->next;
  }
  return NULL;
}

Node *dll_find_by_index(DoublyLinkedList *list, int index) {
  if (list == NULL || index < 0 || index >= list->size) {
    return NULL;
  }

  // 优化：如果索引在后半部分，从尾部开始遍历
  if (index < list->size / 2) {
    // 从头部开始遍历
    Node *current = list->head;
    for (int i = 0; i < index; i++) {
      current = current->next;
    }
    return current;
  } else {
    // 从尾部开始遍历
    Node *current = list->tail;
    for (int i = list->size - 1; i > index; i--) {
      current = current->prev;
    }
    return current;
  }
}

int dll_get_value_at_index(DoublyLinkedList *list, int index) {
  Node *node = dll_find_by_index(list, index);
  if (node == NULL) {
    // 返回一个错误值，实际应用中可以使用错误码或其他方式
    return -1;
  }
  return node->data;
}

// 查询操作
int dll_get_size(DoublyLinkedList *list) {
  if (list == NULL) {
    return 0;
  }
  return list->size;
}

bool dll_is_empty(DoublyLinkedList *list) {
  if (list == NULL) {
    return true;
  }
  return list->size == 0;
}

// 遍历和打印
void dll_print_forward(DoublyLinkedList *list) {
  if (list == NULL) {
    printf("List is NULL\n");
    return;
  }

  if (list->head == NULL) {
    printf("List is empty\n");
    return;
  }

  printf("Forward: ");
  Node *current = list->head;
  while (current != NULL) {
    printf("%d", current->data);
    if (current->next != NULL) {
      printf(" <-> ");
    }
    current = current->next;
  }
  printf("\n");
}

void dll_print_backward(DoublyLinkedList *list) {
  if (list == NULL) {
    printf("List is NULL\n");
    return;
  }

  if (list->tail == NULL) {
    printf("List is empty\n");
    return;
  }

  printf("Backward: ");
  Node *current = list->tail;
  while (current != NULL) {
    printf("%d", current->data);
    if (current->prev != NULL) {
      printf(" <-> ");
    }
    current = current->prev;
  }
  printf("\n");
}

void dll_traverse_forward(DoublyLinkedList *list, void (*callback)(Node *)) {
  if (list == NULL || callback == NULL) {
    return;
  }

  Node *current = list->head;
  while (current != NULL) {
    callback(current);
    current = current->next;
  }
}

void dll_traverse_backward(DoublyLinkedList *list, void (*callback)(Node *)) {
  if (list == NULL || callback == NULL) {
    return;
  }

  Node *current = list->tail;
  while (current != NULL) {
    callback(current);
    current = current->prev;
  }
}

// 其他操作
void dll_clear(DoublyLinkedList *list) {
  if (list == NULL) {
    return;
  }

  Node *current = list->head;
  while (current != NULL) {
    Node *next = current->next;
    dll_destroy_node(current);
    current = next;
  }

  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
}

void dll_reverse(DoublyLinkedList *list) {
  if (list == NULL || list->head == NULL || list->head->next == NULL) {
    return;
  }

  Node *current = list->head;
  Node *temp = NULL;

  // 交换 head 和 tail
  Node *old_head = list->head;
  list->head = list->tail;
  list->tail = old_head;

  // 遍历链表，交换每个节点的 prev 和 next 指针
  while (current != NULL) {
    temp = current->prev;
    current->prev = current->next;
    current->next = temp;
    current = current->prev; // 注意：这里用 prev 因为已经交换了
  }
}
