#ifndef CBUFFER_H
#define CBUFFER_H

#include <stdint.h>
#include <memory.h>

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
} buffer;

void 	buffer_init( buffer* buf_p );
void 	buffer_clear( buffer* buf_p );
void 	buffer_alloc( buffer* buf_p, size_t cap );
void 	buffer_free( buffer* buf_p );
uint8_t buffer_set( buffer* buf_p, uint8_t byte_in );
uint8_t buffer_get( buffer* buf_p, uint8_t* byte_out );

#endif