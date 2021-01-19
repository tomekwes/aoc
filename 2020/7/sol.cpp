#include <boost/algorithm/string/compare.hpp>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/iter_find.hpp>
#include <boost/algorithm/string/finder.hpp>
#include <boost/algorithm/string.hpp>

struct bag {

    int how_many = 0;
    std::string name;

};

void sanitize(std::vector<std::string> input){


    //boost::split(pairs, e, boost::is_any_of(" "));
    //boost::split(key_value, pair, boost::is_any_of(":"));
    for(auto rule: input){
        std::vector<std::string> bag_and_contents;
        boost::iter_split(bag_and_contents, rule, boost::algorithm::first_finder(" contain "));

        std::cout << bag_and_contents[0] << " + " << bag_and_contents[1] << std::endl;
     }


}

int main() {


    std::vector<std::string> input = {
            #include "input.txt"
    };


    sanitize(input);





}
