#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <map>
#include <string>

// returns vetor of maps
auto read_file(std::string fname){

    std::ifstream f(fname);
    
    std::string line = "";

    std::vector<std::string> passports_raw;

    std::string tmp_passport;
    while(std::getline(f, line)){

        

        if( line == "") {
            passports_raw.push_back(tmp_passport);
            tmp_passport = "";
        }else {
        
           tmp_passport += " ";
           tmp_passport += line;

        }

    }
    
    passports_raw.push_back(tmp_passport);

    std::vector<std::map<std::string, std::string>> passports_parsed; 

    for(auto e: passports_raw){

        std::vector<std::string> pairs;
        boost::split(pairs, e, boost::is_any_of(" "));

        std::map<std::string, std::string> passport_fields;
        for ( auto pair: pairs ){

            if (pair != ""){ // because of += " " few lines above need to skip leading empty line
            std::vector<std::string> key_value;
            boost::split(key_value, pair, boost::is_any_of(":"));
            
            passport_fields[key_value[0]] = key_value[1];
            }
        }

        passports_parsed.push_back(passport_fields);

    }

    return passports_parsed;

}

bool validate_passport(std::map<std::string, std::string> passport){


    bool byr = std::any_of(passport.begin(), passport.end(), [](std::pair<const std::string,std::string> &entry){return (entry.first == "byr");});
    bool iyr = std::any_of(passport.begin(), passport.end(), [](std::pair<const std::string,std::string> &entry){return (entry.first == "iyr");});
    bool eyr = std::any_of(passport.begin(), passport.end(), [](std::pair<const std::string,std::string> &entry){return (entry.first == "eyr");});
    bool hgt = std::any_of(passport.begin(), passport.end(), [](std::pair<const std::string,std::string> &entry){return (entry.first == "hgt");});
    bool hcl = std::any_of(passport.begin(), passport.end(), [](std::pair<const std::string,std::string> &entry){return (entry.first == "hcl");});
    bool ecl = std::any_of(passport.begin(), passport.end(), [](std::pair<const std::string,std::string> &entry){return (entry.first == "ecl");});
    bool pid = std::any_of(passport.begin(), passport.end(), [](std::pair<const std::string,std::string> &entry){return (entry.first == "pid");});

    return byr && iyr && eyr && hgt && hcl && ecl && pid;
}

//byr (Birth Year) - four digits; at least 1920 and at most 2002.
//iyr (Issue Year) - four digits; at least 2010 and at most 2020.
//eyr (Expiration Year) - four digits; at least 2020 and at most 2030.
//hgt (Height) - a number followed by either cm or in:
//If cm, the number must be at least 150 and at most 193.
//If in, the number must be at least 59 and at most 76.
//hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f.
//ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth.
//pid (Passport ID) - a nine-digit number, including leading zeroes.
//cid (Country ID) - ignored, missing or not.

bool validate_passport2(std::map<std::string, std::string> passport){

    bool byr = false;
    bool iyr = false;
    bool eyr = false;
    bool hgt = false;
    bool hcl = false;
    bool ecl = false;
    bool pid = false;


    if (validate_passport(passport)){

        if(std::stoi(passport["byr"]) >= 1920 && std::stoi(passport["byr"]) <=  2002){
            byr = true; 
        }

        if(std::stoi(passport["iyr"]) >= 2010 && std::stoi(passport["iyr"]) <=  2020){
            iyr = true; 
        }

        if(std::stoi(passport["eyr"]) >= 2020 && std::stoi(passport["eyr"]) <=  2030){
            eyr = true; 
        }

        if(auto index = passport["hgt"].find("cm", 0); index != std::string::npos ){

            auto height = std::stoi(std::string(passport["hgt"].begin(), passport["hgt"].begin()+index));
            if (height >= 150 && height <= 193) hgt = true; 
        }

        if(auto index = passport["hgt"].find("in", 0); index != std::string::npos ){

            auto height = std::stoi(std::string(passport["hgt"].begin(), passport["hgt"].begin()+index));
            if (height >= 59 && height <= 76 ) hgt = true; 
        }

        if( passport["hcl"].size() == 7){
            for (char letter: passport["hcl"]) {
                if((letter <= 48 && letter < 58) || (letter <= 65 && letter < 71) || (letter <= 97 && letter < 103) ){
                    hcl = true;
                }
            }
        }

        if( passport["ecl"] == "amb" || passport["ecl"] == "blu" ||passport["ecl"] == "brn" ||passport["ecl"] == "gry" ||passport["ecl"] == "hzl" ||passport["ecl"] == "oth" ||passport["ecl"] == "grn" )
        {
            ecl = true;
        }

        if( passport["pid"].size() == 9) pid = true;
    }

    return byr && iyr && eyr && hgt && hcl && ecl && pid;
}

int main(){

    auto passports = read_file("input.txt");


   
    int valid_cnt = 0;
    int total = 0;
    for( auto p: passports){

        total++;
        if( validate_passport2(p)){

            valid_cnt++;
        }

    }


    std::cout << valid_cnt << std::endl;
    std::cout << total << std::endl;
    

}
