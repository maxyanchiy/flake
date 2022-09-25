#pragma once

#include <cstdint>
#include <cstdlib>

namespace flake
{

class CLinearAllocator
{
public:
	explicit		CLinearAllocator( const std::size_t m_allocationSize );
					~CLinearAllocator();

	uint8_t* const	Allocate( const std::size_t size );
	void			Rewind( uint8_t* const ptr );

private:
	uint8_t*	m_memBlock{ nullptr };
	std::size_t m_allocationSize{ 0 };
	std::size_t m_memAvailable{ 0 };
};

}// namespace flake