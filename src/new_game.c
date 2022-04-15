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

/**
 * Esta función está en el battle hack.
*/

void NewGameInitData(void)
{
    if (gSaveFileStatus == SAVE_STATUS_EMPTY || gSaveFileStatus == SAVE_STATUS_CORRUPT)
        RtcReset();
    gDifferentSaveFile = TRUE;
    gSaveBlock2Ptr->encryptionKey = 0;
    ZeroPlayerPartyMons();
    ZeroEnemyPartyMons();
    ResetPokedex();
    ClearFrontierRecord();
    ClearSav1();
    ClearAllMail();
    gSaveBlock2Ptr->specialSaveWarpFlags = 0;
    gSaveBlock2Ptr->gcnLinkFlags = 0;
    InitPlayerTrainerId();
    PlayTimeCounter_Reset();
    ClearPokedexFlags();
    InitEventData();
    ClearTVShowData();
    ResetGabbyAndTy();
    ClearSecretBases();
    ClearBerryTrees();
    SetMoney(&gSaveBlock1Ptr->money, 3000);
    SetCoins(0);
    ResetLinkContestBoolean();
    ResetGameStats();
    ClearAllContestWinnerPics();
    ClearPlayerLinkBattleRecords();
    InitSeedotSizeRecord();
    InitLotadSizeRecord();
    gPlayerPartyCount = 0;
    ZeroPlayerPartyMons();
    ResetPokemonStorageSystem();
    ClearRoamerData();
    ClearRoamerLocationData();
    gSaveBlock1Ptr->registeredItem = 0;
    ClearBag();
    NewGameInitPCItems();
    ClearPokeblocks();
    ClearDecorationInventories();
    InitEasyChatPhrases();
    SetMauvilleOldMan();
    InitDewfordTrend();
    ResetFanClub();
    ResetLotteryCorner();
    WarpToTruck();
    ScriptContext2_RunNewScript(EventScript_ResetAllMapFlags);
    ResetMiniGamesRecords();
    InitUnionRoomChatRegisteredTexts();
    InitLilycoveLady();
    ResetAllApprenticeData();
    ClearRankingHallRecords();
    InitMatchCallCounters();
    ClearMysteryGift();
    WipeTrainerNameRecords();
    ResetTrainerHillResults();
    ResetContestLinkResults();

    memset(&gSaveBlock1Ptr->follower, 0, sizeof(gSaveBlock1Ptr->follower));
}