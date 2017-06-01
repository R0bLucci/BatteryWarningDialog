#include "option.h"
#include <map>
#include <iostream>
#include <regex>

using std::cout;
using std::endl;

std::string const GUI::Option::levelOption = "--battery-level";
std::string const GUI::Option::titleOption = "--title";
std::string const GUI::Option::msgOption = "--message";
std::string const GUI::Option::helpOption = "--help";

GUI::Option::Option() : GUI::Option::Option(0,0) {}

GUI::Option::Option(int counter, char** arguments) :
    counter(counter), arguments(arguments), exitStatusCode(0)
{
    this->initOptions();
}

bool GUI::Option::parseOptions(){
    if(this->counter <= 1 || !this->arguments) return false;

    // first item is just the executable name
    for(int i=1; i < this->counter; ++i){
        if(GUI::Option::helpOption == *(this->arguments + i)){
            this->printHelp();
            this->exitStatusCode = 0;
            return false;
        }else if(std::regex_match(*(this->arguments + i), std::regex("(--)(.+)=.*"))){
            if(!this->setOption(*(this->arguments + i))) {
                this->exitStatusCode = 23;
                return false;
            }
        }else{
            this->printHelp(*(this->arguments + i));
            this->exitStatusCode = 23;
            return false;
        }
    }
    this->exitStatusCode = 0;
    return true;
}

std::vector<std::string> GUI::Option::splitOption(std::string optionValue){
    int length = optionValue.size();
    std::vector<std::string> tokens;
    for(int i = 0; i < length; ++i){
       if(optionValue[i] == '='){
           tokens.push_back(optionValue.substr(0, i));
           tokens.push_back(optionValue.substr(i+1, length));
           break;
       }
   }
    return tokens;
}

bool GUI::Option::setOption(std::string optionValue){
    std::vector<std::string> && keyValuePair = this->splitOption(optionValue);
    bool isValid = false;

    if(keyValuePair.size() != 2) return isValid;

    if(this->options[keyValuePair[0]].size() != 0){
        //cout<< keyValuePair[1] << " Logic and J.Cole" <<endl;
        if(keyValuePair[0] == GUI::Option::levelOption && !this->isDigit(keyValuePair[1])){
            this->printHelp(keyValuePair[1].c_str());
            isValid = false;
        }else{
            this->options[keyValuePair[0]] = keyValuePair[1];
            isValid = true;
        }
    }else{
        //Correctly formatted flag(option) but option does not exists
        //e.g --no-exists="IDK"
        this->printHelp(keyValuePair[0].c_str());
    }
    return isValid;
}

bool GUI::Option::isDigit(std::string value) const {
        return std::regex_match(value, std::regex("[0-9][0-9]*"));
}

void GUI::Option::initOptions(){
    this->options[GUI::Option::levelOption] = "Low Battery Level";
    this->options[GUI::Option::titleOption] = "title";
    this->options[GUI::Option::msgOption] = "message";
}

std::string GUI::Option::getValue(std::string key) {
    return this->options[key];
}

void GUI::Option::printHelp(const char *msg) const{
    std::string help = "Usage:\n"
    "  BatteryWarningDialog [OPTIONS]\n"
    "\n"
    "Help Options:\n"
    "  --help			Show help options\n"
    "\n"
    "Application Options/Flags:\n  " +
    GUI::Option::levelOption + "=\"<number>\"	Specifies battery level\n  " +
    GUI::Option::titleOption + "=\"<value>\"		Specifies title window\n  " +
    GUI::Option::msgOption + "=\"<value>\" 		Specifies message to display\n";
    if(msg){
        const std::string m ="Error: \"" + std::string(msg) + "\" not valid option/flag\n\n";
        cout << m << help;
    }
    else cout << help;
}

 int GUI::Option::getExitStatusCode() const {
     return this->exitStatusCode;
 }
