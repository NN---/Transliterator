#ifndef __PROGCOMMANDLINE_H__
#define __PROGCOMMANDLINE_H__

#include "WindowState.h"

typedef WindowState ProgCommandLineInfo;

class ProgCommandLine : public NN::CommandLine<ProgCommandLineInfo>
{
	struct ParseCommandLineStruct
	{
		TCHAR szCmdLine[10];
		CommandLineInfoType cmdInfo;
	};
public:
	ProgCommandLine()
	{
		SetCommandLine(GetCommandLine());
		ParseCommandLine();
	}
	void ParseCommandLine()
	{
		static const ParseCommandLineStruct aParseCommandLine[]=
		{
			{_T("-min"),{SW_SHOWMINIMIZED}},
			{_T("-max"),{SW_SHOWMAXIMIZED}},
			{_T("-hide"),{SW_HIDE}}
		};
		for(int i=1;i<GetArgc();i++)
			for(int j=0;j<sizeof(aParseCommandLine)/sizeof(ParseCommandLineStruct);j++)
				if(!lstrcmp(GetArgv(i),aParseCommandLine[j].szCmdLine))
				{
					CommandLineInfo()=aParseCommandLine[j].cmdInfo;
					return;
				}
		CommandLineInfo().Reset();
	}
};

#endif // __PROGCOMMANDLINE_H__