#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void)
{
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  // TODO: initialize struct if needed
  p->root = NULL;
  p->nil->color = RBTREE_BLACK;

  return p;
}

void delete_rbtree(rbtree *t)
{
  // TODO: reclaim the tree nodes's memory
  free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key)
{
  // TODO: implement insert
  node_t *new = (node_t *)malloc(sizeof(node_t));
  node_t *y = t->nil;
  node_t *x = t->root;
  new->key = key;

  while (x != t->nil)
  { // x가 nil을 가리킬때까지 이진 탐색을 반복
    y = x;
    if (key < x->key)
      x = x->left;
    else
      x = x->right;
  }
  // while이 끝났을 때는 x는 nil을, y는 그 부모를 가리킴

  new->parent = y;
  if (y == t->nil) // 반복이 끝났는데 y가 nil을 가리키면 트리가 비었다는 뜻
    t->root = new;
  else if (key < y->key)
    y->left = new;
  else
    y->right = new;

  new->left = t->nil;
  new->right = t->nil;
  new->color = RBTREE_RED;

  rbtree_insert_fixup(t, new); // 새로운 삽입으로 규칙 위반일 수 있으니 확인

  return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key)
{
  // TODO: implement find
  return t->root;
}

node_t *rbtree_min(const rbtree *t)
{
  // TODO: implement find
  node_t *x = t->root;      // x가 인수로 들어온 RB tree t의 원소 'root'를 가리키게 함
  while (x->left != t->nil) // x의 (t의 root의) 왼쪽이 nil이 아닐때
  {
    x = x->left; // x가 왼쪽을 가리키게 함(?)
  }
  return x; // x를 반환
}

node_t *rbtree_max(const rbtree *t)
{
  // TODO: implement find
  node_t *x = t->root;
  while (x->right != t->nil)
  {
    x = x->right;
  }
  return x;
}

int rbtree_erase(rbtree *t, node_t *p)
{
  // TODO: implement erase

  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n)
{
  // TODO: implement to_array
  return 0;
}

node_t *left_rotate(rbtree *t, node_t *x)
{                       // x 기준, 왼쪽으로 회전
  node_t *y = x->right; // y 설정
  x->right = y->left;   // y의 왼쪽 서브트리를 x의 오른쪽으로 옮겨줌

  if (y->left != t->nil)
  {                      // 왼쪽 서브트리가 nil이 아니면
    y->left->parent = x; // 왼쪽 서브트리의 부모를 x로 설정
  }

  y->parent = x->parent;   // y의 부모를 x의 부모로 설정
  if (x->parent == t->nil) // 만약 x가 root였으면
    t->root = y;           // y를 root로 설정
  else if (x == x->parent->left)
    x->parent->left = y; // x가 부모의 왼쪽 자식이면 y를 연결해줌
  else
    x->parent->right = y; // x가 부모의 오른쪽 자식이면 y를 연결해줌

  y->left = x;   // y의 왼쪽 자식을 x로 설정
  x->parent = y; // x의 부모를 y로 설정

  return t->root;
}

node_t *right_rotate(rbtree *t, node_t *x)
{ // x 기준, 오른쪽으로 회전
  node_t *y = x->left;
  x->left = y->right;

  if (y->right != t->nil)
    y->right->parent = x;

  y->parent = x->parent;
  if (x->parent == t->nil)
    t->root = y;
  else if (x == x->parent->left)
    x->parent->left = y;
  else
    x->parent->right = y;

  y->right = x;
  x->parent = y;

  return t->root;
}