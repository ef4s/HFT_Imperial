#include "order_creator.h"
#include <cmath>

const float EXP_DECAY_FACTOR = 0.99;
const float GAMMA = 0.1;
const float MARKET_SHUT = 1;

float _trade_intensity;
float _sigma;
unsigned int _max_pos;
float _tick_size;

unsigned int t_bid_1, t_bid_2, t_ask_1, t_ask_2;

order_creator::order_creator(unsigned int maximum_position, float tick_size, float trade_intensity)
{
	_sigma = 0.02;
	_trade_intensity = trade_intensity;
	_tick_size = tick_size;
	_max_pos = maximum_position;
	t_bid_1 = 0;
	t_bid_2 = 0;
	t_ask_1 = 0;
	t_ask_2 = 0;
}

order_creator::~order_creator()
{
}

unsigned int order_creator::get_bid_1()
{
	return t_bid_1;
}

unsigned int order_creator::get_bid_2()
{
	return t_bid_2;
}

unsigned int order_creator::get_ask_1()
{
	return t_ask_1;
}

unsigned int order_creator::get_ask_2()
{
	return t_ask_2;
}


void order_creator::update_sigma(float px)
{
	float new_sigma = EXP_DECAY_FACTOR * pow(_sigma, 2);
	new_sigma += (1 - EXP_DECAY_FACTOR) * pow(px, 2);

	_sigma = sqrt(new_sigma);
}

void order_creator::update_orders(float bid_1_px, float ask_1_px, unsigned int bid_1, unsigned int ask_1, int quantity, float current_time)
{
	float spread = get_spread(current_time, quantity);
	float true_mid = get_true_mid(bid_1_px, ask_1_px, bid_1, ask_1);
	
	get_asks(true_mid, spread, ask_1_px, quantity, t_ask_1, t_ask_2);
	get_bids(true_mid, spread, bid_1_px, quantity, t_bid_1, t_bid_2);
}

void order_creator::get_bids(float true_mid, float spread, float bid_1_px,  int quantity, unsigned int& t_bid_1, unsigned int& t_bid_2)
{
	//bids are low, mean we buy
	//if we have positive inventory our bid quantity should be low
	//TODO: be defensive in the situation where the inventory is greater than the maximum allowed. I.e. cross the spread!
	float b1_pct = ((true_mid + spread) - bid_1_px) / _tick_size;
	t_bid_1 = fmaxf(fminf(round((_max_pos - quantity) * b1_pct), _max_pos - quantity), 0);
	t_bid_2 = (_max_pos - quantity) - t_bid_1;
}

void order_creator::get_asks(float true_mid, float spread, float ask_1_px, int quantity, unsigned int& t_ask_1, unsigned int& t_ask_2)
{
	//asks are high
	//TODO: be defensive in the situation where the inventory is greater than the maximum allowed. I.e. cross the spread!
	float a1_pct = (ask_1_px - (true_mid - spread)) / _tick_size;
	t_ask_1 = fmaxf(fminf(round((_max_pos + quantity) * a1_pct), _max_pos + quantity),0);
	t_ask_2 = (_max_pos + quantity) - t_ask_1;
}

float order_creator::get_spread(float t, int quantity)
{
	float a = quantity * GAMMA * pow(_sigma, 2) * (MARKET_SHUT - t);
	float b = (2 / GAMMA) * log(1 + (GAMMA / _trade_intensity));
	return a + b;
}

float order_creator::get_mid(float bid_1_px, float ask_1_px)
{
	return bid_1_px + ((bid_1_px - ask_1_px) / 2);
}

float order_creator::get_true_mid(float bid_1_px, float ask_1_px, unsigned int bid_1, unsigned int ask_1)
{
	float imb = get_vol_imb(bid_1, ask_1);
	float bid_cont = (1 - imb) * bid_1_px;
	float ask_cont = (1 + imb) * ask_1_px;
	return (bid_cont + ask_cont) / 2;
}

float order_creator::get_vol_imb(unsigned int bid_1, unsigned int ask_1)
{
	if ((bid_1 == 0) && (ask_1 == 0))
	{
		return 0;
	}
	else
	{
		return static_cast<float>(bid_1 - ask_1) / (bid_1 + ask_1);
	}
}
