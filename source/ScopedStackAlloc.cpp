#include "ScopedStackAlloc.h"

namespace flake
{

CScopedStackAllocator::CScopedStackAllocator(CLinearAllocator& alloc) : m_alloc(alloc)
{}

CScopedStackAllocator::~CScopedStackAllocator()
{
	SFinalizer* next{ m_finalizerChain };
	while (next)
	{
		next->DestroyObject( ( void* )( next + sizeof( SFinalizer ) ) );
		next = m_finalizerChain->m_chain;
	}
}

uint8_t* const CScopedStackAllocator::Allocate( const std::size_t size )
{
	return m_alloc.Allocate(size);
}

}// namespace flake
