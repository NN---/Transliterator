#ifndef __CONTROLS_H__
#define __CONTROLS_H__

#pragma once

#include "language.h"
#include "storage.h"
#include "global.h"

void InitCmbProfile(
	HWND hWnd,
	int nCurSel = 0,
	const Storage& storage = g_Storage);

void InitCmbDir(
	HWND hWnd,
	int nCurSel = 0,
	const LangProfile* pProfile = g_Language.GetCurProfile());

#endif // __CONTROLS_H__