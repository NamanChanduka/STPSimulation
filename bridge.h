#ifndef BRIDGE_HEADER
#define BRIDGE_HEADER

#include <bits/stdc++.h>
using namespace std;

class Message
{
public:
	int root;
	int distance;
	int sender;
	char lan;
	Message(int r, int d);
};

class Bridge
{
public:
	int id;
	int root;
	int dist_to_root;
	int parent;
	vector<char> lans;
	map<char, string> lan_type;
	Bridge(int x);
	void setType();
	void print_lans();
	void receive(Message m, int trace, int time);
	vector<Message> send(int trace, int time);
};

class Lan
{
public:
	char id;
	int DB_id;
	vector<int> active_bridges;
	Lan(char x);
};

#endif