/*--
  Open3DMotion 
  Copyright (c) 2004-2012.
  All rights reserved.
  See LICENSE.txt for more information.
--*/

#ifndef _ORMPP_BIN_MEM_FACTORY_H_
#define _ORMPP_BIN_MEM_FACTORY_H_

#include "Open3DMotion/OpenORM/Leaves/MemoryHandler.h"
#include "Open3DMotion/OpenORM/Mappings/RichBinary/BinaryStructure.h"

namespace Open3DMotion
{
	class BinMemFactory
	{
	public:
		virtual ~BinMemFactory() {};
		virtual MemoryHandler* Allocate(size_t numframes, const BinaryStructure& framestruct) = 0;
	};

}

#endif
