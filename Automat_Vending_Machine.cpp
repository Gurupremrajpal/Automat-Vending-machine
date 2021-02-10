/*
* Title: project-1.cpp
 * Abstract: An automat, kind of a vending machine on steroids.
 * Author: Guruprem Singh Rajpal
 * Email: grajpal@csumb.edu / gurupremrajpal@gmail.com
 * Estimate: 3 hours
 * Date: 03/03/2020
*/


#include <iostream>
#include <string>
using namespace std;

const int ORDER_MAX=5;
const int Automat_MAX=10;

class Drink
{
  public:
  Drink();
  Drink(string name, int ounces, double price);
  string getName();
  int getOunces();
  double getPrice();
  void setName(string name);
  void setOunces(int ounces);
  void setPrice(double price);
  void display();
  
  private:
  string myName;
  int myOunces;
  double myPrice;
};

class Food
{
 public: 
 Food();
 Food(string name, int calories, double price);
 string getName();
 int getCalories();
 double getPrice();
 void setName(string name);
 void setCalories(int calories);
 void setPrice(double price);
 void display();

 private:
 string myName;
 int myCalories;
 double myPrice;
};



class Automat
{
  public:
  Automat();
  bool emptyFood();
  bool emptyDrink();
  void enqueue(Food f);
  void enqueue(Drink d);
  void dequeueFood();
  void dequeueDrink();
  Food frontFood();
  Drink frontDrink();
  int foodCount();
  int drinkCount();
  int getTotalCalories();
  int getTotalOunces();
  double getTotalPrice();
  void display();

  private:
  int myFoodFront;
  int myFoodBack;
  Food myFood[Automat_MAX];
  Drink myDrink[Automat_MAX];
  int myDrinkFront;
  int myDrinkBack;
};

class Order
{
 public: 
 Order();
 bool emptyFood();
 bool emptyDrink();
 void push(Food f);
 void push(Drink d);
 void popFood();
 void popDrink();
 Food topFood();
 Drink topDrink();
 int foodCount();
 int drinkCount();
 double getTotalPrice();
 void display();
 void cancel(Automat& a);
 void purchase();
 static int getTotalOrders();

 private:
 int myFoodTop;
 int myDrinkTop;
 Food myFood[ORDER_MAX];
 Drink myDrink[ORDER_MAX];
 static int myTotalOrders;
};

int Order::myTotalOrders = 0;

Drink::Drink():myName(""),myOunces(0),myPrice(0)
{   
}

Drink::Drink(string name, int ounces, double price):myName(name), myOunces(ounces),myPrice(price)
{
}
  
  
string Drink::getName ()
{
  return myName;
}

double Drink::getPrice()
{
  return myPrice;
}

int Drink::getOunces()
{
  return myOunces;
}

void Drink::setOunces(int ounces)
{
  myOunces=ounces;
}

void Drink::setPrice(double price)
{
  myPrice=price;
}

void Drink::display()
{
  cout<< myName<<": "<< myOunces<< "ounces, $"<< myPrice<< '\n';
}

void Drink::setName(string name)
{
  myName=name;
}



Food::Food():myName(""), myPrice(0),myCalories(0)
{ 
}

Food::Food(string name, int calories, double price):myName(name),myCalories(calories),myPrice(price)
{
}

string Food::getName()
{ 
  return myName; 
}

int Food::getCalories()
{
  return myCalories;
}
double Food::getPrice()
{
  return myPrice;
}
void Food::setName(string name)
{
  myName=name;
}
void Food::setCalories(int calories)
{
  myCalories=calories;
}

void Food::setPrice(double price)
{
  myPrice=price;
}

void Food::display()
{
  cout<< myName<<  ": "<< myCalories<< " calories, $"<<myPrice << '\n';
}



Order::Order():myFoodTop(-1),myDrinkTop(-1)
{
  myTotalOrders++;
}

bool Order::emptyFood()
{
  return myFoodTop ==-1;
}

bool Order:: emptyDrink()
{
  return myDrinkTop ==-1;
}
void Order::push(Food f)
{
  if(myFoodTop < ORDER_MAX-1)
  {
    myFoodTop = myFoodTop+1;
    myFood[myFoodTop]=f;
  }
  else
  {
    cerr<< "Food stack is full"<<'\n';
    return;
  }
}

void Order::push(Drink d)
{
  if (myDrinkTop<ORDER_MAX-1)
  {
    myDrinkTop= myDrinkTop+1;
    myDrink[myFoodTop]=d;
  }
  else
    cerr<<"Drink Stack is full"<<'\n';
  return;
}

void Order::popFood()
{
  if (!emptyFood())
  {
    myFoodTop--;
  }
  else 
  {
    cerr<< "Food Stack is empty"<<'\n';
    return;
  }
}
void Order::popDrink()
{
  if(!emptyDrink())
  {
    myDrinkTop--;
  }
  else 
    cerr<< "Drink Stack is empty"<<"\n";
  return;
}

Food Order::topFood()
{
  return myFood[myFoodTop];
}
Drink Order:: topDrink()
{
  return myDrink[myDrinkTop];
}
int Order::foodCount()
{
  return myFoodTop+1;
}
int Order::drinkCount()
{
  return myDrinkTop+1;
}

void Order::cancel(Automat& a)
{
  for(int i=myFoodTop; i>=0; i--)
  {
    popFood();
    a.enqueue(myFood[i]);
  }
  for(int r=myDrinkTop; r>=0; r--)
  {
    popDrink();
    a.enqueue(myDrink[r]);
  }
}

double Order::getTotalPrice()
{
  double totalPrice = 0;
	for(int i=myFoodTop; i>=0; i--)
  {
	totalPrice = totalPrice + myFood[i].getPrice();
  }

	for(int i=myDrinkTop; i>=0; i--)
  {
	totalPrice = totalPrice + myDrink[i].getPrice();
  }
	
	return totalPrice;
}

void Order::purchase()
{
  myFoodTop=-1;
  myDrinkTop=-1;
}

int Order::getTotalOrders()
{
  return myTotalOrders;
}

void Order::display()
{
  cout << "Order: "<<'\n';
  cout<< "Food ("<< foodCount() << " items): "<<'\n';
  
  for(int a=0; a<=myFoodTop; a++)
	{
		cout << "     ";
		myFood[a].display();
	}
	cout << "  Drink (" << drinkCount() << " items):" << '\n';

	for(int i=0; i<=myDrinkTop; i++)
	{
		cout << "     ";
		myDrink[i].display();
	}
  cout << "  Order Total: $" << getTotalPrice() << '\n'<< '\n';
}




Automat::Automat()
{
  myFoodFront=0;
  myFoodBack=0;
  myDrinkFront=0;
  myDrinkBack=0;
}

bool Automat::emptyFood()
{
  return(myFoodFront==myFoodBack);
}

bool Automat::emptyDrink()
{
  return (myDrinkFront==myDrinkBack);
}

void Automat::enqueue(Drink d)
{
  int newBack = (myDrinkBack+1)%Automat_MAX;
  if(newBack != myDrinkFront)
  {
    myDrink[myDrinkBack] = d;
    myDrinkBack = newBack;
  }
  else
  {
    cerr << "The Drink Queue is full " << '\n';
    return;
  }
}

void Automat::enqueue(Food f)
{
  int newBack = (myFoodBack+1)%Automat_MAX;
  if(newBack != myFoodFront)
  {
    myFood[myFoodBack] = f;
    myFoodBack = newBack;
  }
  else
  {
    cerr << "The Food Queue is full " << '\n';
    return;
  }
}


void Automat::dequeueDrink()
{
  if(!emptyDrink())
  {
    myDrinkFront = (myDrinkFront+1)%Automat_MAX;
  }
  else
  {
    cout << "The Drink Queue is empty " << '\n';
    return;
  }
}

void Automat::dequeueFood()
{
  if(!emptyFood())
  {
    myFoodFront = (myFoodFront+1)%Automat_MAX;
  }
  else
  {
    cerr << "The Food Queue is empty " << '\n';
   return;
  }
}

Drink Automat::frontDrink()
{
  return myDrink[myDrinkFront];
}

Food Automat::frontFood()
{
  return myFood[myFoodFront];
}

int Automat::foodCount()
{
  int num = 0;

	for(int i=myFoodFront; i!= myFoodBack; i = (i+1)%Automat_MAX)
	num++;

	return num;
}


int Automat::drinkCount()
{
  int count = 0;

	for(int i=myDrinkFront; i!= myDrinkBack; i = (i+1)%Automat_MAX )
	count++;

	return count;
}

int Automat::getTotalCalories()
{
  int totalCalories = 0;
	
	for(int i=myFoodFront; i!=myFoodBack; i = (i+1)%Automat_MAX)
	totalCalories += myFood[i].getCalories();

	return totalCalories;
}

int Automat::getTotalOunces()
{
  int totalOunces = 0;
	
	for(int i=myDrinkFront; i!=myDrinkBack; i = (i+1)%Automat_MAX)
	totalOunces += myDrink[i].getOunces();

  return totalOunces;
}


double Automat::getTotalPrice()
{
  double totalPrice = 0;
	
	for(int i=myFoodFront; i!=myFoodBack; i = (i+1)%Automat_MAX)
	totalPrice += myFood[i].getPrice();
	for(int i=myDrinkFront; i!=myDrinkBack; i = (i+1)%Automat_MAX)
	totalPrice += myDrink[i].getPrice();

	return totalPrice;
}

void Automat::display()
{
	cout << "Automat: " << '\n';
	cout << "  Food: " << '\n';
	for(int r=myFoodFront; r!=myFoodBack; r = (r+1)%Automat_MAX)
	{
		cout << "     ";
    myFood[r].display();
	}
  
  cout << "     " <<foodCount()<< " food items -Total Calories: " <<getTotalCalories()<< '\n';

	cout << "  Drink: " << '\n';
	for(int i=myDrinkFront; i!=myDrinkBack; i = (i+1)%Automat_MAX)
	{
		cout << "     ";
		myDrink[i].display();
	}
  cout<< "     " <<drinkCount()<< " drinks -Total Ounces: " <<getTotalOunces()<< '\n'<< '\n';
	
  return;
}



int main()
{
  Automat a;
  a.enqueue(Food("Let's Potato Chips", 300, 1.50));
  a.enqueue(Food("Mini Donuts", 500, 1));
  a.enqueue(Drink("Coffee", 6, 5.50));
  a.enqueue(Drink("Nacho Drink", 22, 2.50));
  cout << "Starting Automat\n";
  a.display();

  Order o;
  o.push(a.frontFood());
  a.dequeueFood();
  o.push(a.frontDrink());
  a.dequeueDrink();
  cout << "Ordered one food, one drink\n";
  o.display();
  a.display();
  cout << "Canceled order\n";
  o.cancel(a);
  o.display();
  a.display();
  cout << "Ordered one food, one drink, purchased\n";
  o.push(a.frontFood());
  a.dequeueFood();
  o.push(a.frontDrink());
  a.dequeueDrink();
  o.purchase();
  o.display();
  a.display();

  return 0;
}
