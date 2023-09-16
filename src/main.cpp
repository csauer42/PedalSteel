#include <iostream>
#include "PedalSteelGuitar.h"

std::vector<Pedal> CreatePedals();

int main()
{
    // str | note | pitch | midi num
    //  1    F#4     370       66
    //  2    D#4     310       63
    //  3    G#4     413       68
    //  4    E4      330       64
    //  5    B3      247       59
    //  6    G#3     208       56
    //  7    F#3     185       54
    //  8    E3      165       52
    //  9    D3      148       50
    // 10    B2      123       47

    try
    {
        std::vector<std::string> tuning = {"F#4", "D#4", "G#4", "E4", "B3", "G#3", "F#3", "E3", "D3", "B2"};
        auto psg = Psg(tuning);
        auto pedals = CreatePedals();
        psg.AddPedals(pedals);

        std::cout << psg << "\n";

        psg.SetFret(6);
        psg.PedalDown("A");
        psg.PedalDown("B");

        std::cout << psg << "\n";
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}

std::vector<Pedal> CreatePedals()
{
    std::vector<Pedal> pedals;

    // A: P1 5,10 +2 
    auto p1 = Pedal("A");
    p1.changes.push_back({5, 2});
    p1.changes.push_back({10, 2});
    pedals.push_back(p1);

    // B: P2 3,6 +1
    auto p2 = Pedal("B");
    p2.changes.push_back({3,1});
    p2.changes.push_back({6,1});
    pedals.push_back(p2);

    // C: P3 4,5 +2
    auto p3 = Pedal("C");
    p3.changes.push_back({4, 2});
    p3.changes.push_back({5, 2});
    pedals.push_back(p3);

    // ?: P4 5,6,10 -2
    auto p4 = Pedal("P4");
    p4.changes.push_back({5, -2});
    p4.changes.push_back({6, -2});
    p4.changes.push_back({10, -2});
    pedals.push_back(p4);

    // F: LKL 4,8 +1
    auto lkl = Pedal("F");
    lkl.changes.push_back({4, 1});
    lkl.changes.push_back({8, 1});
    pedals.push_back(lkl);

    // ?: LKV 5,10 -1
    auto lkv = Pedal("LKV");
    lkv.changes.push_back({5, -1});
    lkv.changes.push_back({10, -1});
    pedals.push_back(lkv);

    // D: LKR 4,8 -1
    auto lkr = Pedal("D");
    lkr.changes.push_back({4,-1});
    lkr.changes.push_back({8,-1});
    pedals.push_back(lkr);

    // ?: RKL 1(+2), 2(+1), 6(-2)
    auto rkl = Pedal("RKL");
    rkl.changes.push_back({1, 2});
    rkl.changes.push_back({2, 1});
    rkl.changes.push_back({6, -2});
    pedals.push_back(rkl);

    // E: RKR 2(-1/-2), 9(-1)
    auto rkr = Pedal("E");
    rkr.changes.push_back({2, -1});  // TODO half stop
    rkr.changes.push_back({9, -1});
    pedals.push_back(rkr);

    return pedals;
}