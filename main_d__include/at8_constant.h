/*
 *  \file       at8_constant.h
 *  \brief      chip constant define header file
 *  \author     Willie
 *  \date       2018.04.23
 *  \details    dispatch real chip constant define header file by ic definition.
 */

#ifndef AT8_CONSTANT_H_CPU_DISPATCH
#define AT8_CONSTANT_H_CPU_DISPATCH

#ifdef __CPU_AT8A513
#  include <at8a513_constant.h>
#endif

#ifdef __CPU_AT8A513B
#  include <at8a513b_constant.h>
#endif

#ifdef __CPU_AT8A513C
#  include <at8a513c_constant.h>
#endif

#ifdef __CPU_AT8A513D
#  include <at8a513d_constant.h>
#endif

#ifdef __CPU_AT8A513E
#  include <at8a513e_constant.h>
#endif

#ifdef __CPU_AT8A53
#  include <at8a53_constant.h>
#endif

#ifdef __CPU_AT8A53B
#  include <at8a53b_constant.h>
#endif

#ifdef __CPU_AT8A53D
#  include <at8a53d_constant.h>
#endif

#ifdef __CPU_AT8A54
#  include <at8a54_constant.h>
#endif

#ifdef __CPU_AT8A54D
#  include <at8a54d_constant.h>
#endif

#ifdef __CPU_AT8A56
#  include <at8a56_constant.h>
#endif

#ifdef __CPU_AT8B62D
#  include <at8b62d_constant.h>
#endif

#ifdef __CPU_AT8B71A
#  include <at8b71a_constant.h>
#endif

#ifdef __CPU_AT8B71D
#  include <at8b71d_constant.h>
#endif

#ifdef __CPU_AT8B72A
#  include <at8b72a_constant.h>
#endif

#ifndef __CPU_HAS_SET
#  ifdef __SDCC
#    error "please use ATWIDE at least 3.01 Beta [180420.00] or set __CPU_XXX before include this file."
#  endif
#endif

#endif /* end of include guard: AT8_CONSTANT_H_CPU_DISPATCH */