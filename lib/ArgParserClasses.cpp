#include "ArgParser.h"

ArgumentParser::StringVectorArgument::StringVectorArgument() {
    positional = false;
    stored = false;
    unstoredVector = new std::vector<std::string>;
    storedVector = nullptr;

    minsize = 0;
}

ArgumentParser::StringVectorArgument::~StringVectorArgument() {
    if (unstoredVector != nullptr) {
        delete unstoredVector;
    }
}

void ArgumentParser::StringVectorArgument::SetMinsize(int minSize) {
    minsize = minSize;
}

ArgumentParser::StringVectorArgument& ArgumentParser::StringVectorArgument::StoreValues(std::vector<std::string>& Vector) {
    stored = true;
    delete unstoredVector;
    storedVector = &Vector;
    return (*this);
}

ArgumentParser::StringVectorArgument& ArgumentParser::StringVectorArgument::StoreValue(std::vector<std::string>& Vector) {
    stored = true;
    delete unstoredVector;
    storedVector = &Vector;
    return (*this);
}

ArgumentParser::StringVectorArgument& ArgumentParser::StringVectorArgument::Positional() {
    positional = true;
    return (*this);
}

bool ArgumentParser::StringVectorArgument::IsPositional() {
    return positional;
}

ArgumentParser::StringVectorArgument::StringVectorArgument(const StringVectorArgument& base) {
    stored = base.stored;
    minsize = base.minsize;
    storedVector = base.storedVector;
    positional = base.positional;
    if (base.unstoredVector == nullptr) {
      unstoredVector = nullptr;
    }
    else {
      unstoredVector = new std::vector<std::string>(*base.unstoredVector);
    }
}

void ArgumentParser::StringVectorArgument::operator =(const StringVectorArgument& base) {
    stored = base.stored;
    minsize = base.minsize;
    storedVector = base.storedVector;
    positional = base.positional;
    if (base.unstoredVector == nullptr) {
      unstoredVector = nullptr;
    }
    else {
      unstoredVector = new std::vector<std::string>(*base.unstoredVector);
    }
}

ArgumentParser::StringArgument::StringArgument() {
    intArgumentQuantity = ArgumentType::SIMPLE;
    vectorStringArgument = StringVectorArgument();
    stored = false;
    storedValue = nullptr;
    unstoredValue = nullptr;
}

ArgumentParser::StringArgument::~StringArgument() {;
    if (unstoredValue != nullptr) delete unstoredValue;
}

ArgumentParser::StringVectorArgument& ArgumentParser::StringArgument::MultiValue() {
    intArgumentQuantity = ArgumentType::MULTY;
    return vectorStringArgument;
}

ArgumentParser::StringVectorArgument& ArgumentParser::StringArgument::MultiValue(int minSize) {
    intArgumentQuantity = ArgumentType::MULTY;
    vectorStringArgument.SetMinsize(minSize);
    return vectorStringArgument;
}

ArgumentParser::StringArgument& ArgumentParser::StringArgument::StoreValue(std::string& value) {
    stored = true;
    delete unstoredValue;
    storedValue = &value;
    return (*this);
}

ArgumentParser::StringArgument& ArgumentParser::StringArgument::Default(const std::string& value) {
    delete unstoredValue;
    unstoredValue = new std::string(value);
    return (*this);
}

bool ArgumentParser::StringArgument::IsPositional() {
    if (intArgumentQuantity == ArgumentType::MULTY) {
      return vectorStringArgument.IsPositional();
    }
    return false;
}

ArgumentParser::StringArgument::StringArgument(const StringArgument& base) {
    stored = base.stored;
    intArgumentQuantity = base.intArgumentQuantity;
    storedValue = base.storedValue;
    vectorStringArgument = base.vectorStringArgument;
    if (base.unstoredValue == nullptr) {
      unstoredValue = nullptr;
    }
    else {
      unstoredValue = new std::string(*base.unstoredValue);
    }
}

ArgumentParser::IntVectorArgument::IntVectorArgument() {
    minsize = 0;
}

ArgumentParser::IntVectorArgument::~IntVectorArgument() {
    if (unstoredVector != nullptr) {
        delete unstoredVector;
    }
}

void ArgumentParser::IntVectorArgument::SetMinsize(int minSize) {
    minsize = minSize;
}

ArgumentParser::IntVectorArgument& ArgumentParser::IntVectorArgument::StoreValues(std::vector<int>& Vector) {
    storedVector = (&Vector);
    delete unstoredVector;
    stored = true;
    return (*this);
 }

ArgumentParser::IntVectorArgument& ArgumentParser::IntVectorArgument::StoreValue(std::vector<int>& Vector) {
    storedVector = (&Vector);
    delete unstoredVector;
    stored = true;
    return (*this);
}

ArgumentParser::IntVectorArgument& ArgumentParser::IntVectorArgument::Positional() {
    positional = true;
    return (*this);
}

bool ArgumentParser::IntVectorArgument::IsPositional() {
    return positional;
}

ArgumentParser::IntVectorArgument::IntVectorArgument(const IntVectorArgument& base) {
    stored = base.stored;
    minsize = base.minsize;
    storedVector = base.storedVector;
    if (base.unstoredVector == nullptr) {
      unstoredVector = nullptr;
    }
    else {
      unstoredVector = new std::vector<int> (*base.unstoredVector);
    }
}

ArgumentParser::IntArgument::IntArgument() {
    intArgumentQuantity = ArgumentType::SIMPLE;
    vectorIntArgument;
    unstoredValue = nullptr;
    storedValue = nullptr;
    stored = false;
  }

ArgumentParser::IntVectorArgument& ArgumentParser::IntArgument::MultiValue() {
    intArgumentQuantity = ArgumentType::MULTY;
    return vectorIntArgument;
}

ArgumentParser::IntVectorArgument& ArgumentParser::IntArgument::MultiValue(int minSize) {
    intArgumentQuantity = ArgumentType::MULTY;
    vectorIntArgument.SetMinsize(minSize);
    return vectorIntArgument;
}

ArgumentParser::IntArgument& ArgumentParser::IntArgument::Default(const int& value) { ////
    delete unstoredValue;
    unstoredValue = new int(value);
    return (*this);
}

ArgumentParser::IntArgument& ArgumentParser::IntArgument::StoreValue(int& value) {
    stored = true;
    delete unstoredValue;
    storedValue = &value;
    return (*this);
}

bool ArgumentParser::IntArgument::IsPositional() {
    if (intArgumentQuantity == ArgumentType::MULTY) {
      return vectorIntArgument.IsPositional();
    }
    return false;
}

ArgumentParser::IntArgument::IntArgument(const IntArgument& base) {
    stored = base.stored;
    vectorIntArgument = base.vectorIntArgument;
    intArgumentQuantity = base.intArgumentQuantity;
    storedValue = base.storedValue;
    if (base.unstoredValue != nullptr) {
      unstoredValue = new int(*base.unstoredValue);
    }
    else {
      unstoredValue = nullptr;
    }
}

ArgumentParser::IntArgument::~IntArgument() {
    if (unstoredValue != nullptr) delete unstoredValue;
}

ArgumentParser::FlagArgument::FlagArgument() {
    stored = false;
    unstoredFlag = nullptr;
    storedFlag = nullptr;
}

ArgumentParser::FlagArgument& ArgumentParser::FlagArgument::Default(bool f) {
    delete unstoredFlag;
    unstoredFlag = new bool(f);

    return (*this);
}

ArgumentParser::FlagArgument& ArgumentParser::FlagArgument::StoreValue(bool& flag) {
    delete unstoredFlag;
    unstoredFlag = nullptr;
    stored = true;
    storedFlag = &flag;

    return (*this);
}

ArgumentParser::Argument::Argument(ArgumentType argCl, const std::string& name, char shortName, const std::string& helpForArg)
    : argClass(argCl), argumentName(name), argumentShortName(shortName), help(helpForArg) {}

    
bool ArgumentParser::Argument::IsPositional() {
    if (argClass == ArgumentType::INT) {
        return intArg.IsPositional();
    }
    if (argClass == ArgumentType::STRING) {
        return stringArg.IsPositional();
    }
        return false;
    }

ArgumentParser::IntArgument& ArgumentParser::ArgParser::AddIntArgument(const std::string& name) { 
    arg.push_back(Argument(ArgumentType::INT, name));
    return arg[arg.size() - 1].intArg;
  }

ArgumentParser::IntArgument& ArgumentParser::ArgParser::AddIntArgument(char shortName, const std::string& name) {
    arg.push_back(Argument(ArgumentType::INT, name, shortName));
    return arg[arg.size() - 1].intArg;
  }

ArgumentParser::IntArgument& ArgumentParser::ArgParser::AddIntArgument(char shortName, const std::string& name, const std::string& helpForInt) {
    arg.push_back(Argument(ArgumentType::INT, name, shortName, helpForInt));
    return arg[arg.size() - 1].intArg;
  }

ArgumentParser::IntArgument& ArgumentParser::ArgParser::AddIntArgument(const std::string& name, const std::string& helpForInt) {
    arg.push_back(Argument(ArgumentType::INT, name, ' ', helpForInt));
    return arg[arg.size() - 1].intArg;
  }


ArgumentParser::StringArgument& ArgumentParser::ArgParser::AddStringArgument(const std::string& name) {
    arg.push_back(Argument(ArgumentType::STRING, name));

    return arg[arg.size() - 1].stringArg;
  }

ArgumentParser::StringArgument& ArgumentParser::ArgParser::AddStringArgument(char shortName, const std::string& name) {
    arg.push_back(Argument(ArgumentType::STRING, name, shortName));
    return arg[arg.size() - 1].stringArg;
  }

ArgumentParser::StringArgument& ArgumentParser::ArgParser::AddStringArgument(char shortName, const std::string& name, const std::string& helpForString) {
    arg.push_back(Argument(ArgumentType::STRING, name, shortName, helpForString));
    return arg[arg.size() - 1].stringArg;
  }

ArgumentParser::FlagArgument& ArgumentParser::ArgParser::AddFlag(const std::string& name, const std::string& helpForFlag, char shortName) { 
      arg.push_back(Argument(ArgumentType::FLAG, name, shortName, helpForFlag));
      return arg[arg.size() - 1].flagArg;
  }

ArgumentParser::FlagArgument& ArgumentParser::ArgParser::AddFlag(char shortName, const std::string& name, const std::string& helpForFlag) {
      arg.push_back(Argument(ArgumentType::FLAG, name, shortName, helpForFlag));
      return arg[arg.size() - 1].flagArg;
  }

ArgumentParser::ArgParser::ArgParser(const std::string& argName) {
    name = argName;
  }

std::string ArgumentParser::ArgParser::GetStringValue(const std::string& argName) {
    for (const auto& argument : arg) {
        if (argument.argumentName == argName) {
            //check if there is no value or it isnt saved
            if (!argument.stringArg.stored && argument.stringArg.unstoredValue == nullptr) {
                std::cerr << "String argument doesn't have a value." << std::endl;
                return "";  //no value -> return empty string
            }

            // choosing value due to stored
            const std::string* value = nullptr;
            if (argument.stringArg.stored) {
                value = argument.stringArg.storedValue;
            } else {
                value = argument.stringArg.unstoredValue;
            }

            //if value is found = return value
            if (value != nullptr) {
                return *value;
            } else {
                return "";
            }
        }
    }

    // error if no argument
    std::cerr << "String argument not found." << std::endl;
    return ""; 
}


int ArgumentParser::ArgParser::GetIntValue(const std::string& argName, int j) {
    for (int i = 0; i < arg.size(); i++) {
        if (arg[i].argumentName == argName) {
            if (j == -1) {
                if (arg[i].intArg.stored) {
                    return *(arg[i].intArg.storedValue);
                } else {
                    return *(arg[i].intArg.unstoredValue);
                }
            } else {
                if (arg[i].intArg.vectorIntArgument.stored) {
                    return (arg[i].intArg.vectorIntArgument.storedVector->at(j));
                } else {
                    return (arg[i].intArg.vectorIntArgument.unstoredVector->at(j));
                }
            }
        }
    }
    throw std::runtime_error("Int argument isn't found");
}

bool ArgumentParser::ArgParser::GetFlag(const std::string& argName) {
    for (int i = 0; i < arg.size(); i++) {
        if (arg[i].argumentName == argName) {
            if (arg[i].flagArg.stored) {
                return *arg[i].flagArg.storedFlag;
            } else {
                return *arg[i].flagArg.unstoredFlag;
            }
        }
    }
    return false; 
}


void ArgumentParser::ArgParser::AddHelp(char shortChar, const std::string& helpHeader, const std::string& helpText) {
    helpChar = shortChar;
    helpString1 = helpHeader;
    helpString2 = helpText; 
  }

std::string ArgumentParser::ArgParser::HelpDescription() { //create help string (looking for args and add info abt them)
    std::string helpDescription;
    helpDescription = "Argument parser";
    return helpDescription;
  }
  

bool ArgumentParser::ArgParser::Help() {
    std::string helpOutput = HelpDescription();
    std::cout << helpOutput << std::endl;

    return true;
}