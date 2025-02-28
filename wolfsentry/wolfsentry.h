/*
 * wolfsentry.h
 *
 * Copyright (C) 2021 wolfSSL Inc.
 *
 * This file is part of wolfSentry.
 *
 * wolfSentry is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * wolfSentry is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1335, USA
 */

#ifndef WOLFSENTRY_H
#define WOLFSENTRY_H

#ifndef WOLFSENTRY
#define WOLFSENTRY
#endif

#ifdef WOLFSENTRY_USER_SETTINGS_FILE
#include WOLFSENTRY_USER_SETTINGS_FILE
#endif

#ifndef BUILDING_LIBWOLFSENTRY
#include <wolfsentry/wolfsentry_options.h>
#endif

#ifndef WOLFSENTRY_SINGLETHREADED

#define WOLFSENTRY_THREADSAFE

#if defined(__MACH__) || defined(FREERTOS) || defined(_WIN32)
#define WOLFSENTRY_USE_NONPOSIX_SEMAPHORES
#endif

#ifndef WOLFSENTRY_USE_NONPOSIX_SEMAPHORES
#define WOLFSENTRY_USE_NATIVE_POSIX_SEMAPHORES
#endif

#ifndef WOLFSENTRY_HAVE_NONGNU_ATOMICS
#define WOLFSENTRY_HAVE_GNU_ATOMICS
#endif

#endif /* !WOLFSENTRY_SINGLETHREADED */

#ifndef WOLFSENTRY_NO_CLOCK_BUILTIN
#define WOLFSENTRY_CLOCK_BUILTINS
#endif

#ifndef WOLFSENTRY_NO_MALLOC_BUILTIN
#define WOLFSENTRY_MALLOC_BUILTINS
#endif

#ifndef WOLFSENTRY_NO_ERROR_STRINGS
#define WOLFSENTRY_ERROR_STRINGS
#endif

#ifndef WOLFSENTRY_NO_PROTOCOL_NAMES
#define WOLFSENTRY_PROTOCOL_NAMES
#endif

#if defined(WOLFSENTRY_USE_NATIVE_POSIX_SEMAPHORES) || defined(WOLFSENTRY_CLOCK_BUILTINS) || defined(WOLFSENTRY_MALLOC_BUILTINS)
#ifndef _XOPEN_SOURCE
#if __STDC_VERSION__ >= 201112L
#define _XOPEN_SOURCE 700
#elif __STDC_VERSION__ >= 199901L
#define _XOPEN_SOURCE 600
#else
#define _XOPEN_SOURCE 500
#endif /* __STDC_VERSION__ */
#endif
#endif

#if defined(__STRICT_ANSI__)
#define WOLFSENTRY_FLEXIBLE_ARRAY_SIZE 1
#elif defined(__GNUC__) && !defined(__clang__)
#define WOLFSENTRY_FLEXIBLE_ARRAY_SIZE
#else
#define WOLFSENTRY_FLEXIBLE_ARRAY_SIZE 0
#endif

#ifndef WOLFSENTRY_NO_STDINT_H
#include <stdint.h>
#endif

#ifndef WOLFSENTRY_NO_STDDEF_H
#include <stddef.h>
#endif

#ifndef WOLFSENTRY_NO_INTTYPES_H
#include <inttypes.h>
#endif

#ifndef WOLFSENTRY_NO_ASSERT_H
#include <assert.h>
#endif

#ifdef WOLFSENTRY_THREADSAFE
#if !defined(WOLFSENTRY_NO_SEMAPHORE_H) && !defined(FREERTOS)
#include <semaphore.h>
#endif
#endif

#ifndef WOLFSENTRY_NO_STDIO
#include <stdio.h>
#endif

#ifndef WOLFSENTRY_NO_STRING_H
#include <string.h>
#endif

#ifndef WOLFSENTRY_NO_STRINGS_H
#include <strings.h>
#endif

#ifndef WOLFSENTRY_NO_TIME_H
#ifndef __USE_POSIX199309
/* glibc needs this for struct timespec with -std=c99 */
#define __USE_POSIX199309
#endif
#include <time.h>
#endif

#ifdef FREERTOS
/* size_t is alias to "unsigned int" in STM32 FreeRTOS */
#define SIZET_FMT "%d"
#else
#define SIZET_FMT "%zd"
#endif

typedef unsigned char byte;

typedef uint16_t wolfsentry_addr_family_t;
#include <wolfsentry/wolfsentry_af.h>

typedef uint16_t wolfsentry_proto_t;
typedef uint16_t wolfsentry_port_t;
#ifdef WOLFSENTRY_ENT_ID_TYPE
typedef WOLFSENTRY_ENT_ID_TYPE wolfsentry_ent_id_t;
#else
typedef uint32_t wolfsentry_ent_id_t;
#define WOLFSENTRY_ENT_ID_FMT "%u"
#endif
#define WOLFSENTRY_ENT_ID_NONE 0
typedef uint16_t wolfsentry_addr_bits_t;
#ifdef WOLFSENTRY_HITCOUNT_TYPE
typedef WOLFSENTRY_HITCOUNT_TYPE wolfsentry_hitcount_t;
#else
typedef uint32_t wolfsentry_hitcount_t;
#define WOLFSENTRY_HITCOUNT_FMT "%u"
#endif
#ifdef WOLFSENTRY_TIME_TYPE
typedef WOLFSENTRY_TIME_TYPE wolfsentry_time_t;
#else
typedef int64_t wolfsentry_time_t;
#endif

#ifdef WOLFSENTRY_PRIORITY_TYPE
typedef WOLFSENTRY_PRIORITY_TYPE wolfsentry_priority_t;
#else
typedef uint16_t wolfsentry_priority_t;
#endif
#define WOLFSENTRY_PRIORITY_NEXT 0

#ifndef __unused
#define __unused __attribute__((unused))
#endif

typedef uint32_t enumint_t;

#ifdef BUILDING_LIBWOLFSENTRY
    #if defined(_MSC_VER) || defined(__MINGW32__) || defined(__CYGWIN__) || \
        defined(_WIN32_WCE)
        #if defined(WOLFSENTRY_DLL)
            #define WOLFSENTRY_API __declspec(dllexport)
        #else
            #define WOLFSENTRY_API
        #endif
        #define WOLFSENTRY_LOCAL
    #elif defined(HAVE_VISIBILITY) && HAVE_VISIBILITY
        #define WOLFSENTRY_API   __attribute__ ((visibility("default")))
        #define WOLFSENTRY_LOCAL __attribute__ ((visibility("hidden")))
    #elif defined(__SUNPRO_C) && (__SUNPRO_C >= 0x550)
        #define WOLFSENTRY_API   __global
        #define WOLFSENTRY_LOCAL __hidden
    #else
        #define WOLFSENTRY_API
        #define WOLFSENTRY_LOCAL
    #endif /* HAVE_VISIBILITY */
#else /* !BUILDING_LIBWOLFSENTRY */
    #if defined(_MSC_VER) || defined(__MINGW32__) || defined(__CYGWIN__) || \
        defined(_WIN32_WCE)
        #if defined(WOLFSENTRY_DLL)
            #define WOLFSENTRY_API __declspec(dllimport)
        #else
            #define WOLFSENTRY_API
        #endif
        #define WOLFSENTRY_LOCAL
    #else
        #define WOLFSENTRY_API
        #define WOLFSENTRY_LOCAL
    #endif
#endif /* !BUILDING_LIBWOLFSENTRY */

#include <wolfsentry/wolfsentry_errcodes.h>

struct wolfsentry_context;

#ifdef WOLFSENTRY_THREADSAFE

struct wolfsentry_rwlock;

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_lock_init(struct wolfsentry_rwlock *lock, int pshared);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_lock_alloc(struct wolfsentry_context *wolfsentry, struct wolfsentry_rwlock **lock, int pshared);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_lock_shared(struct wolfsentry_rwlock *lock);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_lock_shared_abstimed(struct wolfsentry_rwlock *lock, struct timespec *abs_timeout);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_lock_shared_timed(struct wolfsentry_context *wolfsentry, struct wolfsentry_rwlock *lock, wolfsentry_time_t max_wait);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_lock_shared_and_reserve_shared2mutex(
    struct wolfsentry_rwlock *lock);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_lock_shared_abstimed_and_reserve_shared2mutex(
    struct wolfsentry_rwlock *lock,
    struct timespec *abs_timeout);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_lock_shared_timed_and_reserve_shared2mutex(
    struct wolfsentry_context *wolfsentry,
    struct wolfsentry_rwlock *lock,
    wolfsentry_time_t max_wait);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_lock_mutex(struct wolfsentry_rwlock *lock);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_lock_mutex_abstimed(struct wolfsentry_rwlock *lock, struct timespec *abs_timeout);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_lock_mutex_timed(struct wolfsentry_context *wolfsentry, struct wolfsentry_rwlock *lock, wolfsentry_time_t max_wait);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_lock_mutex2shared(struct wolfsentry_rwlock *lock);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_lock_mutex2shared_and_reserve_shared2mutex(
    struct wolfsentry_rwlock *lock);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_lock_shared2mutex(struct wolfsentry_rwlock *lock);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_lock_shared2mutex_abstimed(struct wolfsentry_rwlock *lock, struct timespec *abs_timeout);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_lock_shared2mutex_timed(struct wolfsentry_context *wolfsentry, struct wolfsentry_rwlock *lock, wolfsentry_time_t max_wait);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_lock_shared2mutex_reserve(struct wolfsentry_rwlock *lock);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_lock_shared2mutex_redeem(struct wolfsentry_rwlock *lock);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_lock_shared2mutex_redeem_abstimed(struct wolfsentry_rwlock *lock, struct timespec *abs_timeout);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_lock_shared2mutex_redeem_timed(struct wolfsentry_context *wolfsentry, struct wolfsentry_rwlock *lock, wolfsentry_time_t max_wait);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_lock_shared2mutex_abandon(struct wolfsentry_rwlock *lock);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_lock_have_shared(struct wolfsentry_rwlock *lock);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_lock_have_mutex(struct wolfsentry_rwlock *lock);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_lock_unlock(struct wolfsentry_rwlock *lock);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_lock_destroy(struct wolfsentry_rwlock *lock);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_lock_free(struct wolfsentry_context *wolfsentry, struct wolfsentry_rwlock **lock);

#else /* !WOLFSENTRY_THREADSAFE */

#define wolfsentry_lock_init(x, y) WOLFSENTRY_ERROR_ENCODE(OK)
#define wolfsentry_lock_alloc(x, y, z) WOLFSENTRY_ERROR_ENCODE(OK)
#define wolfsentry_lock_shared(x) WOLFSENTRY_ERROR_ENCODE(OK)
#define wolfsentry_lock_shared_abstimed(y, z) WOLFSENTRY_ERROR_ENCODE(OK)
#define wolfsentry_lock_shared_and_reserve_shared2mutex(x) WOLFSENTRY_ERROR_ENCODE(OK)
#define wolfsentry_lock_shared_abstimed_and_reserve_shared2mutex(x, y) WOLFSENTRY_ERROR_ENCODE(OK)
#define wolfsentry_lock_shared_timed_and_reserve_shared2mutex(x, y, z) WOLFSENTRY_ERROR_ENCODE(OK)
#define wolfsentry_lock_mutex_timed(x, y, z) WOLFSENTRY_ERROR_ENCODE(OK)
#define wolfsentry_lock_mutex(x) WOLFSENTRY_ERROR_ENCODE(OK)
#define wolfsentry_lock_mutex_abstimed(y, z) WOLFSENTRY_ERROR_ENCODE(OK)
#define wolfsentry_lock_mutex_timed(x, y, z) WOLFSENTRY_ERROR_ENCODE(OK)
#define wolfsentry_lock_mutex2shared(x) WOLFSENTRY_ERROR_ENCODE(OK)
#define wolfsentry_lock_mutex2shared_and_reserve_shared2mutex(x) WOLFSENTRY_ERROR_ENCODE(OK)
#define wolfsentry_lock_shared2mutex(x) WOLFSENTRY_ERROR_ENCODE(OK)
#define wolfsentry_lock_shared2mutex_abstimed(y, z) WOLFSENTRY_ERROR_ENCODE(OK)
#define wolfsentry_lock_shared2mutex_timed(x, y, z) WOLFSENTRY_ERROR_ENCODE(OK)
#define wolfsentry_lock_shared2mutex_reserve(x) WOLFSENTRY_ERROR_ENCODE(OK)
#define wolfsentry_lock_shared2mutex_redeem(x) WOLFSENTRY_ERROR_ENCODE(OK)
#define wolfsentry_lock_shared2mutex_redeem_abstimed(x, y) WOLFSENTRY_ERROR_ENCODE(OK)
#define wolfsentry_lock_shared2mutex_redeem_timed(x, y, z) WOLFSENTRY_ERROR_ENCODE(OK)
#define wolfsentry_lock_shared2mutex_abandon(x) WOLFSENTRY_ERROR_ENCODE(OK)
#define wolfsentry_lock_have_shared(x) WOLFSENTRY_ERROR_ENCODE(OK)
#define wolfsentry_lock_have_mutex(x) WOLFSENTRY_ERROR_ENCODE(OK)
#define wolfsentry_lock_unlock(x) WOLFSENTRY_ERROR_ENCODE(OK)
#define wolfsentry_lock_destroy(x) WOLFSENTRY_ERROR_ENCODE(OK)
#define wolfsentry_lock_free(x, y) WOLFSENTRY_ERROR_ENCODE(OK)

#endif /* WOLFSENTRY_THREADSAFE */

typedef enum {
    WOLFSENTRY_OBJECT_TYPE_UNINITED = 0,
    WOLFSENTRY_OBJECT_TYPE_TABLE,
    WOLFSENTRY_OBJECT_TYPE_ACTION,
    WOLFSENTRY_OBJECT_TYPE_EVENT,
    WOLFSENTRY_OBJECT_TYPE_ROUTE,
    WOLFSENTRY_OBJECT_TYPE_KV,
    WOLFSENTRY_OBJECT_TYPE_ADDR_FAMILY_BYNUMBER,
    WOLFSENTRY_OBJECT_TYPE_ADDR_FAMILY_BYNAME
} wolfsentry_object_type_t;

typedef enum {
    WOLFSENTRY_ACTION_FLAG_NONE       = 0U,
    WOLFSENTRY_ACTION_FLAG_DISABLED   = 1U << 0U
} wolfsentry_action_flags_t;

typedef enum {
    WOLFSENTRY_ACTION_TYPE_NONE = 0,
    WOLFSENTRY_ACTION_TYPE_POST = 1, /* called when an event is posted. */
    WOLFSENTRY_ACTION_TYPE_INSERT = 2, /* called when a route is added to the route table for this event. */
    WOLFSENTRY_ACTION_TYPE_MATCH = 3, /* called by wolfsentry_route_dispatch() for a route match. */
    WOLFSENTRY_ACTION_TYPE_DELETE = 4, /* called when a route associated with this event expires or is otherwise deleted. */
    WOLFSENTRY_ACTION_TYPE_DECISION = 5 /* called after final decision has been made by wolfsentry_route_event_dispatch*(). */
} wolfsentry_action_type_t;

#define WOLFSENTRY_ACTION_RES_USER_SHIFT 16U

typedef enum {
    WOLFSENTRY_ACTION_RES_NONE        = 0U,
    WOLFSENTRY_ACTION_RES_ACCEPT      = 1U << 0U,
    WOLFSENTRY_ACTION_RES_REJECT      = 1U << 1U,
    WOLFSENTRY_ACTION_RES_CONNECT     = 1U << 2U, /* when an action returns this, increment the connection count for the route. */
    WOLFSENTRY_ACTION_RES_DISCONNECT  = 1U << 3U, /* when an action returns this, decrement the connection count for the route. */
    WOLFSENTRY_ACTION_RES_DEROGATORY  = 1U << 4U,
    WOLFSENTRY_ACTION_RES_COMMENDABLE = 1U << 5U,
    WOLFSENTRY_ACTION_RES_CONTINUE    = 1U << 6U,
    WOLFSENTRY_ACTION_RES_STOP        = 1U << 7U, /* when an action returns this, don't evaluate any more actions in the current action list. */
    WOLFSENTRY_ACTION_RES_INSERT      = 1U << 8U, /* when an action returns this, that means the route should be added to the route table if it isn't already in it. */
    WOLFSENTRY_ACTION_RES_DELETE      = 1U << 9U, /* when an action returns this, delete the route from the table. */
    WOLFSENTRY_ACTION_RES_DEALLOCATED = 1U << 10U, /* when an API call returns this, the route and its associated ID were deallocated from the system. */
    WOLFSENTRY_ACTION_RES_ERROR       = 1U << 11U,
    WOLFSENTRY_ACTION_RES_FALLTHROUGH = 1U << 12U, /* dispatch resolved to the fallthrough route. */
    WOLFSENTRY_ACTION_RES_USER_BASE   = 1U << WOLFSENTRY_ACTION_RES_USER_SHIFT /* start of user-defined results, with user-defined scheme (bitfield, sequential, or other) */
} wolfsentry_action_res_t;

#define WOLFSENTRY_ROUTE_DEFAULT_POLICY_MASK (WOLFSENTRY_ACTION_RES_ACCEPT | WOLFSENTRY_ACTION_RES_REJECT | WOLFSENTRY_ACTION_RES_STOP | WOLFSENTRY_ACTION_RES_ERROR)

struct wolfsentry_table_header;
struct wolfsentry_route;
struct wolfsentry_route_table;
struct wolfsentry_event;
struct wolfsentry_event_table;
struct wolfsentry_action;
struct wolfsentry_action_table;
struct wolfsentry_action_list;
struct wolfsentry_action_list_ent;
struct wolfsentry_cursor;

typedef wolfsentry_errcode_t (*wolfsentry_action_callback_t)(
    struct wolfsentry_context *wolfsentry,
    const struct wolfsentry_action *action,
    void *handler_arg,
    void *caller_arg,
    const struct wolfsentry_event *trigger_event,
    wolfsentry_action_type_t action_type,
    const struct wolfsentry_route *trigger_route,
    struct wolfsentry_route_table *route_table,
    const struct wolfsentry_route *rule_route,
    wolfsentry_action_res_t *action_results);

typedef enum {
    WOLFSENTRY_ROUTE_FLAG_NONE                           = 0U,
    WOLFSENTRY_ROUTE_FLAG_PARENT_EVENT_WILDCARD          = 1U<<0U,
    WOLFSENTRY_ROUTE_FLAG_REMOTE_INTERFACE_WILDCARD      = 1U<<1U,
    WOLFSENTRY_ROUTE_FLAG_LOCAL_INTERFACE_WILDCARD       = 1U<<2U,
    WOLFSENTRY_ROUTE_FLAG_SA_FAMILY_WILDCARD             = 1U<<3U,
    WOLFSENTRY_ROUTE_FLAG_SA_REMOTE_ADDR_WILDCARD        = 1U<<4U,
    WOLFSENTRY_ROUTE_FLAG_SA_LOCAL_ADDR_WILDCARD         = 1U<<5U,
    WOLFSENTRY_ROUTE_FLAG_SA_PROTO_WILDCARD              = 1U<<6U,
    WOLFSENTRY_ROUTE_FLAG_SA_REMOTE_PORT_WILDCARD        = 1U<<7U,
    WOLFSENTRY_ROUTE_FLAG_SA_LOCAL_PORT_WILDCARD         = 1U<<8U,
    WOLFSENTRY_ROUTE_FLAG_TCPLIKE_PORT_NUMBERS           = 1U<<9U,
    WOLFSENTRY_ROUTE_FLAG_DIRECTION_IN                   = 1U<<10U,
    WOLFSENTRY_ROUTE_FLAG_DIRECTION_OUT                  = 1U<<11U,

    /* immutable above here. */

    /* internal use from here... */
    WOLFSENTRY_ROUTE_FLAG_IN_TABLE                       = 1U<<12U,
    WOLFSENTRY_ROUTE_FLAG_PENDING_DELETE                 = 1U<<13U,
    WOLFSENTRY_ROUTE_FLAG_INSERT_ACTIONS_CALLED          = 1U<<14U,
    WOLFSENTRY_ROUTE_FLAG_DELETE_ACTIONS_CALLED          = 1U<<15U,

    /* ...to here. */

    /* mutable below here. */

    WOLFSENTRY_ROUTE_FLAG_PENALTYBOXED                   = 1U<<16U,
    WOLFSENTRY_ROUTE_FLAG_GREENLISTED                    = 1U<<17U,
    WOLFSENTRY_ROUTE_FLAG_DONT_COUNT_HITS                = 1U<<18U,
    WOLFSENTRY_ROUTE_FLAG_DONT_COUNT_CURRENT_CONNECTIONS = 1U<<19U
} wolfsentry_route_flags_t;

#define WOLFSENTRY_ROUTE_IMMUTABLE_FLAGS ((wolfsentry_route_flags_t)WOLFSENTRY_ROUTE_FLAG_IN_TABLE - 1U)

#define WOLFSENTRY_ROUTE_FLAG_TRIGGER_WILDCARD WOLFSENTRY_ROUTE_FLAG_PARENT_EVENT_WILDCARD /* xxx backward compatibility */

struct wolfsentry_route_endpoint {
    wolfsentry_port_t sa_port;
    wolfsentry_addr_bits_t addr_len;
    byte extra_port_count;
    byte interface;
};

struct wolfsentry_route_metadata_exports {
    wolfsentry_time_t insert_time;
    wolfsentry_time_t last_hit_time;
    wolfsentry_time_t last_penaltybox_time;
    wolfsentry_hitcount_t connection_count;
    wolfsentry_hitcount_t derogatory_count;
    wolfsentry_hitcount_t commendable_count;
    wolfsentry_hitcount_t hit_count;
};

struct wolfsentry_route_exports {
    const char *parent_event_label;
    size_t parent_event_label_len;
    wolfsentry_route_flags_t flags;
    wolfsentry_addr_family_t sa_family;
    wolfsentry_proto_t sa_proto;
    struct wolfsentry_route_endpoint remote, local;
    const byte *remote_address, *local_address;
    const wolfsentry_port_t *remote_extra_ports, *local_extra_ports;
    struct wolfsentry_route_metadata_exports meta;
    void *private_data;
    size_t private_data_size;
};

typedef enum {
    WOLFSENTRY_EVENT_FLAG_NONE = 0,
    WOLFSENTRY_EVENT_FLAG_IS_PARENT_EVENT = 1U << 0U,
    WOLFSENTRY_EVENT_FLAG_IS_SUBEVENT = 2U << 0U
} wolfsentry_event_flags_t;

typedef enum {
    WOLFSENTRY_EVENTCONFIG_FLAG_NONE = 0U,
    WOLFSENTRY_EVENTCONFIG_FLAG_INHIBIT_ACTIONS = 1U << 0U
} wolfsentry_eventconfig_flags_t;

struct wolfsentry_eventconfig {
    size_t route_private_data_size;
    size_t route_private_data_alignment;
    uint32_t max_connection_count;
    wolfsentry_time_t penaltybox_duration; /* zero means time-unbounded. */
    wolfsentry_eventconfig_flags_t flags;
};

#define WOLFSENTRY_TIME_NEVER ((wolfsentry_time_t)0)

#ifndef WOLFSENTRY_MAX_ADDR_BYTES
#define WOLFSENTRY_MAX_ADDR_BYTES 16
#elif WOLFSENTRY_MAX_ADDR_BYTES * 8 > 0xffff
#error WOLFSENTRY_MAX_ADDR_BYTES * 8 must fit in a uint16_t.
#endif

#ifndef WOLFSENTRY_MAX_ADDR_BITS
#define WOLFSENTRY_MAX_ADDR_BITS (WOLFSENTRY_MAX_ADDR_BYTES*8)
#else
#if WOLFSENTRY_MAX_ADDR_BITS > (WOLFSENTRY_MAX_ADDR_BYTES*8)
#error WOLFSENTRY_MAX_ADDR_BITS is too large for given/default WOLFSENTRY_MAX_ADDR_BYTES
#endif
#endif

#define WOLFSENTRY_SOCKADDR_MEMBERS(n) {        \
    wolfsentry_addr_family_t sa_family;         \
    wolfsentry_proto_t sa_proto;                \
    wolfsentry_port_t sa_port;                  \
    wolfsentry_addr_bits_t addr_len;            \
    byte interface;                             \
    byte addr[n];                               \
}

struct wolfsentry_sockaddr WOLFSENTRY_SOCKADDR_MEMBERS(WOLFSENTRY_FLEXIBLE_ARRAY_SIZE);

#define WOLFSENTRY_SOCKADDR(n) struct WOLFSENTRY_SOCKADDR_MEMBERS(WOLFSENTRY_BITS_TO_BYTES(n))

typedef wolfsentry_errcode_t (*wolfsentry_get_time_cb_t)(void *context, wolfsentry_time_t *ts);
typedef wolfsentry_time_t (*wolfsentry_diff_time_cb_t)(wolfsentry_time_t earlier, wolfsentry_time_t later);
typedef wolfsentry_time_t (*wolfsentry_add_time_cb_t)(wolfsentry_time_t start_time, wolfsentry_time_t time_interval);
typedef wolfsentry_errcode_t (*wolfsentry_to_epoch_time_cb_t)(wolfsentry_time_t when, long *epoch_secs, long *epoch_nsecs);
typedef wolfsentry_errcode_t (*wolfsentry_from_epoch_time_cb_t)(long epoch_secs, long epoch_nsecs, wolfsentry_time_t *when);
typedef wolfsentry_errcode_t (*wolfsentry_interval_to_seconds_cb_t)(wolfsentry_time_t howlong, long *howlong_secs, long *howlong_nsecs);
typedef wolfsentry_errcode_t (*wolfsentry_interval_from_seconds_cb_t)(long howlong_secs, long howlong_nsecs, wolfsentry_time_t *howlong);

wolfsentry_errcode_t wolfsentry_time_now_plus_delta(struct wolfsentry_context *wolfsentry, wolfsentry_time_t td, wolfsentry_time_t *res);

#ifdef WOLFSENTRY_THREADSAFE
wolfsentry_errcode_t wolfsentry_time_to_timespec(struct wolfsentry_context *wolfsentry, wolfsentry_time_t t, struct timespec *ts);
wolfsentry_errcode_t wolfsentry_time_now_plus_delta_timespec(struct wolfsentry_context *wolfsentry, wolfsentry_time_t td, struct timespec *ts);
#endif

typedef void *(*wolfsentry_malloc_cb_t)(void *context, size_t size);
typedef void (*wolfsentry_free_cb_t)(void *context, void *ptr);
typedef void *(*wolfsentry_realloc_cb_t)(void *context, void *ptr, size_t size);
typedef void *(*wolfsentry_memalign_cb_t)(void *context, size_t alignment, size_t size);
typedef void (*wolfsentry_free_aligned_cb_t)(void *context, void *ptr);

typedef wolfsentry_errcode_t (*wolfsentry_make_id_cb_t)(void *context, wolfsentry_ent_id_t *id);

struct wolfsentry_allocator {
    void *context;
    wolfsentry_malloc_cb_t malloc;
    wolfsentry_free_cb_t free;
    wolfsentry_realloc_cb_t realloc;
    wolfsentry_memalign_cb_t memalign;
    wolfsentry_free_aligned_cb_t free_aligned;
};

struct wolfsentry_timecbs {
    void *context;
    wolfsentry_get_time_cb_t get_time;
    wolfsentry_diff_time_cb_t diff_time;
    wolfsentry_add_time_cb_t add_time;
    wolfsentry_to_epoch_time_cb_t to_epoch_time;
    wolfsentry_from_epoch_time_cb_t from_epoch_time;
    wolfsentry_interval_to_seconds_cb_t interval_to_seconds;
    wolfsentry_interval_from_seconds_cb_t interval_from_seconds;
};

WOLFSENTRY_API void *wolfsentry_malloc(struct wolfsentry_context *wolfsentry, size_t size);
WOLFSENTRY_API void wolfsentry_free(struct wolfsentry_context *wolfsentry, void *ptr);
WOLFSENTRY_API void *wolfsentry_realloc(struct wolfsentry_context *wolfsentry, void *ptr, size_t size);
WOLFSENTRY_API void *wolfsentry_memalign(struct wolfsentry_context *wolfsentry, size_t alignment, size_t size);
WOLFSENTRY_API void wolfsentry_free_aligned(struct wolfsentry_context *wolfsentry, void *ptr);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_get_time(struct wolfsentry_context *wolfsentry, wolfsentry_time_t *time_p);
WOLFSENTRY_API wolfsentry_time_t wolfsentry_diff_time(struct wolfsentry_context *wolfsentry, wolfsentry_time_t later, wolfsentry_time_t earlier);
WOLFSENTRY_API wolfsentry_time_t wolfsentry_add_time(struct wolfsentry_context *wolfsentry, wolfsentry_time_t start_time, wolfsentry_time_t time_interval);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_to_epoch_time(struct wolfsentry_context *wolfsentry, wolfsentry_time_t when, long *epoch_secs, long *epoch_nsecs);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_from_epoch_time(struct wolfsentry_context *wolfsentry, long epoch_secs, long epoch_nsecs, wolfsentry_time_t *when);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_interval_to_seconds(struct wolfsentry_context *wolfsentry, wolfsentry_time_t howlong, long *howlong_secs, long *howlong_nsecs);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_interval_from_seconds(struct wolfsentry_context *wolfsentry, long howlong_secs, long howlong_nsecs, wolfsentry_time_t *howlong);

#ifdef WOLFSENTRY_ERROR_STRINGS
WOLFSENTRY_API const char *wolfsentry_action_res_decode(wolfsentry_action_res_t res, unsigned int bit);
#endif

struct wolfsentry_host_platform_interface {
    struct wolfsentry_allocator *allocator;
    struct wolfsentry_timecbs *timecbs;
};

/* must return _BUFFER_TOO_SMALL and set *addr_internal_bits to an
 * accurate value when supplied with a NULL output buf ptr.
 * whenever _BUFFER_TOO_SMALL is returned, *addr_*_bits must be set to an
 * accurate value.
 */
typedef wolfsentry_errcode_t (*wolfsentry_addr_family_parser_t)(
    struct wolfsentry_context *wolfsentry,
    const char *addr_text,
    int addr_text_len,
    byte *addr_internal,
    wolfsentry_addr_bits_t *addr_internal_bits);

typedef wolfsentry_errcode_t (*wolfsentry_addr_family_formatter_t)(
    struct wolfsentry_context *wolfsentry,
    const byte *addr_internal,
    unsigned int addr_internal_bits,
    char *addr_text,
    int *addr_text_len);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_addr_family_handler_install(
    struct wolfsentry_context *wolfsentry,
    wolfsentry_addr_family_t family_bynumber,
    const char *family_byname, /* if defined(WOLFSENTRY_PROTOCOL_NAMES), must not be NULL, else ignored. */
    int family_byname_len,
    wolfsentry_addr_family_parser_t parser,
    wolfsentry_addr_family_formatter_t formatter,
    int max_addr_bits);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_addr_family_get_parser(
    struct wolfsentry_context *wolfsentry,
    wolfsentry_addr_family_t family,
    wolfsentry_addr_family_parser_t *parser);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_addr_family_get_formatter(
    struct wolfsentry_context *wolfsentry,
    wolfsentry_addr_family_t family,
    wolfsentry_addr_family_formatter_t *formatter);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_addr_family_handler_remove_bynumber(
    struct wolfsentry_context *wolfsentry,
    wolfsentry_addr_family_t family_bynumber,
    wolfsentry_action_res_t *action_results);

struct wolfsentry_addr_family_bynumber;

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_addr_family_drop_reference(
    struct wolfsentry_context *wolfsentry,
    struct wolfsentry_addr_family_bynumber *family_bynumber,
    wolfsentry_action_res_t *action_results);

#ifdef WOLFSENTRY_PROTOCOL_NAMES

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_addr_family_handler_remove_byname(
    struct wolfsentry_context *wolfsentry,
    const char *family_byname,
    int family_byname_len,
    wolfsentry_action_res_t *action_results);

WOLFSENTRY_API wolfsentry_addr_family_t wolfsentry_addr_family_pton(
    struct wolfsentry_context *wolfsentry,
    const char *family_name,
    int family_name_len,
    wolfsentry_errcode_t *errcode);

WOLFSENTRY_API const char *wolfsentry_addr_family_ntop(
    struct wolfsentry_context *wolfsentry,
    wolfsentry_addr_family_t family,
    struct wolfsentry_addr_family_bynumber **addr_family,
    wolfsentry_errcode_t *errcode);

#endif /* WOLFSENTRY_PROTOCOL_NAMES */

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_eventconfig_init(
    struct wolfsentry_context *wolfsentry,
    struct wolfsentry_eventconfig *config);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_eventconfig_check(
    const struct wolfsentry_eventconfig *config);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_init(
    const struct wolfsentry_host_platform_interface *hpi,
    const struct wolfsentry_eventconfig *config,
    struct wolfsentry_context **wolfsentry);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_defaultconfig_get(
    struct wolfsentry_context *wolfsentry,
    struct wolfsentry_eventconfig *config);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_defaultconfig_update(
    struct wolfsentry_context *wolfsentry,
    const struct wolfsentry_eventconfig *config);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_context_flush(struct wolfsentry_context *wolfsentry);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_context_free(struct wolfsentry_context **wolfsentry);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_shutdown(struct wolfsentry_context **wolfsentry);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_context_inhibit_actions(struct wolfsentry_context *wolfsentry);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_context_enable_actions(struct wolfsentry_context *wolfsentry);

typedef enum {
    WOLFSENTRY_CLONE_FLAG_NONE = 0U,
    WOLFSENTRY_CLONE_FLAG_AS_AT_CREATION = 1U << 0U
} wolfsentry_clone_flags_t;
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_context_clone(struct wolfsentry_context *wolfsentry, struct wolfsentry_context **clone, wolfsentry_clone_flags_t flags);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_context_exchange(struct wolfsentry_context *wolfsentry1, struct wolfsentry_context *wolfsentry2);

#ifdef WOLFSENTRY_THREADSAFE

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_context_lock_shared(
    struct wolfsentry_context *wolfsentry);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_context_lock_shared_abstimed(
    struct wolfsentry_context *wolfsentry,
    struct timespec *abs_timeout);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_context_lock_shared_timed(
    struct wolfsentry_context *wolfsentry,
    wolfsentry_time_t max_wait);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_context_lock_shared_and_reserve_shared2mutex(
    struct wolfsentry_context *wolfsentry);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_context_lock_shared_abstimed_and_reserve_shared2mutex(
    struct wolfsentry_context *wolfsentry,
    struct timespec *abs_timeout);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_context_lock_shared_timed_and_reserve_shared2mutex(
    struct wolfsentry_context *wolfsentry,
    wolfsentry_time_t max_wait);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_context_lock_shared2mutex(
    struct wolfsentry_context *wolfsentry);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_context_lock_shared2mutex_abstimed(
    struct wolfsentry_context *wolfsentry,
    struct timespec *abs_timeout);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_context_lock_shared2mutex_timed(
    struct wolfsentry_context *wolfsentry,
    wolfsentry_time_t max_wait);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_context_lock_shared2mutex_reserve(
    struct wolfsentry_context *wolfsentry);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_context_lock_shared2mutex_redeem(
    struct wolfsentry_context *wolfsentry);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_context_lock_shared2mutex_redeem_abstimed(
    struct wolfsentry_context *wolfsentry,
    struct timespec *abs_timeout);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_context_lock_shared2mutex_redeem_timed(
    struct wolfsentry_context *wolfsentry,
    wolfsentry_time_t max_wait);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_context_lock_shared2mutex_abandon(
    struct wolfsentry_context *wolfsentry);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_context_lock_mutex(
    struct wolfsentry_context *wolfsentry);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_context_lock_mutex_abstimed(
    struct wolfsentry_context *wolfsentry,
    struct timespec *abs_timeout);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_context_lock_mutex_timed(
    struct wolfsentry_context *wolfsentry,
    wolfsentry_time_t max_wait);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_context_lock_mutex2shared(
    struct wolfsentry_context *wolfsentry);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_context_lock_mutex2shared_and_reserve_shared2mutex(
    struct wolfsentry_context *wolfsentry);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_context_unlock(
    struct wolfsentry_context *wolfsentry);

#else /* !WOLFSENTRY_THREADSAFE */

#define wolfsentry_context_lock_shared(x) WOLFSENTRY_ERROR_ENCODE(OK)
#define wolfsentry_context_lock_shared_abstimed(x, y) WOLFSENTRY_ERROR_ENCODE(OK)
#define wolfsentry_context_lock_shared_timed(x, y) WOLFSENTRY_ERROR_ENCODE(OK)
#define wolfsentry_context_lock_shared_and_reserve_shared2mutex(x) WOLFSENTRY_ERROR_ENCODE(OK)
#define wolfsentry_context_lock_shared_abstimed_and_reserve_shared2mutex(x, y) WOLFSENTRY_ERROR_ENCODE(OK)
#define wolfsentry_context_lock_shared_timed_and_reserve_shared2mutex(x, y) WOLFSENTRY_ERROR_ENCODE(OK)
#define wolfsentry_context_lock_shared2mutex(x) WOLFSENTRY_ERROR_ENCODE(OK)
#define wolfsentry_context_lock_shared2mutex_abstimed(x, y) WOLFSENTRY_ERROR_ENCODE(OK)
#define wolfsentry_context_lock_shared2mutex_timed(x, y) WOLFSENTRY_ERROR_ENCODE(OK)
#define wolfsentry_context_lock_shared2mutex_reserve(x) WOLFSENTRY_ERROR_ENCODE(OK)
#define wolfsentry_context_lock_shared2mutex_redeem(x) WOLFSENTRY_ERROR_ENCODE(OK)
#define wolfsentry_context_lock_shared2mutex_redeem_abstimed(x, y) WOLFSENTRY_ERROR_ENCODE(OK)
#define wolfsentry_context_lock_shared2mutex_redeem_timed(x, y) WOLFSENTRY_ERROR_ENCODE(OK)
#define wolfsentry_context_lock_shared2mutex_abandon(x) WOLFSENTRY_ERROR_ENCODE(OK)
#define wolfsentry_context_lock_mutex(x) WOLFSENTRY_ERROR_ENCODE(OK)
#define wolfsentry_context_lock_mutex_abstimed(x, y) WOLFSENTRY_ERROR_ENCODE(OK)
#define wolfsentry_context_lock_mutex_timed(x, y) WOLFSENTRY_ERROR_ENCODE(OK)
#define wolfsentry_context_lock_mutex2shared(x) WOLFSENTRY_ERROR_ENCODE(OK)
#define wolfsentry_context_lock_mutex2shared_and_reserve_shared2mutex(x) WOLFSENTRY_ERROR_ENCODE(OK)
#define wolfsentry_context_unlock(x) WOLFSENTRY_ERROR_ENCODE(OK)

#endif /* WOLFSENTRY_THREADSAFE */

#ifndef WOLFSENTRY_MAX_LABEL_BYTES
#define WOLFSENTRY_MAX_LABEL_BYTES 32
#elif WOLFSENTRY_MAX_LABEL_BYTES > 0xff
#error WOLFSENTRY_MAX_LABEL_BYTES must fit in a byte.
#endif

#define WOLFSENTRY_LENGTH_NULL_TERMINATED -1

WOLFSENTRY_API wolfsentry_ent_id_t wolfsentry_get_table_id(const void *table);
WOLFSENTRY_API wolfsentry_ent_id_t wolfsentry_get_object_id(const void *object);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_route_insert_static(
    struct wolfsentry_context *wolfsentry,
    void *caller_arg, /* passed to action callback(s) as the caller_arg. */
    const struct wolfsentry_sockaddr *remote,
    const struct wolfsentry_sockaddr *local,
    wolfsentry_route_flags_t flags,
    const char *event_label,
    int event_label_len,
    wolfsentry_ent_id_t *id,
    wolfsentry_action_res_t *action_results);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_route_delete_static(
    struct wolfsentry_context *wolfsentry,
    void *caller_arg, /* passed to action callback(s) as the caller_arg. */
    const struct wolfsentry_sockaddr *remote,
    const struct wolfsentry_sockaddr *local,
    wolfsentry_route_flags_t flags,
    const char *trigger_label,
    int trigger_label_len,
    wolfsentry_action_res_t *action_results,
    int *n_deleted);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_route_delete_dynamic(
    struct wolfsentry_context *wolfsentry,
    void *caller_arg, /* passed to action callback(s) as the caller_arg. */
    const struct wolfsentry_sockaddr *remote,
    const struct wolfsentry_sockaddr *local,
    wolfsentry_route_flags_t flags,
    const char *trigger_label,
    int trigger_label_len,
    wolfsentry_action_res_t *action_results,
    int *n_deleted);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_route_delete_everywhere(
    struct wolfsentry_context *wolfsentry,
    void *caller_arg, /* passed to action callback(s) as the caller_arg. */
    const struct wolfsentry_sockaddr *remote,
    const struct wolfsentry_sockaddr *local,
    wolfsentry_route_flags_t flags,
    const char *trigger_label,
    int trigger_label_len,
    wolfsentry_action_res_t *action_results,
    int *n_deleted);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_route_delete_by_id(
    struct wolfsentry_context *wolfsentry,
    void *caller_arg, /* passed to action callback(s) as the caller_arg. */
    wolfsentry_ent_id_t id,
    const char *event_label,
    int event_label_len,
    wolfsentry_action_res_t *action_results);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_route_get_table_static(
    struct wolfsentry_context *wolfsentry,
    struct wolfsentry_route_table **table);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_route_get_table_dynamic(
    struct wolfsentry_context *wolfsentry,
    struct wolfsentry_route_table **table);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_route_table_iterate_start(
    struct wolfsentry_context *wolfsentry,
    const struct wolfsentry_route_table *table,
    struct wolfsentry_cursor **cursor);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_route_table_iterate_seek_to_head(
    const struct wolfsentry_context *wolfsentry,
    const struct wolfsentry_route_table *table,
    struct wolfsentry_cursor *cursor);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_route_table_iterate_seek_to_tail(
    const struct wolfsentry_context *wolfsentry,
    const struct wolfsentry_route_table *table,
    struct wolfsentry_cursor *cursor);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_route_table_iterate_current(
    struct wolfsentry_context *wolfsentry,
    const struct wolfsentry_route_table *table,
    struct wolfsentry_cursor *cursor,
    struct wolfsentry_route **route);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_route_table_iterate_prev(
    struct wolfsentry_context *wolfsentry,
    const struct wolfsentry_route_table *table,
    struct wolfsentry_cursor *cursor,
    struct wolfsentry_route **route);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_route_table_iterate_next(
    struct wolfsentry_context *wolfsentry,
    const struct wolfsentry_route_table *table,
    struct wolfsentry_cursor *cursor,
    struct wolfsentry_route **route);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_route_table_iterate_end(
    struct wolfsentry_context *wolfsentry,
    const struct wolfsentry_route_table *table,
    struct wolfsentry_cursor **cursor);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_route_table_default_policy_set(
    struct wolfsentry_context *wolfsentry,
    struct wolfsentry_route_table *table,
    wolfsentry_action_res_t default_policy);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_route_table_default_policy_get(
    struct wolfsentry_context *wolfsentry,
    struct wolfsentry_route_table *table,
    wolfsentry_action_res_t *default_policy);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_route_get_reference(
    struct wolfsentry_context *wolfsentry,
    const struct wolfsentry_route_table *table,
    const struct wolfsentry_sockaddr *remote,
    const struct wolfsentry_sockaddr *local,
    wolfsentry_route_flags_t flags,
    const char *event_label,
    int event_label_len,
    int exact_p,
    wolfsentry_route_flags_t *inexact_matches,
    struct wolfsentry_route **route);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_route_drop_reference(
    struct wolfsentry_context *wolfsentry,
    struct wolfsentry_route *route,
    wolfsentry_action_res_t *action_results);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_route_table_clear_default_event(
    struct wolfsentry_context *wolfsentry,
    struct wolfsentry_route_table *table);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_route_table_set_default_event(
    struct wolfsentry_context *wolfsentry,
    struct wolfsentry_route_table *table,
    const char *event_label,
    int event_label_len);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_route_table_get_default_event(
    struct wolfsentry_context *wolfsentry,
    struct wolfsentry_route_table *table,
    char *event_label,
    int *event_label_len);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_route_table_fallthrough_route_get(
    struct wolfsentry_context *wolfsentry,
    struct wolfsentry_route_table *route_table,
    const struct wolfsentry_route **fallthrough_route);

/* route_exports remains valid only as long as the wolfsentry lock is held (shared or exclusive). */
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_route_export(
    struct wolfsentry_context *wolfsentry,
    const struct wolfsentry_route *route,
    struct wolfsentry_route_exports *route_exports);

/* returned wolfsentry_event remains valid only as long as the wolfsentry lock is held (shared or exclusive). */
WOLFSENTRY_API const struct wolfsentry_event *wolfsentry_route_parent_event(const struct wolfsentry_route *route);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_route_event_dispatch(
    struct wolfsentry_context *wolfsentry,
    const struct wolfsentry_sockaddr *remote,
    const struct wolfsentry_sockaddr *local,
    wolfsentry_route_flags_t flags,
    const char *event_label,
    int event_label_len,
    void *caller_arg, /* passed to action callback(s). */
    wolfsentry_ent_id_t *id,
    wolfsentry_route_flags_t *inexact_matches,
    wolfsentry_action_res_t *action_results);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_route_event_dispatch_with_inited_result(
    struct wolfsentry_context *wolfsentry,
    const struct wolfsentry_sockaddr *remote,
    const struct wolfsentry_sockaddr *local,
    wolfsentry_route_flags_t flags,
    const char *event_label,
    int event_label_len,
    void *caller_arg, /* passed to action callback(s). */
    wolfsentry_ent_id_t *id,
    wolfsentry_route_flags_t *inexact_matches,
    wolfsentry_action_res_t *action_results);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_route_event_dispatch_by_id(
    struct wolfsentry_context *wolfsentry,
    wolfsentry_ent_id_t id,
    const char *event_label,
    int event_label_len,
    void *caller_arg, /* passed to action callback(s) as the caller_arg. */
    wolfsentry_action_res_t *action_results
    );

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_route_event_dispatch_by_id_with_inited_result(
    struct wolfsentry_context *wolfsentry,
    wolfsentry_ent_id_t id,
    const char *event_label,
    int event_label_len,
    void *caller_arg, /* passed to action callback(s) as the caller_arg. */
    wolfsentry_action_res_t *action_results
    );

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_route_stale_purge(
    struct wolfsentry_context *wolfsentry,
    struct wolfsentry_route_table *table);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_route_flush_table(
    struct wolfsentry_context *wolfsentry,
    struct wolfsentry_route_table *table,
    wolfsentry_action_res_t *action_results);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_route_bulk_clear_insert_action_status(
    struct wolfsentry_context *wolfsentry,
    wolfsentry_action_res_t *action_results);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_route_bulk_insert_actions(
    struct wolfsentry_context *wolfsentry,
    wolfsentry_action_res_t *action_results);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_route_get_private_data(
    struct wolfsentry_context *wolfsentry,
    struct wolfsentry_route *route,
    void **private_data,
    size_t *private_data_size);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_route_get_flags(
    struct wolfsentry_route *route,
    wolfsentry_route_flags_t *flags);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_route_get_metadata(
    const struct wolfsentry_route *route,
    struct wolfsentry_route_metadata_exports *metadata);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_route_update_flags(
    struct wolfsentry_context *wolfsentry,
    struct wolfsentry_route *route,
    wolfsentry_route_flags_t flags_to_set,
    wolfsentry_route_flags_t flags_to_clear,
    wolfsentry_route_flags_t *flags_before,
    wolfsentry_route_flags_t *flags_after);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_route_set_wildcard(
    struct wolfsentry_route *route,
    wolfsentry_route_flags_t wildcards_to_set);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_route_format_address(
    struct wolfsentry_context *wolfsentry,
    wolfsentry_addr_family_t sa_family,
    const byte *addr,
    unsigned int addr_bits,
    char *buf,
    int *buflen);

#ifndef WOLFSENTRY_NO_STDIO
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_route_render(struct wolfsentry_context *wolfsentry, const struct wolfsentry_route *r, FILE *f);
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_route_exports_render(struct wolfsentry_context *wolfsentry, const struct wolfsentry_route_exports *r, FILE *f);
#endif

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_action_insert(
    struct wolfsentry_context *wolfsentry,
    const char *label,
    int label_len,
    wolfsentry_action_flags_t flags,
    wolfsentry_action_callback_t handler,
    void *handler_arg,
    wolfsentry_ent_id_t *id);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_action_delete(
    struct wolfsentry_context *wolfsentry,
    const char *label,
    int label_len,
    wolfsentry_action_res_t *action_results);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_action_flush_all(struct wolfsentry_context *wolfsentry);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_action_get_reference(
    struct wolfsentry_context *wolfsentry,
    const char *label,
    int label_len,
    struct wolfsentry_action **action);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_action_drop_reference(
    struct wolfsentry_context *wolfsentry,
    const struct wolfsentry_action *action,
    wolfsentry_action_res_t *action_results);

WOLFSENTRY_API const char *wolfsentry_action_get_label(const struct wolfsentry_action *action);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_action_get_flags(
    struct wolfsentry_action *action,
    wolfsentry_action_flags_t *flags);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_action_update_flags(
    struct wolfsentry_action *action,
    wolfsentry_action_flags_t flags_to_set,
    wolfsentry_action_flags_t flags_to_clear,
    wolfsentry_action_flags_t *flags_before,
    wolfsentry_action_flags_t *flags_after);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_event_insert(
    struct wolfsentry_context *wolfsentry,
    const char *label,
    int label_len,
    wolfsentry_priority_t priority,
    const struct wolfsentry_eventconfig *config,
    wolfsentry_event_flags_t flags,
    wolfsentry_ent_id_t *id);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_event_delete(
    struct wolfsentry_context *wolfsentry,
    const char *label,
    int label_len,
    wolfsentry_action_res_t *action_results);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_event_flush_all(struct wolfsentry_context *wolfsentry);

WOLFSENTRY_API const char *wolfsentry_event_get_label(const struct wolfsentry_event *event);

WOLFSENTRY_API wolfsentry_event_flags_t wolfsentry_event_get_flags(const struct wolfsentry_event *event);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_event_get_config(
    struct wolfsentry_context *wolfsentry,
    const char *label,
    int label_len,
    struct wolfsentry_eventconfig *config);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_event_update_config(
    struct wolfsentry_context *wolfsentry,
    const char *label,
    int label_len,
    struct wolfsentry_eventconfig *config);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_event_get_reference(
    struct wolfsentry_context *wolfsentry,
    const char *trigger_label,
    int trigger_label_len,
    struct wolfsentry_event **event);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_event_drop_reference(
    struct wolfsentry_context *wolfsentry,
    struct wolfsentry_event *event,
    wolfsentry_action_res_t *action_results);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_event_action_prepend(
    struct wolfsentry_context *wolfsentry,
    const char *event_label,
    int event_label_len,
    const char *action_label,
    int action_label_len);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_event_action_append(
    struct wolfsentry_context *wolfsentry,
    const char *event_label,
    int event_label_len,
    const char *action_label,
    int action_label_len);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_event_action_insert_after(
    struct wolfsentry_context *wolfsentry,
    const char *event_label,
    int event_label_len,
    const char *action_label,
    int action_label_len,
    const char *point_action_label,
    int point_action_label_len);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_event_action_delete(
    struct wolfsentry_context *wolfsentry,
    const char *event_label,
    int event_label_len,
    const char *action_label,
    int action_label_len);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_event_set_subevent(
    struct wolfsentry_context *wolfsentry,
    const char *event_label,
    int event_label_len,
    wolfsentry_action_type_t subevent_type,
    const char *subevent_label,
    int subevent_label_len);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_event_action_list_start(
    struct wolfsentry_context *wolfsentry,
    const char *event_label,
    int event_label_len,
    struct wolfsentry_action_list_ent **cursor);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_event_action_list_next(
    struct wolfsentry_context *wolfsentry,
    struct wolfsentry_action_list_ent **cursor,
    const char **action_label,
    int *action_label_len);

WOLFSENTRY_API wolfsentry_hitcount_t wolfsentry_table_n_inserts(struct wolfsentry_table_header *table);

WOLFSENTRY_API wolfsentry_hitcount_t wolfsentry_table_n_deletes(struct wolfsentry_table_header *table);

typedef enum {
    WOLFSENTRY_KV_NONE = 0,
    WOLFSENTRY_KV_NULL,
    WOLFSENTRY_KV_TRUE,
    WOLFSENTRY_KV_FALSE,
    WOLFSENTRY_KV_UINT,
    WOLFSENTRY_KV_SINT,
    WOLFSENTRY_KV_FLOAT,
    WOLFSENTRY_KV_STRING,
    WOLFSENTRY_KV_BYTES
} wolfsentry_kv_type_t;

struct wolfsentry_kv_pair {
    int key_len;
    wolfsentry_kv_type_t v_type;
    union {
        uint64_t v_uint;
        int64_t v_sint;
        double v_float;
        size_t string_len;
        size_t bytes_len;
    } a;
    byte b[WOLFSENTRY_FLEXIBLE_ARRAY_SIZE]; /* the key, and for strings and bytes, the data. */
};

#ifndef WOLFSENTRY_KV_MAX_VALUE_BYTES
#define WOLFSENTRY_KV_MAX_VALUE_BYTES 256
#endif

#define WOLFSENTRY_KV_KEY_LEN(kv) ((kv)->key_len)
#define WOLFSENTRY_KV_KEY(kv) ((char *)((kv)->b))
#define WOLFSENTRY_KV_TYPE(kv) ((kv)->v_type)
#define WOLFSENTRY_KV_V_UINT(kv) ((kv)->a.v_uint)
#define WOLFSENTRY_KV_V_SINT(kv) ((kv)->a.v_sint)
#define WOLFSENTRY_KV_V_FLOAT(kv) ((kv)->a.v_float)
#define WOLFSENTRY_KV_V_STRING_LEN(kv) ((kv)->a.string_len)
#define WOLFSENTRY_KV_V_STRING(kv) ((char *)((kv)->b + (kv)->key_len + 1))
#define WOLFSENTRY_KV_V_BYTES_LEN(kv) ((kv)->a.bytes_len)
#define WOLFSENTRY_KV_V_BYTES(kv) ((kv)->b + (kv)->key_len + 1)

typedef wolfsentry_errcode_t (*wolfsentry_kv_validator_t)(
    struct wolfsentry_context *wolfsentry,
    struct wolfsentry_kv_pair *kv);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_user_value_set_validator(
    struct wolfsentry_context *wolfsentry,
    wolfsentry_kv_validator_t validator,
    wolfsentry_action_res_t *action_results);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_user_value_get_type(
    struct wolfsentry_context *wolfsentry,
    const char *key,
    int key_len,
    wolfsentry_kv_type_t *type);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_user_value_delete(
    struct wolfsentry_context *wolfsentry,
    const char *key,
    int key_len);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_user_value_store_null(
    struct wolfsentry_context *wolfsentry,
    const char *key,
    int key_len,
    int overwrite_p);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_user_value_store_bool(
    struct wolfsentry_context *wolfsentry,
    const char *key,
    int key_len,
    wolfsentry_kv_type_t value,
    int overwrite_p);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_user_value_get_bool(
    struct wolfsentry_context *wolfsentry,
    const char *key,
    int key_len,
    wolfsentry_kv_type_t *value);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_user_value_store_uint(
    struct wolfsentry_context *wolfsentry,
    const char *key,
    int key_len,
    uint64_t value,
    int overwrite_p);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_user_value_get_uint(
    struct wolfsentry_context *wolfsentry,
    const char *key,
    int key_len,
    uint64_t *value);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_user_value_store_sint(
    struct wolfsentry_context *wolfsentry,
    const char *key,
    int key_len,
    int64_t value,
    int overwrite_p);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_user_value_get_sint(
    struct wolfsentry_context *wolfsentry,
    const char *key,
    int key_len,
    int64_t *value);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_user_value_store_double(
    struct wolfsentry_context *wolfsentry,
    const char *key,
    int key_len,
    double value,
    int overwrite_p);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_user_value_get_float(
    struct wolfsentry_context *wolfsentry,
    const char *key,
    int key_len,
    double *value);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_user_value_store_string(
    struct wolfsentry_context *wolfsentry,
    const char *key,
    int key_len,
    const char *value,
    int value_len,
    int overwrite_p);

struct wolfsentry_kv_pair_internal;

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_user_value_get_string(
    struct wolfsentry_context *wolfsentry,
    const char *key,
    int key_len,
    const char **value,
    int *value_len,
    struct wolfsentry_kv_pair_internal **user_value_record);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_user_value_store_bytes(
    struct wolfsentry_context *wolfsentry,
    const char *key,
    int key_len,
    const byte *value,
    int value_len,
    int overwrite_p);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_user_value_store_bytes_base64(
    struct wolfsentry_context *wolfsentry,
    const char *key,
    int key_len,
    const char *value,
    int value_len,
    int overwrite_p);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_user_value_get_bytes(
    struct wolfsentry_context *wolfsentry,
    const char *key,
    int key_len,
    const byte **value,
    int *value_len,
    struct wolfsentry_kv_pair_internal **user_value_record);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_user_value_release_record(
    struct wolfsentry_context *wolfsentry,
    struct wolfsentry_kv_pair_internal **user_value_record);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_kv_pair_export(
    const struct wolfsentry_context *wolfsentry,
    struct wolfsentry_kv_pair_internal *kv,
    const struct wolfsentry_kv_pair **kv_exports);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_kv_type_to_string(
    wolfsentry_kv_type_t type,
    const char **out);

#ifndef WOLFSENTRY_NO_STDIO
WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_kv_render_value(
    const struct wolfsentry_kv_pair *kv,
    char *out,
    int *out_len);
#endif

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_user_values_iterate_start(
    struct wolfsentry_context *wolfsentry,
    struct wolfsentry_cursor **cursor);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_user_values_iterate_seek_to_head(
    const struct wolfsentry_context *wolfsentry,
    struct wolfsentry_cursor *cursor);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_user_values_iterate_seek_to_tail(
    const struct wolfsentry_context *wolfsentry,
    struct wolfsentry_cursor *cursor);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_user_values_iterate_current(
    struct wolfsentry_context *wolfsentry,
    struct wolfsentry_cursor *cursor,
    struct wolfsentry_kv_pair_internal **kv);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_user_values_iterate_prev(
    struct wolfsentry_context *wolfsentry,
    struct wolfsentry_cursor *cursor,
    struct wolfsentry_kv_pair_internal **kv);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_user_values_iterate_next(
    struct wolfsentry_context *wolfsentry,
    struct wolfsentry_cursor *cursor,
    struct wolfsentry_kv_pair_internal **kv);

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_user_values_iterate_end(
    struct wolfsentry_context *wolfsentry,
    struct wolfsentry_cursor **cursor);

#define WOLFSENTRY_BASE64_DECODED_BUFSPC(x) ((((x)+3)/4)*3)

WOLFSENTRY_API wolfsentry_errcode_t wolfsentry_base64_decode(
    const char *src,
    size_t src_len,
    byte *dest,
    size_t *dest_spc,
    int ignore_junk_p);

/* conditionally include wolfsentry_util.h last -- none of the above rely on it.
 */
#ifndef WOLFSENTRY_NO_UTIL_H
#include <wolfsentry/wolfsentry_util.h>
#endif

#endif /* WOLFSENTRY_H */
