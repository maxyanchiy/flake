#include "LinearAllocator.h"

namespace flake
{

CLinearAllocator::CLinearAllocator(const std::size_t m_allocationSize) : 
	m_memBlock{ static_cast<uint8_t*>( std::malloc( m_allocationSize ) ) }
{
	if (!m_memBlock)
	{
		// assert
	}
	m_memAvailable = m_allocationSize;
}

CLinearAllocator::~CLinearAllocator()
{
	if (m_memBlock)
	{
		std::free(m_memBlock);
		m_memBlock = nullptr;
	}
}

uint8_t* const CLinearAllocator::Allocate(const std::size_t size)
{
	if (size > m_memAvailable)
	{
		// assert
		return nullptr;
	}
	m_memAvailable -= size;
	return m_memBlock += size;
}

void CLinearAllocator::Rewind(uint8_t* const ptr)
{
	if (m_memBlock)
	{
		std::free(m_memBlock);
	}
	m_memBlock = ptr;
}

}// namespace flake