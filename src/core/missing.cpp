#include "paragui.h"

#ifndef HAVE_STRDUP
char *strdup(char *s) {
	if(s == NULL) {
		return NULL;
	}
	
	int l = strlen(s) + 1;
	char *ret = (char *)malloc(l);
	if (ret) {
		strcpy(ret,s);
	}
	return ret;
}
#endif
