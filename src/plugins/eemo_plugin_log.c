/* $Id$ */

/*
 * Copyright (c) 2010-2011 SURFnet bv
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
 * Logging
 */

#include "config.h"
#include "eemo.h"
#include "eemo_log.h"
#include "eemo_config.h"
#include <stdio.h>
#include <time.h>
#include <stdarg.h>
#include <syslog.h>
#include <stdlib.h>

/* The logging function */
eemo_log_fn eemo_exported_log = NULL;

/* Initialise logging for the plugin */
void eemo_init_plugin_log(eemo_log_fn log_fn)
{
	eemo_exported_log = log_fn;
}

/* Log something */
void eemo_log(const int log_at_level, const char* file, const int line, const char* format, ...)
{
	static char log_buf[8192];
	va_list args;

	/* Check if the logging function is available */
	if (eemo_exported_log == NULL)
	{
		return;
	}

	/* Print the log message */
	va_start(args, format);
	vsnprintf(log_buf, 8192, format, args);
	va_end(args);

	(eemo_exported_log)(log_at_level, file, line, "%s", log_buf);
}

