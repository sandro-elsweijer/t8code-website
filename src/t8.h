/*
  This file is part of t8code.
  t8code is a C library to manage a collection (a forest) of multiple
  connected adaptive space-trees of general element classes in parallel.

  Copyright (C) 2015 the developers

  t8code is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  t8code is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with t8code; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

/** \file t8.h
 * This is the administrative header file for t8code.
 * It includes standard C headers via subpackages.
 * It also provides application-level convenience code such as logging functions.
 */

#ifndef T8_H
#define T8_H

/* include config headers */
#include <t8_config.h>
#include <sc_config.h>
#if \
  (defined (T8_ENABLE_MPI) && !defined (SC_ENABLE_MPI)) || \
  (!defined (T8_ENABLE_MPI) && defined (SC_ENABLE_MPI))
#error "MPI configured differently in t8code and libsc"
#endif
#if \
  (defined (T8_ENABLE_MPIIO) && !defined (SC_ENABLE_MPIIO)) || \
  (!defined (T8_ENABLE_MPIIO) && defined (SC_ENABLE_MPIIO))
#error "MPI I/O configured differently in t8code and libsc"
#endif

/* indirectly also include p4est_config.h, sc.h */
#include <sc_containers.h>
#include <p4est_base.h>

/** This macro opens the extern "C" brace needed in C headers.
 * It needs to be followed by a semicolon to look like a statement. */
#define T8_EXTERN_C_BEGIN() SC_EXTERN_C_BEGIN

/** This macro closes the extern "C" brace needed in C headers.
 * It needs to be followed by a semicolon to look like a statement. */
#define T8_EXTERN_C_END() SC_EXTERN_C_END

/* call this after including all headers */
T8_EXTERN_C_BEGIN ();

/** Portable way to use the const keyword determined by configure. */
#define t8_const _sc_const

/** Portable way to use the const keyword determined by configure. */
#define t8_restrict _sc_restrict

#define T8_ASSERT P4EST_ASSERT          /**< TODO: write proper function. */
#define T8_ALLOC P4EST_ALLOC            /**< TODO: write proper function. */
#define T8_ALLOC_ZERO P4EST_ALLOC_ZERO  /**< TODO: write proper function. */
#define T8_FREE P4EST_FREE              /**< TODO: write proper function. */

/** A type for processor-local indexing. */
typedef p4est_locidx_t t8_locidx_t;
#define T8_MPI_LOCIDX P4EST_MPI_LOCIDX

/** A type for global indexing that holds really big numbers. */
typedef p4est_gloidx_t t8_gloidx_t;
#define T8_MPI_GLOIDX P4EST_MPI_GLOIDX

/** A type for counting topological entities (trees, tree vertices, ...). */
typedef p4est_topidx_t t8_topidx_t;
#define T8_MPI_TOPIDX P4EST_MPI_TOPIDX

typedef enum {
  T8_MPI_TAG_FIRST = SC_TAG_FIRST,
  T8_MPI_PARTITION_CMESH = SC_TAG_LAST,
  T8_MPI_TAG_LAST
} t8_MPI_tag_t;

/** Return a pointer to an array element indexed by a t8_topidx_t.
 * \param [in] index needs to be in [0]..[elem_count-1].
 * \return           A void * pointing to entry \a it in \a array.
 */
void               *t8_sc_array_index_topidx (sc_array_t * array,
                                              t8_topidx_t it);

/** Return a pointer to an array element indexed by a t8_locidx_t.
 * \param [in] index needs to be in [0]..[elem_count-1].
 * \return           A void * pointing to entry \a it in \a array.
 */
void               *t8_sc_array_index_locidx (sc_array_t * array,
                                              t8_locidx_t it);

/** Query the package identity as registered in libsc.
 * \return          This is -1 before \ref t8_init and the identifier after.
 */
int                 t8_get_package_id (void);

/** Logging function parametrized by local/global category and priority.
 * \param [in] category     Either SC_LC_NORMAL for outputting on every rank
 *                          or SC_LC_GLOBAL for outputting on the root rank.
 * \param [in] priority     Please see sc.h for legal log priorities.
 * \param [in] fmt          Printf-style format string.
 * \param [in] ap           Argument list; see stdarg.h.
 */
void                t8_logv (int category, int priority,
                             const char *fmt, va_list ap);

/* *INDENT-OFF* */
/** Logging function parametrized by local/global category and priority.
 * \param [in] category     Either SC_LC_NORMAL for outputting on every rank
 *                          or SC_LC_GLOBAL for outputting on the root rank.
 * \param [in] priority     Please see sc.h for legal log priorities.
 * \param [in] fmt          Printf-style format string.
 */
void                t8_logf (int category, int priority, const char *fmt, ...)
#ifndef T8_DOXYGEN
  __attribute__ ((format (printf, 3, 4)))
#endif
  ;

/** Log a message on the root rank with priority SC_LP_ERROR.
 * \param [in] fmt          Printf-style format string.
 */
void                t8_global_errorf (const char *fmt, ...)
#ifndef T8_DOXYGEN
  __attribute__ ((format (printf, 1, 2)))
#endif
  ;

/** Log a message on the root rank with priority SC_LP_ESSENTIAL.
 * \param [in] fmt          Printf-style format string.
 */
void                t8_global_essentialf (const char *fmt, ...)
#ifndef T8_DOXYGEN
  __attribute__ ((format (printf, 1, 2)))
#endif
  ;

/** Log a message on the root rank with priority SC_LP_PRODUCTION.
 * \param [in] fmt          Printf-style format string.
 */
void                t8_global_productionf (const char *fmt, ...)
#ifndef T8_DOXYGEN
  __attribute__ ((format (printf, 1, 2)))
#endif
  ;

/** Log a message on the root rank with priority SC_LP_INFO.
 * \param [in] fmt          Printf-style format string.
 */
void                t8_global_infof (const char *fmt, ...)
#ifndef T8_DOXYGEN
  __attribute__ ((format (printf, 1, 2)))
#endif
  ;

/** Log a message, no matter what rank, with priority SC_LP_INFO.
 * \param [in] fmt          Printf-style format string.
 */
void                t8_infof (const char *fmt, ...)
#ifndef T8_DOXYGEN
  __attribute__ ((format (printf, 1, 2)))
#endif
  ;

/** Log a message, no matter what rank, with priority SC_LP_DEBUG.
 * \param [in] fmt          Printf-style format string.
 */
void                t8_debugf (const char *fmt, ...)
#ifndef T8_DOXYGEN
  __attribute__ ((format (printf, 1, 2)))
#endif
  ;
/* *INDENT-ON* */

/** Register t8code with libsc and print version and variable information.
 * \param [in] log_threshold Declared in sc.h.  SC_LP_DEFAULT is fine.
 *                           You can also choose from log levels SC_LP_*.
 */
void                t8_init (int log_threshold);

/** Compare function for t8_gloidx_t for usage with standard sorting algorithms.
 *  \param [in] gidx1 A pointer to the first t8_gloidx_t.
 *  \param [in] gidx2 A pointer to the second t8_gloidx_t.
 *  \return -1 if *gidx1 < *gidx2, 0 if equal and +1 if gidx1 > gidx2
 */
int                 t8_compare_gloidx (const void *gidx1, const void *gidx2);

/** Absolute value for glo_idx
 * \param [in] x    An integer of type t8_gloidx_t
 * \return          The absolute value of x.
 */
static inline       t8_gloidx_t
t8_glo_abs (const t8_gloidx_t x)
{
  return x >= 0 ? x : -x;
}

/* call this at the end of a header file to match T8_EXTERN_C_BEGIN (). */
T8_EXTERN_C_END ();

#endif /* !T8_H */
