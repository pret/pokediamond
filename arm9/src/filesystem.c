#include "global.h"
#include "FS_file.h"
#include "heap.h"
#include "filesystem.h"

static char * sNarcFileList[] = {
    "battle/skill/waza_seq.narc",
    "battle/skill/sub_seq.narc",
#ifdef PEARL
    "poketool/personal_pearl/personal.narc",
#else
    "poketool/personal/personal.narc",
#endif
    "poketool/personal/growtbl.narc",
    "poketool/pokegra/pokegra.narc",
    "poketool/pokegra/height.narc",
    "poketool/trgra/trbgra.narc",
    "battle/graphic/batt_bg.narc",
    "wazaeffect/we.arc",
    "poketool/waza/waza_tbl.narc",
    "fielddata/script/scr_seq_release.narc",
    "msgdata/scenario/scr_msg.narc",
    "graphic/poketch.narc",
    "graphic/bag_gra.narc",
    "graphic/font.narc",
    "itemtool/itemdata/item_data.narc",
    "itemtool/itemdata/item_icon.narc",
    "graphic/tmap_gra.narc",
    "graphic/box.narc",
    "poketool/icongra/poke_icon.narc",
    "graphic/plist_gra.narc",
    "wazaeffect/effectclact/wechar.narc",
    "wazaeffect/effectclact/wepltt.narc",
    "wazaeffect/effectclact/wecell.narc",
    "wazaeffect/effectclact/wecellanm.narc",
    "graphic/imageclip.narc",
    "msgdata/msg.narc",
    "battle/graphic/batt_obj.narc",
    "data/underg_radar.narc",
    "wazaeffect/effectdata/waza_particle.narc",
    "battle/skill/be_seq.narc",
    "data/namein.narc",
    "fielddata/eventdata/zone_event_release.narc",
    "poketool/personal/wotbl.narc",
    "poketool/personal/evo.narc",
    "graphic/fontoam.narc",
    "graphic/field_board.narc",
    "fielddata/encountdata/d_enc_data.narc",
    "graphic/winframe.narc",
    "graphic/pst_gra.narc",
    "fielddata/build_model/build_model.narc",
    "fielddata/mapmatrix/map_matrix.narc",
    "fielddata/areadata/area_data.narc",
    "fielddata/areadata/area_build_model/area_build.narc",
    "fielddata/areadata/area_map_tex/map_tex_set.narc",
    "contest/graphic/contest_bg.narc",
    "contest/graphic/contest_obj.narc",
    "data/ugeffect_obj_graphic.narc",
    "demo/title/titledemo.narc",
    "fielddata/areadata/area_move_model/move_model_list.narc",
    "data/ug_trap.narc",
    "graphic/trainer_case.narc",
    "data/ug_fossil.narc",
    "graphic/ntag_gra.narc",
    "data/tradelist.narc",
    "data/ug_parts.narc",
    "graphic/opening.narc",
    "poketool/trainer/trdata.narc",
    "poketool/trainer/trpoke.narc",
    "poketool/trmsg/trtbl.narc",
    "poketool/trgra/trfgra.narc",
    "particledata/particledata.narc",
    "graphic/shop_gra.narc",
    "wazaeffect/we_sub.narc",
    "data/ug_anim.narc",
    "data/weather_sys.narc",
    "graphic/menu_gra.narc",
    "fielddata/land_data/land_data_release.narc",
    "itemtool/itemdata/nuts_data.narc",
    "resource/eng/zukan/zukan.narc",
    "poketool/pokefoot/pokefoot.narc",
    "fielddata/areadata/area_build_model/areabm_texset.narc",
    "battle/graphic/b_plist_gra.narc",
    "graphic/config_gra.narc",
    "graphic/unionroom.narc",
    "application/zukanlist/zkn_data/zukan_data.narc",
    "graphic/pmsi.narc",
    "battle/graphic/b_bag_gra.narc",
    "graphic/oekaki.narc",
    "graphic/mail_gra.narc",
    "graphic/f_note_gra.narc",
    "data/mmodel/mmodel.narc",
    "graphic/ev_pokeselect.narc",
    "graphic/poru_gra.narc",
    "graphic/touch_subwindow.narc",
    "graphic/fld_comact.narc",
    "graphic/record.narc",
    "graphic/porudemo.narc",
    "graphic/poruact.narc",
    "data/wifinote.narc",
    "contest/data/contest_data.narc",
    "application/custom_ball/data/cb_data.narc",
    "data/wifip2pmatch.narc",
    "graphic/demo_trade.narc",
    "pokeanime/poke_anm.narc",
    "graphic/mysign.narc",
    "fielddata/mm_list/move_model_list.narc",
    "data/field_cutin.narc",
    "data/demo_climax.narc",
    "wazaeffect/effectdata/ball_particle.narc",
    "wazaeffect/pt_debug/debug_particle.narc",
    "graphic/dendou_pc.narc",
    "application/wifi_earth/wifi_earth_place.narc",
    "battle/tr_ai/tr_ai_seq.narc",
    "graphic/worldtrade.narc",
    "graphic/dendou_demo.narc",
    "arc/encdata_ex.narc",
    "data/mmodel/fldeff.narc",
    "battle/graphic/vs_demo_gra.narc",
    "poketool/pokezukan.narc",
    "arc/bm_anime.narc",
    "arc/bm_anime_list.narc",
    "graphic/field_encounteffect.narc",
    "graphic/waza_oshie_gra.narc",
    "poketool/pokeanm/pokeanm.narc",
    "fielddata/pokemon_trade/fld_trade.narc",
    "graphic/mystery.narc",
    "poketool/pokegra/otherpoke.narc",
    "demo/egg/data/egg_data.narc",
    "demo/egg/data/particle/egg_demo_particle.narc",
    "arc/ship_demo.narc",
    "poketool/pokegra/height_o.narc",
    "graphic/nutmixer.narc",
    "graphic/btower.narc",
    "demo/shinka/data/particle/shinka_demo_particle.narc",
    "demo/intro/intro.narc",
    "arc/tv.narc",
    "graphic/ending.narc",
    "demo/title/op_demo.narc",
    "application/wifi_earth/wifi_earth.narc",
    "graphic/ranking.narc",
    "arc/ppark.narc",
    "demo/syoujyou/syoujyou.narc",
    "data/slot.narc",
    "battle/b_tower/btdtr.narc",
    "battle/b_tower/btdpm.narc",
    "demo/intro/intro_tv.narc",
    "poketool/trmsg/trtblofs.narc",
    "poketool/pokegra/poke_yofs.narc",
    "application/zukanlist/zkn_data/zukan_enc_diamond.narc",
    "application/zukanlist/zkn_data/zukan_enc_pearl.narc",
    "graphic/hiden_effect.narc",
    "poketool/pokegra/poke_shadow.narc",
    "fielddata/encountdata/p_enc_data.narc",
    "poketool/pokegra/poke_shadow_ofx.narc",
    "poketool/shinzukan.narc",
};

void ReadFromNarcMemberByPathAndId(void * dest, const char * path, s32 file_idx, u32 offset, u32 size)
{
    FSFile file;
    register u32 chunk_starts[3];
    u32 btnf_size = 0;
    u32 chunk_size = 0;
    u32 file_start = 0;
    u32 file_end = 0;
    u16 num_files = 0;

    FS_InitFile(&file);
    FS_OpenFile(&file, path);

    FS_SeekFile(&file, 12, FS_SEEK_SET);
    FS_ReadFile(&file, &chunk_size, 2);
    chunk_starts[0] = chunk_size;
    FS_SeekFile(&file, (s32)(chunk_starts[0] + 4), FS_SEEK_SET);
    FS_ReadFile(&file, &chunk_size, 4);
    FS_ReadFile(&file, &num_files, 2);
    GF_ASSERT(num_files > file_idx);
    chunk_starts[1] = chunk_starts[0] + chunk_size;
    FS_SeekFile(&file, (s32)(chunk_starts[1] + 4), FS_SEEK_SET);
    FS_ReadFile(&file, &chunk_size, 4);
    btnf_size = chunk_size;
    FS_SeekFile(&file, (s32)(chunk_starts[0] + 12 + 8 * file_idx), FS_SEEK_SET);
    FS_ReadFile(&file, &file_start, 4);
    FS_ReadFile(&file, &file_end, 4);
    chunk_starts[2] = chunk_starts[1] + btnf_size;
    FS_SeekFile(&file, (s32)(chunk_starts[2] + 8 + file_start + offset), FS_SEEK_SET);
    if (size == 0)
        chunk_size = file_end - file_start;
    else
        chunk_size = size;
    GF_ASSERT(chunk_size != 0);
    FS_ReadFile(&file, dest, (s32)chunk_size);
    FS_CloseFile(&file);
}

void * AllocAndReadFromNarcMemberByPathAndId(const char * path, s32 file_idx, HeapID heapId, u32 offset, u32 size, BOOL r4)
{
    FSFile file;
    register u32 chunk_starts[3];
    u32 btnf_size = 0;
    u32 chunk_size = 0;
    u32 file_start = 0;
    u32 file_end = 0;
    u16 num_files = 0;
    void * dest = NULL;

    FS_InitFile(&file);
    FS_OpenFile(&file, path);

    FS_SeekFile(&file, 12, FS_SEEK_SET);
    FS_ReadFile(&file, &chunk_size, 2);
    chunk_starts[0] = chunk_size;
    FS_SeekFile(&file, (s32)(chunk_starts[0] + 4), FS_SEEK_SET);
    FS_ReadFile(&file, &chunk_size, 4);
    FS_ReadFile(&file, &num_files, 2);
    GF_ASSERT(num_files > file_idx);
    chunk_starts[1] = chunk_starts[0] + chunk_size;
    FS_SeekFile(&file, (s32)(chunk_starts[1] + 4), FS_SEEK_SET);
    FS_ReadFile(&file, &chunk_size, 4);
    btnf_size = chunk_size;
    FS_SeekFile(&file, (s32)(chunk_starts[0] + 12 + 8 * file_idx), FS_SEEK_SET);
    FS_ReadFile(&file, &file_start, 4);
    FS_ReadFile(&file, &file_end, 4);
    chunk_starts[2] = chunk_starts[1] + btnf_size;
    FS_SeekFile(&file, (s32)(chunk_starts[2] + 8 + file_start + offset), FS_SEEK_SET);
    if (size == 0)
        chunk_size = file_end - file_start;
    else
        chunk_size = size;
    GF_ASSERT(chunk_size != 0);
    switch (r4)
    {
    case 0:
        dest = AllocFromHeap(heapId, chunk_size);
        break;
    default:
        dest = AllocFromHeapAtEnd(heapId, chunk_size);
        break;
    }
    FS_ReadFile(&file, dest, (s32)chunk_size);
    FS_CloseFile(&file);
    return dest;
}

void ReadWholeNarcMemberByIdPair(void * dest, NarcId narc_id, s32 file_id)
{
    ReadFromNarcMemberByPathAndId(dest, sNarcFileList[narc_id], file_id, 0, 0);
}

void * AllocAndReadWholeNarcMemberByIdPair(NarcId narc_id, s32 file_id, HeapID heapId)
{
    return AllocAndReadFromNarcMemberByPathAndId(sNarcFileList[narc_id], file_id, heapId, 0, 0, FALSE);
}

void * AllocAtEndAndReadWholeNarcMemberByIdPair(NarcId narc_id, s32 file_id, HeapID heapId)
{
    return AllocAndReadFromNarcMemberByPathAndId(sNarcFileList[narc_id], file_id, heapId, 0, 0, TRUE);
}

void ReadFromNarcMemberByIdPair(void * dest, NarcId narc_id, s32 file_id, u32 offset, u32 size)
{
    ReadFromNarcMemberByPathAndId(dest, sNarcFileList[narc_id], file_id, offset, size);
}

void * AllocAndReadFromNarcMemberByIdPair(NarcId narc_id, s32 file_id, HeapID heapId, u32 offset, u32 size)
{
    return AllocAndReadFromNarcMemberByPathAndId(sNarcFileList[narc_id], file_id, heapId, offset, size, FALSE);
}

void * AllocAtEndAndReadFromNarcMemberByIdPair(NarcId narc_id, s32 file_id, HeapID heapId, u32 offset, u32 size)
{
    return AllocAndReadFromNarcMemberByPathAndId(sNarcFileList[narc_id], file_id, heapId, offset, size, TRUE);
}

u32 GetNarcMemberSizeByIdPair(NarcId narc_id, s32 file_idx)
{
    FSFile file;
    register u32 chunk_starts[3];
    u32 btnf_size = 0;
    u32 chunk_size = 0;
    u32 file_start = 0;
    u32 file_end = 0;
    u16 num_files = 0;

    FS_InitFile(&file);
    FS_OpenFile(&file, sNarcFileList[narc_id]);

    FS_SeekFile(&file, 12, FS_SEEK_SET);
    FS_ReadFile(&file, &chunk_size, 2);
    chunk_starts[0] = chunk_size;
    FS_SeekFile(&file, (s32)(chunk_starts[0] + 4), FS_SEEK_SET);
    FS_ReadFile(&file, &chunk_size, 4);
    FS_ReadFile(&file, &num_files, 2);
    GF_ASSERT(num_files > file_idx);
    chunk_starts[1] = chunk_starts[0] + chunk_size;
    FS_SeekFile(&file, (s32)(chunk_starts[1] + 4), FS_SEEK_SET);
    FS_ReadFile(&file, &chunk_size, 4);
    btnf_size = chunk_size;
    FS_SeekFile(&file, (s32)(chunk_starts[0] + 12 + 8 * file_idx), FS_SEEK_SET);
    FS_ReadFile(&file, &file_start, 4);
    FS_ReadFile(&file, &file_end, 4);
    chunk_starts[2] = chunk_starts[1] + btnf_size;
    FS_SeekFile(&file, (s32)(chunk_starts[2] + 8 + file_start + 0), FS_SEEK_SET);
    chunk_size = file_end - file_start;
    GF_ASSERT(chunk_size != 0);
    // Bug: File is never closed
    return chunk_size;
}

NARC * NARC_New(NarcId narc_id, HeapID heapId)
{
    NARC * narc = (NARC *)AllocFromHeap(heapId, sizeof(NARC));
    u32 btnf_start;
    u32 chunk_size;
    if (narc != NULL)
    {
        narc->btaf_start = 0;
        FS_InitFile(&narc->file);
        FS_OpenFile(&narc->file, sNarcFileList[narc_id]);
        FS_SeekFile(&narc->file, 12, FS_SEEK_SET);
        FS_ReadFile(&narc->file, &narc->btaf_start, 2);
        FS_SeekFile(&narc->file, (s32)(narc->btaf_start + 4), FS_SEEK_SET);
        FS_ReadFile(&narc->file, &chunk_size, 4);
        FS_ReadFile(&narc->file, &narc->num_files, 2);
        btnf_start = narc->btaf_start + chunk_size;
        FS_SeekFile(&narc->file, (s32)(btnf_start + 4), FS_SEEK_SET);
        FS_ReadFile(&narc->file, &chunk_size, 4);
        narc->gmif_start = btnf_start + chunk_size;
    }
    return narc;
}

void NARC_Delete(NARC * narc)
{
    FS_CloseFile(&narc->file);
    FreeToHeap(narc); // free to heap
}

void * NARC_AllocAndReadWholeMember(NARC * narc, u32 file_id, HeapID heapId)
{
    u32 file_start;
    u32 file_end;
    void * dest;
    GF_ASSERT(narc->num_files > file_id);
    FS_SeekFile(&narc->file, (s32)(narc->btaf_start + 12 + 8 * file_id), FS_SEEK_SET);
    FS_ReadFile(&narc->file, &file_start, 4);
    FS_ReadFile(&narc->file, &file_end, 4);
    FS_SeekFile(&narc->file, (s32)(narc->gmif_start + 8 + file_start), FS_SEEK_SET);
    dest = AllocFromHeap(heapId, file_end - file_start);
    if (dest != NULL)
    {
        FS_ReadFile(&narc->file, dest, (s32)(file_end - file_start));
    }
    return dest;
}

void NARC_ReadWholeMember(NARC * narc, u32 file_id, void * dest)
{
    u32 file_start;
    u32 file_end;
    GF_ASSERT(narc->num_files > file_id);
    FS_SeekFile(&narc->file, (s32)(narc->btaf_start + 12 + 8 * file_id), FS_SEEK_SET);
    FS_ReadFile(&narc->file, &file_start, 4);
    FS_ReadFile(&narc->file, &file_end, 4);
    FS_SeekFile(&narc->file, (s32)(narc->gmif_start + 8 + file_start), FS_SEEK_SET);
    FS_ReadFile(&narc->file, dest, (s32)(file_end - file_start));
}

u32 NARC_GetMemberSize(NARC * narc, u32 file_id)
{
    u32 file_start;
    u32 file_end;
    GF_ASSERT(narc->num_files > file_id);
    FS_SeekFile(&narc->file, (s32)(narc->btaf_start + 12 + 8 * file_id), FS_SEEK_SET);
    FS_ReadFile(&narc->file, &file_start, 4);
    FS_ReadFile(&narc->file, &file_end, 4);
    return file_end - file_start;
}

void NARC_ReadFromMember(NARC * narc, u32 file_id, u32 pos, u32 size, void * dest)
{
    u32 file_start;
    GF_ASSERT(narc->num_files > file_id);
    FS_SeekFile(&narc->file, (s32)(narc->btaf_start + 12 + 8 * file_id), FS_SEEK_SET);
    FS_ReadFile(&narc->file, &file_start, 4);
    FS_SeekFile(&narc->file, (s32)(narc->gmif_start + 8 + file_start + pos), FS_SEEK_SET);
    FS_ReadFile(&narc->file, dest, (s32)size);
}

void NARC_ReadFile(NARC * narc, u32 size, void * dest)
{
    FS_ReadFile(&narc->file, dest, (s32)size);
}

u16 NARC_GetFileCount(NARC * narc)
{
    return narc->num_files;
}
