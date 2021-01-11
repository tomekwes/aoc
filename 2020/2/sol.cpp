#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>


struct db_entry{

    int range_low = 0;
    int range_high = 0;
    std::string rule = "";
    std::string password = "";

};


bool validation_star1(db_entry ent) {

    int cnt = 0;
    for(auto letter: ent.password){

        if (std::string(1,letter) == ent.rule){
            cnt++;
        }

    }

    if (cnt >= ent.range_low && cnt <= ent.range_high) {
        return true;
    }


    return false; // password not valid
}

bool validation_star2(db_entry ent) {

    bool left = (std::string(1,ent.password[ent.range_low-1]) == ent.rule);

    bool right = (std::string(1,ent.password[ent.range_high-1]) == ent.rule);

    
    // the idea is to XOR it
    return left != right;

}

std::vector<db_entry> read_file(std::string fname) {


    std::vector<db_entry> output;

    std::ifstream f(fname);
    
    std::string line = "";

    while(std::getline(f, line)){

        db_entry tmp;

        // line should look like 
        // <range_low>-<range_high> <rule>: <password>

        auto it_low = line.find('-');
        tmp.range_low = std::stoi(line.substr(0, it_low));
        auto it_high = line.find_first_of(' '); 
        tmp.range_high = std::stoi(std::string(line.begin() + it_low+1, line.begin()+ it_high) );

        tmp.rule = std::string(line.begin() + it_high+1, line.begin()+ it_high+2 );
        
        tmp.password = std::string(line.begin()+it_high+4, line.end());

        std::cout << tmp.password << std::endl;

        output.push_back(tmp);

    }


    return output;



}

int main(){

    
    auto input = read_file("input.txt");



    int valid_passwords = 0;
    int valid_passwords2 = 0;
    for (auto i: input){

       if (validation_star1(i)){ valid_passwords++;} 
       if (validation_star2(i)){ valid_passwords2++;} 

    }


    std::cout << valid_passwords << std::endl;
    std::cout << valid_passwords2 << std::endl;

}

