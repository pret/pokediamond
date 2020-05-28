//===================================================================
/**
 * @file	agbdownload.h
 * @bfief	AGB�J�Z�b�g����̂ӂ����f�[�^�_�E�����[�h
 * @author	Satoshi Mitsuhara
 * @date	06.06.09
 *
 * $Id: agbdownload.h,v 1.1 2006/06/08 17:59:07 mitsuhara Exp $
 */
//===================================================================
#ifndef __AGBDOWNLOAD_H__
#define __AGBDOWNLOAD_H__


// �f�[�^�T�C�Y���u����Ă���A�h���X
#define AGBMISSIONDATASIZE	0x08100000
// �r�[�R����񂪔z�u����Ă���A�h���X
#define AGBBEACONDATAPTR	0x08100010
// �ӂ����f�[�^���z�u����Ă���A�h���X
#define AGBMISSIONDATAPTR	0x08100100

#define AGB_MAKER_CODE		0x3130		// �C�V��

extern int GetAgbCartridgeDataSize(void);
extern BOOL GetAgbCartridgeBeaconData(void *dist, int size);
extern BOOL ReadAgbCartridgeData(void *dist, int size);


#endif	// __AGBDOWNLOAD_H__
/*  */

