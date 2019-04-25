// #include <cstdio>
#include <tgbot/tgbot.h>
#include <string> 
#include <iostream>
#include <progbase/console.h>  



int main()
{     
    int id = 0;
    TgBot::Bot bot("624807853:AAFpoKOjWkpGqXcbtCdhRAoORvllck13X8A");
    bot.getEvents().onCommand("start", [&bot, &id](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Hi!"); 
        id = message->chat->id; 
    });
    bot.getEvents().onAnyMessage([&bot, &id](TgBot::Message::Ptr message) {
        // printf("User wrote %s\n", message->text.c_str());
        // if (StringTools::startsWith(message->text, "/start"))
        // {
        //     return;
        // }
        std::string msg; 
        id = message->chat->id;
        getline(std::cin, msg);  
        bot.getApi().sendMessage(message->chat->id, "Your message is: " + msg);
    });
    try
    {
        // printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(bot);
        while (true)
        {
            printf("Long poll started\n");
            longPoll.start();                        
            if (id != 0)
                break;
        } 
        while(true) {
            std::string msg;
            getline(std::cin, msg); 
            bot.getApi().sendMessage(id, "Your message is: " + msg);

        }
    }
    catch (TgBot::TgException &e)
    {
        printf("error: %s\n", e.what());
    }
    return 0;
}