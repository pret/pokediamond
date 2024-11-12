#include "global.h"

#include "constants/items.h"

#include "scrcmd.h"

const u16 gGameCornerPrizes[19][2] = {
    { ITEM_SILK_SCARF, 1000  },
    { ITEM_WIDE_LENS,  1000  },
    { ITEM_ZOOM_LENS,  1000  },
    { ITEM_METRONOME,  1000  },
    { ITEM_TM90,       2000  },
    { ITEM_TM58,       2000  },
    { ITEM_TM75,       4000  },
    { ITEM_TM32,       4000  },
    { ITEM_TM44,       6000  },
    { ITEM_TM89,       6000  },
    { ITEM_TM10,       6000  },
    { ITEM_TM27,       8000  },
    { ITEM_TM21,       8000  },
    { ITEM_TM35,       10000 },
    { ITEM_TM24,       10000 },
    { ITEM_TM13,       10000 },
    { ITEM_TM29,       10000 },
    { ITEM_TM74,       15000 },
    { ITEM_TM68,       20000 },
};

BOOL ScrCmd_GetPrizeItemIdAndCost(struct ScriptContext *ctx) // 02A6
{
    u16 idx = ScriptGetVar(ctx);
    u16 *prize_item_id = ScriptGetVarPointer(ctx);
    u16 *prize_cost_in_coins = ScriptGetVarPointer(ctx);

    *prize_item_id = gGameCornerPrizes[idx][0];
    *prize_cost_in_coins = gGameCornerPrizes[idx][1];

    return FALSE;
}
