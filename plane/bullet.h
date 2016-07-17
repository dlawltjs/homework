#ifndef __BULLET_H__
#define __BULLET_H__

typedef struct {
	int m_nFSM;
	int m_nStep;
	double m_fXpos;
	double m_fYpos;
	
	double m_fvx;
	double m_fvy;
	double m_fSpeed;
		
	double m_faccLifeTime; //현재 생존시간 
	double m_fLifeLimit; //수명

	_S_MAP_OBJECT *m_pBody;

} S_BULLET_OBJECT;

void bullet_init(S_BULLET_OBJECT *pObj,double x,double y,double speed,_S_MAP_OBJECT *pBody);
void  bullet_apply(S_BULLET_OBJECT *pObj,double deltaTick);
void bullet_draw(S_BULLET_OBJECT *pObj,_S_MAP_OBJECT *pMapBuf);

void bullet_fire(S_BULLET_OBJECT *pObj,
int x,int y,
double speed,double vx,double vy,
double lifeLimit);

#endif
