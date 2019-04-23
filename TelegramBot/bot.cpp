#include <cstdio>
#include <tgbot/tgbot.h>
#include <string> 
#include <iostream>
#include <progbase/console.h>  

int main()
{
    std::string console_msg;
    TgBot::Message::Ptr g_message;
    getline(std::cin, console_msg);     
    TgBot::Bot bot("624807853:AAFpoKOjWkpGqXcbtCdhRAoORvllck13X8A");
    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Hi!");
    });//@todo learn this shit
    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        printf("User wrote %s\n", message->text.c_str());
        if (StringTools::startsWith(message->text, "/start"))
        {
            return;
        }
        bot.getApi().sendMessage(message->chat->id, "Your message is: " + message->text);
    });
    try
    {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(bot);
        while (true)
        {
            printf("Long poll started\n");
            longPoll.start();            
        }
    }
    catch (TgBot::TgException &e)
    {
        printf("error: %s\n", e.what());
    }
    return 0;
}