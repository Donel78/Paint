#include "main.h"


int stack_is_empty(struct Stack *stack)
{
  return stack == NULL;
}
void stack_push(struct Stack **s_stack, int data)
{
  struct Stack *s_new = malloc(sizeof *s_new);
  if (!stack_is_empty(s_new))
  {
    s_new->data = data;
    s_new->previous = *s_stack;
    *s_stack = s_new;
  }
}

int stack_pop(struct Stack **s_stack)
{
  int ret = -1;
  if (!stack_is_empty(*s_stack))
  {
    struct Stack *tmp = (*s_stack)->previous;
    ret = (*s_stack)->data;  
    free(*s_stack), *s_stack = NULL;
    *s_stack = tmp;
  }
  return ret;
}

void stack_clear(struct Stack **s_stack)
{
  while (!stack_is_empty(*s_stack))
  {
    stack_pop(s_stack);
  }
}

