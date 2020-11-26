// CAN'T RUN, TRY THIS?

// copy and paste this in terminal
// g++ main.cpp fun.cpp -o main_exec && ./main_exec

// if access denied, copy and paste this
// g++ main.cpp function.cpp -o main_exec && chmod +x ./main_exec && ./main_exec

#include "fun.h"

int main()
{
  CLEAR;
  int option = 0, flag = 1;
  while (flag)
  {
    printMainMenu();
    while (option < 1 || option > 8)
    {
      printf(">> ");
      scanf("%d", &option);
      getchar();
      CLEAR;
    }
    switch (option)
    {
    case 1:
    {
      char name[255], checkName = 0;
      int price = 0, checkPrice = 0;
      int quantity = 0, checkQuantity = 0;
      while (!checkName)
      {
        printf("Insert the name of the dish [Lowercase letters]: ");
        scanf("%[^\n]", name);
        getchar();
        checkName = checkCapital((char *)name);
      }
      while (!checkPrice)
      {
        printf("Insert the price of the dish [1000..50000]: ");
        scanf("%d", &price);
        getchar();
        checkPrice = price >= 1000 && price <= 50000 ? 1 : 0;
      }
      while (!checkQuantity)
      {
        printf("Insert the quantity of the dish [1..999]: ");
        scanf("%d", &quantity);
        getchar();
        checkQuantity = quantity >= 1 && quantity <= 999 ? 1 : 0;
      }
      addDish((char *)name, price, quantity);
      puts("The dish has been added!");
      close();
      break;
    }
    case 2:
    {
      char name[255];
      int checkNameDish = 0;
      if (checkDish())
      {
        printDish();
        while (!checkNameDish)
        {
          name[0] = '\0';
          printf("Insert dish's name to be deleted: ");
          scanf("%[^\n]", name);
          getchar();
          if (!strlen(name))
            continue;
          checkNameDish = checkDishExistence(name);
        }
        puts("The dish has been removed!");
      }
      else
      {
        puts("No dish available");
      }
      close();
      break;
    }
    case 3:
    {
      char name[255];
      int checkNameCustomer = 0;
      while (!checkNameCustomer)
      {
        printf("Insert the customer's name [Without space]: ");
        scanf("%[^\n]", name);
        getchar();
        checkNameCustomer = addCustomer(name);
      }
      puts("Customer has been added!");
      close();
      break;
    }
    case 4:
    {
      char name[255];
      printf("Insert the customer's name to be searched: ");
      scanf("%[^\n]", name);
      getchar();
      if (searchCustomer(name))
        printf("%s is present.\n", name);
      else
        printf("%s is not present.\n", name);
      close();
      break;
    }
    case 5:
    {
      puts("Customer's List");
      viewWarteg();
      close();
      break;
    }
    case 6:
    {
      if (!checkCustomerAda())
      {
        puts("There is no customer yet!");
        close();
        break;
      }
      if (!checkDishAda())
      {
        puts("There is no Dish yet!");
        close();
        break;
      }
      int checkOrder = 0, i = 1;
      char name[255], dish[255];
      while (!checkOrder)
      {
        printf("Insert The customer's name: ");
        scanf("%s", name);
        getchar();
        checkOrder = searchCustomer(name);
      }
      printf("Insert the amount of dish: ");
      scanf("%d", &checkOrder);
      getchar();
      while (i <= checkOrder)
      {
        if (!checkDishApaMasihAda())
        {
          puts("There is no dish left!");
          break;
        }
        printf("[%d] Insert the dish's name and quantity: ", i);
        scanf("%[^\n]", dish);
        getchar();
        if (order(dish, name))
          i++;
      }
      puts("Order success!");
      close();
      break;
    }
    case 7:
    {
      int index, checkIndex = 0;
      while (!checkIndex)
      {
        int c = checkCustomerAda();
        if (c == 0)
        {
          printf("There is no Customer yet!\n");
          break;
        }
        else if (c == -1)
          break;
        printf("Insert the customer's index: ");
        scanf("%d", &index);
        getchar();
        checkIndex = checkCustomerHasOrder(index);
      }
      close();
      break;
    }
    case 8:
    {
      puts("Please expand your terminal to full screen!");
      close();
      closing();
      return 0;
    }
    }
    option = 0;
  }
  return 0;
}