#pragma once
#ifndef _WEBHOOKSENDER_H_
#define _WEBHOOKSENDER_H_

#include <string>
#include <deque>
#include <mutex>
#include <condition_variable>
#include <thread>

// Posts chat lines to a Discord webhook on a background thread,
// so EuroScope never waits on the network.
class WebhookSender
{
public:
	WebhookSender();
	~WebhookSender();

	// Lines are in the system ANSI code page (as EuroScope gives them).
	void Enqueue(const std::string& url, const std::string& username, const std::string& line);
	void Stop();

private:
	struct Item
	{
		std::string url;
		std::string username;
		std::string line; // UTF-8
	};

	void Run();
	static bool Post(const std::string& url, const std::string& username, const std::string& content);

	std::deque<Item> queue;
	std::mutex lock;
	std::condition_variable wake;
	bool stopping = false;
	std::thread worker;
};

#endif
