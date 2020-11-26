#ifndef MOD_FUNCTION_H
#define MOD_FUNCTION_H

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define CLEAR system("cls||clear")
#define ENTER printf("Press enter to continue...")

struct Dish;
struct Order;
struct Customer;

// main menu
char* os();
void tanggal();
void printMainMenu();
int checkCapital(char* str);
void close();

// add dish
Dish* nodeDish(char* name, int price, int quantity);
void addDish(char* name, int price, int quantity);

// remove dish
int checkDish();
int mostLongDish();
void printChar(int sum, char print);
void printDish();
int checkDishExistence(char* name);

// add customer
int addCustomer(char* name);
unsigned long djb2(char* str, int max);
int checkCustomer(char* name);

// search customer
int searchCustomer(char* name);

// view warteg
void viewWarteg();

// order
int checkDishAda();
int checkDishApaMasihAda();
int checkOrderDish(char* name, int quantity);
int order(char* dish, char* name);

// payment
int checkCustomerAda();
int checkCustomerHasOrder(int index);

// exit warteg
void closing();

#endif