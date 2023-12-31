/*--
  Open3DMotion 
  Copyright (c) 2004-2012.
  All rights reserved.
  See LICENSE.txt for more information.
--*/

#ifndef _ORMPP_MAP_ARRAY_FLOAT64_H_
#define _ORMPP_MAP_ARRAY_FLOAT64_H_

#include "Open3DMotion/OpenORM/Mappings/MapArraySimpleValue.h"
#include "Open3DMotion/OpenORM/Leaves/TreeFloat64.h"

namespace Open3DMotion
{
	class MapArrayFloat64 : public MapArraySimpleValue<TreeFloat64, double>
	{
	public:
		MapArrayFloat64(const char* _elementname) :
			MapArraySimpleValue<TreeFloat64, double>(_elementname)
		{
		}
	};
}
#endif
