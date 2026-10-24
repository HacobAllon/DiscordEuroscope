/*
	Copyright(C) 2023-2024 Kirollos Nashaat

	This program is free software : you can redistribute it and /or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.If not, see < https://www.gnu.org/licenses/>.
*/
#pragma once
#include "inc\\3.2\\EuroScopePlugIn.h"
#include "inc\\discord_rpc.h"
#include "ConfigManager.h"
#include "WebhookSender.h"
#include <vector>
#include <map>
#include <fstream>

#ifndef __E_KEK_H
#define __E_KEK_H

class DiscordEuroscopeExt : public EuroScopePlugIn::CPlugIn
{
public:
	DiscordEuroscopeExt();
	virtual ~DiscordEuroscopeExt();
	virtual bool OnCompileCommand(const char* sCommandLine);
	virtual void OnCompilePrivateChat(const char* sSenderCallsign, const char* sReceiverCallsign, const char* sChatMessage);
	int EuroInittime;

	int CountACinRange();
	int CountTrackedAC();
	void CheckWineBridge(bool announce_ok);
	std::vector<std::string> tracklist;
	DiscordEuroScope_Configuration::ConfigManager config;

private:
	void SendToWebhook(const std::string& sender, const std::string& message);
	bool TestWebhook();
	std::string WebhookUsername();
	static std::string FormatChatLine(const std::string& format, const std::string& sender, const std::string& message, const std::string& time);
	WebhookSender webhook;
};

extern DiscordEuroscopeExt* pMyPlugIn;

//#define DISCORDTIMERID (0xb00b)
extern UINT_PTR DISCORDTIMERID;
VOID CALLBACK DiscordTimer(_In_ HWND hwnd, _In_ UINT uMsg, _In_ UINT_PTR idEvent, _In_ DWORD dwTime);

#endif __E_KEK_H