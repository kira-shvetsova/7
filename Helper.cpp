#include "Helper.h"

std::string Helper::replaceSingleQuote(const std::string& input)
{
    std::string result;
    result.reserve(input.size()); // Reserve space to avoid frequent reallocations

    for (char ch : input)
    {
        if (ch == '\'')
        {
            result += "''"; // Replace single quote with two single quotes
        }
        else
        {
            result += ch;   // Keep other characters as is
        }
    }
    return result;
}

std::string Helper::escapeValue(std::string value)
{
    return "'" +
           Helper::replaceSingleQuote(value) +
           "'";
}

std::vector<std::string> Helper::splitString(const std::string &str, char delimiter)
{
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter))
    {
        tokens.push_back(token);
    }

    return tokens;
}

bool Helper::isValidNameOrSurname(const QString &name)
{
    if (name.isEmpty() || !name[0].isUpper())
    {
        return false;
    }

    for (QChar c : name)
    {
        if (!c.isLetter())
        {
            return false;
        }
    }
    return true;
}

bool Helper::isValidNumber(const QString &number)
{
    if (number.isEmpty())
    {
        return false;
    }

    for (QChar c : number)
    {
        if (!c.isDigit() && c != '-')
        {
            return false;
        }
    }
    return true;
}
