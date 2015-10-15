#ifndef __SIM_CON_HASH_H__
#define __SIM_CON_HASH_H__

#include <stdint.h>
#include <string.h>
#include <string>
#include <iostream>

using namespace std;

template<class T>
class SimConHash
{
public:
	SimConHash()
	{
		m_uiNodeNum = 0;
		memset(m_arRing, 0, sizeof(m_arRing));
		memset(m_arCondition, 0, sizeof(m_arCondition));
	}

	~SimConHash();

	T *Query(uint32_t uiKey)
	{
		for (uint32_t uiCur = 0; uiCur < m_uiNodeNum; uiCur++)
		{
			if (uiKey < m_arCondition[uiCur])
			{
				return m_arRing + uiCur;
			}
		}
	}

	T *GetArray()
	{
		return m_arRing;
	}

	uint32_t GetNodeNum();

	void InsertNode(uint32_t uiKeyBeg, T t)
	{
		m_arRing[m_uiNodeNum] = t;
		m_arCondition[m_uiNodeNum] = uiKeyBeg;
		m_uiNodeNum++;
	}

private:

	const uint32_t kMaxNodeNum = 100;

	T m_arRing[kMaxNodeNum];
	uint32_t m_arCondition[kMaxNodeNum];

	uint32_t m_uiNodeNum;

};




#endif
