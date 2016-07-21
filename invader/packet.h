#ifndef __PACKET_H__
#define __PACKET_H__

typedef struct _S_PACKET_BASE {
	unsigned short header;
	unsigned short req_type;
} _S_PACKET_BASE;

typedef struct _S_PACKET_REQ_SETPOS {
	_S_PACKET_BASE m_base;
	unsigned int index;
	float m_fxpos;
	float m_fypos;
} _S_PACKET_REQ_SETPOS;



typedef struct _S_PACKET_REQ_GETPOS {
	_S_PACKET_BASE m_base;
	unsigned int m_nIndex;
} _S_PACKET_REQ_GETPOS;
  

typedef struct _S_PACKET_RCV_POS {
	unsigned short header;
	unsigned short m_nIndex;
	float m_fxpos;
	float m_fypos;
} _S_PACKET_RCV_POS;

#endif

