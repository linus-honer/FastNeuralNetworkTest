#include "TrainingDataReader.h"
#include <assert.h>
#include <iosfwd>
#include <algorithm>
#include <iostream>
#include <cstdint>

namespace BPN
{
    trainingDataReader::trainingDataReader(std::string const& filename, int32_t numInputs, int32_t numOutputs)
        : m_filename(filename)
        , m_numInputs(numInputs)
        , m_numOutputs(numOutputs)
    {
        assert(!filename.empty() && m_numInputs > 0 && m_numOutputs > 0)
    }

    bool trainingDataReader::readData()
    {
        assert(!m_filename.empty());

        std::fstream inputFile;
        inputFile.open(m_filename, std::ios::in);

        if(inputfile.is_open())
        {
            std::string line;

            int32_t const totalValuesToRead = m_numInputs + m_numOutputs;

            while (!inputFile.eof())
            {
                std::getline(inputFile, line);
                if (line.length() > 2)
                {
                    m_entries.push_back(TrainingEntry());
                    TrainingEntry& entry = m_entries.back();

                    char* cstr = new char[line.size() + 1];
                    strcpy_s(cstr, line.size() + 1, line.c_str());

                    // Read values
                    int i = 0;
                    char* nextToken = nullptr;
                    char* pToken = strtok_s(cstr, ",", &nextToken);

                    while(pToken != nullptr && i < totalValuesToRead)
                    {
                        if (i < m_numInputs)
                        {
                            entry.m_inputs.push_back(atof(pToken));
                        }
                        else
                        {
                            double const outputValue = atof(pToken);
                            entry.m_expectedOutputs.push_back((int32_t) outputValue);
                        }

                        pToken = strtok_s(nullptr, ",", &nextToken);
                        i++;
                    }
                }
            }

            inputFile.close();

            // TODO: create data if not empty
        }

        return true;
    }
}