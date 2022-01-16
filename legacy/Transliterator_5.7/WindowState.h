#ifndef __WINDOWSTATE_H__
#define __WINDOWSTATE_H__

struct WindowState
{
	int nCmdShow;
	void Reset()
	{ nCmdShow=SW_SHOWNORMAL; }
	const bool IsDefault() const
	{ return nCmdShow==SW_SHOWNORMAL; }
	const bool operator==(const WindowState& state) const
	{ return nCmdShow==state.nCmdShow; }
};

#endif // __WINDOWSTATE_H__