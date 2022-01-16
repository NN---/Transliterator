#ifndef __TRANSLITCOMMANDLINE_H__
#define __TRANSLITCOMMANDLINE_H__

#include <NN/CommandLine.h>

typedef WindowState TranslitCommandLineInfo;

class TranslitCommandLine : public CommandLine<TranslitCommandLineInfo>
{
	struct ParseCommandLineStruct
	{
		TCHAR szCmdLine[10];
		CommandLineInfoType cmdInfo;
	};
public:
	TranslitCommandLine()
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
		CommandLineInfo()=CommandLineInfoType::Default();
	}
};

#endif __TRANSLITCOMMANDLINE_H__