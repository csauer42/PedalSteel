#include "PedalSteelGuitar.h"
#include <map>

// F# D# G# E B G# F# E D B
// A: P1 5,10 +2 
// B: P2 3,6 +1
// C: P3 4,5 +2
// ?: P4 5,6,10 -2
// F: LKL 4,8 +1
// X: LKV 5,10 -1
// D: LKR 4,8 -1
// ?: RKL 1(+2), 2(+1), 6(-2)
// E: RKR 2(-1/-2), 9(-1)

static const int k_rootString = 3;  // string 4 w/ vector offset
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

static const std::map<std::string, std::string> g_relativeMinor {
    {"C", "Am"},
    {"C#", "A#m"},
    {"Db", "Bbm"},
    {"D", "Bm"},
    {"D#", "Cm"},
    {"Eb", "Cm"},
    {"E", "C#m"},
    {"F", "Dm"},
    {"F#", "D#m"},
    {"Gb", "Ebm"},
    {"G", "Em"},
    {"G#", "Fm"},
    {"Ab", "Fm"},
    {"A", "F#m"},
    {"A#", "Gm"},
    {"Bb", "Gm"},
    {"B", "G#m"}
};

Psg::Psg(std::vector<std::string> tuning)
 : m_fret(0)
{
    for (auto const& string : tuning)
    {
        m_open.push_back(Note(string));
        m_strings.push_back(Note(string));
    }
}

void Psg::AddPedals(std::vector<Pedal> pedals)
{
    for (auto pedal : pedals)
    {
        m_pedals.push_back(pedal);
    }
    std::cout << "Added Pedals\n";    
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
    PedalDown(FindPedal(id));
}

void Psg::PedalUp(std::string const& id)
{
    PedalUp(FindPedal(id));
}

void Psg::PedalHalf(std::string const& id)
{
    PedalHalf(FindPedal(id));
}

Pedal& Psg::FindPedal(std::string const& id)
{
    for (auto& pedal : m_pedals)
    {
        if (pedal.id == id)
        {
            return pedal;
        }
    }
    throw("Could not find pedal " + id);
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

void Psg::PedalHalf(Pedal& pedal)
{
    // TODO require pedal up after pedal half for now,
    // but add half state to go from 1/2 to up or down automatically
    std::cout << "Pedal half stop " << pedal.id << "\n";
    if (pedal.down) PedalUp(pedal);
    bool hasHalfStop = false;

    for (auto& ch : pedal.changes)
    {
        if (ch.halfStop)
        {
            hasHalfStop = true;
            m_strings[ch.string-1] = m_strings[ch.string-1] + ch.shift / 2;
            pedal.down = true;
        }
    }

    if (!hasHalfStop)
    {
        throw("PedalHalf called on pedal with no half stop");
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
    throw("Invalid note name in GetRoot");
}

bool Psg::IsFlatKey(std::string const& root)
{
    return g_flatKeys.at(root);
}