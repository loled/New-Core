/*
  _____                        ____              
 |  ___| __ ___ _______ _ __  / ___|___  _ __ ___
 | |_ | '__/ _ \_  / _ \ '_ \| |   / _ \| '__/ _ \
 |  _|| | | (_) / /  __/ | | | |__| (_) | | |  __/
 |_|  |_|  \___/___\___|_| |_|\____\___/|_|  \___|
         Lightning speed and strength
                 conjured directly from the depths of logic!  
                        Infusion-WoW 2011 - 2013 (C)
<--------------------------------------------------------------------------->
 - Developer(s): Ghostcrawler336
 - Complete: 100%
 - ScriptName: 'Staff Outfit Vendor'
 - Comment: Untested
<--------------------------------------------------------------------------->
*/
#include "ScriptPCH.h"
 
enum defines
{
   // Game Master Outfit
ADMIN_HEAD = 2586,
ADMIN_CHEST = 11508,
ADMIN_FEET = 12064,
ADMIN_WEAPONS = 100,
   // Admin Outfit
GM_HEAD = 2586,
GM_CHEST = 11508,
GM_FEET = 12064,
GM_WEAPONS = 100
};
 
class npc_staff : public CreatureScript
{
        public:
                npc_staff() : CreatureScript("npc_staff"){}
 
                bool OnGossipHello(Player * pPlayer, Creature * pCreature)
                {
                         if(pPlayer->GetSession()->GetSecurity() < SEC_MODERATOR)
                     pCreature->MonsterWhisper("You're not a staff member!", pPlayer->GetGUID(), true);
                            return false;
                        pPlayer->ADD_GOSSIP_ITEM(4, "Game Master Outfit", GOSSIP_SENDER_MAIN, 0);
                        pPlayer->ADD_GOSSIP_ITEM(4, "Admin Outfit", GOSSIP_SENDER_MAIN, 1);
                        pPlayer->PlayerTalkClass->SendGossipMenu(9425, pCreature->GetGUID());
                        return true;
                }
 
                bool OnGossipSelect(Player * pPlayer, Creature * pCreature, uint32 /*uiSender*/, uint32 uiAction)
                {
                        if(!pPlayer)
                                return true;
                       
                        switch(uiAction)
                        {
                                case 0: // Game Master Outfit
                                         if (pPlayer->GetSession()->GetSecurity() == SEC_GAMEMASTER)
                                        {
                                                pPlayer->AddItem(GM_HEAD, 1);
                                                pPlayer->AddItem(GM_CHEST, 1);
                                                pPlayer->AddItem(GM_FEET, 1 );
                                                pPlayer->AddItem(GM_WEAPONS, 1 );
                                                pCreature->MonsterWhisper("Enjoy your game master outfit!", pPlayer->GetGUID(), true);
                                                pPlayer->PlayerTalkClass->SendGossipMenu(true, 1);
                                        }
                                        else
                                        {
                                                pPlayer->GetSession()->SendNotification("You need to be an game master to view this vendor!");
                                                pPlayer->PlayerTalkClass->SendGossipMenu(true, 1);
                                        }
                                        break;
 
                                case 1:
                                        // Admin Outfit
                 if (pPlayer->GetSession()->GetSecurity() == SEC_ADMINISTRATOR)
                                        {
                                                pPlayer->AddItem(ADMIN_HEAD, 1);
                                                pPlayer->AddItem(ADMIN_CHEST, 1);
                                                pPlayer->AddItem(ADMIN_FEET, 1);
                                                pPlayer->AddItem(ADMIN_WEAPONS, 1);
                                                pCreature->MonsterWhisper("Enjoy your admin outfit!", pPlayer->GetGUID(), true);
                                                pPlayer->PlayerTalkClass->SendGossipMenu(true, 1);
                                        }
                                        else
                                        {
                                                pPlayer->GetSession()->SendNotification("You need to be a admin to view this vendor!");
                                                pPlayer->PlayerTalkClass->SendGossipMenu(true, 1);
                                        }
                                        break;
 
                        }
                        return true;
                }
 
};
 
void AddSC_npc_staff()
{
        new npc_staff();
}