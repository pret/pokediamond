/*---------------------------------------------------------------------------*
  Project:  simple particle library
  File:     spl_manager.h

  ‚r‚o‚kƒ}ƒl[ƒWƒƒ

  $Id: spl_manager.h,v 1.3 2005/11/09 09:53:26 matsuda Exp $
  $Log: spl_manager.h,v $
  Revision 1.3  2005/11/09 09:53:26  matsuda
  SPLƒ‰ƒCƒuƒ‰ƒŠ‚ªXV‚³‚ê‚½‚Ì‚ÅXV

  Revision 1.9  2005/08/30 09:15:30  okane_shinji
  SPL_SetDrawOrder‚ð’Ç‰Á

  Revision 1.8  2005/06/27 07:46:14  okane_shinji
  Ê£¿ô¥Þ¥Í¡¼¥¸¥ã¤ò¼è¤ê°·¤¦¤È¤­¤Ç¤â·×»»¥µ¥¤¥¯¥ëÀßÄê¤¬Í­¸ú¤Ë¤Ê¤ë¤è¤¦¤Ë½¤Àµ

  Revision 1.7  2005/01/20 04:20:48  okane_shinji
  ƒp[ƒeƒBƒNƒ‹”‚ÆƒGƒ~ƒbƒ^”‚ðŽæ“¾‚·‚éŠÖ”’Ç‰Á

  Revision 1.6  2004/11/26 06:07:31  okane_shinji
  ‹@”\’Ç‰Á

  Revision 1.5  2004/08/17 05:40:39  okane_shinji
  ƒp[ƒeƒBƒNƒ‹‚Ìƒ|ƒŠƒSƒ“‘®«‚Ìmiscƒtƒ‰ƒO‚ð•ÏX‚Å‚«‚é‚æ‚¤‚É•ÏXB

  Revision 1.4  2004/07/05 07:33:02  okane_shinji
  ƒ|ƒŠƒSƒ“IDŠ„‚è“–‚Ä‚ð‰Â•Ï‚ÉBŠÖ”–¼‚ð•ÏXB

  Revision 1.3  2004/06/23 07:21:21  okane_shinji
  ƒJƒ‰[ƒAƒjƒAƒ‹[ƒvÄ¶Aƒ|ƒŠƒSƒ“AƒfƒBƒŒƒNƒVƒ‡ƒiƒ‹ƒrƒ‹ƒ{[ƒh‚Ì‰ü—Ç

  Revision 1.2  2004/05/24 09:44:09  konoh
  ¡ƒƒ‚ƒŠŠm•Û‚Ì•û–@‚ðƒ†[ƒUƒR[ƒ‹ƒoƒbƒN‚Ås‚¤‚æ‚¤‚É•ÏX

  Revision 1.1  2004/04/08 00:23:26  konoh
  (none)

 *---------------------------------------------------------------------------*/

#ifndef __SPL_MANAGER_H__
#define __SPL_MANAGER_H__

#include "spl_emitter.h"
#include "spl_particle.h"
#include "spl_resource.h"
#include "spl_texture.h"

/* \‘¢‘Ì‚È‚Ç -------------------------------------------------------------- */

// ƒƒ‚ƒŠŠm•ÛƒR[ƒ‹ƒoƒbƒN
typedef void* (*SPLAlloc)(u32);

// ƒ}ƒl[ƒWƒƒ\‘¢‘Ì
typedef struct SPLManager
{
    // ƒq[ƒvŠÖŒW
    SPLAlloc alloc;

    // ƒŠƒXƒgŠÖŒW
    SPLEmitterList act_emtr_list;
    SPLEmitterList ina_emtr_list;
    SPLParticleList ina_ptcl_list;

    // ƒŠƒ\[ƒXŠÖŒW
    SPLResource* res_ary;
    SPLTexture*  tex_ary;
    u16 res_num;
    u16 tex_num;

    u16 max_emtr_num;
    u16 max_ptcl_num;
    
    //u16 min_polygonID ;
    //u16 max_polygonID ;

    struct
    {
        u32 min:6;
        u32 max:6;
        u32 current:6;
        u32 fix:6;
        u32 drawOrder:1;
        u32 reserved:7;
    } polygonID ;

    s32 misc_flag ;

    // •`‰æEŒvŽZ‚É•K—v‚Èƒ}ƒl[ƒWƒƒ‚ÌƒJƒŒƒ“ƒgŠÂ‹«‚ðŠi”[‚·‚é‚½‚ß‚Ì\‘¢‘Ì
    struct
    {
        // Œ»Ýˆ—’†‚ÌƒGƒ~ƒbƒ^
        SPLEmitter* p_emtr ;

        // Œ»Ý“K—p‚³‚ê‚Ä‚¢‚éƒJƒƒ‰
        const MtxFx43*    p_cmr  ;
    } current_state ;


    u16 uCurrentCycle ;
    u16 reserved ;

} SPLManager;

/* ------------------------------------------------------------------------- */

#define SPL_MANAGER_DRAWORDER_INREVERSE 0
#define SPL_MANAGER_DRAWORDER_INTURN    1

/* ------------------------------------------------------
 * •`‰æ‡‚ðÝ’è
 *------------------------------------------------------*/
static inline void SPL_SetDrawOrder( SPLManager* p_mgr, int flag )
{
    p_mgr->polygonID.drawOrder = flag ;
}

/* ------------------------------------------------------
 * ƒ|ƒŠƒSƒ“‘®«‚Ìmiscƒtƒ‰ƒO‚ðÝ’è
 *------------------------------------------------------*/
static inline void SPL_SetPolygonAttrMiscFlag( SPLManager* p_mgr, int flag )
{
    p_mgr->misc_flag = flag ;
}

/* ------------------------------------------------------
 * Œ»Ý—LŒø‚ÈƒGƒ~ƒbƒ^‚Ì”‚ðŽæ“¾
 *------------------------------------------------------*/
static inline s32 SPL_GetEmitterNum( SPLManager* p_mgr )
{
    return p_mgr->act_emtr_list.node_num ;
}

/* ------------------------------------------------------
 * Œ»Ý—LŒø‚Èƒp[ƒeƒBƒNƒ‹‚Ì”‚ðŽæ“¾
 *------------------------------------------------------*/
static inline s32 SPL_GetWholeParticleNum( SPLManager* p_mgr )
{
    return p_mgr->max_ptcl_num - p_mgr->ina_ptcl_list.node_num ;
}



#endif
