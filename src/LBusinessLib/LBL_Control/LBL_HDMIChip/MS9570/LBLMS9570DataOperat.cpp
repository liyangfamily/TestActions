#include "LBLMS9570DataOperat.h"

namespace LBL
{
	namespace MS9570
	{

		LBLMS9570DataOperat::LBLMS9570DataOperat()
		{
		}


		LBLMS9570DataOperat::~LBLMS9570DataOperat()
		{
		}

		bool LBLMS9570DataOperat::setBypass(int value)
		{
			m_data.bypass = value;
			return false;
		}
		int LBLMS9570DataOperat::getBypass()
		{
			return m_data.bypass;
		}
	}
}