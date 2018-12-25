/*!
 * \file       at8.h
 * \brief      chip header file
 * \author     HuangTing
 * \date       2018.06.04 (auto generated)
 * \details    dispatch real chip header file by ic definition.
 */

#ifndef AT8_H_CPU_DISPATCH
#define AT8_H_CPU_DISPATCH

#ifdef __CPU_AT8A513
#  define __CPU_HAS_SET 1
#  include <at8a513.h>
#endif

#ifdef __CPU_AT8A513B
#  define __CPU_HAS_SET 1
#  include <at8a513b.h>
#endif

#ifdef __CPU_AT8A513C
#  define __CPU_HAS_SET 1
#  include <at8a513c.h>
#endif

#ifdef __CPU_AT8A513D
#  define __CPU_HAS_SET 1
#  include <at8a513d.h>
#endif

#ifdef __CPU_AT8A513E
#  define __CPU_HAS_SET 1
#  include <at8a513e.h>
#endif

#ifdef __CPU_AT8A513J
#  define __CPU_HAS_SET 1
#  include <at8a513j.h>
#endif

#ifdef __CPU_AT8A53
#  define __CPU_HAS_SET 1
#  include <at8a53.h>
#endif

#ifdef __CPU_AT8A53B
#  define __CPU_HAS_SET 1
#  include <at8a53b.h>
#endif

#ifdef __CPU_AT8A53D
#  define __CPU_HAS_SET 1
#  include <at8a53d.h>
#endif

#ifdef __CPU_AT8A53J
#  define __CPU_HAS_SET 1
#  include <at8a53j.h>
#endif

#ifdef __CPU_AT8A54
#  define __CPU_HAS_SET 1
#  include <at8a54.h>
#endif

#ifdef __CPU_AT8A54D
#  define __CPU_HAS_SET 1
#  include <at8a54d.h>
#endif

#ifdef __CPU_AT8A56
#  define __CPU_HAS_SET 1
#  include <at8a56.h>
#endif

#ifdef __CPU_AT8B62D
#  define __CPU_HAS_SET 1
#  include <at8b62d.h>
#endif

#ifdef __CPU_AT8B71A
#  define __CPU_HAS_SET 1
#  include <at8b71a.h>
#endif

#ifdef __CPU_AT8B71D
#  define __CPU_HAS_SET 1
#  include <at8b71d.h>
#endif

#ifdef __CPU_AT8B72A
#  define __CPU_HAS_SET 1
#  include <at8b72a.h>
#endif

#ifndef __CPU_HAS_SET
#  ifdef __SDCC
#    error "IC is not specified. Please use ATWIDE 3.10 and up to define IC automatically. Or #define __CPU_XXX before including NY8.h."
#  endif
#endif

#endif /* end of include guard: AT8_H_CPU_DISPATCH */