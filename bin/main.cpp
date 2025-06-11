#include <functional>
#include <lib/ArgParser.h>

#include <iostream>
#include <numeric>

struct Options {
    bool sum = false;
    bool mult = false;
};

int main(int argc, char** argv) {
    Options opt;
    std::vector<int> values;
    ArgumentParser::ArgParser parser("Program");

    parser.AddIntArgument("N").MultiValue(1).Positional().StoreValues(values);
    parser.AddFlag("sum", "add args").StoreValue(opt.sum);
    parser.AddFlag("mult", "multiply args").StoreValue(opt.mult);
    parser.AddHelp('h', "help", "Program accumulate arguments");

    if(!parser.Parse(argc, argv)) {
        std::cout << "Wrong argument" << std::endl;
        std::cout << parser.HelpDescription() << std::endl;
        return 0;
    }

    // if(parser.Help()) {

    //     std::cout << parser.HelpDescription() << std::endl;
    //     return 0;
    // }

    if(opt.sum) {
        std::cout << "Result: " << std::accumulate(values.begin(), values.end(), 0) << std::endl;
    } else if(opt.mult) {
        std::cout << "Result: " << std::accumulate(values.begin(), values.end(), 1, std::multiplies<int>()) << std::endl;
    } else {
        std::cout << "No one options had chosen" << std::endl;
        std::cout << parser.HelpDescription();
        return 1;
    }

    return 0;

}


//./labwork4 --help
//./labwork4 1 2 3 4 --sum   
//./labwork4 20 100 3 --mult  
//./labwork4 1 2 3 4
//./labwork4 1 2 3 4 --sum --mult
//./labwork4 -n 4 1 2 3 --sum
//./labwork4 --mult 20
//./labwork4 --mult 20 1 0