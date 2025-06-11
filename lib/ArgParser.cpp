#include "ArgParser.h"
#include "ArgParserClasses.cpp"

bool ArgumentParser::ArgParser::validateIntArgument(const Argument& argument) {
    if (argument.intArg.intArgumentQuantity == ArgumentType::SIMPLE) {
        if (argument.intArg.stored || argument.intArg.unstoredValue != nullptr) {
            return true;
        }
        return false;
    } else {
        std::vector<int>* vectorToCheck = nullptr;
        if (argument.intArg.vectorIntArgument.stored) {
            vectorToCheck = argument.intArg.vectorIntArgument.storedVector;
        } else {
            vectorToCheck = argument.intArg.vectorIntArgument.unstoredVector;
        }

        if (vectorToCheck->size() >= argument.intArg.vectorIntArgument.minsize) {
            return true;
        }
        return false;
    }
}

bool ArgumentParser::ArgParser::validateStringArgument(const Argument& argument) {
    if (argument.stringArg.intArgumentQuantity == ArgumentType::SIMPLE) {
        if (argument.stringArg.stored || argument.stringArg.unstoredValue != nullptr) {
            return true;
        }
        return false;
    } else {
        std::vector<std::string>* vectorToCheck = nullptr;
        if (argument.stringArg.vectorStringArgument.stored) {
            vectorToCheck = argument.stringArg.vectorStringArgument.storedVector;
        } else {
            vectorToCheck = argument.stringArg.vectorStringArgument.unstoredVector;
        }

        if (vectorToCheck->size() >= argument.stringArg.vectorStringArgument.minsize) {
            return true;
        }
        return false;
    }
}

bool ArgumentParser::ArgParser::validate() {
    for (const auto& currentArg : arg) {
        if (currentArg.argClass == ArgumentType::INT) {
            if (!validateIntArgument(currentArg)) {
                return false;
            }
        } else if (currentArg.argClass == ArgumentType::STRING) {
            if (!validateStringArgument(currentArg)) {
                return false;
            }
        }
    }
    return true;
}

void ArgumentParser::ArgParser::processPositionalArg(std::string inputData) { // add positional arg to string or int vector
  for (int j = 0; j < arg.size(); j++) {
        if (arg[j].IsPositional()) {
          if (arg[j].argClass == ArgumentParser::ArgumentType::INT) {
              if (arg[j].intArg.vectorIntArgument.stored) {
                  arg[j].intArg.vectorIntArgument.storedVector->push_back(stoi(inputData));
              } else {
                  arg[j].intArg.vectorIntArgument.unstoredVector->push_back(stoi(inputData));
              }
          } else {
              if (arg[j].stringArg.vectorStringArgument.stored) {
                  arg[j].stringArg.vectorStringArgument.storedVector->push_back(inputData);
              } else {
                  arg[j].stringArg.vectorStringArgument.unstoredVector->push_back(inputData);
              }
          }
          break;
        }
      }
}


void ArgumentParser::ArgParser::processValue(Argument& argument, const std::string& value) {
    if (argument.argClass == ArgumentType::INT) { // process int
        int intValue = std::stoi(value);
        if (argument.intArg.intArgumentQuantity == ArgumentType::SIMPLE) { // simple int
            if (argument.intArg.stored) {
                (*argument.intArg.storedValue) = intValue;
            } else {
                if (argument.intArg.unstoredValue == nullptr) {
                    argument.intArg.unstoredValue = new int(intValue);
                } else {
                    (*argument.intArg.unstoredValue) = intValue;
                }
            }
        } else { //multy string
            if (argument.intArg.vectorIntArgument.stored) {
                argument.intArg.vectorIntArgument.storedVector->push_back(intValue);
            } else {
                argument.intArg.vectorIntArgument.unstoredVector->push_back(intValue);
            }
        }
    } else if (argument.argClass == ArgumentType::STRING) { // process string
        if (argument.stringArg.intArgumentQuantity == ArgumentType::SIMPLE) { // simple string
            if (argument.stringArg.stored) {
                (*argument.stringArg.storedValue) = value;
            } else {
                if (argument.stringArg.unstoredValue == nullptr) {
                    argument.stringArg.unstoredValue = new std::string(value);
                } else {
                    (*argument.stringArg.unstoredValue) = value;
                }
            }
        } else { // multy string
            if (argument.stringArg.vectorStringArgument.stored) {
                argument.stringArg.vectorStringArgument.storedVector->push_back(value);
            } else {
                argument.stringArg.vectorStringArgument.unstoredVector->push_back(value);
            }
        }
    }
}

void ArgumentParser::ArgParser::processShortArg(std::string inputData, bool& ISFLAG_) {
    int i = 1;
    std::string data1;

    while (i < inputData.size() && inputData[i] != '=') {// take flag's name
        data1.push_back(inputData[i]);
        i++;
    }

    if (i == inputData.size()) {// flag w/o value (arg is flag)
        for (char flag : data1) {
            for (int j = 0; j < arg.size(); j++) {
                if (arg[j].argumentShortName == flag) {
                    if (arg[j].flagArg.stored) {
                        (*arg[j].flagArg.storedFlag) = true;
                    } else {
                        if (arg[j].flagArg.unstoredFlag == nullptr) {
                            arg[j].flagArg.unstoredFlag = new bool(true);
                        } else {
                            (*arg[j].flagArg.unstoredFlag) = true;
                        }
                    }
                    if (arg[j].argClass == ArgumentType::FLAG) {
                        ISFLAG_ = true;
                    }
                    break;
                }
            }
        }
    } else { 
        i++;
        std::string data2 = inputData.substr(i);
        for (int j = 0; j < arg.size(); j++) { // process the value 
            if (arg[j].argumentShortName == data1[0]) {
                processValue(arg[j], data2); 
                break;
            }
        }
    }
}

void ArgumentParser::ArgParser::processLongArg(std::string inputData, bool& ISFLAG_) {
    int i = 2;
    std::string data1;
    while (i < inputData.size() && inputData[i] != '=') { // take flag's name
        data1.push_back(inputData[i]);
        i++;
    }
    if (i == inputData.size()) { // flag w/o value (arg is flag)
        for (int j = 0; j < arg.size(); j++) {
            if (arg[j].argumentName == data1) {
                if (arg[j].flagArg.stored) {
                    (*arg[j].flagArg.storedFlag) = true;
                } else {
                    if (arg[j].flagArg.unstoredFlag == nullptr) {
                        arg[j].flagArg.unstoredFlag = new bool(true);
                    } else {
                        (*arg[j].flagArg.unstoredFlag) = true;
                    }
                }
                if (arg[j].argClass == ArgumentType::FLAG) {
                    ISFLAG_ = true;
                }
                break;
            }
        }
    } else { // flag w value (value = data2)
        i++;
        std::string data2 = inputData.substr(i); 
        for (int j = 0; j < arg.size(); j++) { // process the value 
            if (arg[j].argumentName == data1) {
                processValue(arg[j], data2);
                break;
            }
        }
    }
}

bool ArgumentParser::ArgParser::Parse(int argc, char** argv)  {
  std::vector<std::string> inputData;
    for (int i = 0; i < argc; i++) {
      inputData.push_back(argv[i]);
    }

    return Parse(inputData);
}

bool ArgumentParser::ArgParser::Parse(const std::vector<std::string>& inputData) { 
    bool ISFLAG_ = false;
    if (inputData.size() == 2) {
      if (inputData[1] == "--help") {
        Help();
        return true;
      }
    }

    for (int i = 1; i < inputData.size(); i++) { 
        if (inputData[i][0] != '-') {
            processPositionalArg(inputData[i]);
        } else if (inputData[i][1] != '-') {
            processShortArg(inputData[i], ISFLAG_);
            // checking next arg:
            if (i + 1 < inputData.size() && inputData[i + 1][0] != '-') {
                processShortArg(inputData[i] + "=" + inputData[i + 1], ISFLAG_); // process with value (for case: value w/o =)
                if (!ISFLAG_) {
                    i++; 
                }
            }
        } else {
            processLongArg(inputData[i], ISFLAG_);
            // checking next arg:
            if (i + 1 < inputData.size() && inputData[i + 1][0] != '-') {
                processLongArg(inputData[i] + "=" + inputData[i + 1], ISFLAG_); // process with value (for case: value w/o =)
                if (!ISFLAG_) {
                    i++; 
                }
            }
        }
    } 
    return validate();
}