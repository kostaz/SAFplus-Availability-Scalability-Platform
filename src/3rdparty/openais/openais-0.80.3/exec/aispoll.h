/*
 * Copyright (c) 2003-2004 MontaVista Software, Inc.
 * Copyright (c) 2006-2007 Red Hat, Inc.
 *
 * All rights reserved.
 *
 * Author: Steven Dake (sdake@redhat.com)
 *
 * This software licensed under BSD license, the text of which follows:
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * - Neither the name of the MontaVista Software, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef POLL_H_DEFINED
#define POLL_H_DEFINED

#include <pthread.h>

typedef void * poll_timer_handle;
typedef unsigned int poll_handle;

poll_handle poll_create (
	void (*serialize_lock) (void),
	void (*serialize_unlock) (void));

int poll_destroy (poll_handle poll_handle);

int poll_dispatch_add (
	poll_handle handle,
	int fd,
	int events,
	void *data,

	int (*dispatch_fn) (poll_handle handle,
		int fd,
		int revents,
		void *data));

int poll_dispatch_modify (
	poll_handle handle,
	int fd,
	int events,

	int (*dispatch_fn) (poll_handle poll_handle,
		int fd,
		int revents,
		void *data));


int poll_dispatch_delete (
	poll_handle handle,
	int fd);

int poll_timer_add (
	poll_handle handle,
	int msec_in_future, void *data,
	void (*timer_fn) (void *data),
	poll_timer_handle *timer_handle_out);

int poll_timer_delete (
	poll_handle handle,
	poll_timer_handle timer_handle);

int poll_run (
	poll_handle handle);

int poll_stop (
	poll_handle handle);

#ifdef COMPILE_OUT
void poll_print_state (
	poll_handle handle, int fd);
#endif

#endif	/* POLL_H_DEFINED */
