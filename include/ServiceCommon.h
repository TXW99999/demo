#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

class CriticalSection
{
public:
	CriticalSection() { ::InitializeCriticalSection(&m_cs); }
	virtual ~CriticalSection() { ::DeleteCriticalSection(&m_cs); }
	void Lock() { ::EnterCriticalSection(&m_cs); }
	void Unlock() { ::LeaveCriticalSection(&m_cs); }
	operator PCRITICAL_SECTION() { return &m_cs; }

protected:
	CRITICAL_SECTION m_cs;
};

class Locker
{
public:
	Locker(PCRITICAL_SECTION cs) : m_p(cs) { ::EnterCriticalSection(m_p); }
	~Locker() { ::LeaveCriticalSection(m_p); }

protected:
	PCRITICAL_SECTION m_p;
};

typedef struct{
	char ip[32];
	int port;
}_service_info;
