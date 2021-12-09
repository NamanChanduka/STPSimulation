#include "bridge.h"
using namespace std;

Bridge::Bridge(int x)
{
	id = x;
	root = id;
	dist_to_root = 0;
	parent = x;
}

void Bridge::setType()
{
	for (int i = 0; i < lans.size(); i++)
	{
		lan_type[lans[i]] = "NP";
	}
}

void Bridge::print_lans()
{
	cout << "B" << id << ":";
	for (auto l : lans)
	{
		cout << " " << l;
	}
	cout << endl;
}

void Bridge::receive(Message m, int trace, int time)
{
	if (trace == 1)
	{
		cout << time << " r "
			 << "B" << id << " (B" << m.root << " | " << m.distance << " | B" << m.sender << ") || "
			 << "Message received on lan " << m.lan << endl;
	}
	if (m.root < root)
	{
		root = m.root;
		dist_to_root = m.distance + 1;
		lan_type[m.lan] = "RP";
		parent = m.sender;
		for (char lan : lans)
		{
			if (lan != m.lan)
			{
				lan_type[lan] = "NP";
			}
		}
	}
	else if ((m.root == root) && (dist_to_root > m.distance + 1))
	{
		root = m.root;
		dist_to_root = m.distance + 1;
		lan_type[m.lan] = "RP";
		parent = m.sender;
		for (char lan : lans)
		{
			if (lan != m.lan)
			{
				lan_type[lan] = "NP";
			}
		}
	}
	else if ((m.root == root) && (dist_to_root == m.distance + 1) && (m.sender < parent))
	{
		root = m.root;
		dist_to_root = m.distance + 1;
		lan_type[m.lan] = "RP";
		parent = m.sender;
		for (char lan : lans)
		{
			if (lan != m.lan)
			{
				lan_type[lan] = "NP";
			}
		}
	}
}

vector<Message> Bridge::send(int trace, int time)
{
	vector<Message> messages;
	for (char lan : lans)
	{
		if (lan_type[lan] == "NP")
		{
			if (trace == 1)
			{
				cout << time << " s "
					 << "B" << id << " (B" << root << " | " << dist_to_root << " | B" << id << ") || "
					 << "    Message sent on lan " << lan << endl;
			}
			Message m(root, dist_to_root);
			m.sender = id;
			m.lan = lan;
			messages.push_back(m);
		}
	}
	return messages;
}

Lan::Lan(char x)
{
	id = x;
	DB_id = -1;
}

Message::Message(int r, int d)
{
	root = r;
	distance = d;
}