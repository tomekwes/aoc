#include <iostream>
#include <vector>

int star1(std::vector<int> input){

// not the best solution but easy one for sure
    for( int i=0; i < input.size(); i ++){
        
        for(int j=i+1; j < input.size(); j++){

            if (input[i] + input[j] == 2020) {

                return input[i] * input[j] ;


            }

        }

    }

    return -1;
}


int star2(std::vector<int> input){

    // not the best solution but easy one for sure
    for( int i=0; i < input.size(); i ++){

        for(int j=0; j < input.size(); j++){

            for(int k=0; k < input.size(); k++){
                if (input[i] + input[j] + input[k] == 2020) {

                    return input[i] * input[j] * input[k];


                }

            }

        }

    }
    return -1;
}

int main(){


    std::vector<int> input = { 
        #include "input.txt"
    };


    std::cout << star1(input) << std::endl;
    std::cout << star2(input) << std::endl;

}
