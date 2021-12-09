#include <bits/stdc++.h>
#include "bridge.h"
using namespace std;

class BridgeSimulator
{
public:
    vector<Bridge> totalBridges;
    vector<Lan> totalLans;
    int trace;
    BridgeSimulator(vector<Bridge> tb, vector<Lan> tl, int t);
    void StartSimulation();
    void PrintResults();
};
