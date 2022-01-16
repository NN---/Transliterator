#ifndef __SPLITSTR_H__
#define __SPLITSTR_H__

inline void splitstr(const char* str,char* l,char* r,int nl,int nr,char c)
{
	// left
	if(*str)
		while(*str&&*str!=c&&nl--)
			*l++=*str++;
	*l=0;

	// right
	if(*str)
	{
		str++;
		while(*str&&*str!=c&&nr--)
			*r++=*str++;
	}
	*r=0;
}

#endif // __SPLITSTR_H__