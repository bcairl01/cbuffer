
#include <cbuffer.h>


/// Helper Macros
#define BUFFER_SET_NEXT(buf_p,byte)		buf_p->data[buf_p->wr_idx++]=byte; ++buf_p->size
#define BUFFER_GET_NEXT(buf_p,byte)		byte=buf_p->data[buf_p->rd_idx++]; --buf_p->size 
#define BUFFER_GET_SIZE(buf_p)			(buf_p->size)
#define BUFFER_WR_IDX_WRAP(buf_p)		buf_p->wr_idx%=buf_p->capacity
#define BUFFER_RD_IDX_WRAP(buf_p)		buf_p->rd_idx%=buf_p->capacity
#define BUFFER_OVERFLOW(buf_p)			buf_p->overflow=1UL;
#define BUFFER_NO_OVERFLOW(buf_p)		buf_p->overflow=0UL;



/// @brief 	Initializes support structure
///	@param 	buf_p		pointer to buffer.
void buffer_init( cbuffer* buf_p )
{
	buf_p->rd_idx 		= 
	buf_p->wr_idx 		= 
	buf_p->capacity 	= 0UL;
	buf_p->size 		= 0UL;
	buf_p->overflow 	= 0UL;
	buf_p->data 		= NULL;
}



/// @brief 	Zeros available buffer space
///	@param 	buf_p		pointer to buffer.
void buffer_clear( cbuffer* buf_p )
{
	if(buf_p->data)
	{
		size_t idx = 0;
		for( ; idx < buf_p->capacity; idx++ )
			buf_p->data[idx]=0;
	}
}



/// @brief 	Allocates buffer space
///	@param 	buf_p		pointer to buffer.
/// @param 	cap 		buffer capacity
void buffer_alloc( cbuffer* buf_p, size_t cap )
{
	buf_p->capacity = cap;
	buf_p->data 	= (uint8_t*)malloc(cap*sizeof(uint8_t));

	buffer_clear(buf_p);
}



/// @brief 	Frees allocated buffer space
///	@param 	buf_p		pointer to buffer.
void buffer_free( cbuffer* buf_p )
{
	buf_p->capacity = 0;
	free(buf_p->data);
	buf_p->data = NULL;
}



/// @brief 	Adds single byte to the  buffer
///	@param 	buf_p		pointer to buffer.
/// @param 	byte_in 	byte to add
/// @return '1' upon success
uint8_t buffer_put( cbuffer* buf_p, uint8_t byte_in )
{
	if( BUFFER_GET_SIZE(buf_p) < buf_p->capacity )
	{
		BUFFER_SET_NEXT(buf_p,byte_in);
		BUFFER_WR_IDX_WRAP(buf_p);
		return 1UL;
	}
	BUFFER_OVERFLOW(buf_p);
	return 0UL;
}



/// @brief 	Gets single byte from the buffer
///	@param 	buf_p		pointer to buffer.
/// @param 	byte_out 	output byte
/// @return '1' upon success
uint8_t buffer_get( cbuffer* buf_p, uint8_t* byte_out )
{	
	if( BUFFER_GET_SIZE(buf_p) )
	{
		BUFFER_GET_NEXT(buf_p,*byte_out);
		BUFFER_RD_IDX_WRAP(buf_p);
		return 1UL;
	}
	return 0UL;
}