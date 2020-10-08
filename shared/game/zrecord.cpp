#include "zrecord.h"

#include <iomanip>
#include <sstream>
#include <iostream>

#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

#include <string>

#include <platform/iresource.h>

namespace {

    std::string trim(const std::string& str)
    {
        size_t first = str.find_first_not_of(' ');
        if (std::string::npos == first)
        {
            return str;
        }
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, (last - first + 1));
    }

const int RECORD_LINE_WIDTH = 25;
//const int MAX_RECORD = 5;

const std::string RECORD_FILE_NAME = "record.txt";

const std::vector<std::string> RECORD_TEXT = {
    "1.MARIO              5000",
    "2.GORDON FREEMAN     3750",
    "3.MASTER CHIEF       2750",
    "4.LARA CROFT         1450",
    "5.UNKNOWN HERO          0"
};

}

zrecord::zrecord(iresource& resource) :
    m_resource(resource)
{
    auto text = resource.load_text_data(RECORD_FILE_NAME);
    std::cout << "loaded record:\n" << text << std::endl;

    if(text.empty()) {
        parse(RECORD_TEXT);
    }
    else {
        std::stringstream sstream;
        sstream << text;
        std::string buffer;
        std::vector<std::string> record;
        while(getline(sstream, buffer)) {
            record.push_back(buffer);
        }
        parse(record);
    }
    build_text_records();
}

std::vector<std::string> zrecord::get_record_text() const
{
    return m_text_records;
}

void zrecord::process(const std::string& player, int value)
{
    bool sync = false;
    for(size_t i = 0; i < m_records.size(); i++) {
        if(player == m_records[i].first) {
            if(value > m_records[i].second) {
                m_records[i].second = value;
                sync = true;
            }
            break;
        }
    }
    if(sync) {
        std::sort(m_records.begin(), m_records.end(), [](std::pair<std::string, int>& a1, std::pair<std::string, int>& a2){
            return a1.second > a2.second;
        });
        build_text_records();
        std::stringstream sstream;
        for(size_t i = 0; i < m_text_records.size(); i++) {
            sstream << m_text_records[i] << "\n";
        }
        m_resource.save_text_data(RECORD_FILE_NAME, sstream.str());
    }
}

std::string zrecord::get_hero_name()
{
    return "UNKNOWN HERO";
}

void zrecord::parse(const std::vector<std::string>& record)
{
    m_records.clear();
    std::string::size_type sz;
    for(size_t i = 0; i < record.size(); i++) {
        const std::string& buffer = record[i];

        //std::cout << "parse record: " << buffer << std::endl;

        size_t last_space = buffer.find_last_of(' ');
        std::string heroname_raw = buffer.substr(buffer.find_first_of('.') + 1, last_space - 1);
        std::string heroname = trim(heroname_raw);
        std::string score_str = buffer.substr(last_space + 1, buffer.size() - 1);
        int score = std::stoi(score_str, &sz);;

        //std::cout << "heroname: '" << heroname << "'" << " score: '" << score << "'" << std::endl;

        m_records.push_back(std::make_pair(heroname, score));
    }
}

void zrecord::build_text_records()
{
    m_text_records.resize(0);
    m_text_records.reserve(m_records.size());

    int header_size = 0;
    for(size_t i = 0; i < m_records.size(); i++) {
        std::stringstream sstream;
        header_size = 2 + (int)m_records[i].first.size();
        sstream << i + 1 << "." << m_records[i].first << std::setw(RECORD_LINE_WIDTH - header_size) << m_records[i].second;
        m_text_records.push_back(sstream.str());
    }
}
