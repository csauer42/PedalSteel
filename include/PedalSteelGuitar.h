#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <array>

struct Note
{
    explicit Note(int val)
        : value(val)
    {}

    explicit Note(std::string note)
        : value(Encode(note))
    {}

    std::string Value() const
    {
        switch(value)
        {
            case 0: return "A";
            case 1: return "Bb";
            case 2: return "B";
            case 3: return "C";
            case 4: return "C#";
            case 5: return "D";
            case 6: return "Eb";
            case 7: return "E";
            case 8: return "F";
            case 9: return "F#";
            case 10: return "G";
            case 11: return "G#";
            default: return "ERROR";
        }
    }

    int Encode(std::string note) const
    {
        if (note == "A") return 0;
        if (note == "Bb" || note == "A#") return 1;
        if (note == "B") return 2;
        if (note == "C") return 3;
        if (note == "Db" || note == "C#") return 4;
        if (note == "D") return 5;
        if (note == "Eb" || note == "D#") return 6;
        if (note == "E") return 7;
        if (note == "F") return 8;
        if (note == "Gb" || note == "F#") return 9;
        if (note == "G") return 10;
        if (note == "Ab" || note == "G#") return 11;
        throw("Invalid note string");
    }

    friend std::ostream& operator<<(std::ostream& stream, const Note& note)
    {
        stream << note.Value();
        return stream;
    }

    friend Note operator+(Note lhs, const int rhs)
    {
        lhs.value += rhs;
        lhs.value %= 12;
        return lhs;
    }

    friend Note operator-(Note lhs, const int rhs)
    {
        if (lhs.value == 0)
        {
            lhs.value = 11;
        }
        else
        {
            lhs.value -= rhs;
        }
        return lhs;
    }

    int value;

};

struct Change
{
    int string;
    int shift;
};

struct Pedal
{
    std::vector<Change> changes;
    bool down;
    std::string id;
};

class Psg
{
public:
    Psg(std::vector<std::string>);
    void SetFret(int fret);
    void AddPedals(std::vector<Pedal>&);
    void PedalDown(std::string const&);
    void PedalUp(std::string const&);

    friend std::ostream& operator<<(std::ostream& stream, const Psg& psg)
    {
        for (size_t ii = 0; ii < psg.m_strings.size(); ii++)
        {
            stream << "[" << std::setw(2) << (ii+1) << "] " << psg.m_strings[ii] << "\n";
        }
        return stream;
    }

private:
    void PedalDown(Pedal&);
    void PedalUp(Pedal&);

    unsigned int m_fret;
    std::array<Note, 10> m_open;
    std::array<Note, 10> m_strings;
    std::vector<Pedal> m_pedals;

};