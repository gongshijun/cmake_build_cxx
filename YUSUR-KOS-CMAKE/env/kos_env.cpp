/*
 * @Description: Copyright(c) All rights reserved.
 * @Company: YUSUR
 * @Author: Shijun Gong
 * @Date: 2019-01-10 16:13:59
 * @LastEditTime: 2019-03-26 20:56:22
 * @LastEditors: Shijun Gong
 */
#include "kos_env.h"

#include "conf/kos_conf.h"

 // create global easylogging class
INITIALIZE_EASYLOGGINGPP

namespace kos 
{ 

	void init_el_conf()
	{
    	// Load configuration from file
    	el::Configurations conf(KOS_LOG_CONF_FILE_PATH);
    	// Reconfigure single logger
    	el::Loggers::reconfigureLogger("default", conf);
    	// Actually reconfigure all loggers instead
    	el::Loggers::reconfigureAllLoggers(conf);
    	// Now all the loggers will use configuration from file
	}

	#if defined KOS_LOG_PRINT
	el::Logger* defaultLogger = el::Loggers::getLogger("default");
	#endif

	// std::shared_ptr<DataMaster> data_master = nullptr;
	// std::shared_ptr<Graph> graph = nullptr;
	void init_kos_env(const unsigned long& row, const unsigned long& col, const unsigned int& buckets_num, 
		const unsigned long long& graph_node_num)
	{
		init_el_conf();
		// data_master = std::shared_ptr<DataMaster>(new DataMaster(row, col, buckets_num));
		// graph = std::shared_ptr<Graph>(new Graph(graph_node_num));
	}

	void init_kos_env_no_graph()
	{
		init_el_conf();
	}
} // namespace KOS