//=============================================================================
/**
 * @file	ug_goods.h
 * @brief	�n����GOODS�����Ǘ�����N���X
 * @author	k.ohno
 * @date    2006.02.14
 */
//=============================================================================

#ifndef __UG_GOODS_H__
#define __UG_GOODS_H__

#define UG_GOODS_NONE (0)

/*
// GOODS�^�C�v
enum GoodsType_e {
    UG_GOODS_NONE = 0,
    UG_GOODS_PC1,  //�n���p�p�\�R�����n�^1	��b�B���x��1
    UG_GOODS_PC2,  //�n���p�p�\�R�����n�^2	��b�B���x��2
    UG_GOODS_PC3,  //�n���p�p�\�R�����n�^3	��b�B���x��3
    UG_GOODS_PC4,  //�n���p�p�\�R�����n�^4	��b�B���x��4
    UG_GOODS_OBJECT01,   //�|�P�Z���e�[�u��	�O�b�Y
    UG_GOODS_OBJECT02,   //������N�b�V����	�O�b�Y
    UG_GOODS_OBJECT03,   //�����N�b�V����	�O�b�Y
    UG_GOODS_OBJECT04,   //�����ӂ��}�V��	�O�b�Y
    UG_GOODS_OBJECT05,   //�|�P�Z���O�b�Y	�O�b�Y
    UG_GOODS_OBJECT06,   //�V���b�v����	�O�b�Y
    UG_GOODS_OBJECT07,   //���傤�Ђ񂾂�	�O�b�Y
    UG_GOODS_OBJECT08,   //�f�p�[�g�O�b�Y	�O�b�Y
    UG_GOODS_OBJECT09,   //�f�p�[�g�O�b�Y	�O�b�Y
    UG_GOODS_OBJECT10,   //�e���r	�O�b�Y
    UG_GOODS_OBJECT11,   //�s���N�N�b�V����	�O�b�Y
    UG_GOODS_OBJECT12,   //������	�O�b�Y
    UG_GOODS_OBJECT13,   //�ꂢ������	�O�b�Y
    UG_GOODS_OBJECT14,   //�V���N	�O�b�Y
    UG_GOODS_OBJECT15,   //�Q�[����	�O�b�Y
    UG_GOODS_OBJECT16,   //���̃^���X	�O�b�Y
    UG_GOODS_OBJECT17,   //�ӂ��ӂ��x�b�h	�O�b�Y
    UG_GOODS_OBJECT18,   //���������ق񂾂�	�O�b�Y
    UG_GOODS_OBJECT19,   //���������ق񂾂�	�O�b�Y
    UG_GOODS_OBJECT20,   //���݂΂�	�O�b�Y
    UG_GOODS_OBJECT21,   //�_���{�[��	�O�b�Y
    UG_GOODS_OBJECT22,   //�������ȃe�[�u��	�O�b�Y
    UG_GOODS_OBJECT23,   //�����كO�b�Y	�O�b�Y
    UG_GOODS_OBJECT24,   //�����كO�b�Y	�O�b�Y
    UG_GOODS_OBJECT25,   //�}���كO�b�Y	�O�b�Y
    UG_GOODS_OBJECT26,   //�}���كO�b�Y	�O�b�Y
    UG_GOODS_OBJECT27,   //TV�ǃO�b�Y	�O�b�Y
    UG_GOODS_OBJECT28,   //TV�ǃO�b�Y	�O�b�Y
    UG_GOODS_OBJECT29,   //�A�W�g�O�b�Y	�O�b�Y
    UG_GOODS_OBJECT30,   //�A�W�g�O�b�Y	�O�b�Y
    UG_GOODS_OBJECT31,   //�����イ��	�O�b�Y
    UG_GOODS_OBJECT32,   //���񂫂イ�}�V��	�O�b�Y
    UG_GOODS_OBJECT33,   //��������}�V��	�O�b�Y
    UG_GOODS_OBJECT34,   //���񂫂イ����	�O�b�Y
    UG_GOODS_OBJECT35,   //�W���̂�������	�O�b�Y
    UG_GOODS_OBJECT36,   //�W���̂�	�O�b�Y
    UG_GOODS_OBJECT37,   //�W���̃X�C�b�`	�O�b�Y
    UG_GOODS_OBJECT38,   //�W���̂�����	�O�b�Y
    UG_GOODS_OBJECT39,   //�ł�ǂ��̂�����	�O�b�Y
    UG_GOODS_OBJECT40,   //������̂�����	�O�b�Y
    UG_GOODS_OBJECT41,   //��������Ђ傤	�O�b�Y
    UG_GOODS_OBJECT42,   //������Ђ傤	�O�b�Y
    UG_GOODS_OBJECT43,   //�������Ȃ���	�O�b�Y
    UG_GOODS_OBJECT44,   //�������Ȃ���	�O�b�Y
    UG_GOODS_OBJECT45,   //�������e���g	�O�b�Y
    UG_GOODS_OBJECT46,   //�������e���g	�O�b�Y
    UG_GOODS_OBJECT47,   //�Ƃ��߂��e���g	�O�b�Y
    UG_GOODS_OBJECT48,   //�߂���u���b�N�P	�O�b�Y
    UG_GOODS_OBJECT49,   //�߂���u���b�N�Q	�O�b�Y
    UG_GOODS_OBJECT50,   //�߂���u���b�N�R	�O�b�Y
    UG_GOODS_OBJECT51,   //�߂���u���b�N�S	�O�b�Y
    UG_GOODS_OBJECT52,   //�߂���u���b�N�T	�O�b�Y
    UG_GOODS_OBJECT53,   //���ĂȂ��u���b�N	�O�b�Y
    UG_GOODS_OBJECT54,   //���Ă��׃u���b�N	�O�b�Y
    UG_GOODS_OBJECT55,   //�悱���׃u���b�N	�O�b�Y
    UG_GOODS_TRAP01,     //���[�v������	㩃O�b�Y
    UG_GOODS_TRAP02,     //�e���|�[�g������	㩃O�b�Y
    UG_GOODS_TRAP03,     //���Ȃ�����	㩃O�b�Y
    UG_GOODS_TRAP04,     //�������Ȃ�����	㩃O�b�Y
    UG_GOODS_TRAP05,     //�͂�Ă񂻂���	㩃O�b�Y
    UG_GOODS_TRAP06,     //�����񂻂���	㩃O�b�Y
    UG_GOODS_TRAP07,     //�͂��肻����	㩃O�b�Y
    UG_GOODS_TRAP08,     //�����邻����	㩃O�b�Y
    UG_GOODS_TRAP09,     //������������	㩃O�b�Y
    UG_GOODS_TRAP10,     //���ނ肻����	㩃O�b�Y
    UG_GOODS_TRAP11,     //����܂�������	㩃O�b�Y
    UG_GOODS_TRAP12,     //���킻����	㩃O�b�Y
    UG_GOODS_TRAP13,     //�炭����������	㩃O�b�Y
    UG_GOODS_TRAP14,     //���킻����	㩃O�b�Y
    UG_GOODS_TRAP15,     //�o�u��������	㩃O�b�Y
    UG_GOODS_TRAP16,     //���тꂻ����	㩃O�b�Y
    UG_GOODS_TRAP17,     //�ł񂶂͂�����	㩃O�b�Y
    UG_GOODS_TRAP18,     //�����ق�������	㩃O�b�Y
    UG_GOODS_TRAP19,     //�T�C����������	㩃O�b�Y
    UG_GOODS_TRAP20,     //���̂͂�����	㩃O�b�Y
    UG_GOODS_TRAP21,     //�͂Ȃт炻����	㩃O�b�Y
    UG_GOODS_TRAP22,     //�Ђ̂�������	㩃O�b�Y
    UG_GOODS_TRAP23,     //�ق̂�������	㩃O�b�Y
    UG_GOODS_TRAP24,     //���[�_�[������	㩃O�b�Y
    UG_GOODS_TROPHY01,   //���킢���J�b�v	�g���t�B�[
    UG_GOODS_TROPHY02,   //�����������J�b�v	�g���t�B�[
    UG_GOODS_TROPHY03,   //���������J�b�v	�g���t�B�[
    UG_GOODS_TROPHY04,   //�����܂����J�b�v	�g���t�B�[
    UG_GOODS_TROPHY05,   //���������J�b�v	�g���t�B�[
    UG_GOODS_TROPHY06,   //�������������傤	�g���t�B�[
    UG_GOODS_TROPHY07,   //�s���N�������傤	�g���t�B�[
    UG_GOODS_TROPHY08,   //�������������傤	�g���t�B�[
    UG_GOODS_TROPHY09,   //�����낷�����傤	�g���t�B�[
    UG_GOODS_TROPHY10,   //���ꂢ�Ȃق�����	�g���t�B�[
    UG_GOODS_TROPHY11,   //�����₭�ق�����	�g���t�B�[
    UG_GOODS_TROPHY12,   //����҂̂ق�����	�g���t�B�[
    UG_GOODS_TROPHY13,   //����߂��ق�����	�g���t�B�[
    UG_GOODS_TROPHY14,   //�u�����Y�g���t�B�[	�g���t�B�[
    UG_GOODS_TROPHY15,   //�V���o�[�g���t�B�[	�g���t�B�[
    UG_GOODS_TROPHY16,   //�S�[���h�g���t�B�[	�g���t�B�[
    UG_GOODS_TROPHY17,   //�v���`�i�g���t�B�[	�g���t�B�[
    UG_GOODS_TROPHY18,   //�{�[���̃I�u�W�F	�g���t�B�[
    UG_GOODS_TROPHY19,   //�܂�܂�I�u�W�F	�g���t�B�[
    UG_GOODS_TROPHY20,   //�����΂�I�u�W�F	�g���t�B�[
    UG_GOODS_DOLL01,     //�|�P�����h�[��	�ʂ������
    UG_GOODS_DOLL02,     //�|�P�����h�[��	�ʂ������
    UG_GOODS_DOLL03,     //�|�P�����h�[��	�ʂ������
    UG_GOODS_DOLL04,     //�|�P�����h�[��	�ʂ������
    UG_GOODS_DOLL05,     //�|�P�����h�[��	�ʂ������
    UG_GOODS_DOLL06,     //�|�P�����h�[��	�ʂ������
    UG_GOODS_DOLL07,     //�|�P�����h�[��	�ʂ������
    UG_GOODS_DOLL08,     //�|�P�����h�[��	�ʂ������
    UG_GOODS_DOLL09,     //�|�P�����h�[��	�ʂ������
    UG_GOODS_DOLL10,     //�|�P�����h�[��	�ʂ������
    UG_GOODS_DOLL11,     //�|�P�����h�[��	�ʂ������
    UG_GOODS_DOLL12,     //�|�P�����h�[��	�ʂ������
    UG_GOODS_DOLL13,     //�|�P�����h�[��	�ʂ������
    UG_GOODS_DOLL14,     //�|�P�����h�[��	�ʂ������
    UG_GOODS_DOLL15,     //�|�P�����h�[��	�ʂ������
    UG_GOODS_DOLL16,     //�|�P�����h�[��	�ʂ������
    UG_GOODS_DOLL17,     //�|�P�����h�[��	�ʂ������
    UG_GOODS_DOLL18,     //�|�P�����h�[��	�ʂ������
    UG_GOODS_DOLL19,     //�|�P�����h�[��	�ʂ������
    UG_GOODS_DOLL20,     //�|�P�����h�[��	�ʂ������
    UG_GOODS_DOLL21,     //�|�P�����h�[��	�������Ȃʂ������
    UG_GOODS_DOLL22,     //�|�P�����h�[��	�������Ȃʂ������
    UG_GOODS_DOLL23,     //�|�P�����h�[��	�������Ȃʂ������
    UG_GOODS_DOLL24,     //�|�P�����h�[��	�������Ȃʂ������
    UG_GOODS_DOLL25,     //�|�P�����h�[��	�������Ȃʂ������
    UG_GOODS_DOLL26,     //�|�P�����h�[��	�������Ȃʂ������
    UG_GOODS_DOLL27,     //�|�P�����h�[��	�������Ȃʂ������
    UG_GOODS_DOLL28,     //�|�P�����h�[��	�������Ȃʂ������
    UG_GOODS_DOLL29,     //�|�P�����h�[��	�������Ȃʂ������
    UG_GOODS_DOLL30,     //�|�P�����h�[��	�������Ȃʂ������
    UG_GOODS_POSTER01,   //�|�P�����|�X�^�[	�|�X�^�[
    UG_GOODS_POSTER02,   //�|�P�����|�X�^�[	�|�X�^�[
    UG_GOODS_POSTER03,   //�|�P�����|�X�^�[	�|�X�^�[
    UG_GOODS_POSTER04,   //�|�P�����|�X�^�[	�|�X�^�[
    UG_GOODS_POSTER05,   //�|�P�����|�X�^�[	�|�X�^�[
    UG_GOODS_POSTER06,   //�|�P�����|�X�^�[	�|�X�^�[
    UG_GOODS_POSTER07,   //�|�P�����|�X�^�[	�|�X�^�[
    UG_GOODS_POSTER08,   //�|�P�����|�X�^�[	�|�X�^�[
    UG_GOODS_POSTER09,   //�|�P�����|�X�^�[	�|�X�^�[
    UG_GOODS_POSTER10,   //�|�P�����|�X�^�[	�|�X�^�[
    UG_GOODS_POSTER11,   //�|�P�����|�X�^�[	�������ȃ|�X�^�[
    UG_GOODS_POSTER12,   //�|�P�����|�X�^�[	�������ȃ|�X�^�[
    UG_GOODS_POSTER13,   //�|�P�����|�X�^�[	�������ȃ|�X�^�[
    UG_GOODS_POSTER14,   //�|�P�����|�X�^�[	�������ȃ|�X�^�[
    UG_GOODS_POSTER15,   //�|�P�����|�X�^�[	�������ȃ|�X�^�[
    UG_GOODS_POSTER16,   //�|�P�����|�X�^�[	�������ȃ|�X�^�[
    UG_GOODS_POSTER17,   //�|�P�����|�X�^�[	�������ȃ|�X�^�[
    UG_GOODS_POSTER18,   //�|�P�����|�X�^�[	�������ȃ|�X�^�[
    UG_GOODS_POSTER19,   //�|�P�����|�X�^�[	�������ȃ|�X�^�[
    UG_GOODS_POSTER20,   //�|�P�����|�X�^�[	�������ȃ|�X�^�[
    UG_GOODS_POSTER21,   //�|�P�����|�X�^�[	�������ȃ|�X�^�[
    UG_GOODSTYPE_MAX,
};
*/

#endif // __UG_GOODS_H__




