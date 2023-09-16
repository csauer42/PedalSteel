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
        , flatKey(false)
    {}

    explicit Note(std::string note)
        : value(Encode(note))
        , flatKey(false)
    {}

    std::string StrValue() const
    {
        int octave = value / 12 - 1;
        int noteVal = value % 12;
        std::string octStr = std::to_string(octave);
        std::string noteStr;

        switch(noteVal)
        {
            case 0: noteStr = "C"; break;
            case 1: noteStr = flatKey ? "Db" : "C#"; break;
            case 2: noteStr = "D"; break;
            case 3: noteStr = flatKey ? "Eb" : "D#"; break;
            case 4: noteStr = "E"; break;
            case 5: noteStr = "F"; break;
            case 6: noteStr = flatKey ? "Gb" : "F#"; break;
            case 7: noteStr = "G"; break;
            case 8: noteStr = flatKey ? "Ab" : "G#"; break;
            case 9: noteStr = "A"; break;
            case 10: noteStr = flatKey ? "Bb" : "A#"; break;
            case 11: noteStr = "B"; break;
            default: throw("Invalid note value");
        }
        return noteStr + octStr;
    }

    int Encode(std::string note) const
    {
        std::string noteName;
        int octave, noteVal;
        // split note and octave
        if (note.size() == 2)
        {
            noteName = note.substr(0, 1);
            octave = stoi(note.substr(1,1));
        }
        else if (note.size() == 3)
        {
            noteName = note.substr(0,2);
            octave = stoi(note.substr(2,1));
        }
        else
        {
            throw("Invalid note input");
        }

        
        if (noteName == "C") noteVal = 0;
        else if (noteName == "Db" || noteName == "C#") noteVal = 1;
        else if (noteName == "D") noteVal = 2;
        else if (noteName == "Eb" || noteName == "D#") noteVal = 3;
        else if (noteName == "E") noteVal = 4;
        else if (noteName == "F") noteVal = 5;
        else if (noteName == "Gb" || noteName == "F#") noteVal = 6;
        else if (noteName == "G") noteVal = 7;
        else if (noteName == "Ab" || noteName == "G#") noteVal = 8;
        else if (noteName == "A") noteVal = 9;
        else if (noteName == "Bb" || noteName == "A#") noteVal = 10;
        else if (noteName == "B") noteVal = 11;
        else throw("Invalid note string");

        return (12 * (octave + 1)) + noteVal;
    }

    friend std::ostream& operator<<(std::ostream& stream, const Note& note)
    {
        stream << note.StrValue();
        return stream;
    }

    friend Note operator+(Note lhs, const int rhs)
    {
        lhs.value += rhs;
        return lhs;
    }

    friend Note operator-(Note lhs, const int rhs)
    {
        lhs.value -= rhs;
        return lhs;
    }

    int value;
    bool flatKey;

};

struct Change
{
    int string;
    int shift;
};

struct Pedal
{
    Pedal()
    {
        down = false;
    }
    Pedal(std::string pid)
    {
        id = pid;
        down = false;
    }
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
    std::string GetRoot(Note const&);
    bool IsFlatKey(std::string const&);

    unsigned int m_fret;
    bool m_flatKey = false;
    std::array<Note, 10> m_open;
    std::array<Note, 10> m_strings;
    std::vector<Pedal> m_pedals;

};