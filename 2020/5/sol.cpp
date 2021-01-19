#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>


int get_row(std::string input){

    int range_lower = 0;
    int range_upper = 127;

    for(int i = 0; i < 7; i++) {

        if(input[i] == 'F'){

            int middle = floor((range_upper + range_lower)/2.0);

            range_upper = middle;
        }

        if(input[i] == 'B'){
            int middle = ceil((range_upper + range_lower)/2.0);

            range_lower = middle;

        }

    }

    return range_lower;
}


int get_collumn(std::string input){

    int range_lower = 0;
    int range_upper = 7;

    for(int i = 7; i <= 9; i++) {


        if(input[i] == 'L'){

            int middle = floor((range_upper + range_lower)/2.0);

            range_upper = middle;

        }

        if(input[i] == 'R'){
            int middle = ceil((range_upper + range_lower)/2.0);

            range_lower = middle;
        }

    }
    return range_lower;
}

// 2nd type of solution
// convert to binary

int get_row2(std::string input){
    
    std::string row = std::string(input.begin(), input.begin() + 7);

    std::transform(row.begin(), row.end(), row.begin(),
                   [](unsigned char c) -> unsigned char { if(c == 'F') return '0';
                        if(c == 'B') return '1';
                        return c;
                   });


    return std::stoi(row, nullptr, 2);
}
int get_collumn2(std::string input){
    
    std::string row = std::string(input.begin()+7, input.end() );

    std::transform(row.begin(), row.end(), row.begin(),
                   [](unsigned char c) -> unsigned char { if(c == 'L') return '0';
                        if(c == 'R') return '1';
                        return c;
                   });


    return std::stoi(row, nullptr, 2);
}

int main() {


    std::vector<std::string> inputs { 
                        #import "input.txt"
    };

    std::vector<int> hs;

    for (auto i: inputs){

        hs.push_back(get_row2(i) * 8 + get_collumn2(i));

    }


    std::cout << *std::max_element(hs.begin(), hs.end()) << std::endl;

    std::sort(hs.begin(), hs.end());

    int last = hs[0];
    
    for( int i = 1; i < hs.size(); i++){

        if(hs[i-1] + 1 != hs[i] ){

            std::cout << hs[i-1] << " - " << hs[i] << std::endl;

        }

    }

}
