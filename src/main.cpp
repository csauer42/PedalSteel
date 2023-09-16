#include <iostream>
#include "PedalSteelGuitar.h"

std::vector<Pedal> CreatePedals();

int main()
{
    // F# D# G# E B G# F# E D B
    // 9  6  11 7 2 11 9  7 5 2

    // create
    std::vector<std::string> tuning = {"F#", "D#", "G#", "E", "B", "G#", "F#", "E", "D", "B"};
    auto psg = Psg(tuning);
    auto pedals = CreatePedals();
    psg.AddPedals(pedals);


    // test
    psg.SetFret(8);
    std::cout << psg;

    psg.PedalDown("A");
    psg.PedalDown("B");
    std::cout << psg;

    return 0;
}

std::vector<Pedal> CreatePedals()
{
    std::vector<Pedal> pedals;

    // A: P1 5,10 +2 
    auto p1 = Pedal();
    p1.changes.push_back({5, 2});
    p1.changes.push_back({10, 2});
    p1.id = "A";
    p1.down = false;
    pedals.push_back(p1);

    // B: P2 3,6 +1
    auto p2 = Pedal();
    p2.changes.push_back({3,1});
    p2.changes.push_back({6,1});
    p2.id = "B";
    p2.down = false;
    pedals.push_back(p2);

    // C: P3 4,5 +2
    auto p3 = Pedal();
    p3.changes.push_back({4, 2});
    p3.changes.push_back({5, 2});
    p3.id = "C";
    p3.down = false;
    pedals.push_back(p3);

    // ?: P4 5,6,10 -2
    auto p4 = Pedal();
    p4.changes.push_back({5, -2});
    p4.changes.push_back({6, -2});
    p4.changes.push_back({10, -2});
    p4.id = "P4";
    p4.down = false;
    pedals.push_back(p4);

    // F: LKL 4,8 +1
    auto lkl = Pedal();
    lkl.changes.push_back({4, 1});
    lkl.changes.push_back({8, 1});
    lkl.id = "F";
    lkl.down = false;
    pedals.push_back(lkl);

    // ?: LKV 5,10 -1
    auto lkv = Pedal();
    lkv.changes.push_back({5, -1});
    lkv.changes.push_back({10, -1});
    lkv.id = "LKV";
    lkv.down = false;
    pedals.push_back(lkv);

    // D: LKR 4,8 -1
    auto lkr = Pedal();
    lkr.changes.push_back({4,-1});
    lkr.changes.push_back({8,-1});
    lkr.id = "D";
    lkr.down = false;
    pedals.push_back(lkr);

    // ?: RKL 1(+2), 2(+1), 6(-2)
    auto rkl = Pedal();
    rkl.changes.push_back({1, 2});
    rkl.changes.push_back({2, 1});
    rkl.changes.push_back({6, -2});
    rkl.id = "RKL";
    rkl.down = false;
    pedals.push_back(rkl);

    // E: RKR 2(-1/-2), 9(-1)
    auto rkr = Pedal();
    rkr.changes.push_back({2, -1});  // TODO half stop
    rkr.changes.push_back({9, -1});
    rkr.id = "E";
    rkr.down = false;
    pedals.push_back(rkr);

    return pedals;
}