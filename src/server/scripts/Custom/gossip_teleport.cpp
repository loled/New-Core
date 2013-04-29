#include "ScriptPCH.h"

enum Spells
{
	SPELL_Teleport_to_theramore = 49359
};

class gossip_teleport : public CreatureScript
{
public:
	gossip_teleport() : CreatureScript("gossip_teleport") { }

	bool OnGossipHello(Player* player, Creature* creature)
	{
		if(player->isInCombat())
			return false;

		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Teleport me to the Quest Zone again, i want to complete my quest!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Nevermind, i want to stay here.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
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
			player->CastSpell(player, SPELL_Teleport_to_theramore, true);
			player->CLOSE_GOSSIP_MENU();
			break;

		case GOSSIP_ACTION_INFO_DEF+2:
			player->CLOSE_GOSSIP_MENU();
			break;

		default:
			OnGossipHello(player, creature);
			break;
		}
		return true;
	}
};
void AddSC_teleport_gossip()
{
	new gossip_teleport;
}