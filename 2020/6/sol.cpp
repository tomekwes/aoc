#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <numeric>


std::set<std::string> string_to_set(std::string i) {

    std::set<std::string> ret;
    for(auto l: i){
       ret.insert(std::string(1,l));
    }

    return ret;
}



struct group {

    std::vector<std::string> raw_answ;
    std::set<std::string> group_total_answ;


    //needed for 1st star
    //putting groups answ to set so that I get all unique replies
    void parse_raw_answ() {

        for(auto a: raw_answ) {
            for( auto single: a){

                group_total_answ.insert(std::string(1,single));

            }
        }

    }

    //needed for 2nd star
    // get every persons answ as set then get intersection of those sets
    std::set<std::string> intersection() {

        //if only one person is in group
        if(raw_answ.size() == 1){
            return string_to_set(raw_answ[0]);
        }

        auto inter = string_to_set(raw_answ[0]); //get 1st set

        for(int i = 1; i < raw_answ.size(); i++){
            
            std::vector<std::string> tmp;
            std::set<std::string> new_person = string_to_set(raw_answ[i]); // get next set
            std::set_intersection(inter.begin(), inter.end(), new_person.begin(), new_person.end(), std::back_inserter(tmp));
            inter = std::set<std::string>(tmp.begin(), tmp.end());

        }


        return inter;
    }    
};


std::vector<group> split_to_groups(std::vector<std::string> input){

    std::vector<group> ret_val;
    
    group tmp;
    for(auto i : input){

        if( i == "") {
            ret_val.push_back(tmp);
            tmp = {};
        }else{

            tmp.raw_answ.push_back(i);
        }

    }
    ret_val.push_back(tmp); // add last group

    return ret_val;
}



int main(){


    std::vector<std::string> input = {
#import "input.txt"
        //"abc",
        //"",
        //"a",
        //"b",
        //"c",
        //"",
        //"ab",
        //"ac",
        //"",
        //"a",
        //"a",
        //"a",
        //"a",
        //"",
        //"b"
    };

    auto groups = split_to_groups(input);

    int star2_cnt = 0;
    for(auto& g: groups) {

        g.parse_raw_answ();
        star2_cnt += g.intersection().size();

    }


    auto cnt = std::accumulate(groups.begin(), groups.end(), 0, [](auto t, auto n) {
                    return t+n.group_total_answ.size();
            });
    

    std::cout << cnt << std::endl;

    std::cout << star2_cnt<< std::endl;

}
