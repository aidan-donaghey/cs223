struct node
{
  struct node *prev;
  struct node *next;
  int data;
};



void push(struct node** head_ref, int newdata)
{
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
 
    new_node->data = newdata;
 
    new_node->next = (*head_ref);
    new_node->prev = NULL;
 
    if ((*head_ref) != NULL)
        (*head_ref)->prev = new_node;
 
    (*head_ref) = new_node;
}

void append(struct node** head_ref, int newdata)
{
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    struct node* last = *head_ref; 
    new_node->data = newdata;
    new_node->next = NULL;
 
    if (*head_ref == NULL) {
        new_node->prev = NULL;
        *head_ref = new_node;
        return;
    }
    while (last->next != NULL)
        last = last->next;
    last->next = new_node;
    new_node->prev = last;
 
    return;
}

void insertBefore(struct node** head_ref, struct node* next_node, int newdata)
{
    /*1. check if the given next_node is NULL */
    if (next_node == NULL) {
        return;
    }
 
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    new_node->data = newdata;
 
    new_node->prev = next_node->prev;
    next_node->prev = new_node;
    new_node->next = next_node;
    if (new_node->prev != NULL)
        new_node->prev->next = new_node;
    else
        (*head_ref) = new_node;
}