#include "PedalSteelGuitar.h"
#include <map>

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

static const Note c = Note("C4");
static const int k_rootString = 3;
static const std::map<std::string, bool> g_flatKeys {
    {"C", false},
    {"C#", false},
    {"Db", true},
    {"D", false},
    {"D#", true},
    {"Eb", true},
    {"E", false},
    {"F", true},
    {"F#", false},
    {"Gb", true},
    {"G", false},
    {"G#", true},
    {"Ab", true},
    {"A", false},
    {"A#", true},
    {"Bb", true},
    {"B", false}
};

Psg::Psg(std::vector<std::string> tuning)
 : m_fret(0)
 , m_open{c, c, c, c, c, c, c, c, c, c}
 , m_strings{c, c, c, c, c, c, c, c, c, c}
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
    std::string root = GetRoot(m_open[k_rootString] + fret);
    bool flatKey = IsFlatKey(root);
 
    for (size_t ii = 0; ii < m_strings.size(); ii++)
    {
        m_strings[ii] = m_open[ii] + fret;
        m_strings[ii].flatKey = flatKey;
    }
    m_fret = fret;
    std::cout << "Bar at fret " << m_fret << " (major chord " << root << ")\n";
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

std::string Psg::GetRoot(Note const& note)
{
    const std::string noteName = note.StrValue();
    if (noteName.size() == 2)
    {
        return noteName.substr(0, 1);
    }
    else if (noteName.size() == 3)
    {
        return noteName.substr(0, 2);
    }
    throw("Invalid note name in IsFlatKey");
}

bool Psg::IsFlatKey(std::string const& root)
{
    return g_flatKeys.at(root);
}