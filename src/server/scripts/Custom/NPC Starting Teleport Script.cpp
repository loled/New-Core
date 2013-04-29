#include "ScriptPCH.h"

enum Spells
{
  SPELL_Teleport_to_Gunship_QuestArea = 95066,
	SPELL_Teleport_to_Mall_Boring = 95065
};

class gunship_teleport : public CreatureScript
{
public:
	gunship_teleport() : CreatureScript("gunship_teleport") { }

	bool OnGossipHello(Player* player, Creature* creature)
	{
		if(player->isInCombat())
			return false;

		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I want to get teleported to the gunship quest area, and do the journeys and have a nice time on the gunship, AND get my useful reward when I'm done.!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I dont want to do the journeys AND get an useful reward. I want to skip all that, and go right ahead to the mall.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
		player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player* player, Creature* creature, uint32 uiSender, uint32 uiAction)
	{
		player->PlayerTalkClass->ClearMenus();

		if(uiSender != GOSSIP_SENDER_MAIN)
			return false;

		switch(uiAction)
		{
		case GOSSIP_ACTION_INFO_DEF+1:
			player->CastSpell(player, SPELL_Teleport_to_Gunship_QuestArea, true);
			player->CLOSE_GOSSIP_MENU();
			break;

		case GOSSIP_ACTION_INFO_DEF+2:
			player->CastSpell(player, SPELL_Teleport_to_Mall_Boring, true);
			player->CLOSE_GOSSIP_MENU();
			break;

		default:
			OnGossipHello(player, creature);
			break;
		}
		return true;
	}
};
void AddSC_gunship_teleport()
{
	new gunship_teleport;
}
