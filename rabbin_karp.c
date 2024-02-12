#include <stdio.h>
#include <string.h>

#define R 256 //alphabetic len
#define Q 99999997 //num for hash calculation

unsigned get_hash(const char *str, const char *end) {
    unsigned hash = 0;
    while (str < end) {
        hash = (hash * R + *str) % Q;
        str++;
    }
    return hash;
}

unsigned pow_mod(unsigned base, unsigned exp, unsigned mod) {
    unsigned result = 1;
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

unsigned update_hash(unsigned hash, unsigned n, char left, char right) {
    hash = (hash + Q - left * n % Q) % Q; // remove senior symbol
    hash = (hash * R + right) % Q; // add new symbol
    return hash;
}

int rabbin_karp(const char *needle, const char *haystack) {
    unsigned n, target, cur, left, right;
    unsigned len_needle = strlen(needle);
    unsigned len_haystack = strlen(haystack);

    if (len_needle > len_haystack) return -1; //needle longer haystack

    target = get_hash(needle, needle + len_needle);
    cur = get_hash(haystack, haystack + len_needle);
    n = pow_mod(R, len_needle - 1, Q);

    for (left = 0, right = len_needle - 1; right < len_haystack; left++, right++) {
        if (cur == target) { // hashes same 
            if (strncmp(needle, haystack + left, len_needle) == 0) {
                return left; //needle found
            }
        }
        cur = update_hash(cur, n, haystack[left], haystack[right + 1]);
    }

    return -1;
}


int main() {
    char *genius = "Dennis Ritchie is a real genius";
    printf("%d\n", rabbin_karp("real", genius));
    return 0;
}
