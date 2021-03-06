#ifndef __BUS_CONNECTION_HEADER__
#define __BUS_CONNECTION_HEADER__

#include "JTC.h"
#include "CString.h"
#include "Socket.h"
#include "TunnelConnection.h"
#include "Globals.h"
#include "CCemi_L_BusMon_Frame.h"

using namespace EibStack;

class CBusMonConnection : public CTunnelingConnection
{
public:
	CBusMonConnection(const CString& ipaddress);
	virtual ~CBusMonConnection();

	virtual bool Connect();
	virtual bool HandleTunnelRequest(unsigned char* buffer, int len, CCemi_L_Data_Frame& frame);
};

#endif
