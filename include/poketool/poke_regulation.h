//============================================================================================
/**
 * @file	poke_regulation.h
 * @brief	���M�����[�V���������p�v���O����
 * @author	k.ohno
 * @date	2006.5.25
 */
//============================================================================================
#ifndef __POKE_REGULATION_H__
#define __POKE_REGULATION_H__

#include "poketool/poke_tool.h"
#include "savedata/regulation.h"
#include "application/zukanlist/zkn_height_gram.h"

// PokeRegulationMatchPartialPokeParty��PokeRegulationMatchFullPokeParty �̖߂�l
enum{
    POKE_REG_OK,               // ����
    POKE_REG_TOTAL_LV_FAILED,  // �g�[�^����LV���I�[�o�[���Ă���
    POKE_REG_BOTH_POKE,        // �����|�P����������
    POKE_REG_BOTH_ITEM,        // �����A�C�e��������
//--------------------------------------------------------
    POKE_REG_NUM_FAILED,       // �K�v�ȃ|�P�����̐l������������Ă��Ȃ�
    POKE_REG_ILLEGAL_POKE,     // �����ɍ���Ȃ��|�P����������
};

extern ZKN_HEIGHT_GRAM_PTR PokeRegulationInit(int heap_id );
// �|�P���������M�����[�V�����ɓK�����Ă��邩�ǂ������ׂ���A�}�ӂ�j��
extern void PokeRegulationEnd(ZKN_HEIGHT_GRAM_PTR pZKN);
// �|�P���������M�����[�V�����ɓK�����Ă��邩�ǂ������ׂ�  
extern BOOL PokeRegulationCheckPokePara(const REGULATION* pReg, POKEMON_PARAM* pp, ZKN_HEIGHT_GRAM_PTR pZKN);
// �|�P�p�[�e�B�����M�����[�V�����Ɋ��S�K�����Ă��邩�ǂ������ׂ� �o�g���ŏI�`�F�b�N�p
extern int PokeRegulationMatchFullPokeParty(const REGULATION* pReg, POKEPARTY * party,
                                            const ZKN_HEIGHT_GRAM_PTR pZKN, u8* sel);
// �|�P�p�[�e�B���Ƀ��M�����[�V�����ɓK�����Ă���
//  �p�[�e�B�[���g�߂邩�ǂ������ׂ� �K���O�̃|�P���������Ă����v  �󂯕t���p
extern int PokeRegulationMatchPartialPokeParty(const REGULATION* pReg, POKEPARTY * party,ZKN_HEIGHT_GRAM_PTR pZKN);

#endif// __POKE_REGULATION_H__
