#include "global.h"
#include "new_game.h"
#include "random.h"
#include "pokemon.h"
#include "roamer.h"
#include "pokemon_size_record.h"
#include "script.h"
//#include "lottery_corner.h"
#include "play_time.h"
//#include "mauville_old_man.h"
//#include "match_call.h"
//#include "lilycove_lady.h"
#include "load_save.h"
//#include "pokeblock.h"
//#include "dewford_trend.h"
#include "berry.h"
//#include "rtc.h"
#include "easy_chat.h"
#include "event_data.h"
#include "money.h"
//#include "trainer_hill.h"
//#include "tv.h"
#include "coins.h"
#include "text.h"
#include "overworld.h"
#include "mail.h"
#include "battle_records.h"
#include "item.h"
#include "pokedex.h"
//#include "apprentice.h"
//#include "frontier_util.h"
#include "pokedex.h"
#include "save.h"
#include "link_rfu.h"
#include "main.h"
//#include "contest.h"
#include "item_menu.h"
#include "pokemon_storage_system.h"
#include "pokemon_jump.h"
//#include "decoration_inventory.h"
//#include "secret_base.h"
#include "player_pc.h"
#include "field_specials.h"
#include "berry_powder.h"
//#include "mystery_gift.h"
#include "union_room_chat.h"
#include "trainer_tower.h"

/**
 * ::ACIMUT::
 * 2022/04/15
 * - Supongo que hay que simplificar aquí.
 * - Hacer un hook a la old school.
 */

/*void NewGameInitData(void)
{
    u8 rivalName[PLAYER_NAME_LENGTH + 1];

    StringCopy(rivalName, gSaveBlock1Ptr->rivalName);
    gDifferentSaveFile = TRUE;
    gSaveBlock2Ptr->encryptionKey = 0;
    ZeroPlayerPartyMons();
    ZeroEnemyPartyMons();
    ClearBattleTower();
    ClearSav1();
    ClearMailData();
    gSaveBlock2Ptr->specialSaveWarpFlags = 0;
    gSaveBlock2Ptr->gcnLinkFlags = 0;
    gSaveBlock2Ptr->unkFlag1 = TRUE;
    gSaveBlock2Ptr->unkFlag2 = FALSE;
    InitPlayerTrainerId();
    PlayTimeCounter_Reset();
    ClearPokedexFlags();
    InitEventData();
    ResetFameChecker();
    SetMoney(&gSaveBlock1Ptr->money, 3000);
    ResetGameStats();
    ClearPlayerLinkBattleRecords();
    InitHeracrossSizeRecord();
    InitMagikarpSizeRecord();
    sub_806E190();
    gPlayerPartyCount = 0;
    ZeroPlayerPartyMons();
    ResetPokemonStorageSystem();
    ClearRoamerData();
    gSaveBlock1Ptr->registeredItem = 0;
    ClearBag();
    NewGameInitPCItems();
    ClearEnigmaBerries();
    InitEasyChatPhrases();
    ResetTrainerFanClub();
    UnionRoomChat_InitializeRegisteredTexts();
    ResetMiniGamesResults();
    InitMEventData();
    SetAllRenewableItemFlags();
    WarpToPlayersRoom();
    ScriptContext2_RunNewScript(EventScript_ResetAllMapFlags);
    StringCopy(gSaveBlock1Ptr->rivalName, rivalName);
    ResetTrainerTowerResults();

    memset(&gSaveBlock1Ptr->follower, 0, sizeof(gSaveBlock1Ptr->follower));
}*/

void ResetFollowerSaveBlock1(void)
{
    ResetTrainerTowerResults();
    memset(&gSaveBlock1Ptr->follower, 0, sizeof(gSaveBlock1Ptr->follower));
}


