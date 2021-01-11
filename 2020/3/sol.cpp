#include <iostream>
#include <string>
#include <vector>


int main(){



    std::vector<std::string> input = {
        #include "input.txt"
    };


    const int width = input[0].size();
    const int height = input.size();


            std::cout << height << " x " << width << std::endl;


    struct move {

        int right = 0;
        int left = 0;
    };

    std::vector<move> moves = {{1,1}, {3,1} , {5,1}, {7,1}, {1,2} } ;
    std::vector<int> solutions;

    
    for(auto m: moves) {

        int tree_cnt = 0;
        int w = 0;
        int h = 0;

        while ( h < height ){

            if (input[h][w % width] == '#'){


                tree_cnt++;

            }


            w+=m.right;
            h+=m.left;


        }

        solutions.push_back(tree_cnt);
    }

    long mul_solutions = 1;
    for( auto s: solutions){

        std::cout << s << std::endl;
        mul_solutions = mul_solutions *  s;
    }

    std::cout << "-> " << mul_solutions << " <-"  <<std::endl;
    std::cout << sizeof(long long) << std::endl;
}
