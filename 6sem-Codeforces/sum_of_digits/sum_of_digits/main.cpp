//
//  main.cpp
//  sum_of_digits
//
//  Created by Anton Karazeev on 19/08/2017.
//  Copyright © 2017 Anton Karazeev. All rights reserved.
//

/*
in:
4
9 81
12 9
6 10
7 9

out:
9
No solution
1122
111112
*/

#include <iostream>
#include <vector>

int main(){
    int max_len = 100; // max number of digits
    int max_sum = 9 * max_len; // max sum of digits
    int max_sq_sum = 81 * max_len; // max sum of squares

    /* Dynamic programming */
    std::vector<std::vector<int> > table(max_sum, std::vector<int> (max_sq_sum, -1)); // initialize matrix with -1
    table[0][0] = 0;
    
    for (int i = 1; i < max_sum; ++i){
        for (int j = 1; j < max_sq_sum; ++j){
            for (int digit = 1; digit <= 9; ++digit){
                if (i >= digit && j >= (digit * digit) && table[i - digit][j - (digit * digit)] != -1) {
                    int tmp = 1 + table[i - digit][j - (digit * digit)]; // increase prev value by 1
                    
                    if (tmp <= max_len && (table[i][j] == -1 || tmp < table[i][j])) {
                        table[i][j] = tmp; // length of number with sum of digits i and sum of squares j
                    }
                }
            }
        }
    }
    
    int n; // number of tests
    std::cin >> n;
    
    std::vector<std::pair<int, int> > tests;
    
    /* Read input */
    for (int i = 0; i < n; ++i) {
        int s1;
        int s2;
        std::cin >> s1;
        std::cin >> s2;
        
        tests.push_back({s1, s2});
    }
    
    /* Main part */
    for (auto& iter : tests) {
        int s1 = iter.first;
        int s2 = iter.second;

        if(s1 > max_sum - 1 or s2 > max_sq_sum - 1 or table[s1][s2] == -1) {
            std::cout << "No solution" << std::endl;
        } else{
            // move to the left upper corner while it is possible
            while(s1 != 0 || s2 != 0){
                // iterate from the lowest digit -- 1
                for(int digit = 1; digit <= 9; ++digit){
                    if(s1 >= digit and s2 >= digit * digit and table[s1][s2] == 1 + table[s1 - digit][s2 - (digit * digit)]){
                        std::cout << char('0' + digit);
                        
                        s1 -= digit;
                        s2 -= digit * digit;
                        
                        break;
                    }
                }
            }
            std::cout << std::endl;
        }
    }
    return 0;
}
