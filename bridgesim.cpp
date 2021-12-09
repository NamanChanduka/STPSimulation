#include "bridgesim.h"
using namespace std;

BridgeSimulator::BridgeSimulator(vector<Bridge> tb, vector<Lan> tl, int t)
{
    totalBridges = tb;
    totalLans = tl;
    trace = t;
}

bool compareBridge(Bridge b1, Bridge b2)
{
    return (b1.id < b2.id);
}

bool compareMessage(Message m1, Message m2)
{
    return (m1.sender > m2.sender);
}

bool compareLan(Lan l1, Lan l2)
{
    return (l1.id < l2.id);
}

bool sameRoot(vector<Message> receive)
{

    if (receive.size() == 0)
        return false;
    else
    {
        int rootsame = receive[0].root;
        for (Message m : receive)
        {
            if (m.root != rootsame)
                return false;
        }
    }
    return true;
}

void BridgeSimulator::StartSimulation()
{
    sort(totalBridges.begin(), totalBridges.end(), compareBridge);
    sort(totalLans.begin(), totalLans.end(), compareLan);
    vector<Message> receiving;
    int time = 0;
    while (!sameRoot(receiving))
    {
        for (Message m : receiving)
        {
            vector<int> send_to_bridges;
            for (Lan l : totalLans)
            {
                if (l.id == m.lan)
                {
                    send_to_bridges = l.active_bridges;
                }
            }
            for (int bridge : send_to_bridges)
            {
                if (bridge != m.sender)
                {
                    for (int i = 0; i < totalBridges.size(); i++)
                    {
                        if (bridge == totalBridges[i].id)
                        {
                            totalBridges[i].receive(m, trace, time);
                        }
                    }
                }
            }
        }
        if (trace == 1)
        {
            cout << "--------SENDING--------" << endl;
        }

        receiving.clear();

        for (int i = 0; i < totalBridges.size(); i++)
        {
            for (Message m : totalBridges[i].send(trace, time))
            {
                receiving.push_back(m);
            }
        }
        if (trace == 1 && !sameRoot(receiving))
        {
            cout << "-------RECEIVING-------" << endl;
        }
        else if (trace == 1 && sameRoot(receiving))
        {
            cout << "***************Spanning Tree Stopped***************" << endl
                 << endl;
        }

        sort(receiving.begin(), receiving.end(), compareMessage);
        time++;
    }
    for (Message m : receiving)
    {
        for (int i = totalLans.size() - 1; i >= 0; i--)
        {
            if (totalLans[i].id == m.lan)
            {
                totalLans[i].DB_id = m.sender;
            }
        }
    }
    for (int i = 0; i < totalLans.size(); i++)
    {
        int DB = totalLans[i].DB_id;
        for (int j = totalBridges.size() - 1; j >= 0; j--)
        {
            if (totalBridges[j].id == DB)
            {
                totalBridges[j].lan_type[totalLans[i].id] = "DP";
            }
        }
    }
    for (int i = 0; i < totalBridges.size(); i++)
    {
        int numberDP = 0;
        for (char lan : totalBridges[i].lans)
        {
            if (totalBridges[i].lan_type[lan] == "DP")
            {
                numberDP++;
            }
        }
        if (numberDP == 0)
        {
            for (char lan : totalBridges[i].lans)
            {
                totalBridges[i].lan_type[lan] = "NP";
            }
        }
    }
}

void BridgeSimulator::PrintResults()
{
    for (Bridge b : totalBridges)
    {
        cout << "B" << b.id << ":";
        for (char lan : b.lans)
        {
            cout << " " << lan << "-" << b.lan_type[lan];
        }
        cout << endl;
    }
}