#ifndef _HBUILTIN_H_
#define _HBUILTIN_H_

int _myexit(state_t *);
int _mycd(state_t *);
int _myhelp(state_t *);
int _myhistory(state_t *);
int _myalias(state_t *);
int set_alias(state_t *state, char *str);

#endif
