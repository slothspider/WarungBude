#include "fun.h"

const int MAX_ELEMENT = 26;

struct Dish
{
  char name[255];
  int price, quantity;
  Dish *prev, *next;
} * headDish, *tailDish, *currDish, *newDish, *delDish;

struct Order
{
  char dish[255];
  int quantity, price;
  Order *prev, *next;
} * newOrder, *currOrder, *delOrder;

struct Customer
{
  char name[255];
  Order *headOrder, *tailOrder;
  Customer *prev, *next;
} * headCustomer[MAX_ELEMENT], *tailCustomer[MAX_ELEMENT], *currCustomer, *newCustomer, *delCustomer;

Dish *nodeDish(char *name, int price, int quantity)
{
  Dish *temp = (Dish *)malloc(sizeof(Dish));
  strcpy(temp->name, name);
  temp->price = price;
  temp->quantity = quantity;
  temp->next = temp->prev = NULL;
  return temp;
}

Customer *nodeCustomer(char *name)
{
  Customer *temp = (Customer *)malloc(sizeof(Customer));
  strcpy(temp->name, name);
  temp->headOrder = temp->tailOrder = NULL;
  temp->prev = temp->next = NULL;
  return temp;
}

Order *nodeOrder(char *dish, int quantity, int price)
{
  Order *temp = (Order *)malloc(sizeof(Order));
  strcpy(temp->dish, dish);
  temp->quantity = quantity;
  temp->price = price;
  temp->prev = temp->next = NULL;
  return temp;
}

char *os()
{
#ifdef _WIN32
  return (char *)"Windows 32-bit";
#elif _WIN64
  return (char *)"Windows 64-bit";
#elif __APPLE__ || __MACH__
  return (char *)"Mac OSX";
#elif __linux__
  return (char *)"Linux";
#elif __FreeBSD__
  return (char *)"FreeBSD";
#elif __unix || __unix__
  return (char *)"Unix";
#else
  return (char *)"Other";
#endif
}

void close()
{
  ENTER;
  getchar();
  CLEAR;
}

void tanggal()
{
  time_t rawtime;
  time(&rawtime);
  struct tm *info;
  info = localtime(&rawtime);
  printf("%s", asctime(info));
}

void printMainMenu()
{
  printf("%s\n", os());
  tanggal();
  printf("1. Add Dish\n");
  printf("2. Remove Dish\n");
  printf("3. Add Customer\n");
  printf("4. Search Customer\n");
  printf("5. View Warteg\n");
  printf("6. Order\n");
  printf("7. Payment\n");
  printf("8. Exit Warteg\n");
}

int checkCapital(char *str)
{
  for (int i = 0; str[i] != '\0'; i++)
  {
    if (str[i] < 'a' || str[i] > 'z')
    {
      if (str[i] != ' ')
        return 0;
    }
  }
  return 1;
}

int checkDish()
{
  if (headDish)
    return 1;
  return 0;
}

void addDish(char *name, int price, int quantity)
{
  Dish *temp = nodeDish(name, price, quantity);
  if (!headDish)
  {
    headDish = tailDish = temp;
  }
  else
  {
    tailDish->next = temp;
    temp->prev = tailDish;
    tailDish = temp;
  }
}

int mostLongDish()
{
  currDish = headDish;
  int most = 0, sum = 0;
  while (currDish)
  {
    sum = 0;
    for (int i = 0; currDish->name[i] != '\0'; i++)
    {
      sum++;
    }
    if (sum > most)
    {
      most = sum;
    }
    currDish = currDish->next;
  }
  return most;
}

void printChar(int sum, char print)
{
  for (int i = 0; i < sum; i++)
  {
    printf("%c", print);
  }
}

void printDish()
{
  int space = mostLongDish();
  space = (space == 0) ? 10 : space;
  currDish = headDish;

  printf("%*s\n", space + 15, "Bude's Menu");
  printChar(space + 26, '=');
  puts("");

  printf("No.   ");
  printChar((space - 4) / 2, ' ');
  printf("Name");
  printChar((space - 4) / 2, ' ');
  printf("   Quantity");
  printf("   Price\n");

  int counter = 1;
  while (currDish)
  {
    printf("%d.   ", counter++);
    printChar((space - strlen(currDish->name)) / 2, ' ');
    printf("%s", currDish->name);
    printChar((space - strlen(currDish->name)) / 2, ' ');
    printf("      %03d", currDish->quantity);
    printf("     Rp%d\n", currDish->price);
    currDish = currDish->next;
  }
  printChar(space + 26, '=');
  puts("");
}

void popDish(Dish **curr)
{
  if ((*curr) == headDish)
  {
    if ((*curr)->next != NULL)
    {
      (*curr) = ((*curr)->next);
      headDish->next = (*curr)->prev = NULL;
      free(headDish);
      headDish = (*curr);
    }
    else
    {
      headDish = tailDish = NULL;
      free(headDish);
    }
  }
  else if ((*curr) == tailDish)
  {
    if (tailDish->prev != NULL)
    {
      (*curr) == (*curr)->prev;
      tailDish->prev = ((*curr)->next) = NULL;
      free(headDish);
      tailDish = (*curr);
    }
    else
    {
      headDish = tailDish = NULL;
      free(headDish);
    }
  }
  else
  {
    (*curr)->prev->next = (*curr)->next;
    (*curr)->next->prev = (*curr)->prev;

    (*curr)->prev = (*curr)->next = NULL;
    free((*curr));
  }
}

int checkDishExistence(char *name)
{
  currDish = headDish;
  while (currDish)
  {
    if (!strcmp(currDish->name, name))
    {
      popDish(&currDish);
      return 1;
    }
    else
    {
      currDish = currDish->next;
    }
  }
  return 0;
}

unsigned long DJB2(char *str, int max)
{
  unsigned long hash = 5381;
  int c;
  while ((c = *str++))
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  return hash % max;
}

int checkCustomer(char *name)
{
  for (int i = 0; name[i] != '\0'; i++)
  {
    if (name[i] == ' ')
      return 0;
  }
  return 1;
}

void insertCustomerDJB2(char *name)
{
  int index = DJB2(name, MAX_ELEMENT);
  if (headCustomer[index])
  {
    Customer *temp = nodeCustomer(name);
    tailCustomer[index]->next = temp;
    tailCustomer[index] = temp;
  }
  else
  {
    headCustomer[index] = tailCustomer[index] = nodeCustomer(name);
  }
}

int addCustomer(char *name)
{
  if (checkCustomer(name))
    insertCustomerDJB2(name);
  else
    return 0;
  return 1;
}

int searchCustomer(char *name)
{
  int index = DJB2(name, MAX_ELEMENT);
  currCustomer = headCustomer[index];
  while (currCustomer)
  {
    if (!strcmp(name, currCustomer->name))
      return 1;
    else
      currCustomer = currCustomer->next;
  }
  return 0;
}

void viewWarteg()
{
  int counter = 0;
  for (int i = 0; i < MAX_ELEMENT; i++)
  {
    if (headCustomer[i])
    {
      currCustomer = headCustomer[i];
      while (currCustomer)
      {
        counter++;
        printf("%d. %s\n", i, currCustomer->name);
        currCustomer = currCustomer->next;
      }
    }
  }
  if (!counter)
    puts("There is no Customer!");
}

int checkOrderDish(char *name, int quantity)
{
  int namaValid = 0;
  currDish = headDish;
  while (currDish)
  {
    if (!strcmp(currDish->name, name))
    {
      namaValid = currDish->price;
      break;
    }
    else
      currDish = currDish->next;
  }
  if (!namaValid)
    return 0;

  if (quantity > 0 && quantity <= currDish->quantity)
  {
    currDish->quantity = currDish->quantity - quantity;
    return namaValid;
  }
  return 0;
}

int order(char *dish, char *name)
{
  int quantity = 0, pengali = 1;
  int length = strlen(dish);
  while (length > 2 && (dish[length - 1] >= '0' && dish[length - 1] <= '9'))
  {
    quantity += (dish[length - 1] - '0') * pengali;
    pengali *= 10;
    length--;
  }
  if (dish[length - 1] != 'x')
    return 0;
  dish[length - 2] = '\0';
  int price = checkOrderDish(dish, quantity);
  if (!price)
    return 0;
  // masukkan ke orderan
  int indexName = DJB2(name, MAX_ELEMENT);
  Order *temp = nodeOrder(dish, quantity, price);
  if (!headCustomer[indexName]->headOrder)
  {
    headCustomer[indexName]->headOrder = headCustomer[indexName]->tailOrder = temp;
  }
  else
  {
    headCustomer[indexName]->tailOrder->next = temp;
    temp->prev = headCustomer[indexName]->tailOrder;
    headCustomer[indexName]->tailOrder = temp;
  }
  return 1;
}

int checkDishAda()
{
  if (headDish)
    return 1;
  return 0;
}

int checkDishApaMasihAda()
{
  currDish = headDish;
  while (currDish)
  {
    if (currDish->quantity > 0)
      return 1;
    currDish = currDish->next;
  }
  return 0;
}

int checkCustomerAda()
{
  for (int i = 0; i < MAX_ELEMENT; i++)
  {
    if (headCustomer[i])
      return 1;
  }
  return 0;
}

int checkCustomerHasOrder(int index)
{
  if (headCustomer[index])
  {
    if (headCustomer[index]->headOrder)
    {
      currOrder = headCustomer[index]->headOrder;
      printf("\n%s\n", headCustomer[index]->name);
      int counter = 1, sumPayment = 0;
      while (currOrder)
      {
        printf("[%d] %s x%d\n", counter++, currOrder->dish, currOrder->quantity);
        sumPayment = sumPayment + (currOrder->price * currOrder->quantity);
        currOrder = currOrder->next;
      }
      printf("Total: Rp%d\n", sumPayment);
      // removePaymentOrder
      while (headCustomer[index]->headOrder)
      {
        if (headCustomer[index]->headOrder == headCustomer[index]->tailOrder)
        {
          headCustomer[index]->headOrder = headCustomer[index]->tailOrder = NULL;
          free(headCustomer[index]->headOrder);
        }
        else
        {
          Order *newHead = headCustomer[index]->headOrder->next;
          headCustomer[index]->headOrder->next = newHead->prev = NULL;
          free(headCustomer[index]->headOrder);
          headCustomer[index]->headOrder = newHead;
        }
      }

      // removePaymentCustomer
      if (headCustomer[index] && headCustomer[index] == tailCustomer[index])
      {
        headCustomer[index] = tailCustomer[index] = NULL;
        free(headCustomer[index]);
      }
      else
      {
        Customer *newHead = headCustomer[index]->next;
        headCustomer[index]->next = newHead->prev = NULL;
        free(headCustomer[index]);
        headCustomer[index] = newHead;
      }
      return counter;
    }
    else
    {
      printf("Customer hasn't buy dish!\n");
      return -1;
    }
  }
  return 0;
}

void closing()
{
  char c;
  FILE *algoText;
  algoText = fopen("splash-screen.txt", "r");
  c = fgetc(algoText);
  while (c != EOF)
  {
    printf("%c", c);
    c = fgetc(algoText);
  }
  fclose(algoText);
}