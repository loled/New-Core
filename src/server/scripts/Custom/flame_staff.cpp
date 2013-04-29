#include "ScriptPCH.h"
#include "Spell.h" 

class flame_staff : public ItemScript
{
public:
    flame_staff() : ItemScript("flame_staff") { }

    bool OnUse(Player* pPlayer, Item* pItem, SpellCastTargets const& /*targets*/)
    {
		printf("Flame: Calling on use.");
        if(pPlayer->GetQuestStatus(25323) == QUEST_STATUS_INCOMPLETE)
        {
			printf("Flame: Quest detected.");
            if(Creature* cr = pPlayer->FindNearestCreature(38896,20))
            {
				printf("Flame: Creature detected.");
                cr->DisappearAndDie();
                pPlayer->CastSpell(pPlayer, 74723, true, NULL);
                return false;
            }
            else
				pPlayer->GetSession()->SendNotification("Objetivo no encontrado.");
		}
        return true;
    }
};

void AddSC_flame_staff()
{
    new flame_staff();
}