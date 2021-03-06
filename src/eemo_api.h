/*
 * Copyright (c) 2010-2015 SURFnet bv
 * Copyright (c) 2015 Roland van Rijswijk-Deij
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of SURFnet bv nor the names of its contributors 
 *    may be used to endorse or promote products derived from this 
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*
 * The Extensible Ethernet Monitor (EEMO)
 * EEMO plugin API
 */

#ifndef _EEMO_API_H
#define _EEMO_API_H

#include "config.h"
#include "eemo.h"
#include "eemo_log.h"
#include "raw_handler.h"
#include "dns_handler.h"
#include "ether_handler.h"
#include "ip_handler.h"
#include "icmp_handler.h"
#include "tcp_handler.h"
#include "udp_handler.h"
#include "ip_metadata.h"

/* Function table exported by EEMO; always check version before using */
#define EEMO_EXPORT_FN_VERSION		4

/* Configuration functions need to be defined here, otherwise we get cross-referencing headers */
typedef eemo_rv (*eemo_conf_get_int_fn)(const char*, const char*, int*, int);
typedef eemo_rv (*eemo_conf_get_bool_fn)(const char*, const char*, int*, int);
typedef eemo_rv (*eemo_conf_get_string_fn)(const char*, const char*, char**, char*);
typedef eemo_rv (*eemo_conf_get_string_array_fn)(const char*, const char*, char***, int*);
typedef eemo_rv (*eemo_conf_free_string_array_fn)(char**, int);

typedef struct
{
	/* Version */
	unsigned int			fn_table_version;

	/* Logging */
	eemo_log_fn			log;

	/* Configuration */
	eemo_conf_get_int_fn		conf_get_int;
	eemo_conf_get_bool_fn		conf_get_bool;
	eemo_conf_get_string_fn		conf_get_string;
	eemo_conf_get_string_array_fn	conf_get_string_array;
	eemo_conf_free_string_array_fn	conf_free_string_array;

	/* Raw packet handler administration */
	eemo_reg_raw_handler_fn		reg_raw_handler;
	eemo_unreg_raw_handler_fn	unreg_raw_handler;
	
	/* Ethernet handler administration */
	eemo_reg_ether_handler_fn	reg_ether_handler;
	eemo_unreg_ether_handler_fn	unreg_ether_handler;

	/* IP handler administration */
	eemo_reg_ip_handler_fn		reg_ip_handler;
	eemo_unreg_ip_handler_fn	unreg_ip_handler;

	/* ICMP handler administration */
	eemo_reg_icmp_handler_fn	reg_icmp_handler;
	eemo_unreg_icmp_handler_fn	unreg_icmp_handler;

	/* TCP handler administration */
	eemo_reg_tcp_handler_fn		reg_tcp_handler;
	eemo_unreg_tcp_handler_fn	unreg_tcp_handler;

	/* UDP handler administration */
	eemo_reg_udp_handler_fn		reg_udp_handler;
	eemo_unreg_udp_handler_fn	unreg_udp_handler;

	/* DNS query handler administration */
	eemo_reg_dns_handler_fn		reg_dns_handler;
	eemo_unreg_dns_handler_fn	unreg_dns_handler;
}
eemo_export_fn_table, *eemo_export_fn_table_ptr;

/* Plugin function definitions */

/* Initialise plugin */
typedef eemo_rv (*eemo_plugin_init_fn) (eemo_export_fn_table_ptr, const char* /* conf_base_path */);

/* Uninitialise plugin */
typedef eemo_rv (*eemo_plugin_uninit_fn) (eemo_export_fn_table_ptr);

/* Retrieve description */
typedef const char* (*eemo_plugin_getdescription_fn) (void);

/* Get status */
typedef eemo_rv (*eemo_plugin_status_fn) (void);

/* Function table exported by plugins; always supply a version number */
#define EEMO_PLUGIN_FN_VERSION		1

typedef struct
{
	/* Version */
	unsigned int 			fn_table_version;

	/* Plugin functions */
	eemo_plugin_init_fn		plugin_init;
	eemo_plugin_uninit_fn		plugin_uninit;
	eemo_plugin_getdescription_fn	plugin_getdescription;
	eemo_plugin_status_fn		plugin_status;
}
eemo_plugin_fn_table, *eemo_plugin_fn_table_ptr, **eemo_plugin_fn_table_ptrptr;

/* Retrieve plugin function table; when implemented, this function should always be called eemo_plugin_get_fn_table */
typedef eemo_rv (*eemo_plugin_get_fn_table_fn) (eemo_plugin_fn_table_ptrptr);

#endif /* !_EEMO_API_H */

