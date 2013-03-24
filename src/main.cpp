#include "tirclib.h"

int main()
{
    std::shared_ptr<IrcConnection> conn(new IrcConnection("irc.rizon.net", 6667, "tircbot", "tircbot"));
    conn->AddHandler(REPLY_PRIVMSG, [](IrcMessage const& msg) { std::cout << msg.full << std::endl; });
    conn->Connect();
    return 0;
}
