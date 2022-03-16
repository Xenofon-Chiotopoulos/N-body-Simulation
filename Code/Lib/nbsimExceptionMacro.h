/*=============================================================================

  PHAS0100ASSIGNMENT2: PHAS0100 Assignment 2 Gravitational N-body Simulation

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#ifndef nbsimExceptionMacro_h
#define nbsimExceptionMacro_h

#include "nbsimException.h"

#define nbsimExceptionThrow() throw nbsim::Exception(__FILE__,__LINE__)

#endif
