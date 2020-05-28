
extern	void				ShinkaDisp_SystemInit(void);
extern	void				ShinkaDisp_DefaultBlendSet(void);
extern	GF_G3DMAN			*ShinkaDisp_3D_Init(int heapID);
extern	void				ShinkaDisp_3DSetUp(void);
extern	void				ShinkaDisp_3DVramInit(void);
extern	void				ShinkaDisp_ParticleMain(void);
extern	SHINKA_PARTICLE_SYS	*ShinkaParticle_Init(SHINKA_PARTICLE_PARAM* param);
extern	void				ShinkaParticle_SprSet(SHINKA_PARTICLE_SYS* eps, int no);
extern	BOOL				ShinkaParticle_Main(SHINKA_PARTICLE_SYS* eps);
extern	void				ShinkaParticle_End(SHINKA_PARTICLE_SYS* eps);
