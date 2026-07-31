#include <string.h> 
#include <stdlib.h> 
int max(int a, int b) {
    return (a > b) ? a : b;
}

int lengthOfLongestSubstring(char * s){
    int n = strlen(s); 
    if (n == 0) {
        return 0;
    }
    int char_index[128]; 
    for (int i = 0; i < 128; i++) {
        char_index[i] = -1;
    }

    int max_length = 0; 
    int left = 0;      
    for (int right = 0; right < n; right++) {
        char current_char = s[right];
        int prev_index = char_index[(unsigned char)current_char];
        if (prev_index != -1 && prev_index >= left) {
            left = prev_index + 1;
        }
        char_index[(unsigned char)current_char] = right;

        max_length = max(max_length, right - left + 1);
    }
    
    return max_length; 
}