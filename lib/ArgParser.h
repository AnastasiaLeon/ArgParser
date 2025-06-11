#pragma once

#include <iostream>
#include <vector>
#include <string>

namespace ArgumentParser {

enum ArgumentType {
  INT,
  STRING,
  FLAG,
  SIMPLE,
  MULTY
};

class StringVectorArgument {
public:
  int minsize;
  bool positional, stored = false;
  std::vector<std::string>* unstoredVector = new std::vector<std::string>;
  std::vector<std::string>* storedVector = nullptr;

  StringVectorArgument();
  ~StringVectorArgument();
  void SetMinsize(int minSize);
  StringVectorArgument& StoreValues(std::vector<std::string>& vect);
  StringVectorArgument& StoreValue(std::vector<std::string>& vect);
  StringVectorArgument& Positional();
  bool IsPositional();
  StringVectorArgument(const StringVectorArgument& base);
  void operator =(const StringVectorArgument& base);
};

class StringArgument {
public:
  ArgumentType intArgumentQuantity = ArgumentType::SIMPLE;
  StringVectorArgument vectorStringArgument;
  bool stored;
  std::string* storedValue = nullptr;
  std::string* unstoredValue = nullptr;

  StringArgument();
  ~StringArgument();
  StringVectorArgument& MultiValue();
  StringVectorArgument& MultiValue(int minSize);
  StringArgument& StoreValue(std::string& value);
  StringArgument& Default(const std::string& value);
  bool IsPositional();
  StringArgument(const StringArgument& base);
};


class IntVectorArgument {
public:
  int minsize;
  bool positional, stored = false;
  std::vector<int>* unstoredVector = nullptr;
  std::vector<int>* storedVector = new std::vector<int>();
  
  IntVectorArgument();
  ~IntVectorArgument();
  void SetMinsize(int minSize);
  IntVectorArgument& StoreValues(std::vector<int>& vc);
  IntVectorArgument& StoreValue(std::vector<int>& vc);
  IntVectorArgument& Positional();
  bool IsPositional();
  IntVectorArgument(const IntVectorArgument& base);
};


class IntArgument {
public:
  ArgumentType intArgumentQuantity = ArgumentType::SIMPLE;
  IntVectorArgument vectorIntArgument;
  int* unstoredValue = nullptr;
  int* storedValue = nullptr;
  bool stored = false;

  IntArgument();
  ~IntArgument();
  IntVectorArgument& MultiValue();
  IntVectorArgument& MultiValue(int minSize);
  IntArgument& Default(const int& value);//
  IntArgument& StoreValue(int& value);//
  bool IsPositional();
  IntArgument(const IntArgument& base);
};

class FlagArgument {
public:
  bool stored = false;
  bool* unstoredFlag = nullptr;
  bool* storedFlag = nullptr;

  FlagArgument();
  FlagArgument& Default(bool f);
  FlagArgument& StoreValue(bool& f);
};

class Argument {
private:
    std::string help;
    
public:
    std::string argumentName;
    char argumentShortName;
    ArgumentType argClass;
    FlagArgument flagArg;
    IntArgument intArg;
    StringArgument stringArg;

    Argument(ArgumentType argCl, const std::string& name, char shortName = ' ', const std::string& helpForArg = "");
    bool IsPositional();
};


class ArgParser {
 private:
  std::string name;//argument name
  std::vector<Argument> arg;//vector for objects (class argument)
  char helpChar = ' ';//short help
  std::string helpString1 = "";//help header
  std::string helpString2 = "";//help text

 public:
  IntArgument& AddIntArgument(const std::string& name);
  IntArgument& AddIntArgument(char shortName, const std::string& name, const std::string& helpForInt);
  IntArgument& AddIntArgument(char shortName, const std::string& name);
  IntArgument& AddIntArgument(const std::string& name, const std::string& helpForInt);
  StringArgument& AddStringArgument(const std::string& name);
  StringArgument& AddStringArgument(char shortName, const std::string& name);
  StringArgument& AddStringArgument(char shortName, const std::string& name, const std::string& helpForString);
  FlagArgument& AddFlag(const std::string& name, const std::string& helpForFlag = "", char shortName = ' ');
  FlagArgument& AddFlag(char shortName, const std::string& name, const std::string& helpForFlag = "");
  ArgParser(const std::string& argName);
  std::string GetStringValue(const std::string& argName);
  int GetIntValue(const std::string& argName, int j = -1);
  bool GetFlag(const std::string& argName);
  bool Help();
  void AddHelp(char h, const std::string& hp1, const std::string& hp2);
  std::string HelpDescription();
  bool Parse(const std::vector<std::string>& inputData); //vector of strings
  bool Parse(int argc, char** argv);
  void processPositionalArg(std::string inputData);
  void processShortArg(std::string inputData, bool& ISFLAG_);
  // void processShortArg(std::string inputData);
  void processLongArg(std::string inputData, bool& ISFLAG_);
  // void processLongArg(std::string inputData);
  void processArg(std::string flagName, std::string value = "");
  bool validate();
  bool validateStringArgument(const Argument& argument);
  bool validateIntArgument(const Argument& argument);
  void processValue(Argument& argument, const std::string& value);
};
} //namespace ArgumentParser