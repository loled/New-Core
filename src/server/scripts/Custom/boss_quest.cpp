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
 - Complete: %100
 - ScriptName: 'boss_quest'
 - Comment: Request by xxx
<--------------------------------------------------------------------------->
*/
#include "ScriptPCH.h"
#define TELEPORTER_ENTRY 190005 // Define Teleporter enter ID here

enum Spells // Spell Names, IDs
{
   SPELL_NAME    = 100,
   SPELL_NAME1    = 100,
   SPELL_NAME2   = 100,
};

     
class boss_quest : public CreatureScript
{
public:
	boss_quest() : CreatureScript("boss_quest") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_questAI(creature);
    }

    struct boss_questAI : public ScriptedAI
    {
       boss_questAI(Creature* creature) : ScriptedAI(creature) {}

		void JustDied(Unit* killer)
        {                                           // X             Y             Z         MapId                                          Timer
		   killer->SummonCreature(TELEPORTER_ENTRY, 3330.056396f, -8384.273438f, 5.452732f, 1, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 35000);
        };

		 // Define reset timers
		uint32 SPELL_NAME_Timer;
		uint32 SPELL_NAME1_Timer;
		uint32 SPELL_NAME2_Timer;
		
		void Reset() //Spell reset timers
        {
          SPELL_NAME_Timer = 4000;
          SPELL_NAME1_Timer = 6000;
	      SPELL_NAME2_Timer = 1000;       
        }
 
		 
	       void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            //SPELL_NAME_Timer
            if (SPELL_NAME_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_NAME);
                SPELL_NAME_Timer = 4000;
            }
            else SPELL_NAME_Timer -= diff;

	            //SPELL_NAME1_Timer
            if (SPELL_NAME1_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_NAME1);
                SPELL_NAME1_Timer = 6000;
            }
            else SPELL_NAME1_Timer -= diff;

			  //SPELL_NAME2_Timer
            if (SPELL_NAME2_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_NAME2);
                SPELL_NAME2_Timer = 1000;
            }
            else SPELL_NAME2_Timer -= diff;

             DoMeleeAttackIfReady();
           
        }
    };
};

void AddSC_boss_quest()
{
    new boss_quest();
}