#ifndef ORDER_CREATOR_H
#define ORDER_CREATOR_H
class order_creator
{
public:
	order_creator(unsigned int max_position, float tick_size, float trade_intensity);
	~order_creator();

	void update_orders(float bid_1_px, float ask_1_px, unsigned int bid_1,
		unsigned int ask_1, int quantity, float current_time);
	unsigned int get_bid_1();
	unsigned int get_bid_2();
	unsigned int get_ask_1();
	unsigned int get_ask_2();

private:
	void get_bids(float, float, float, int, unsigned int&, unsigned int&);
	void get_asks(float, float, float, int, unsigned int&, unsigned int&);
	void update_sigma(float);
	float get_spread(float, int);
	float get_mid(float, float);
	float get_true_mid(float bid_1_px, float ask_1_px, unsigned int bid_1, unsigned int ask_1);
	float get_vol_imb(unsigned int bid_1, unsigned int ask_1);
};
#endif

