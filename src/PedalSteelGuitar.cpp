#include "PedalSteelGuitar.h"

// F# D# G# E B G# F# E D B
// 9  6  11 7 2 11 9  7 5 2
// A: P1 5,10 +2 
// B: P2 3,6 +1
// C: P3 4,5 +2
// ?: P4 5,6,10 -2
// F: LKL 4,8 +1
// ?: LKV 5,10 -1
// D: LKR 4,8 -1
// ?: RKL 1(+2), 2(+1), 6(-2)
// E: RKR 2(-1/-2), 9(-1)

Psg::Psg(std::vector<std::string> tuning)
 : m_fret(0)
 , m_open{Note(0), Note(0), Note(0), Note(0), Note(0), Note(0), Note(0), Note(0), Note(0), Note(0)}
 , m_strings{Note(0), Note(0), Note(0), Note(0), Note(0), Note(0), Note(0), Note(0), Note(0), Note(0)}
{
    if (tuning.size() != 10)
    {
        throw("Only 10 string guitars supported at this time");
    }
    for (size_t ii = 0; ii < tuning.size(); ii++)
    {
        m_open[ii] = Note(tuning[ii]);
        m_strings[ii] = Note(tuning[ii]);
    }
}

void Psg::AddPedals(std::vector<Pedal>& p)
{
    m_pedals = p;
    std::cout << "Added Pedal\n";    
}

void Psg::SetFret(int fret)
{
    for (size_t ii = 0; ii < m_strings.size(); ii++)
    {
        m_strings[ii] = m_open[ii] + fret;
    }
    m_fret = fret;
    std::cout << "Bar at fret " << m_fret << "\n";
}

void Psg::PedalDown(std::string const& id)
{
    for (auto pedal : m_pedals)
    {
        if (pedal.id == id)
        {
            return PedalDown(pedal);
        }
    }
    std::cout << "ERROR: PedalDown could not find pedal " << id << "\n";
}

void Psg::PedalUp(std::string const& id)
{
    for (auto pedal : m_pedals)
    {
        if (pedal.id == id)
        {
            return PedalUp(pedal);
        }
    }
    std::cout << "ERROR: PedalUp could not find pedal " << id << "\n";
}

void Psg::PedalDown(Pedal& pedal)
{
    std::cout << "Pedal down " << pedal.id << "\n";
    if (!pedal.down)
    {
        for (auto ch : pedal.changes)
        {
            m_strings[ch.string-1] = m_strings[ch.string-1] + ch.shift;
        }
        pedal.down = true;
    }
}

void Psg::PedalUp(Pedal& pedal)
{
    std::cout << "Pedal up " << pedal.id << "\n";
    if (pedal.down)
    {
        for (auto ch : pedal.changes)
        {
            m_strings[ch.string-1] = m_open[ch.string-1] + m_fret;
        }
        pedal.down = false;
    }
}