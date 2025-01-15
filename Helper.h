#ifndef HELPER_H
#define HELPER_H

#include <QString>
#include <sstream>
#include <vector>
#include <string>

class Helper
{
public:

    static std::string replaceSingleQuote(const std::string& input);

    static std::string escapeValue(std::string value);

    static std::vector<std::string> splitString(const std::string &str, char delimiter);

    static bool isValidNameOrSurname(const QString &name);

    static bool isValidNumber(const QString &number);
};

#endif // HELPER_H
