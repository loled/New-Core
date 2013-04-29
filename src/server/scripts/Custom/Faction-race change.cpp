/*
<--------------------------------------------------------------------------->
 - Developer(s): Ghostcrawler336
 - Complete: 100%
 - ScriptName: 'Faction / Race Changer' 
 - Comment: Untested
<--------------------------------------------------------------------------->
*/
#include "ScriptPCH.h"

enum  defines
{
 faction_token = 888999, // Faction Change Token
 race_token = 888998 // Race Change Token
};

class npc_changer : public CreatureScript
{
	public:
		npc_changer() : CreatureScript("npc_changer"){}

		bool OnGossipHello(Player * pPlayer, Creature * pCreature)
		{
			
			
			pPlayer->ADD_GOSSIP_ITEM(4, "Change My Race 5 Tokens", GOSSIP_SENDER_MAIN, 0);
		    pPlayer->ADD_GOSSIP_ITEM(4, "Change My Faction 10 Tokens", GOSSIP_SENDER_MAIN, 1);
			pPlayer->PlayerTalkClass->SendGossipMenu(9425, pCreature->GetGUID());
			return true;
		}

		bool OnGossipSelect(Player * Player, Creature * Creature, uint32 /*uiSender*/, uint32 uiAction)
		{
			if(!Player)
				return true;

			switch(uiAction)
			{
				case 0:
					if(Player->HasItemCount(race_token, 5))
					{
						Player->DestroyItemCount(race_token, 5, true, true);
						Player->DestroyItemCount(race_token, 5, true, false);
						Player->SetAtLoginFlag(AT_LOGIN_CHANGE_RACE);
						CharacterDatabase.PExecute("UPDATE characters SET at_login = at_login | '128' WHERE guid = %u", Player->GetGUID());
						Player->GetSession()->SendNotification("You need to relog, to change your race!");
						Player->PlayerTalkClass->CloseGossip();
					}
					else
					{
						Player->GetSession()->SendNotification("You need atleast 5 race change token!");
						Player->PlayerTalkClass->CloseGossip();
					}
					break;
				case 1:
					if(Player->HasItemCount(faction_token, 10))
					{
						Player->DestroyItemCount(faction_token, 10, true, true);
						Player->DestroyItemCount(faction_token, 10, true, false);
						Player->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
						CharacterDatabase.PExecute("UPDATE characters SET at_login = at_login | '64' WHERE guid = %u", Player->GetGUID());
						Player->GetSession()->SendNotification("You need to relog, to change your faction!");
						Player->PlayerTalkClass->CloseGossip();

					}

					else
					{
						Player->GetSession()->SendNotification("You need atleast 10 faction change token!");
						Player->PlayerTalkClass->CloseGossip();
					}
					break;
			}
			return true;
		}

};

void AddSC_npc_changer()
{
	new npc_changer();
}
