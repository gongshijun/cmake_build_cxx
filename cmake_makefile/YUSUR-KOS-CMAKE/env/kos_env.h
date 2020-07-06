/*
 * @Description: Copyright(c) All rights reserved.
 * @Company: YUSUR
 * @Author: Shijun Gong
 * @Date: 2019-01-10 16:11:52
 * @LastEditTime: 2019-03-26 20:54:30
 * @LastEditors: Shijun Gong
 */
#ifndef KOS_ENV_KOS_ENV_H_
#define KOS_ENV_KOS_ENV_H_

#include <conf/kos_conf.h>

/*
	////////////////////////////////////
	// KOS GLOBAL CONFIGURATION
#if defined(KOS_DEBUG_ENABLE)
#   if defined(_MSC_VER)
#       include <intrin.h>
#       // "(void)0," is for suppressing C4127 warning in "assert(false), "asser(true)" and the like
#       define KOS_ASSERT( x ) if ( !((void)0, (x))) { __debugbreak();}
#   endif
#else
#   define KOS_ASSERT( x ) {}
#endif

#if defined (KOS_DEBUG_ENABLE) || defined (KOS_LOG_ENABLE)
#   define KOS_LOG_ENABLE
#   define KOS_LOG_CONF_FILE_PATH "@KOS_LOG_CONF_FILE_PATH@"
#endif
////////////////////////////////////////
*/

#include "third_party/easylogging++.h"

namespace kos {

/////////////////////////////////////
// KOS log system

// user modify
// open thread safe log, Define macros inside "easylogging++.h"
// #define ELPP_THREAD_SAFE
void init_el_conf();

#define KOS_COUT_INFO LOG(INFO)
#define KOS_COUT_DEBUG LOG(DEBUG)

#if defined (KOS_LOG_PRINT)

	// #include "third_party/easylogging++.h"
	// using namespace el;
	extern el::Logger* defaultLogger;

#define KOS_PRINT_INFO( X ) defaultLogger->info( X )
#define KOS_PRINT_DEBUG( X ) defaultLogger->debug( X )

#endif
//////////////////////////////////////

/////////////////////////////////////
// KOS CFD Layer Predefine
#define CFD_DATA_TAB_SIZE 29
#define CFD_RESULT_TAB_SZIE 19
#define CFD_YCC_DATA_TAB_SIZE 19
#define CFD_YCC_RESULT_TAB_SIZE 19
#define CFD_DATA_TLB_SZIE 19
#define CFD_RESULT_TLB_SIZE 19
// #define CFD_RESULT_INFO_TAB_SIZE 19

#define CFD_DATA_SEND_REPEAT_TIMES 2
#define CFD_RESULT_SEND_REPEAT_TIMES 2
#define CFD_INST_SEND_REPEAT_TIMES 2

// procompile for CFD debug
// DOL & YCC & CFD Test
#define CFD_DEBUG
#define CFD_DEBUG_ONLY

// #define CFD_MULTI_THREAD
/////////////////////////////////////

/////////////////////////////////////
// KOS YCC Layer Predefine
// hardware resource configuration

// the number of bit required for distinguishing kernel type
// In this current version, kernels' type just tow categories: kernel or fusion
#define KERNEL_TYPE_BIT_NUM 1

// number of bit required for distinguishing kernel/fusion ID
#define KERNEL_ID_BIT_NUM 10

// hardware input FIFO number
#define ALL_INFIFO_NUM 4

// hardware output FIFO number
#define ALL_OUTFIFO_NUM 4

// hardware kernel id bit number
#define KERNEL_ID_BIT 10

// kernel type: kernel or fusion
#define KERNEL_TYPE_KERNEL 0
#define KERNEL_TYPE_FUSION 1
/////////////////////////////////////

void init_kos_env(const unsigned long& row, const unsigned long& col, const unsigned int& buckets_num,
        const unsigned long long& graph_node_num = 100);
void init_kos_env_no_graph();

} // namespace KOS

#endif // KOS_ENV_KOS_ENV_H_