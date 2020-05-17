#ifndef CXXRAY_STRINGS_H
#define CXXRAY_STRINGS_H

#include <string>
#include <algorithm>
#include <cctype>

namespace CxxRay {

inline
void ltrim(std::string & s)
{
    auto const pos = std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    });

    s.erase(s.begin(), pos);
}

inline
void rtrim(std::string & s)
{
    auto const pos = std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base();

    s.erase(pos, s.end());
}

inline
void trim(std::string & s)
{
    ltrim(s);
    rtrim(s);
}

inline
void strip_comments(std::string & s)
{
    auto const pos = std::find_if(s.begin(), s.end(), [](int ch) {
        return ch == '#';
    });

    s.erase(pos, s.end());
}

} // namespace CxxRay

#endif
