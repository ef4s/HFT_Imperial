#include "order_creator.h"
#include <iostream>

//bool order_creator_init();
//bool order_creator_init_specify_pos();
void update_orders_test();

using namespace std;

int main()
{
	//cout << "First test passed: " << order_creator_init() << endl;
	//cout << "Second test passed: " << order_creator_init_specify_pos() << endl;
	//cout << endl;

	update_orders_test();

	return 0;
}

/*bool order_creator_init()
{
	try
	{
		order_creator a;
		return true;
	}
	catch (std::exception & e)
	{
		return false;
	}
}*/
/*
bool order_creator_init_specify_pos()
{
	try
	{
		order_creator a(50, 0.01);
		return true;
	}
	catch (std::exception & e)
	{
		return false;
	}
}*/

void update_orders_test()
{
	order_creator a(50, 0.25, 50);

	cout << "Bid 2 \t Bid 1 \t Ask 1 \t Ask 2 " << endl;

	a.update_orders(99.75, 100.25, 100, 100, 0, 12/16.5);
	cout << a.get_bid_2() << '\t' << a.get_bid_1() << '\t'
		<< a.get_ask_1() << '\t' << a.get_ask_2() << endl;

	a.update_orders(99.75, 100.25, 100, 50, 0, 12 / 16.5);
	cout << a.get_bid_2() << '\t' << a.get_bid_1() << '\t'
		<< a.get_ask_1() << '\t' << a.get_ask_2() << endl;

	a.update_orders(99.75, 100.25, 100, 0, 0, 12 / 16.5);
	cout << a.get_bid_2() << '\t' << a.get_bid_1() << '\t'
		<< a.get_ask_1() << '\t' << a.get_ask_2() << endl;

	a.update_orders(99.75, 100.25, 100, 0, 10, 12 / 16.5);
	cout << a.get_bid_2() << '\t' << a.get_bid_1() << '\t'
		<< a.get_ask_1() << '\t' << a.get_ask_2() << endl;


	a.update_orders(99.75, 100.50, 100, 100, 0, 12 / 16.5);
	cout << a.get_bid_2() << '\t' << a.get_bid_1() << '\t'
		<< a.get_ask_1() << '\t' << a.get_ask_2() << endl;

	char p;
	cin >> p;
}