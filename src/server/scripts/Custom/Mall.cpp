/************************************
*        Made by Parranoia          *
*        For Ghost-Gaming           *
*     Released By Ghostcrawler336   *
*************************************
*/
 
#include "ScriptPCH.h"
#include "Chat.h"
 
class cs_mall : public CommandScript
{
        public:
                cs_mall() : CommandScript("cs_mall"){}
 
        ChatCommand * GetCommands() const
        {
                static ChatCommand WorldChatCommandTable[] =
                {
                        {"mall",        0,                              false,          &HandleMallCommand,     "", NULL},
                        {NULL,          0,                              false,          NULL,                                           "", NULL}
                };
 
                return WorldChatCommandTable;
        }
 
        static bool HandleMallCommand(ChatHandler* handler, const char* /*args*/)
        {
                Player* player = handler->GetSession()->GetPlayer();
                if (player->isInCombat())
                {
                        player->GetSession()->SendNotification("You cannot use this in combat!");
                        return false;
                }
 
                if (player->GetTeam() == ALLIANCE)
                        player->TeleportTo(1, -5148.209961f,  -1932.010010f, 89.188103f, 6.194330f);             // Alliance mall coords (MAP, X, Y, Z, O)
                else
                        player->TeleportTo(1,  -5148.209961f, -1932.010010f, 89.188103f, 6.194330f);              // Horde mall coords (MAP, X, Y, Z, O)
                return true;
        }
};
 
void AddSC_cs_mall()
{
        new cs_mall();
}
