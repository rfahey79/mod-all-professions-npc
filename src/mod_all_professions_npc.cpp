#include "ScriptMgr.h"
#include "Creature.h"
#include "Player.h"
#include "ScriptedGossip.h"
#include "Chat.h"
#include "Config.h"

namespace {
    enum GossipSender {
        SENDER_MAIN = 1
    };

    enum GossipAction {
        ACTION_ALCHEMY              = 100,
        ACTION_BLACKSMITHING        = 101,
        ACTION_ENCHANTING           = 102,
        ACTION_ENGINEERING          = 103,
        ACTION_HERBALISM            = 104,
        ACTION_INSCRIPTION          = 105,
        ACTION_JEWELCRAFTING        = 106,
        ACTION_LEATHERWORKING       = 107,
        ACTION_MINING               = 108,
        ACTION_SKINNING             = 109,
        ACTION_TAILORING            = 110,
        ACTION_COOKING              = 111,
        ACTION_FIRST_AID            = 112,
        ACTION_FISHING              = 113,
    };

    // WotLK base profession/secondary learning spells.
    // These are the usual 3.3.5a apprentice spells
    enum ProfessionsSpells {
        SPELL_ALCHEMY               = 2259,
        SPELL_BLACKSMITHING         = 2018,
        SPELL_ENCHANTING            = 7411,
        SPELL_ENGINEERING           = 4036,
        SPELL_HERBALISM             = 2366,
        SPELL_INSCRIPTION           = 45357,
        SPELL_JEWELCRAFTING         = 25229,
        SPELL_LEATHERWORKING        = 2108,
        SPELL_MINING                = 2575,
        SPELL_SKINNING              = 8613,
        SPELL_TAILORING             = 3908,
        SPELL_COOKING               = 2550,
        SPELL_FIRST_AID             = 3273,
        SPELL_FISHING               = 7620,
    };

    // SkillLine IDs
    enum SkillLines {
        SKILL_FIRST_AID             = 129,
        SKILL_BLACSMITHING          = 164,
        SKILL_LEATHERWORKING        = 165,
        SKILL_ALCHEMY               = 171,
        SKILL_HERBALISM             = 182,
        SKILL_COOKING               = 185,
        SKILL_MINING                = 186,
        SKILL_TAILORING             = 197,
        SKILL_ENGINEERING           = 202,
        SKILL_ENCHANTING            = 333,
        SKILL_FISHING               = 356,
        SKILL_SKINNING              = 393,
        SKILL_JEWELCRAFTING         = 755,
        SKILL_INSCRIPTION           = 773,
    };

    bool IsPrimaryProfession(uint32 skillLine)  {
        switch(skillLine) {
            case SKILL_ALCHEMY:
            case SKILL_BLACSMITHING:
            case SKILL_ENCHANTING:
            case SKILL_ENGINEERING:
            case SKILL_HERBALISM:
            case SKILL_INSCRIPTION:
            case SKILL_JEWELCRAFTING:
            case SKILL_LEATHERWORKING:
            case SKILL_SKINNING:
            case SKILL_TAILORING:
                return true;
            default: return false;
        }
    }

    bool PlayerAlreadyKnowsProfession(Player* player, unit32 skillLine) {
        return player->HasSkill(skillLine);
    }

    bool CanLearnPrimaryProfession(Player* player) {
        // Azeroth/WotLK standard: max 2 primary professions
        // Count currently known primary professions.
        // worldserver.conf allows you to override this max count.
        // uint32 count = 0;
        // uint32 maxProfessions = sConfigMgr->GetOption<uint32>("MaxPrimaryTradeSkill", 2);

        // if(player->HasSkill(SKILL_ALCHEMY)) ++count;
        // if(player->HasSkill(SKILL_BLACSMITHING)) ++count;
        // if(player->HasSkill(SKILL_ENCHANTING)) ++count;
        // if(player->HasSkill(SKILL_ENGINEERING)) ++count;
        // if(player->HasSkill(SKILL_HERBALISM)) ++count;
        // if(player->HasSkill(SKILL_INSCRIPTION)) ++count;
        // if(player->HasSkill(SKILL_JEWELCRAFTING)) ++count;
        // if(player->HasSkill(SKILL_LEATHERWORKING)) ++count;
        // if(player->HasSkill(SKILL_MINING)) ++count;
        // if(player->HasSkill(SKILL_SKINNING)) ++count;
        // if(player->HasSkill(SKILL_TAILORING)) ++count;

        // return count < maxProfessions; /// We need to learn how to pull this number from config and default to 2 if we don't have it.

        return player->GetFreePrimaryProfessionPoints() > 0;
    }

    void TeachProfession(Player* player, Creature* creature, uint32 skillLine, uint32 spellId, char const* professionName) {
        if(PlayerAlreadyKnowsProfession(player, skillLine)) {
            ChatHandler(player->GetSession()).PSendSysMessage("You already know %s", professionName);
            CloseGossipMenuFor(player);
            return;
        }

        if(IsPrimaryProfession(skillLine) && !CanLearnPrimaryProfession(player))  {
            ChatHandler(player->GetSession()).SendSysMessage("You already know %s primary professions.", sConfigMgr->GetOption<uint32>("MaxPrimaryTradeSkill", 2)); // find the max primary profession count
        }

        player->LearnSpell(spellId, false);

        if(!player->HasSkill(skillLine)) {
            ChatHandler(player.GetSession()).PSendSysMessage("Tried to teach %s, but the skill line was not added. Verify the spell ID for your core/database", professionName);
        }
        else {
            ChatHandler(player->GetSession()).PSendSysMessage("You have learned %s.", professionName);
        }

        CloseGossipMenuFor(player);
    }

    class npc_all_professions_trainer: public CreatureScript {
        public:
            npc_all_professions_trainer(): CreatureScript("npc_all_professions_trainer") {}

            bool OnGossipHellow(Player* player, Creature* creature) override {
                ClearGossipMenuForPlayer(player);

                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Learn Alchemy", SENDER_MAIN, ACTION_ALCHEMY);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Learn Blacksmithing", SENDER_MAIN, ACTION_BLACKSMITHING);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Learn Enchanting", SENDER_MAIN, ACTION_ENCHANTING);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Learn Engineering", SENDER_MAIN, ACTION_ENGINEERING);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Learn Herbalism", SENDER_MAIN, ACTION_HERBALISM);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Learn Inscription", SENDER_MAIN, ACTION_INSCRIPTION);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Learn Jewelcrafting", SENDER_MAIN, ACTION_JEWELCRAFTING);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Learn Leatherworking", SENDER_MAIN, ACTION_LEATHERWORKING);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Learn Mining", SENDER_MAIN, ACTION_MINING);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Learn Skinning", SENDER_MAIN, ACTION_SKINNING);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Learn Tailoring", SENDER_MAIN, ACTION_TAILORING);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Learn Cooking", SENDER_MAIN, ACTION_COOKING);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Learn First Aid", SENDER_MAIN, ACTION_FIRST_AID);
                AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Learn Fishing", SENDER_MAIN, ACTION_FISHING);

                SendGossipMenuFor(player, 907, creature->GetGUID()); // generic gossip text
                return true;
            }

            bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override {
                ClearGossipMenuFor(player);

                if(sender != SENDER_MAIN)
                    return false;

                switch(action) {
                    case ACTION_ALCHEMY:
                        TeachProfession(player, creature, SKILL_ALCHEMY, SPELL_ALCHEMY, "Alchemy");
                        break;
                    case ACTION_BLACKSMITHING:
                        TeachProfession(player, creature, SKILL_BLACKSMITHING, SPELL_BLACKSMITHING, "Blacksmithing");
                        break;
                    case ACTION_ENCHANTING:
                        TeachProfession(player, creature, SKILL_ENCHANTING, SPELL_ENCHANTING, "Enchanting");
                        break;
                    case ACTION_ENGINEERING:
                        TeachProfession(player, creature, SKILL_ENGINEERING, SPELL_ENGINEERING, "Engineering");
                        break;
                    case ACTION_HERBALISM:
                        TeachProfession(player, creature, SKILL_HERBALISM, SPELL_HERBALISM, "Herbalism");
                        break;
                    case ACTION_INSCRIPTION:
                        TeachProfession(player, creature, SKILL_INSCRIPTION, SPELL_INSCRIPTION, "Inscription");
                        break;
                    case ACTION_JEWELCRAFTING:
                        TeachProfession(player, creature, SKILL_JEWELCRAFTING, SPELL_JEWELCRAFTING, "Jewelcrafting");
                        break;
                    case ACTION_LEATHERWORKING:
                        TeachProfession(player, creature, SKILL_LEATHERWORKING, SPELL_LEATHERWORKING, "Leatherworking");
                        break;
                    case ACTION_MINING:
                        TeachProfession(player, creature, SKILL_MINING, SPELL_MINING, "Mining");
                        break;
                    case ACTION_SKINNING:
                        TeachProfession(player, creature, SKILL_SKINNING, SPELL_SKINNING, "Skinning");
                        break;
                    case ACTION_TAILORING:
                        TeachProfession(player, creature, SKILL_TAILORING, SPELL_TAILORING, "Tailoring");
                        break;
                    case ACTION_COOKING:
                        TeachProfession(player, creature, SKILL_COOKING, SPELL_COOKING, "Cooking");
                        break;
                    case ACTION_FIRST_AID:
                        TeachProfession(player, creature, SKILL_FIRST_AID, SPELL_FIRST_AID, "First Aid");
                        break;
                    case ACTION_FISHING:
                        TeachProfession(player, creature, SKILL_FISHING, SPELL_FISHING, "Fishing");
                        break;
                    default:
                        CloseGossipMenuFor(player);
                        break;
                }

                return true;
            }
    }
};

void Addmod_all_professoins_npcScripts() {
    new npc_all_professions_trainer();
}