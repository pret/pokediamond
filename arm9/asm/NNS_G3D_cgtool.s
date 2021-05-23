	.include "asm/macros.inc"
	.include "global.inc"

	.section .data

	.global NNS_G3dSendJointSRT_FuncArray
NNS_G3dSendJointSRT_FuncArray: ; 0x02106608
	.word NNSi_G3dSendJointSRTBasic
	.word NNSi_G3dSendJointSRTMaya
	.word NNSi_G3dSendJointSRTSi3d

	.global NNS_G3dGetJointScale_FuncArray
NNS_G3dGetJointScale_FuncArray: ; 0x02106614
	.word NNSi_G3dGetJointScaleBasic
	.word NNSi_G3dGetJointScaleMaya
	.word NNSi_G3dGetJointScaleSi3d

	.global NNS_G3dSendTexSRT_FuncArray
NNS_G3dSendTexSRT_FuncArray: ; 0x02106620
	.word NNSi_G3dSendTexSRTMaya
	.word NNSi_G3dSendTexSRTSi3d
	.word NNSi_G3dSendTexSRT3dsMax
	.word NNSi_G3dSendTexSRTXsi
