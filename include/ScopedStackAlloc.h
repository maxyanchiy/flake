#pragma once

#include <new>

#include "LinearAllocator.h"

namespace flake
{

struct SFinalizer
{
	void (*DestroyObject) (void* ptr);
	SFinalizer* m_chain{ nullptr };
};

template<typename T> void destructorCall(void* ptr)
{
	static_cast<T*>(ptr)->~T();
}

class CScopedStackAllocator
{
public:
	explicit			CScopedStackAllocator( CLinearAllocator& alloc );
					~CScopedStackAllocator();

	uint8_t* const			Allocate( const std::size_t size );

	template<typename T> T* const	NewObject()
	{
		SFinalizer* const finalizer{ (SFinalizer*) m_alloc.Allocate(sizeof(SFinalizer) + sizeof(T)) };
		T* const object{ new (finalizer + sizeof(SFinalizer)) T() };
		finalizer->DestroyObject = &destructorCall<T>;
		finalizer->m_chain = m_finalizerChain;
		m_finalizerChain = finalizer;
		return object;
	}

	template<typename T> T* const	NewPOD()
	{
		T* const pod{ new ( m_alloc.Allocate( sizeof( T ) ) ) T() };
		return pod;
	}

private:
	CLinearAllocator&	m_alloc;
	SFinalizer*		m_finalizerChain;
	void*			m_rewindPoint{ nullptr };
};

}// namespace flake
