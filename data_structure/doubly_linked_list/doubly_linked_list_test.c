#include "doubly_linked_list.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

// 测试辅助函数
static int test_count = 0;
static int pass_count = 0;
static int fail_count = 0;

#define TEST_ASSERT(condition, msg)                                            \
  do {                                                                         \
    test_count++;                                                              \
    if (condition) {                                                           \
      printf("  ✓ PASS: %s\n", msg);                                           \
      pass_count++;                                                            \
    } else {                                                                   \
      printf("  ✗ FAIL: %s\n", msg);                                           \
      fail_count++;                                                            \
    }                                                                          \
  } while (0)

#define TEST_SECTION(title) printf("\n========== %s ==========\n", title)

// 回调函数用于遍历测试
static void print_node_data(Node *node) {
  if (node != NULL) {
    printf("  Node data: %d\n", node->data);
  }
}

// 测试 1: 创建和初始化
void test_create_and_init(void) {
  TEST_SECTION("测试 1: 创建和初始化");

  // 测试 dll_create
  DoublyLinkedList *list = dll_create();
  TEST_ASSERT(list != NULL, "dll_create 应该返回非空指针");
  TEST_ASSERT(list->head == NULL, "新链表头节点应为 NULL");
  TEST_ASSERT(list->tail == NULL, "新链表尾节点应为 NULL");
  TEST_ASSERT(list->size == 0, "新链表大小应为 0");
  TEST_ASSERT(dll_is_empty(list) == true, "新链表应为空");

  // 测试 dll_init
  DoublyLinkedList list2;
  dll_init(&list2);
  TEST_ASSERT(list2.head == NULL, "初始化后头节点应为 NULL");
  TEST_ASSERT(list2.tail == NULL, "初始化后尾节点应为 NULL");
  TEST_ASSERT(list2.size == 0, "初始化后大小应为 0");

  // 清理
  dll_destroy(list);
  printf("  测试完成\n");
}

// 测试 2: 头部插入
void test_insert_at_head(void) {
  TEST_SECTION("测试 2: 头部插入");

  DoublyLinkedList *list = dll_create();

  // 插入第一个元素
  TEST_ASSERT(dll_insert_at_head(list, 10) == true, "头部插入应该成功");
  TEST_ASSERT(list->size == 1, "插入后大小应为 1");
  TEST_ASSERT(list->head != NULL && list->head->data == 10,
              "头节点数据应为 10");
  TEST_ASSERT(list->tail != NULL && list->tail->data == 10,
              "尾节点数据应为 10");

  // 插入第二个元素
  TEST_ASSERT(dll_insert_at_head(list, 20) == true, "头部插入应该成功");
  TEST_ASSERT(list->size == 2, "插入后大小应为 2");
  TEST_ASSERT(list->head->data == 20, "头节点数据应为 20");
  TEST_ASSERT(list->tail->data == 10, "尾节点数据应为 10");

  // 插入第三个元素
  dll_insert_at_head(list, 30);
  TEST_ASSERT(list->size == 3, "插入后大小应为 3");
  TEST_ASSERT(list->head->data == 30, "头节点数据应为 30");
  TEST_ASSERT(list->tail->data == 10, "尾节点数据应为 10");

  printf("  链表内容（正向）: ");
  dll_print_forward(list);
  printf("  链表内容（反向）: ");
  dll_print_backward(list);

  dll_destroy(list);
  printf("  测试完成\n");
}

// 测试 3: 尾部插入
void test_insert_at_tail(void) {
  TEST_SECTION("测试 3: 尾部插入");

  DoublyLinkedList *list = dll_create();

  // 插入第一个元素
  TEST_ASSERT(dll_insert_at_tail(list, 10) == true, "尾部插入应该成功");
  TEST_ASSERT(list->size == 1, "插入后大小应为 1");
  TEST_ASSERT(list->head->data == 10, "头节点数据应为 10");
  TEST_ASSERT(list->tail->data == 10, "尾节点数据应为 10");

  // 插入第二个元素
  dll_insert_at_tail(list, 20);
  TEST_ASSERT(list->size == 2, "插入后大小应为 2");
  TEST_ASSERT(list->head->data == 10, "头节点数据应为 10");
  TEST_ASSERT(list->tail->data == 20, "尾节点数据应为 20");

  // 插入第三个元素
  dll_insert_at_tail(list, 30);
  TEST_ASSERT(list->size == 3, "插入后大小应为 3");
  TEST_ASSERT(list->head->data == 10, "头节点数据应为 10");
  TEST_ASSERT(list->tail->data == 30, "尾节点数据应为 30");

  printf("  链表内容: ");
  dll_print_forward(list);

  dll_destroy(list);
  printf("  测试完成\n");
}

// 测试 4: 按索引插入
void test_insert_at_index(void) {
  TEST_SECTION("测试 4: 按索引插入");

  DoublyLinkedList *list = dll_create();

  // 先插入一些元素
  dll_insert_at_tail(list, 10);
  dll_insert_at_tail(list, 30);
  dll_insert_at_tail(list, 40);

  printf("  插入前: ");
  dll_print_forward(list);

  // 在索引 1 处插入 20
  TEST_ASSERT(dll_insert_at_index(list, 1, 20) == true,
              "在索引 1 处插入应该成功");
  TEST_ASSERT(list->size == 4, "插入后大小应为 4");
  TEST_ASSERT(dll_get_value_at_index(list, 1) == 20, "索引 1 处的值应为 20");

  // 在索引 0 处插入（头部）
  TEST_ASSERT(dll_insert_at_index(list, 0, 5) == true,
              "在索引 0 处插入应该成功");
  TEST_ASSERT(list->head->data == 5, "头节点应为 5");

  // 在末尾插入
  TEST_ASSERT(dll_insert_at_index(list, list->size, 50) == true,
              "在末尾插入应该成功");
  TEST_ASSERT(list->tail->data == 50, "尾节点应为 50");

  printf("  插入后: ");
  dll_print_forward(list);

  // 测试无效索引
  TEST_ASSERT(dll_insert_at_index(list, -1, 0) == false, "负数索引应该失败");
  TEST_ASSERT(dll_insert_at_index(list, 100, 0) == false,
              "超出范围索引应该失败");

  dll_destroy(list);
  printf("  测试完成\n");
}

// 测试 5: 在节点前后插入
void test_insert_around_node(void) {
  TEST_SECTION("测试 5: 在节点前后插入");

  DoublyLinkedList *list = dll_create();

  // 创建基础链表: 10 <-> 30
  dll_insert_at_tail(list, 10);
  dll_insert_at_tail(list, 30);

  Node *middle_node = dll_find_by_value(list, 30);
  TEST_ASSERT(middle_node != NULL, "应该能找到值为 30 的节点");

  // 在节点前插入
  TEST_ASSERT(dll_insert_before_node(list, middle_node, 20) == true,
              "在节点前插入应该成功");
  TEST_ASSERT(list->size == 3, "插入后大小应为 3");

  // 在节点后插入
  Node *node_20 = dll_find_by_value(list, 20);
  TEST_ASSERT(dll_insert_after_node(list, node_20, 25) == true,
              "在节点后插入应该成功");
  TEST_ASSERT(list->size == 4, "插入后大小应为 4");

  printf("  链表内容: ");
  dll_print_forward(list);

  dll_destroy(list);
  printf("  测试完成\n");
}

// 测试 6: 头部删除
void test_delete_at_head(void) {
  TEST_SECTION("测试 6: 头部删除");

  DoublyLinkedList *list = dll_create();

  // 空链表删除应该失败
  TEST_ASSERT(dll_delete_at_head(list) == false, "空链表删除应该失败");

  // 插入元素
  dll_insert_at_tail(list, 10);
  dll_insert_at_tail(list, 20);
  dll_insert_at_tail(list, 30);

  printf("  删除前: ");
  dll_print_forward(list);

  // 删除头部
  TEST_ASSERT(dll_delete_at_head(list) == true, "头部删除应该成功");
  TEST_ASSERT(list->size == 2, "删除后大小应为 2");
  TEST_ASSERT(list->head->data == 20, "头节点应为 20");

  // 再删除
  dll_delete_at_head(list);
  TEST_ASSERT(list->head->data == 30, "头节点应为 30");

  // 删除最后一个元素
  dll_delete_at_head(list);
  TEST_ASSERT(list->head == NULL, "删除后链表应为空");
  TEST_ASSERT(list->tail == NULL, "删除后尾节点应为 NULL");
  TEST_ASSERT(dll_is_empty(list) == true, "链表应为空");

  dll_destroy(list);
  printf("  测试完成\n");
}

// 测试 7: 尾部删除
void test_delete_at_tail(void) {
  TEST_SECTION("测试 7: 尾部删除");

  DoublyLinkedList *list = dll_create();

  // 空链表删除应该失败
  TEST_ASSERT(dll_delete_at_tail(list) == false, "空链表删除应该失败");

  // 插入元素
  dll_insert_at_tail(list, 10);
  dll_insert_at_tail(list, 20);
  dll_insert_at_tail(list, 30);

  printf("  删除前: ");
  dll_print_forward(list);

  // 删除尾部
  TEST_ASSERT(dll_delete_at_tail(list) == true, "尾部删除应该成功");
  TEST_ASSERT(list->size == 2, "删除后大小应为 2");
  TEST_ASSERT(list->tail->data == 20, "尾节点应为 20");

  // 再删除
  dll_delete_at_tail(list);
  TEST_ASSERT(list->tail->data == 10, "尾节点应为 10");

  // 删除最后一个元素
  dll_delete_at_tail(list);
  TEST_ASSERT(list->tail == NULL, "删除后尾节点应为 NULL");
  TEST_ASSERT(list->head == NULL, "删除后头节点应为 NULL");

  dll_destroy(list);
  printf("  测试完成\n");
}

// 测试 8: 按索引删除
void test_delete_at_index(void) {
  TEST_SECTION("测试 8: 按索引删除");

  DoublyLinkedList *list = dll_create();

  dll_insert_at_tail(list, 10);
  dll_insert_at_tail(list, 20);
  dll_insert_at_tail(list, 30);
  dll_insert_at_tail(list, 40);

  printf("  删除前: ");
  dll_print_forward(list);

  // 删除中间元素
  TEST_ASSERT(dll_delete_at_index(list, 1) == true, "删除索引 1 应该成功");
  TEST_ASSERT(list->size == 3, "删除后大小应为 3");
  TEST_ASSERT(dll_get_value_at_index(list, 1) == 30, "索引 1 处的值应为 30");

  // 删除头部
  TEST_ASSERT(dll_delete_at_index(list, 0) == true, "删除索引 0 应该成功");
  TEST_ASSERT(list->head->data == 30, "头节点应为 30");

  // 删除尾部
  TEST_ASSERT(dll_delete_at_index(list, list->size - 1) == true,
              "删除尾部应该成功");
  TEST_ASSERT(list->tail->data == 30, "尾节点应为 30");

  printf("  删除后: ");
  dll_print_forward(list);

  // 测试无效索引
  TEST_ASSERT(dll_delete_at_index(list, -1) == false, "负数索引应该失败");
  TEST_ASSERT(dll_delete_at_index(list, 100) == false, "超出范围索引应该失败");

  dll_destroy(list);
  printf("  测试完成\n");
}

// 测试 9: 按值删除
void test_delete_by_value(void) {
  TEST_SECTION("测试 9: 按值删除");

  DoublyLinkedList *list = dll_create();

  dll_insert_at_tail(list, 10);
  dll_insert_at_tail(list, 20);
  dll_insert_at_tail(list, 30);
  dll_insert_at_tail(list, 20); // 重复值

  printf("  删除前: ");
  dll_print_forward(list);

  // 删除第一个匹配的值
  TEST_ASSERT(dll_delete_by_value(list, 20) == true, "按值删除应该成功");
  TEST_ASSERT(list->size == 3, "删除后大小应为 3");

  // 删除不存在的值
  TEST_ASSERT(dll_delete_by_value(list, 99) == false, "删除不存在的值应该失败");

  // 删除存在的值
  TEST_ASSERT(dll_delete_by_value(list, 10) == true, "按值删除应该成功");

  printf("  删除后: ");
  dll_print_forward(list);

  dll_destroy(list);
  printf("  测试完成\n");
}

// 测试 10: 查找操作
void test_find_operations(void) {
  TEST_SECTION("测试 10: 查找操作");

  DoublyLinkedList *list = dll_create();

  dll_insert_at_tail(list, 10);
  dll_insert_at_tail(list, 20);
  dll_insert_at_tail(list, 30);
  dll_insert_at_tail(list, 40);

  // 按值查找
  Node *node = dll_find_by_value(list, 20);
  TEST_ASSERT(node != NULL, "应该能找到值为 20 的节点");
  TEST_ASSERT(node->data == 20, "找到的节点数据应为 20");

  node = dll_find_by_value(list, 99);
  TEST_ASSERT(node == NULL, "不存在的值应该返回 NULL");

  // 按索引查找
  node = dll_find_by_index(list, 0);
  TEST_ASSERT(node != NULL && node->data == 10, "索引 0 应为 10");

  node = dll_find_by_index(list, 2);
  TEST_ASSERT(node != NULL && node->data == 30, "索引 2 应为 30");

  node = dll_find_by_index(list, 3);
  TEST_ASSERT(node != NULL && node->data == 40, "索引 3 应为 40");

  // 测试优化：从尾部开始查找（索引在后半部分）
  dll_insert_at_tail(list, 50);
  dll_insert_at_tail(list, 60);
  node = dll_find_by_index(list, 5);
  TEST_ASSERT(node != NULL && node->data == 60, "索引 5 应为 60");

  // 获取索引处的值
  TEST_ASSERT(dll_get_value_at_index(list, 1) == 20, "索引 1 的值应为 20");
  TEST_ASSERT(dll_get_value_at_index(list, -1) == -1, "无效索引应返回 -1");

  // 测试边界情况
  TEST_ASSERT(dll_find_by_index(list, -1) == NULL, "负数索引应该返回 NULL");
  TEST_ASSERT(dll_find_by_index(list, 100) == NULL,
              "超出范围索引应该返回 NULL");

  dll_destroy(list);
  printf("  测试完成\n");
}

// 测试 11: 查询操作
void test_query_operations(void) {
  TEST_SECTION("测试 11: 查询操作");

  DoublyLinkedList *list = dll_create();

  // 空链表
  TEST_ASSERT(dll_get_size(list) == 0, "空链表大小应为 0");
  TEST_ASSERT(dll_is_empty(list) == true, "空链表应为空");

  // 添加元素
  dll_insert_at_tail(list, 10);
  TEST_ASSERT(dll_get_size(list) == 1, "链表大小应为 1");
  TEST_ASSERT(dll_is_empty(list) == false, "链表不应为空");

  dll_insert_at_tail(list, 20);
  dll_insert_at_tail(list, 30);
  TEST_ASSERT(dll_get_size(list) == 3, "链表大小应为 3");

  dll_destroy(list);
  printf("  测试完成\n");
}

// 测试 12: 遍历操作
void test_traverse_operations(void) {
  TEST_SECTION("测试 12: 遍历操作");

  DoublyLinkedList *list = dll_create();

  dll_insert_at_tail(list, 10);
  dll_insert_at_tail(list, 20);
  dll_insert_at_tail(list, 30);

  printf("  正向遍历:\n");
  dll_traverse_forward(list, print_node_data);

  printf("  反向遍历:\n");
  dll_traverse_backward(list, print_node_data);

  printf("  正向打印: ");
  dll_print_forward(list);

  printf("  反向打印: ");
  dll_print_backward(list);

  dll_destroy(list);
  printf("  测试完成\n");
}

// 测试 13: 清空链表
void test_clear(void) {
  TEST_SECTION("测试 13: 清空链表");

  DoublyLinkedList *list = dll_create();

  dll_insert_at_tail(list, 10);
  dll_insert_at_tail(list, 20);
  dll_insert_at_tail(list, 30);

  TEST_ASSERT(list->size == 3, "清空前大小应为 3");

  dll_clear(list);

  TEST_ASSERT(list->size == 0, "清空后大小应为 0");
  TEST_ASSERT(list->head == NULL, "清空后头节点应为 NULL");
  TEST_ASSERT(list->tail == NULL, "清空后尾节点应为 NULL");
  TEST_ASSERT(dll_is_empty(list) == true, "清空后应为空");

  // 清空后可以继续使用
  dll_insert_at_tail(list, 100);
  TEST_ASSERT(list->size == 1, "清空后可以继续使用");

  dll_destroy(list);
  printf("  测试完成\n");
}

// 测试 14: 反转链表
void test_reverse(void) {
  TEST_SECTION("测试 14: 反转链表");

  DoublyLinkedList *list = dll_create();

  dll_insert_at_tail(list, 10);
  dll_insert_at_tail(list, 20);
  dll_insert_at_tail(list, 30);
  dll_insert_at_tail(list, 40);

  printf("  反转前: ");
  dll_print_forward(list);

  dll_reverse(list);

  printf("  反转后: ");
  dll_print_forward(list);

  TEST_ASSERT(list->head->data == 40, "反转后头节点应为 40");
  TEST_ASSERT(list->tail->data == 10, "反转后尾节点应为 10");
  TEST_ASSERT(dll_get_value_at_index(list, 1) == 30, "反转后索引 1 应为 30");
  TEST_ASSERT(dll_get_value_at_index(list, 2) == 20, "反转后索引 2 应为 20");

  // 测试空链表和单节点链表
  dll_clear(list);
  dll_reverse(list); // 空链表反转
  TEST_ASSERT(list->size == 0, "空链表反转后大小仍为 0");

  dll_insert_at_tail(list, 100);
  dll_reverse(list); // 单节点链表反转
  TEST_ASSERT(list->head->data == 100, "单节点反转后数据不变");

  dll_destroy(list);
  printf("  测试完成\n");
}

// 测试 15: 综合测试
void test_comprehensive(void) {
  TEST_SECTION("测试 15: 综合测试");

  DoublyLinkedList *list = dll_create();

  // 混合插入操作
  dll_insert_at_head(list, 1);
  dll_insert_at_tail(list, 5);
  dll_insert_at_index(list, 1, 3);
  dll_insert_at_tail(list, 7);

  printf("  综合插入后: ");
  dll_print_forward(list);
  TEST_ASSERT(list->size == 4, "综合插入后大小应为 4");

  // 混合删除操作
  dll_delete_at_head(list);
  dll_delete_at_tail(list);
  dll_delete_by_value(list, 3);

  printf("  综合删除后: ");
  dll_print_forward(list);
  TEST_ASSERT(list->size == 1, "综合删除后大小应为 1");

  // 再次操作
  dll_insert_at_head(list, 10);
  dll_insert_at_tail(list, 20);
  dll_insert_at_tail(list, 30);

  // 反转
  dll_reverse(list);
  TEST_ASSERT(list->head->data == 30, "反转后头节点应为 30");

  // 清空并重新填充
  dll_clear(list);
  for (int i = 1; i <= 5; i++) {
    dll_insert_at_tail(list, i * 10);
  }
  TEST_ASSERT(list->size == 5, "重新填充后大小应为 5");

  printf("  最终链表: ");
  dll_print_forward(list);

  dll_destroy(list);
  printf("  测试完成\n");
}

// 主测试函数
int main(void) {
  printf("\n");
  printf("========================================\n");
  printf("   双向链表功能测试\n");
  printf("========================================\n");

  // 运行所有测试
  test_create_and_init();
  test_insert_at_head();
  test_insert_at_tail();
  test_insert_at_index();
  test_insert_around_node();
  test_delete_at_head();
  test_delete_at_tail();
  test_delete_at_index();
  test_delete_by_value();
  test_find_operations();
  test_query_operations();
  test_traverse_operations();
  test_clear();
  test_reverse();
  test_comprehensive();

  // 输出测试结果摘要
  printf("\n");
  printf("========================================\n");
  printf("   测试结果摘要\n");
  printf("========================================\n");
  printf("  总测试数: %d\n", test_count);
  printf("  通过: %d\n", pass_count);
  printf("  失败: %d\n", fail_count);
  printf("========================================\n");

  if (fail_count == 0) {
    printf("  所有测试通过！✓\n");
    return 0;
  } else {
    printf("  有测试失败！✗\n");
    return 1;
  }
}
