#ifndef CBUFFER_H
#define CBUFFER_H

#include <stdlib.h>
#include <stdint.h>

/// @brief 	Generic Ring-Buffer Structure
/// @var 	capacity 		size of allocated buffer space
/// @var	rd_idx			next slot in buffer to read from
/// @var	wr_idx			next slot in buffer to write to
/// @var	size			number of unread bytes in buffer
/// @var	data			buffer stack space
/// @var	overflow		buffer-overflow flag
typedef struct 
{
	uint16_t				capacity;
	uint16_t				rd_idx;
	uint16_t				wr_idx;
	uint16_t 				size;
	uint8_t*				data;
	uint8_t					overflow;
} cbuffer;

#define BUFFER_OK(buf_p) 	(buf_p && buf_p->data && buf_p->cap && !buf_p->overflow)

void 	buffer_init( cbuffer* buf_p );
void 	buffer_clear( cbuffer* buf_p );
void 	buffer_alloc( cbuffer* buf_p, size_t cap );
void 	buffer_free( cbuffer* buf_p );
uint8_t buffer_put( cbuffer* buf_p, uint8_t byte_in );
uint8_t buffer_get( cbuffer* buf_p, uint8_t* byte_out );

#endif