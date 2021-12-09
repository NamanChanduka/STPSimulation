#include <bits/stdc++.h>
#include "bridge.h"
#include "bridgesim.h"
using namespace std;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int trace, n;
    vector<Lan> totallans;
    vector<Bridge> totalbridges;
    cin >> trace;
    cin >> n;
    /*cout << trace << endl
         << n << endl;*/
    string line;
    getline(cin, line);
    for (int i = 0; i < n; i++)
    {
        set<char> lanchar;
        getline(cin, line);
        for (int j = line.size() - 1; j >= 0; j--)
        {
            if (line[j] != ':' && line[j] != ' ')
            {
                lanchar.insert(line[j]);
            }

            if (line[j] == ':')
            {
                int no = 0;
                for (int k = 1; k < j; k++)
                {
                    int add = int(line[k] - '0');
                    no = no * 10 + add;
                }
                Bridge b(no);
                for (auto x : lanchar)
                {
                    int flag = 0;
                    for (int i = 0; i < totallans.size(); i++) //cant use for(auto) loop
                    {                                          //as it creates a copy
                        if (totallans[i].id == x)              //and I need to update
                        {                                      //the actual lan object
                            flag = 1;
                            totallans[i].active_bridges.push_back(b.id);
                            b.lans.push_back(totallans[i].id);
                        }
                    }
                    if (flag == 0)
                    {
                        Lan l1(x);
                        l1.active_bridges.push_back(b.id);
                        b.lans.push_back(l1.id);
                        totallans.push_back(l1);
                    }
                }
                b.setType();
                totalbridges.push_back(b);
                break;
            }
        }
    }
    /* for (auto x : totalbridges)
    {
        x.print_lans();
    }

    for (auto x : totallans)
    {
        cout << x.id << " ";
        for (auto y : x.active_bridges)
        {
            cout << y << " ";
        }
        cout << endl;
    }*/
    BridgeSimulator bridgesim(totalbridges, totallans, trace);
    //cout << "bridgesim trace = " << bridgesim.trace << endl;
    bridgesim.StartSimulation();
    bridgesim.PrintResults();
    return 0;
}