#include <stdio.h>
#include <regex.h>
#include <stdlib.h>

char *cregex = "^[[:alnum:]]*@[[:alnum:]]*.[[:alnum:]]";
char *cline = "nigga@mail.ru";

int main(){
  int res;
  regex_t regex;

  regcomp(&regex, cregex, 0);
  res = regexec(&regex, cline, 0, NULL, 0);
  if(res == 0)
    puts("Match");
  if(res == REG_NOMATCH)
    puts("No mutches");
   regfree(&regex);

  return 0;
}
