#include <stdio.h>
#include <assert.h>

unsigned search(char *s, unsigned len) {
  if (len<3)
    return len; // not found
  unsigned seen=0;
  for (unsigned i=0; i<len; i++) {
    char ch=s[i];                 // других чтений s[...] не должно быть
    if (seen==0 && ch=='+')
            seen=1;
    else if (seen==1 && ch=='+')
            seen=2;
    else if (seen==2 && ch=='x')
            return i-2;  // found
    else if (seen==2 && ch=='+')
            seen=2;
    else
            seen=0;    // reset
  }
  return len;                // not found
}

unsigned naive_search(char *s, unsigned len) {
  if (len < 3)
    return len;
  for (unsigned i = 0; i + 2 < len; i++) {
    if (s[i] == '+' && s[i + 1] == '+' && s[i + 2] == 'x')
      return i;
  }
  return len;
}

int main() {
  char s[LEN];
  unsigned len;
  __CPROVER_assume(len <= LEN);
  assert(search(s, len) == naive_search(s, len));
  return 0;
}
