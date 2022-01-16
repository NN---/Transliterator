#ifndef __CHANGE_H__
#define __CHANGE_H__

inline size_t strcpy_change(char** out,const char* in)
{
	char** out_o=out;
	while(*in)
	{
		**out=*in;
		(*out)++;
		in++;
	}
	return *out-*out_o;
}

#endif // __CHANGE_H__