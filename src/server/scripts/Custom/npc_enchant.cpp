#include "ScriptPCH.h"

enum Enchants
{
    ENCHANT_WEP_LANDSLIDE					= 4099,
	ENCHANT_WEP_POWER_TORRENT				= 4097,
	ENCHANT_WEP_WINDWALK					= 4098,
	ENCHANT_WEP_HEARTSONG					= 4084,
	ENCHANT_WEP_HURRICANE					= 4083,
	ENCHANT_WEP_ELEMENTAL_SLAYER			= 4074,
	ENCHANT_WEP_AVALANCHE					= 4067,
	ENCHANT_WEP_MENDING						= 4066,
	ENCHANT_2HWEP_MIGHTY_AGILITY			= 4227,

    ENCHANT_OFF_HAND_SUPERIOR_INTELLECT		= 4091,
	ENCHANT_SHIELD_MASTERY					= 4085,
	ENCHANT_SHIELD_PROTECTION				= 4073,

	ENCHANT_HEAD_VICIOUS_INTELLECT			= 4245,
	ENCHANT_HEAD_VICIOUS_AGILITY			= 4246,
	ENCHANT_HEAD_VICIOUS_STRENGTH			= 4247,

    ENCHANT_SHOULDER_VICIOUS_INTELLECT		= 4248,
	ENCHANT_SHOULDER_VICIOUS_AGILITY		= 4250,
	ENCHANT_SHOULDER_VICIOUS_STRENGTH		= 4249,

    ENCHANT_CLOAK_GREATER_CRITICAL_STRIKE	= 4100,
	ENCHANT_CLOAK_GREATER_INTELLECT			= 4096,
	ENCHANT_CLOAK_PROTECTION				= 4090,
	ENCHANT_CLOAK_GREATER_SPELL_PIERCING	= 4064,

	ENCHANT_GLOVES_GREATER_MASTERY			= 4107,
	ENCHANT_GLOVES_MIGHTY_STRENGTH			= 4106,
	ENCHANT_GLOVES_GREATER_EXPERTISE		= 4082,
	ENCHANT_GLOVES_HASTE					= 4068,

	ENCHANT_BRACERS_GREATER_CRITICAL_STRIKE = 4101,
	ENCHANT_BRACERS_GREATER_SPEED			= 4108,
	ENCHANT_BRACERS_AGILITY					= 4258,
	ENCHANT_BRACERS_MAJOR_STRENGTH			= 4256,
	ENCHANT_BRACERS_MIGHTY_INTELLECT		= 4257,
	ENCHANT_BRACERS_GREATER_EXPERTISE		= 4095,
	ENCHANT_BRACERS_EXCEPTIONAL_SPIRIT		= 4093,
	ENCHANT_BRACERS_PRECISION				= 4089,
	ENCHANT_BRACERS_SUPERIOR_DODGE			= 4086,

	ENCHANT_CHEST_PEERLESS_STATS			= 4102,
	ENCHANT_CHEST_GREATER_STAMINA			= 4103,
	ENCHANT_CHEST_EXCEPTIONAL_SPIRIT		= 4088,
	ENCHANT_CHEST_MIGHTY_RESILIENCE			= 4077,

	ENCHANT_BOOTS_ASSASSINS_STEP			= 4105,
	ENCHANT_BOOTS_LAVAWALKER				= 4104,
	ENCHANT_BOOTS_MASTERY					= 4094,
	ENCHANT_BOOTS_PRECISION					= 4092,
	ENCHANT_BOOTS_MAJOR_AGILITY				= 4076,
	ENCHANT_BOOTS_HASTE						= 4069,

	ENCHANT_RING_AGILITY					= 4079,
	ENCHANT_RING_GREATER_STAMINA			= 4081,
	ENCHANT_RING_INTELLECT					= 4080,
	ENCHANT_RING_STRENGTH					= 4078,
};

#define ONE_HAND_WEAPON_COST	10000 * 20 //20g
#define TWO_HAND_WEAPON_COST	10000 * 30 //30g
#define MAIN_PIECES_COST		10000 * 15 //15g
#define OFF_PIECES_COST			10000 * 10 //10g
#define SHIELD_COST				10000 * 10 //10g
 
void Enchant(Player* player, Item* item, uint32 enchantid)
{
    if (!item)
    {
        player->GetSession()->SendNotification("You need to equip an item in that slot to enchant it!");
        return;
    }

    if (!enchantid)
		return;
		
    player->ApplyEnchantment(item, PERM_ENCHANTMENT_SLOT, false);
    item->SetEnchantment(PERM_ENCHANTMENT_SLOT, enchantid, 0, 0);
    player->ApplyEnchantment(item, PERM_ENCHANTMENT_SLOT, true);
	std::string color = "|cff";
	switch (item->GetProto()->Quality)
	{
	case 0:
		color += "9d9d9d"; 
		break;
	case 1:
		color += "ffffff";
		break;
	case 2:
		color += "1eff00";
		break;
	case 3:
		color += "0070dd";
		break;
	case 4:
		color += "a335ee";
		break;
	case 5:
		color += "ff8000";
		break;
	}
	std::string itemname = item->GetProto()->Name1;
	ChatHandler(player).PSendSysMessage("|cffFFFFFF[%s%s|cffFFFFFF] |cffFF0000succesfully enchanted!", color.c_str(), itemname.c_str());
}
 
class npc_enchantment : public CreatureScript
{
public:
    npc_enchantment() : CreatureScript("npc_enchantment") { }
 
        bool OnGossipHello(Player* player, Creature* creature)
        {
            player->ADD_GOSSIP_ITEM(1, "[Enchant Weapon]", GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM(1, "[Enchant 2H Weapon]", GOSSIP_SENDER_MAIN, 2);
			player->ADD_GOSSIP_ITEM(1, "[Enchant Off-Hand]", GOSSIP_SENDER_MAIN, 3);
            player->ADD_GOSSIP_ITEM(1, "[Enchant Head]", GOSSIP_SENDER_MAIN, 4);
            player->ADD_GOSSIP_ITEM(1, "[Enchant Shoulders]", GOSSIP_SENDER_MAIN, 5);
            player->ADD_GOSSIP_ITEM(1, "[Enchant Cloak]", GOSSIP_SENDER_MAIN, 6);
            player->ADD_GOSSIP_ITEM(1, "[Enchant Chest]", GOSSIP_SENDER_MAIN, 7);
            player->ADD_GOSSIP_ITEM(1, "[Enchant Bracers]", GOSSIP_SENDER_MAIN, 8);
            player->ADD_GOSSIP_ITEM(1, "[Enchant Gloves]", GOSSIP_SENDER_MAIN, 9);
            player->ADD_GOSSIP_ITEM(1, "[Enchant Legs]", GOSSIP_SENDER_MAIN, 10);
            player->ADD_GOSSIP_ITEM(1, "[Enchant Feet]", GOSSIP_SENDER_MAIN, 11);

            if (player->HasSkill(SKILL_ENCHANTING) && player->GetSkillValue(SKILL_ENCHANTING) == 450)
                player->ADD_GOSSIP_ITEM(1, "[Enchant Rings]", GOSSIP_SENDER_MAIN, 12);

            player->SEND_GOSSIP_MENU(100001, creature->GetGUID());
			return true;
		}
 
        bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
        {
			player->PlayerTalkClass->ClearMenus();
			Item * mainItem;

            switch (action)
            {

                case 1: // Enchant Weapon
					player->ADD_GOSSIP_ITEM(1, "Avalanche [20g]", GOSSIP_SENDER_MAIN, 102);
					player->ADD_GOSSIP_ITEM(1, "Elemental Slayer [20g]", GOSSIP_SENDER_MAIN, 103);
                    player->ADD_GOSSIP_ITEM(1, "Heartsong [20g]", GOSSIP_SENDER_MAIN, 100);
                    player->ADD_GOSSIP_ITEM(1, "Hurricane [20g]", GOSSIP_SENDER_MAIN, 101);
                    player->ADD_GOSSIP_ITEM(1, "Landslide [20g]", GOSSIP_SENDER_MAIN, 104);
                    player->ADD_GOSSIP_ITEM(1, "Power Torrent [20g]", GOSSIP_SENDER_MAIN, 105);
                    player->ADD_GOSSIP_ITEM(1, "Mending [20g]", GOSSIP_SENDER_MAIN, 106);
                    player->ADD_GOSSIP_ITEM(1, "Windwalk [20g]", GOSSIP_SENDER_MAIN, 107);
					player->ADD_GOSSIP_ITEM(1, "<-Back", GOSSIP_SENDER_MAIN, 300);
                    player->PlayerTalkClass->SendGossipMenu(100002, creature->GetGUID());
					return true;
					break;

                case 2: // Enchant 2H Weapon
					{
						mainItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND);
						if (!mainItem || mainItem->GetProto()->InventoryType != INVTYPE_2HWEAPON)
						{
							player->GetSession()->SendAreaTriggerMessage("|cffFF0000You need a Two-Hand Weapon equipped!");
							return false;
							player->CLOSE_GOSSIP_MENU();;
						}
						if (mainItem->GetProto()->InventoryType == INVTYPE_2HWEAPON)
						{
							player->ADD_GOSSIP_ITEM(1, "Avalanche [20g]", GOSSIP_SENDER_MAIN, 102);
							player->ADD_GOSSIP_ITEM(1, "Elemental Slayer [20g]", GOSSIP_SENDER_MAIN, 103);
							player->ADD_GOSSIP_ITEM(1, "Heartsong [20g]", GOSSIP_SENDER_MAIN, 100);
							player->ADD_GOSSIP_ITEM(1, "Hurricane [20g]", GOSSIP_SENDER_MAIN, 101);
							player->ADD_GOSSIP_ITEM(1, "Landslide [20g]", GOSSIP_SENDER_MAIN, 104);
							player->ADD_GOSSIP_ITEM(1, "Power Torrent [20g]", GOSSIP_SENDER_MAIN, 105);
							player->ADD_GOSSIP_ITEM(1, "Mending [20g]", GOSSIP_SENDER_MAIN, 106);
							player->ADD_GOSSIP_ITEM(1, "Windwalk [20g]", GOSSIP_SENDER_MAIN, 107);
							player->ADD_GOSSIP_ITEM(1, "Mighty Agility [30g]", GOSSIP_SENDER_MAIN, 108);
							player->ADD_GOSSIP_ITEM(1, "<-Back", GOSSIP_SENDER_MAIN, 300);
							player->PlayerTalkClass->SendGossipMenu(100003, creature->GetGUID());
							return true;
						}
					}
					break;

                case 3: // Enchant Shield
					{
						mainItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);
						if (!mainItem)
						{
							player->GetSession()->SendAreaTriggerMessage("|cffFF0000You need an Off-Hand or Shield equipped!");
							player->CLOSE_GOSSIP_MENU();
							return false;							
						}
						if (mainItem->GetProto()->InventoryType == INVTYPE_SHIELD)
						{
							player->ADD_GOSSIP_ITEM(1, "Mastery [10g]", GOSSIP_SENDER_MAIN, 109);
							player->ADD_GOSSIP_ITEM(1, "Protection [10g]", GOSSIP_SENDER_MAIN, 110);
							player->ADD_GOSSIP_ITEM(1, "Superior Intellect [10g]", GOSSIP_SENDER_MAIN, 111);
							player->ADD_GOSSIP_ITEM(1, "<-Back", GOSSIP_SENDER_MAIN, 300);
							player->PlayerTalkClass->SendGossipMenu(100004, creature->GetGUID());
							return true;
						}
						if (mainItem->GetProto()->InventoryType == INVTYPE_WEAPONOFFHAND)
						{
							player->ADD_GOSSIP_ITEM(1, "Superior Intellect [10g]", GOSSIP_SENDER_MAIN, 111);
							player->ADD_GOSSIP_ITEM(1, "<-Back", GOSSIP_SENDER_MAIN, 300);
							player->SEND_GOSSIP_MENU(100004, creature->GetGUID());
						}
						
					}
					break;

                case 4: // Enchant Head
                    player->ADD_GOSSIP_ITEM(1, "Arcanum of Vicious Agility [15g]", GOSSIP_SENDER_MAIN, 112);
                    player->ADD_GOSSIP_ITEM(1, "Arcanum of Vicious Intellect [15g]", GOSSIP_SENDER_MAIN, 113);
                    player->ADD_GOSSIP_ITEM(1, "Arcanum of Vicious Strength [15g]", GOSSIP_SENDER_MAIN, 114);
					player->ADD_GOSSIP_ITEM(1, "<-Back", GOSSIP_SENDER_MAIN, 300);
                    player->PlayerTalkClass->SendGossipMenu(100005, creature->GetGUID());
					return true;
					break;

                case 5: // Enchant Shoulders
                    player->ADD_GOSSIP_ITEM(1, "Greater Inscription of the Vicious Agility [15g]", GOSSIP_SENDER_MAIN, 115);
                    player->ADD_GOSSIP_ITEM(1, "Greater Inscription of the Vicious Intellect [15g]", GOSSIP_SENDER_MAIN, 116);
                    player->ADD_GOSSIP_ITEM(1, "Greater Inscription of the Vicious Strength [15g]", GOSSIP_SENDER_MAIN, 117);
					player->ADD_GOSSIP_ITEM(1, "<-Back", GOSSIP_SENDER_MAIN, 300);
                    player->PlayerTalkClass->SendGossipMenu(100006, creature->GetGUID());
					return true;
					break;

                case 6: // Enchant Cloak
					player->ADD_GOSSIP_ITEM(1, "Greater Critical Strike [10g]", GOSSIP_SENDER_MAIN, 118);
                    player->ADD_GOSSIP_ITEM(1, "Greater Intellect [10g]", GOSSIP_SENDER_MAIN, 119);
                    player->ADD_GOSSIP_ITEM(1, "Greater Spell Piercing [10g]", GOSSIP_SENDER_MAIN, 120);
                    player->ADD_GOSSIP_ITEM(1, "Protection [10g]", GOSSIP_SENDER_MAIN, 121);
					player->ADD_GOSSIP_ITEM(1, "<-Back", GOSSIP_SENDER_MAIN, 300);
                    player->PlayerTalkClass->SendGossipMenu(100007, creature->GetGUID());
					return true;
					break;

				case 7: //Enchant chest
					player->ADD_GOSSIP_ITEM(1, "Exceptional Spirit [15g]", GOSSIP_SENDER_MAIN, 122);
					player->ADD_GOSSIP_ITEM(1, "Greater Stamina [15g]", GOSSIP_SENDER_MAIN, 123);
					player->ADD_GOSSIP_ITEM(1, "Mighty Resilience [15g]", GOSSIP_SENDER_MAIN, 124);
					player->ADD_GOSSIP_ITEM(1, "Peerless Stats [15g]", GOSSIP_SENDER_MAIN, 125);
					player->ADD_GOSSIP_ITEM(1, "<-Back", GOSSIP_SENDER_MAIN, 300);
					player->PlayerTalkClass->SendGossipMenu(100008, creature->GetGUID());
					return true;
					break;

				case 8: //Enchant Bracers
					player->ADD_GOSSIP_ITEM(1, "Agility [10g]", GOSSIP_SENDER_MAIN, 126);
					player->ADD_GOSSIP_ITEM(1, "Exceptional Spirit [10g]", GOSSIP_SENDER_MAIN, 127);
					player->ADD_GOSSIP_ITEM(1, "Greater Critical Strike [10g]", GOSSIP_SENDER_MAIN, 128);
					player->ADD_GOSSIP_ITEM(1, "Greater Expertise [10g]", GOSSIP_SENDER_MAIN, 129);
					player->ADD_GOSSIP_ITEM(1, "Greater Speed [10g]", GOSSIP_SENDER_MAIN, 130);
					player->ADD_GOSSIP_ITEM(1, "Major Strength [10g]", GOSSIP_SENDER_MAIN, 131);
					player->ADD_GOSSIP_ITEM(1, "Mighty Intellect [10g]", GOSSIP_SENDER_MAIN, 132);
					player->ADD_GOSSIP_ITEM(1, "Precision [10g]", GOSSIP_SENDER_MAIN, 133);
					player->ADD_GOSSIP_ITEM(1, "Superior Dodge [10g]", GOSSIP_SENDER_MAIN, 134);
					player->ADD_GOSSIP_ITEM(1, "<-Back", GOSSIP_SENDER_MAIN, 300);
					player->PlayerTalkClass->SendGossipMenu(100009, creature->GetGUID());
					return true;
					break;

				case 9: //Enchant Gloves
					player->ADD_GOSSIP_ITEM(1, "Greater Expertise [15g]", GOSSIP_SENDER_MAIN, 135);
					player->ADD_GOSSIP_ITEM(1, "Greater Mastery [15g]", GOSSIP_SENDER_MAIN, 136);
					player->ADD_GOSSIP_ITEM(1, "Haste [15g]", GOSSIP_SENDER_MAIN, 137);
					player->ADD_GOSSIP_ITEM(1, "Mighty Strength [15g]", GOSSIP_SENDER_MAIN, 138);
					player->ADD_GOSSIP_ITEM(1, "<-Back", GOSSIP_SENDER_MAIN, 300);
					player->PlayerTalkClass->SendGossipMenu(100010, creature->GetGUID());
					return true;
					break;

				case 11: //Enchant feet
					player->ADD_GOSSIP_ITEM(1, "Assassins Step [10g]", GOSSIP_SENDER_MAIN, 139);
					player->ADD_GOSSIP_ITEM(1, "Haste [10g]", GOSSIP_SENDER_MAIN, 140);
					player->ADD_GOSSIP_ITEM(1, "Lavawalker [10g]", GOSSIP_SENDER_MAIN, 141);
					player->ADD_GOSSIP_ITEM(1, "Major Agility [10g]", GOSSIP_SENDER_MAIN, 142);
					player->ADD_GOSSIP_ITEM(1, "Mastery [10g]", GOSSIP_SENDER_MAIN, 143);
					player->ADD_GOSSIP_ITEM(1, "Precision [10g]", GOSSIP_SENDER_MAIN, 144);
					player->ADD_GOSSIP_ITEM(1, "<-Back", GOSSIP_SENDER_MAIN, 300);
					player->PlayerTalkClass->SendGossipMenu(100012, creature->GetGUID());
					return true;
					break;

				case 12: //Enchant rings
					player->ADD_GOSSIP_ITEM(1, "Agility [10g]", GOSSIP_SENDER_MAIN, 145);
					player->ADD_GOSSIP_ITEM(1, "Greater Stamina [10g]", GOSSIP_SENDER_MAIN, 146);
					player->ADD_GOSSIP_ITEM(1, "Intellect [10g]", GOSSIP_SENDER_MAIN, 147);
					player->ADD_GOSSIP_ITEM(1, "Strength [10g]", GOSSIP_SENDER_MAIN, 148);
					player->ADD_GOSSIP_ITEM(1, "<-Back", GOSSIP_SENDER_MAIN, 300);
					player->PlayerTalkClass->SendGossipMenu(100013, creature->GetGUID());
					return true;
					break;

                case 100:
					if (player->GetMoney() < ONE_HAND_WEAPON_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", ONE_HAND_WEAPON_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-ONE_HAND_WEAPON_COST);
                    Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), ENCHANT_WEP_AVALANCHE);
                    player->CLOSE_GOSSIP_MENU();
                    break;

                case 101:
					if (player->GetMoney() < ONE_HAND_WEAPON_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", ONE_HAND_WEAPON_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-ONE_HAND_WEAPON_COST);
                    Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), ENCHANT_WEP_ELEMENTAL_SLAYER);
                    player->CLOSE_GOSSIP_MENU();
                    break;

                case 102:
					if (player->GetMoney() < ONE_HAND_WEAPON_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", ONE_HAND_WEAPON_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-ONE_HAND_WEAPON_COST);
                    Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), ENCHANT_WEP_HEARTSONG);
                    player->CLOSE_GOSSIP_MENU();
                    break;

                case 103:
					if (player->GetMoney() < ONE_HAND_WEAPON_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", ONE_HAND_WEAPON_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-ONE_HAND_WEAPON_COST);
                    Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), ENCHANT_WEP_HURRICANE);
                    player->CLOSE_GOSSIP_MENU();
                    break;

                case 104:
					if (player->GetMoney() < ONE_HAND_WEAPON_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", ONE_HAND_WEAPON_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-ONE_HAND_WEAPON_COST);
                    Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), ENCHANT_WEP_LANDSLIDE);
                    player->CLOSE_GOSSIP_MENU();
                    break;

				case 105:
					if (player->GetMoney() < ONE_HAND_WEAPON_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", ONE_HAND_WEAPON_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-ONE_HAND_WEAPON_COST);
                    Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), ENCHANT_WEP_MENDING);
                    player->CLOSE_GOSSIP_MENU();
                    break;

				case 106:
					if (player->GetMoney() < ONE_HAND_WEAPON_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", ONE_HAND_WEAPON_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-ONE_HAND_WEAPON_COST);
                    Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), ENCHANT_WEP_POWER_TORRENT);
                    player->CLOSE_GOSSIP_MENU();
                    break;

				case 107:
					if (player->GetMoney() < ONE_HAND_WEAPON_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", ONE_HAND_WEAPON_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-ONE_HAND_WEAPON_COST);
                    Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), ENCHANT_WEP_WINDWALK);
                    player->CLOSE_GOSSIP_MENU();
                    break;

				case 108:
					if (player->GetMoney() < TWO_HAND_WEAPON_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", TWO_HAND_WEAPON_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					mainItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND);
					if (mainItem->GetProto()->InventoryType == INVTYPE_2HWEAPON)
					{
						player->ModifyMoney(-TWO_HAND_WEAPON_COST);
						Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), ENCHANT_2HWEP_MIGHTY_AGILITY);
						player->CLOSE_GOSSIP_MENU();
					}
					else
					{
						player->GetSession()->SendAreaTriggerMessage("|cffFF0000You don't have 2H equipped! Nice try.");
						player->CLOSE_GOSSIP_MENU();
					}
                    break;

				case 109:
					if (player->GetMoney() < SHIELD_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", SHIELD_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					mainItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);
					if (mainItem->GetProto()->InventoryType == INVTYPE_SHIELD)
					{
						player->ModifyMoney(-SHIELD_COST);
						Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_SHIELD_MASTERY);
						player->CLOSE_GOSSIP_MENU();
					}
					else
					{
						player->GetSession()->SendAreaTriggerMessage("|cffFF0000You don't have Shield equipped! Nice try.");
						player->CLOSE_GOSSIP_MENU();
					}
                    break;

				case 110:
					if (player->GetMoney() < SHIELD_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", SHIELD_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					mainItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);
					if (mainItem->GetProto()->InventoryType == INVTYPE_SHIELD)
					{
						player->ModifyMoney(-SHIELD_COST);
						Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_SHIELD_PROTECTION);
						player->CLOSE_GOSSIP_MENU();
					}
					else
					{
						player->GetSession()->SendAreaTriggerMessage("|cffFF0000You don't have Shield equipped! Nice try.");
						player->CLOSE_GOSSIP_MENU();
					}
                    break;

				case 111:
					if (player->GetMoney() < SHIELD_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", SHIELD_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-SHIELD_COST);
					Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_OFF_HAND_SUPERIOR_INTELLECT);
					player->CLOSE_GOSSIP_MENU();
                    break;

				case 112:
					if (player->GetMoney() < MAIN_PIECES_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", MAIN_PIECES_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-MAIN_PIECES_COST);
					Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), ENCHANT_HEAD_VICIOUS_AGILITY);
                    player->CLOSE_GOSSIP_MENU();
                    break;

				case 113:
					if (player->GetMoney() < MAIN_PIECES_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", MAIN_PIECES_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-MAIN_PIECES_COST);
					Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), ENCHANT_HEAD_VICIOUS_INTELLECT);
                    player->CLOSE_GOSSIP_MENU();
                    break;

				case 114:
					if (player->GetMoney() < MAIN_PIECES_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", MAIN_PIECES_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-MAIN_PIECES_COST);
					Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), ENCHANT_HEAD_VICIOUS_STRENGTH);
                    player->CLOSE_GOSSIP_MENU();
                    break;

				case 115:
					if (player->GetMoney() < MAIN_PIECES_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", MAIN_PIECES_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-MAIN_PIECES_COST);
					Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), ENCHANT_SHOULDER_VICIOUS_AGILITY);
                    player->CLOSE_GOSSIP_MENU();
                    break;

				case 116:
					if (player->GetMoney() < MAIN_PIECES_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", MAIN_PIECES_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-MAIN_PIECES_COST);
					Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), ENCHANT_SHOULDER_VICIOUS_INTELLECT);
                    player->CLOSE_GOSSIP_MENU();
                    break;

				case 117:
					if (player->GetMoney() < MAIN_PIECES_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", MAIN_PIECES_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-MAIN_PIECES_COST);
					Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), ENCHANT_SHOULDER_VICIOUS_STRENGTH);
                    player->CLOSE_GOSSIP_MENU();
                    break;

				case 118:
					if (player->GetMoney() < OFF_PIECES_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", OFF_PIECES_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-OFF_PIECES_COST);
					Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), ENCHANT_CLOAK_GREATER_CRITICAL_STRIKE);
                    player->CLOSE_GOSSIP_MENU();
                    break;

				case 119:
					if (player->GetMoney() < OFF_PIECES_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", OFF_PIECES_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-OFF_PIECES_COST);
					Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), ENCHANT_CLOAK_GREATER_INTELLECT);
                    player->CLOSE_GOSSIP_MENU();
                    break;

				case 120:
					if (player->GetMoney() < OFF_PIECES_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", OFF_PIECES_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-OFF_PIECES_COST);
					Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), ENCHANT_CLOAK_GREATER_SPELL_PIERCING);
                    player->CLOSE_GOSSIP_MENU();
                    break;

				case 121:
					if (player->GetMoney() < OFF_PIECES_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", OFF_PIECES_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-OFF_PIECES_COST);
					Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), ENCHANT_CLOAK_PROTECTION);
                    player->CLOSE_GOSSIP_MENU();
                    break;

				case 122:
					if (player->GetMoney() < MAIN_PIECES_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", MAIN_PIECES_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-MAIN_PIECES_COST);
					Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), ENCHANT_CHEST_EXCEPTIONAL_SPIRIT);
                    player->CLOSE_GOSSIP_MENU();
                    break;

				case 123:
					if (player->GetMoney() < MAIN_PIECES_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", MAIN_PIECES_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-MAIN_PIECES_COST);
					Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), ENCHANT_CHEST_GREATER_STAMINA);
                    player->CLOSE_GOSSIP_MENU();
                    break;

				case 124:
					if (player->GetMoney() < MAIN_PIECES_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", MAIN_PIECES_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-MAIN_PIECES_COST);
					Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), ENCHANT_CHEST_MIGHTY_RESILIENCE);
                    player->CLOSE_GOSSIP_MENU();
                    break;

				case 125:
					if (player->GetMoney() < MAIN_PIECES_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", MAIN_PIECES_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-MAIN_PIECES_COST);
					Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), ENCHANT_CHEST_PEERLESS_STATS);
                    player->CLOSE_GOSSIP_MENU();
                    break;

				case 126:
					if (player->GetMoney() < OFF_PIECES_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", OFF_PIECES_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-OFF_PIECES_COST);
					Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), ENCHANT_BRACERS_AGILITY);
                    player->CLOSE_GOSSIP_MENU();
                    break;

				case 127:
					if (player->GetMoney() < OFF_PIECES_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", OFF_PIECES_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-OFF_PIECES_COST);
					Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), ENCHANT_BRACERS_EXCEPTIONAL_SPIRIT);
                    player->CLOSE_GOSSIP_MENU();
                    break;

				case 128:
					if (player->GetMoney() < OFF_PIECES_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", OFF_PIECES_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-OFF_PIECES_COST);
					Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), ENCHANT_BRACERS_GREATER_CRITICAL_STRIKE);
                    player->CLOSE_GOSSIP_MENU();
                    break;

				case 129:
					if (player->GetMoney() < OFF_PIECES_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", OFF_PIECES_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-OFF_PIECES_COST);
					Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), ENCHANT_BRACERS_GREATER_EXPERTISE);
                    player->CLOSE_GOSSIP_MENU();
                    break;

				case 130:
					if (player->GetMoney() < OFF_PIECES_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", OFF_PIECES_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-OFF_PIECES_COST);
					Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), ENCHANT_BRACERS_GREATER_SPEED);
                    player->CLOSE_GOSSIP_MENU();
                    break;

				case 131:
					if (player->GetMoney() < OFF_PIECES_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", OFF_PIECES_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-OFF_PIECES_COST);
					Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), ENCHANT_BRACERS_MAJOR_STRENGTH);
                    player->CLOSE_GOSSIP_MENU();
                    break;

				case 132:
					if (player->GetMoney() < OFF_PIECES_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", OFF_PIECES_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-OFF_PIECES_COST);
					Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), ENCHANT_BRACERS_MIGHTY_INTELLECT);
                    player->CLOSE_GOSSIP_MENU();
                    break;
				case 133:
					if (player->GetMoney() < OFF_PIECES_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", OFF_PIECES_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-OFF_PIECES_COST);
					Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), ENCHANT_BRACERS_PRECISION);
                    player->CLOSE_GOSSIP_MENU();
					break;
				case 134:
					if (player->GetMoney() < OFF_PIECES_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", OFF_PIECES_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-OFF_PIECES_COST);
					Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), ENCHANT_BRACERS_SUPERIOR_DODGE);
                    player->CLOSE_GOSSIP_MENU();
					break;

				case 135:
					if (player->GetMoney() < MAIN_PIECES_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", MAIN_PIECES_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-MAIN_PIECES_COST);
					Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), ENCHANT_GLOVES_GREATER_EXPERTISE);
                    player->CLOSE_GOSSIP_MENU();
                    break;

				case 136:
					if (player->GetMoney() < MAIN_PIECES_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", MAIN_PIECES_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-MAIN_PIECES_COST);
					Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), ENCHANT_GLOVES_GREATER_MASTERY);
                    player->CLOSE_GOSSIP_MENU();
                    break;

				case 137:
					if (player->GetMoney() < MAIN_PIECES_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", MAIN_PIECES_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-MAIN_PIECES_COST);
					Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), ENCHANT_GLOVES_HASTE);
                    player->CLOSE_GOSSIP_MENU();
                    break;

				case 138:
					if (player->GetMoney() < MAIN_PIECES_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", MAIN_PIECES_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-MAIN_PIECES_COST);
					Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), ENCHANT_GLOVES_MIGHTY_STRENGTH);
                    player->CLOSE_GOSSIP_MENU();
                    break;

				case 139:
					if (player->GetMoney() < OFF_PIECES_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", MAIN_PIECES_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-OFF_PIECES_COST);
					Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), ENCHANT_BOOTS_ASSASSINS_STEP);
                    player->CLOSE_GOSSIP_MENU();
                    break;

				case 140:
					if (player->GetMoney() < OFF_PIECES_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", MAIN_PIECES_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-OFF_PIECES_COST);
					Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), ENCHANT_BOOTS_HASTE);
                    player->CLOSE_GOSSIP_MENU();
                    break;

				case 141:
					if (player->GetMoney() < OFF_PIECES_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", MAIN_PIECES_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-OFF_PIECES_COST);
					Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), ENCHANT_BOOTS_LAVAWALKER);
                    player->CLOSE_GOSSIP_MENU();
                    break;

				case 142:
					if (player->GetMoney() < OFF_PIECES_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", MAIN_PIECES_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-OFF_PIECES_COST);
					Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), ENCHANT_BOOTS_MAJOR_AGILITY);
                    player->CLOSE_GOSSIP_MENU();
                    break;

				case 143:
					if (player->GetMoney() < OFF_PIECES_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", MAIN_PIECES_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-OFF_PIECES_COST);
					Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), ENCHANT_BOOTS_MASTERY);
                    player->CLOSE_GOSSIP_MENU();
                    break;

				case 144:
					if (player->GetMoney() < OFF_PIECES_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", MAIN_PIECES_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-OFF_PIECES_COST);
					Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), ENCHANT_BOOTS_PRECISION);
                    player->CLOSE_GOSSIP_MENU();
                    break;

				case 145:
					if (player->GetMoney() < OFF_PIECES_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", MAIN_PIECES_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-OFF_PIECES_COST);
					Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), ENCHANT_RING_AGILITY);
					Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), ENCHANT_RING_AGILITY);
                    player->CLOSE_GOSSIP_MENU();
                    break;

				case 146:
					if (player->GetMoney() < OFF_PIECES_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", MAIN_PIECES_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-OFF_PIECES_COST);
					Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), ENCHANT_RING_GREATER_STAMINA);
					Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), ENCHANT_RING_GREATER_STAMINA);
                    player->CLOSE_GOSSIP_MENU();
                    break;

				case 147:
					if (player->GetMoney() < OFF_PIECES_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", MAIN_PIECES_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-OFF_PIECES_COST);
					Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), ENCHANT_RING_INTELLECT);
					Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), ENCHANT_RING_INTELLECT);
                    player->CLOSE_GOSSIP_MENU();
                    break;

				case 148:
					if (player->GetMoney() < OFF_PIECES_COST) {
						ChatHandler(player).PSendSysMessage("You don't have enough money to purchase this! It costs %d gold", MAIN_PIECES_COST/10000);
						player->CLOSE_GOSSIP_MENU();;
						break;
					}

					player->ModifyMoney(-OFF_PIECES_COST);
					Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), ENCHANT_RING_STRENGTH);
					Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), ENCHANT_RING_STRENGTH);
                    player->CLOSE_GOSSIP_MENU();
                    break;

				case 300:
					player->ADD_GOSSIP_ITEM(1, "[Enchant Weapon]", GOSSIP_SENDER_MAIN, 1);
					player->ADD_GOSSIP_ITEM(1, "[Enchant 2H Weapon]", GOSSIP_SENDER_MAIN, 2);
					player->ADD_GOSSIP_ITEM(1, "[Enchant Shield]", GOSSIP_SENDER_MAIN, 3);
					player->ADD_GOSSIP_ITEM(1, "[Enchant Head]", GOSSIP_SENDER_MAIN, 4);
					player->ADD_GOSSIP_ITEM(1, "[Enchant Shoulders]", GOSSIP_SENDER_MAIN, 5);
					player->ADD_GOSSIP_ITEM(1, "[Enchant Cloak]", GOSSIP_SENDER_MAIN, 6);
					player->ADD_GOSSIP_ITEM(1, "[Enchant Chest]", GOSSIP_SENDER_MAIN, 7);
					player->ADD_GOSSIP_ITEM(1, "[Enchant Bracers]", GOSSIP_SENDER_MAIN, 8);
					player->ADD_GOSSIP_ITEM(1, "[Enchant Gloves]", GOSSIP_SENDER_MAIN, 9);
					player->ADD_GOSSIP_ITEM(1, "[Enchant Legs]", GOSSIP_SENDER_MAIN, 10);
					player->ADD_GOSSIP_ITEM(1, "[Enchant Feet]", GOSSIP_SENDER_MAIN, 11);

					if (player->HasSkill(SKILL_ENCHANTING) && player->GetSkillValue(SKILL_ENCHANTING) == 450)
						player->ADD_GOSSIP_ITEM(1, "[Enchant Rings]", GOSSIP_SENDER_MAIN, 12);

					player->PlayerTalkClass->SendGossipMenu(100001, creature->GetGUID());
					break;

			}

			return true;
        }


};

void AddSC_npc_enchantment()
{
  new npc_enchantment();
}