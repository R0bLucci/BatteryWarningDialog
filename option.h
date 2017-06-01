#ifndef OPTION_H
#define OPTION_H

#include <string>
#include <map>
#include <vector>

namespace GUI {

    class Option
    {

    private:
        void initOptions();
        std::map<std::string, std::string> options;
        int counter;
        char** arguments;
        int exitStatusCode;

        std::vector<std::string> splitOption(std::string optionValue);
        bool setOption(std::string optionValue);
        bool isDigit(std::string value) const;

    public:
        Option();
        Option(int counter, char** arguments);
        std::string getValue(std::string key);

        void printHelp(const char * msg = 0) const;

        bool parseOptions();
        int getExitStatusCode() const;
        static const std::string levelOption;
        static const std::string titleOption;
        static const std::string msgOption;
        static const std::string helpOption;
    };
}

#endif // OPTION_H
